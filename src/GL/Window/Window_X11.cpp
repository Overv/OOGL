/*
	Copyright (C) 2012 Alexander Overvoorde

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

// The X11 implementation of the window class is heavily inspired by the implementation in SFML 2.
// A huge thanks goes to Laurent Gomila for developing that code.

#include <GL/Window/Window.hpp>

#ifdef OOGL_PLATFORM_LINUX

#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/Xrandr.h>

namespace GL
{
	Window::Window( uint width, uint height, const std::string& title, WindowStyle::window_style_t style )
	{
		// Connect to X server
		display = XOpenDisplay( NULL );
		screen = DefaultScreen( display );

		// Configure window style
		fullscreen = style & WindowStyle::Fullscreen;

		XSetWindowAttributes attributes;
		attributes.event_mask = FocusChangeMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask | EnterWindowMask | LeaveWindowMask;
		attributes.override_redirect = fullscreen;

		int x, y;
		if ( fullscreen ) {
			x = 0;
			y = 0;

			EnableFullscreen( true, width, height );
		} else {
			x = ( DisplayWidth( display, screen ) - width ) / 2;
			y = ( DisplayHeight( display, screen ) - height ) / 2;
		}

		// Create window on server
		::Window desktop = RootWindow( display, screen );
		int depth = DefaultDepth( display, screen );

		window = XCreateWindow( display, desktop, x, y, width, height, 0, depth, InputOutput, DefaultVisual( display, screen ), CWEventMask | CWOverrideRedirect, &attributes );
		XStoreName( display, window, title.c_str() );

		// Window style
		if ( !fullscreen )
		{
			Atom windowHints = XInternAtom( display, "_MOTIF_WM_HINTS", false );

			// These are extensions, so they'll have to be manually defined
			struct WMHints
			{
				unsigned long Flags;
				unsigned long Functions;
				unsigned long Decorations;
				long InputMode;
				unsigned long State;
			};

			static const unsigned long MWM_HINTS_FUNCTIONS = 1 << 0;
			static const unsigned long MWM_HINTS_DECORATIONS = 1 << 1;
			static const unsigned long MWM_DECOR_BORDER = 1 << 1;
			static const unsigned long MWM_DECOR_RESIZEH = 1 << 2;
			static const unsigned long MWM_DECOR_TITLE = 1 << 3;
			static const unsigned long MWM_DECOR_MENU = 1 << 4;
			static const unsigned long MWM_DECOR_MINIMIZE = 1 << 5;
			static const unsigned long MWM_DECOR_MAXIMIZE = 1 << 6;
			static const unsigned long MWM_FUNC_RESIZE = 1 << 1;
			static const unsigned long MWM_FUNC_MOVE = 1 << 2;
			static const unsigned long MWM_FUNC_MINIMIZE = 1 << 3;
			static const unsigned long MWM_FUNC_MAXIMIZE = 1 << 4;
			static const unsigned long MWM_FUNC_CLOSE = 1 << 5;

			WMHints hints;
			hints.Flags = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
			hints.Decorations = MWM_DECOR_BORDER | MWM_DECOR_TITLE | MWM_DECOR_MINIMIZE | MWM_DECOR_MENU;
			hints.Functions = MWM_FUNC_MOVE | MWM_FUNC_MINIMIZE;

			if ( ( style & WindowStyle::Close ) || ( style & WindowStyle::Resize ) ) {
				hints.Functions |= MWM_FUNC_CLOSE;
			}
			if ( style & WindowStyle::Resize ) {
				hints.Decorations |= MWM_DECOR_MAXIMIZE | MWM_DECOR_RESIZEH;
				hints.Functions |= MWM_FUNC_MAXIMIZE | MWM_FUNC_RESIZE;
			}

			const unsigned char* ptr = reinterpret_cast<const unsigned char*>( &hints );
			XChangeProperty( display, window, windowHints, windowHints, 32, PropModeReplace, ptr, 5 );
		}

		// Add input handler for close button
		close = XInternAtom( display, "WM_DELETE_WINDOW", false );
		XSetWMProtocols( display, window, &close, 1 );

		// Show window
		XMapWindow( display, window );
		XFlush( display );

		// Handle fullscreen input
		if ( fullscreen )
		{
			XGrabPointer( display, window, true, 0, GrabModeAsync, GrabModeAsync, window, None, CurrentTime );
			XGrabKeyboard( display, window, true, GrabModeAsync, GrabModeAsync, CurrentTime );
		}

		// Initialize window properties
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->open = true;
		this->mousex = 0;
		this->mousey = 0;
		memset( this->mouse, 0, sizeof( this->mouse ) );
		memset( this->keys, 0, sizeof( this->keys ) );
		this->context = 0;
	}

	Window::~Window()
	{
		if ( !open ) return;

		if ( context ) delete context;

		Close();
	}

	void Window::SetPos( int x, int y )
	{
		if ( !open ) return;
		XMoveWindow( display, window, x, y );
    	XFlush( display );
	}

	void Window::SetSize( uint width, uint height )
	{
		if ( !open ) return;
		XResizeWindow( display, window, width, height );
    	XFlush( display );
	}

	void Window::SetTitle( const std::string& title )
	{
		if ( !open ) return;
		XStoreName( display, window, title.c_str() );
	}

	void Window::SetVisible( bool visible )
	{
		if ( !open ) return;
		
		if ( visible )
        	XMapWindow( display, window );
    	else
        	XUnmapWindow( display, window );

    	XFlush( display );
	}

	void Window::Close()
	{
		XDestroyWindow( display, window );
		XFlush( display );
		
		if ( fullscreen ) EnableFullscreen( false );

		XCloseDisplay( display );

		open = false;
	}

	bool Window::GetEvent( Event& ev )
	{
		// Fetch new events
		XEvent event;
		while ( XCheckIfEvent( display, &event, &CheckEvent, reinterpret_cast<XPointer>( window ) ) )
		{
			WindowEvent( event );
		}

		// Return oldest event - if available
		if ( events.empty() ) return false;
		
		ev = events.front();
		events.pop();

		return true;
	}

	void Window::EnableFullscreen( bool enabled, int width, int height )
	{
		if ( enabled )
		{
			XRRScreenConfiguration* config = XRRGetScreenInfo( display, RootWindow( display, screen ) );

			Rotation currentRotation;
            oldVideoMode = XRRConfigCurrentConfiguration( config, &currentRotation );

			int nbSizes;
			XRRScreenSize* sizes = XRRConfigSizes( config, &nbSizes );
			for ( int i = 0; i < nbSizes; i++ )
			{
				if ( sizes[i].width == width && sizes[i].height == height )
				{
					XRRSetScreenConfig( display, config, RootWindow( display, screen ), i, currentRotation, CurrentTime );
					break;
				}
			}

			XRRFreeScreenConfigInfo( config );
		} else {
			XRRScreenConfiguration* config = XRRGetScreenInfo( display, RootWindow( display, screen ) );
			Rotation currentRotation;
			XRRConfigCurrentConfiguration( config, &currentRotation );
			XRRSetScreenConfig( display, config, RootWindow( display, screen ), oldVideoMode, currentRotation, CurrentTime );
			XRRFreeScreenConfigInfo( config );
		}
	}

	Context& Window::GetContext( uchar color, uchar depth, uchar stencil, uchar antialias )
	{
		if ( context )
			return *context;
		else
			return *( context = new Context( color, depth, stencil, antialias, display, screen, window ) );
	}

	void Window::Present()
	{
		if ( !context ) return;
		context->Activate();
		glXSwapBuffers( display, window );
	}

	void Window::WindowEvent( const XEvent& event )
	{
		Event ev;
		ev.Type = Event::Unknown;

		// Translate XEvent to Event
		uint button = 0;
		char buffer[32];
		KeySym symbol;

		switch ( event.type )
		{
			case ClientMessage:
				if ( ( event.xclient.format == 32 ) && ( event.xclient.data.l[0] ) == static_cast<long>( close ) )
				{
					if ( fullscreen ) EnableFullscreen( false );
					open = false;
					ev.Type = Event::Close;
				}
				break;

			case ConfigureNotify:
				if ( (uint)event.xconfigure.width != width || (uint)event.xconfigure.height != height )
				{
					width = event.xconfigure.width;
					height = event.xconfigure.height;

					if ( events.empty() ) {
						ev.Type = Event::Resize;
						ev.Window.Width = width;
						ev.Window.Height = height;
					} else if ( events.back().Type == Event::Resize ) {
						events.back().Window.Width = width;
						events.back().Window.Height = height;
					}
				} else if ( event.xconfigure.x != x || event.xconfigure.y != y ) {
					x = event.xconfigure.x;
					y = event.xconfigure.y;

					if ( events.empty() ) {
						ev.Type = Event::Move;
						ev.Window.X = x;
						ev.Window.Y = y;
					} else if ( events.back().Type == Event::Move ) {
						events.back().Window.X = x;
						events.back().Window.Y = y;
					}
				}
				break;

			case FocusIn:
				ev.Type = Event::Focus;
				focus = true;
				break;

			case FocusOut:
				ev.Type = Event::Blur;
				focus = false;
				break;

			case KeyPress:
				static XComposeStatus keyboard;
            	XLookupString( const_cast<XKeyEvent*>( &event.xkey ), buffer, sizeof( buffer ), &symbol, &keyboard );

				ev.Type = Event::KeyDown;
				ev.Key.Code = TranslateKey( symbol );
				ev.Key.Alt = event.xkey.state & Mod1Mask;
				ev.Key.Control = event.xkey.state & ControlMask;
				ev.Key.Shift = event.xkey.state & ShiftMask;

				keys[ev.Key.Code] = true;
				break;

			case KeyRelease:
				XLookupString( const_cast<XKeyEvent*>( &event.xkey ), buffer, sizeof( buffer ), &symbol, &keyboard );

				ev.Type = Event::KeyUp;
				ev.Key.Code = TranslateKey( symbol );
				ev.Key.Alt = event.xkey.state & Mod1Mask;
				ev.Key.Control = event.xkey.state & ControlMask;
				ev.Key.Shift = event.xkey.state & ShiftMask;

				keys[ev.Key.Code] = false;
				break;

			case ButtonPress:
				button = event.xbutton.button;

				if ( button == Button1 || button == Button2 || button == Button3 )
				{
					mousex = event.xbutton.x;
					mousey = event.xbutton.y;

					ev.Type = Event::MouseDown;
					ev.Mouse.X = mousex;
					ev.Mouse.Y = mousey;

					if ( button == Button1 ) ev.Mouse.Button = MouseButton::Left;
					else if ( button == Button2 ) ev.Mouse.Button = MouseButton::Middle;
					else if ( button == Button3 ) ev.Mouse.Button = MouseButton::Right;
				}
				break;

			case ButtonRelease:
				button = event.xbutton.button;

				if ( button == Button1 || button == Button2 || button == Button3 )
				{
					mousex = event.xbutton.x;
					mousey = event.xbutton.y;

					ev.Type = Event::MouseUp;
					ev.Mouse.X = mousex;
					ev.Mouse.Y = mousey;

					if ( button == Button1 ) ev.Mouse.Button = MouseButton::Left;
					else if ( button == Button2 ) ev.Mouse.Button = MouseButton::Middle;
					else if ( button == Button3 ) ev.Mouse.Button = MouseButton::Right;
				} else if ( button == Button4 || button == Button5 ) {
					mousex = event.xbutton.x;
					mousey = event.xbutton.y;

					ev.Type = Event::MouseWheel;
					ev.Mouse.Delta = button == Button4 ? 1 : -1;;
					ev.Mouse.X = mousex;
					ev.Mouse.Y = mousey;
				}
				break;

			case MotionNotify:
				mousex = event.xmotion.x;
				mousey = event.xmotion.y;

				ev.Type = Event::MouseMove;
				ev.Mouse.X = mousex;
				ev.Mouse.Y = mousey;
				break;
		}

		// Add event to internal queue
		if ( ev.Type != Event::Unknown )
			events.push( ev );
	}

	Bool Window::CheckEvent( Display*, XEvent* event, XPointer userData )
	{
		return event->xany.window == reinterpret_cast< ::Window >( userData );
	}

	Key::key_t Window::TranslateKey( uint code )
	{
		if ( code >= 'a' && code <= 'z' ) code -= 'a' - 'A';

		switch ( code )
		{
		case XK_Shift_L: return Key::Shift;
		case XK_Shift_R: return Key::Shift;
		case XK_Alt_L: return Key::Alt;
		case XK_Alt_R: return Key::Alt;
		case XK_Control_L: return Key::Control;
		case XK_Control_R: return Key::Control;
		case XK_semicolon: return Key::Semicolon;
		case XK_slash: return Key::Slash;
		case XK_equal: return Key::Equals;
		case XK_minus: return Key::Hyphen;
		case XK_bracketleft: return Key::LeftBracket;
		case XK_bracketright: return Key::RightBracket;
		case XK_comma: return Key::Comma;
		case XK_period: return Key::Period;
		case XK_dead_acute: return Key::Quote;
		case XK_backslash: return Key::Backslash;
		case XK_dead_grave: return Key::Tilde;
		case XK_Escape: return Key::Escape;
		case XK_space: return Key::Space;
		case XK_Return: return Key::Enter;
		case XK_KP_Enter: return Key::Enter;
		case XK_BackSpace: return Key::Backspace;
		case XK_Tab: return Key::Tab;
		case XK_Prior: return Key::PageUp;
		case XK_Next: return Key::PageDown;
		case XK_End: return Key::End;
		case XK_Home: return Key::Home;
		case XK_Insert: return Key::Insert;
		case XK_Delete: return Key::Delete;
		case XK_KP_Add: return Key::Add;
		case XK_KP_Subtract: return Key::Subtract;
		case XK_KP_Multiply: return Key::Multiply;
		case XK_KP_Divide: return Key::Divide;
		case XK_Pause: return Key::Pause;
		case XK_Left: return Key::Left;
		case XK_Right: return Key::Right;
		case XK_Up: return Key::Up;
		case XK_Down: return Key::Down;

		default:
			if ( code >= XK_F1 && code <= XK_F12 )
				return (Key::key_t)( Key::F1 + code - XK_F1 );
			else if ( code >= XK_KP_0 && code <= XK_KP_9 )
				return (Key::key_t)( Key::Numpad0 + code - XK_KP_0 );
			else if ( code >= 'A' && code <= 'Z' )
				return (Key::key_t)( Key::A + code - 'A' );
			else if ( code >= '0' && code <= '9' )
				return (Key::key_t)( Key::Num0 + code - '0' );
		}

		return Key::Unknown;
	}
}

#endif