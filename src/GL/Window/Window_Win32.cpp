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

#include <GL/Window/Window.hpp>

#ifdef OOGL_PLATFORM_WINDOWS

namespace GL
{
	Window::Window( uint width, uint height, const std::string& title, WindowStyle::window_style_t style )
	{
		// Create class for OpenGL window
		WNDCLASS wc = { 0 };
		wc.lpfnWndProc = WindowEventHandler;
		wc.hInstance = GetModuleHandle( NULL );
		wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
		wc.hCursor = LoadCursor( NULL, IDC_ARROW );
		wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
		wc.lpszClassName = "OOGL_WINDOW";
		wc.style = CS_OWNDC;
		RegisterClass( &wc );
		
		// Configure window style
		ulong windowStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE;
		if ( style & WindowStyle::Close ) windowStyle |= WS_SYSMENU;
		if ( style & WindowStyle::Resize ) windowStyle |= WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX;

		int x = 0;
		int y = 0;

		if ( !( style & WindowStyle::Fullscreen ) )
		{
			// Calculate window size for requested client size
			RECT rect = { 0, 0, width, height };
			AdjustWindowRect( &rect, windowStyle, false );
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;

			// Center window on screen
			GetClientRect( GetDesktopWindow(), &rect );
			x = ( rect.right - rect.left - width ) / 2;
			y = ( rect.bottom - rect.top - height ) / 2;
		}

		// Create window
		HWND window = CreateWindow( "OOGL_WINDOW", title.c_str(), windowStyle, x, y, width, height, NULL, NULL, GetModuleHandle( NULL ), this );

		// Initialize fullscreen mode
		if ( style & WindowStyle::Fullscreen )
		{
			DEVMODE dm;
			dm.dmSize = sizeof( dm );
			dm.dmPelsWidth = width;
			dm.dmPelsHeight = height;
			dm.dmBitsPerPel = 32;
			dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

			ChangeDisplaySettings( &dm, CDS_FULLSCREEN );

			SetWindowLong( window, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
			SetWindowLong( window, GWL_EXSTYLE, WS_EX_APPWINDOW );

			SetWindowPos( window, HWND_TOP, 0, 0, width, height, SWP_FRAMECHANGED );
			ShowWindow( window, SW_SHOW );
		}

		// Initialize window properties
		RECT rect;
		GetWindowRect( window, &rect );

		this->x = rect.left;
		this->y = rect.top;

		GetClientRect( window, &rect );

		this->width = rect.right - rect.left;
		this->height = rect.bottom - rect.top;
		this->open = true;
		this->style = windowStyle;
		this->mousex = 0;
		this->mousey = 0;
		memset( this->mouse, 0, sizeof( this->mouse ) );
		memset( this->keys, 0, sizeof( this->keys ) );
		this->context = 0;
	}

	Window::~Window()
	{
		if ( context ) delete context;

		DestroyWindow( window );

		UnregisterClass( "OGLWINDOW", GetModuleHandle( NULL ) );
	}

	void Window::SetPos( int x, int y )
	{
		if ( !open ) return;
		SetWindowPos( window, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
	}

	void Window::SetSize( uint width, uint height )
	{
		if ( !open ) return;
		RECT rect = { 0, 0, width, height };
		AdjustWindowRect( &rect, style, false );
		SetWindowPos( window, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER );
	}

	void Window::SetTitle( const std::string& title )
	{
		if ( !open ) return;
		SetWindowText( window, title.c_str() );
	}

	void Window::SetVisible( bool visible )
	{
		if ( !open ) return;
		ShowWindow( window, visible ? SW_SHOW : SW_HIDE );
	}

	void Window::Close()
	{
		CloseWindow( window );
		open = false;
	}

	bool Window::GetEvent( Event& ev )
	{
		// Fetch new events
		MSG msg;
		while ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		// Return oldest event - if available
		if ( events.empty() ) return false;
		
		ev = events.front();
		events.pop();

		return true;
	}

	Context& Window::GetContext( uchar color, uchar depth, uchar stencil, uchar antialias )
	{
		if ( context )
			return *context;
		else
			return *( context = new Context( color, depth, stencil, antialias, GetDC( window ) ) );
	}

	void Window::Present()
	{
		if ( !context ) return;
		context->Activate();
		SwapBuffers( GetDC( window ) );
	}

	LRESULT Window::WindowEvent( UINT msg, WPARAM wParam, LPARAM lParam )
	{
		Event ev;
		ev.Type = Event::Unknown;

		// Translate message to Event
		switch ( msg )
		{
		case WM_CLOSE:
			Close();
			ev.Type = Event::Close;
			break;

		case WM_SIZE:
			width = GET_X_LPARAM( lParam );
			height = GET_Y_LPARAM( lParam );

			if ( events.empty() ) {
				ev.Type = Event::Resize;
				ev.Window.Width = width;
				ev.Window.Height = height;
			} else if ( events.back().Type == Event::Resize ) {
				events.back().Window.Width = width;
				events.back().Window.Height = height;
			}
			break;

		case WM_MOVE:
			RECT rect;
			GetWindowRect( window, &rect );
			x = rect.left;
			y = rect.top;

			if ( events.empty() ) {
				ev.Type = Event::Move;
				ev.Window.X = x;
				ev.Window.Y = y;
			} else if ( events.back().Type == Event::Move ) {
				events.back().Window.X = x;
				events.back().Window.Y = y;
			}
			break;

		case WM_ACTIVATE:
			if ( wParam == WA_INACTIVE ) {
				ev.Type = Event::Blur;
				focus = false;
			} else {
				ev.Type = Event::Focus;
				focus = true;
			}
			break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			ev.Type = Event::KeyDown;
			ev.Key.Code = TranslateKey( wParam );
			ev.Key.Alt = HIWORD( GetAsyncKeyState( VK_MENU ) ) != 0;
			ev.Key.Control = HIWORD( GetAsyncKeyState( VK_CONTROL ) ) != 0;
			ev.Key.Shift = HIWORD( GetAsyncKeyState( VK_SHIFT ) ) != 0;

			keys[ev.Key.Code] = true;
			break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
			ev.Type = Event::KeyUp;
			ev.Key.Code = TranslateKey( wParam );
			ev.Key.Alt = HIWORD( GetAsyncKeyState( VK_MENU ) ) != 0;
			ev.Key.Control = HIWORD( GetAsyncKeyState( VK_CONTROL ) ) != 0;
			ev.Key.Shift = HIWORD( GetAsyncKeyState( VK_SHIFT ) ) != 0;

			keys[ev.Key.Code] = false;
			break;

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			mousex = GET_X_LPARAM( lParam );
			mousey = GET_Y_LPARAM( lParam );

			if ( msg == WM_LBUTTONDOWN ) ev.Mouse.Button = MouseButton::Left;
			else if ( msg == WM_RBUTTONDOWN ) ev.Mouse.Button = MouseButton::Right;
			else if ( msg == WM_MBUTTONDOWN ) ev.Mouse.Button = MouseButton::Middle;
			else break;

			ev.Type = Event::MouseDown;
			ev.Mouse.X = mousex;
			ev.Mouse.Y = mousey;

			mouse[ev.Mouse.Button] = true;
			break;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			mousex = GET_X_LPARAM( lParam );
			mousey = GET_Y_LPARAM( lParam );

			if ( msg == WM_LBUTTONUP ) ev.Mouse.Button = MouseButton::Left;
			else if ( msg == WM_RBUTTONUP ) ev.Mouse.Button = MouseButton::Right;
			else if ( msg == WM_MBUTTONUP ) ev.Mouse.Button = MouseButton::Middle;
			else break;

			ev.Type = Event::MouseUp;
			ev.Mouse.X = mousex;
			ev.Mouse.Y = mousey;

			mouse[ev.Mouse.Button] = false;
			break;

		case WM_MOUSEWHEEL:
			mousex = GET_X_LPARAM( lParam );
			mousey = GET_Y_LPARAM( lParam );

			ev.Type = Event::MouseWheel;
			ev.Mouse.Delta = GET_WHEEL_DELTA_WPARAM( wParam ) > 0 ? 1 : -1;
			ev.Mouse.X = mousex;
			ev.Mouse.Y = mousey;
			break;

		case WM_MOUSEMOVE:
			mousex = GET_X_LPARAM( lParam );
			mousey = GET_Y_LPARAM( lParam );

			ev.Type = Event::MouseMove;
			ev.Mouse.X = mousex;
			ev.Mouse.Y = mousey;
			break;

		default:
			return DefWindowProc( window, msg, wParam, lParam );
		}

		// Add event to internal queue
		if ( ev.Type != Event::Unknown )
			events.push( ev );

		return 0;
	}

	LRESULT CALLBACK Window::WindowEventHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		Window* window;

		if ( msg == WM_NCCREATE )
		{
			// Store pointer to associated Window class as userdata in Win32 window
			window = reinterpret_cast<Window*>( ( (LPCREATESTRUCT)lParam )->lpCreateParams );
			window->window = hwnd;

			SetWindowLong( hwnd, GWL_USERDATA, reinterpret_cast<long>( window ) );

			return DefWindowProc( hwnd, msg, wParam, lParam );
		} else {
			window = reinterpret_cast<Window*>( GetWindowLong( hwnd, GWL_USERDATA ) );
		
			if( window != nullptr )
				return window->WindowEvent( msg, wParam, lParam );
			else
				return DefWindowProc( hwnd, msg, wParam, lParam );
		}
	}

	Key::key_t Window::TranslateKey( uint code )
	{
		switch ( code )
		{
		case VK_SHIFT: return Key::Shift;
		case VK_MENU: return Key::Alt;
		case VK_CONTROL: return Key::Control;
		case VK_OEM_1: return Key::Semicolon;
		case VK_OEM_2: return Key::Slash;
		case VK_OEM_PLUS: return Key::Equals;
		case VK_OEM_MINUS: return Key::Hyphen;
		case VK_OEM_4: return Key::LeftBracket;
		case VK_OEM_6: return Key::RightBracket;
		case VK_OEM_COMMA: return Key::Comma;
		case VK_OEM_PERIOD: return Key::Period;
		case VK_OEM_7: return Key::Quote;
		case VK_OEM_5: return Key::Backslash;
		case VK_OEM_3: return Key::Tilde;
		case VK_ESCAPE: return Key::Escape;
		case VK_SPACE: return Key::Space;
		case VK_RETURN: return Key::Enter;
		case VK_BACK: return Key::Backspace;
		case VK_TAB: return Key::Tab;
		case VK_PRIOR: return Key::PageUp;
		case VK_NEXT: return Key::PageDown;
		case VK_END: return Key::End;
		case VK_HOME: return Key::Home;
		case VK_INSERT: return Key::Insert;
		case VK_DELETE: return Key::Delete;
		case VK_ADD: return Key::Add;
		case VK_SUBTRACT: return Key::Subtract;
		case VK_MULTIPLY: return Key::Multiply;
		case VK_DIVIDE: return Key::Divide;
		case VK_PAUSE: return Key::Pause;
		case VK_LEFT: return Key::Left;
		case VK_RIGHT: return Key::Right;
		case VK_UP: return Key::Up;
		case VK_DOWN: return Key::Down;

		default:
			if ( code >= VK_F1 && code <= VK_F12 )
				return (Key::key_t)( Key::F1 + code - VK_F1 );
			else if ( code >= VK_NUMPAD0 && code <= VK_NUMPAD9 )
				return (Key::key_t)( Key::Numpad0 + code - VK_NUMPAD0 );
			else if ( code >= 'A' && code <= 'Z' )
				return (Key::key_t)( Key::A + code - 'A' );
			else if ( code >= '0' && code <= '9' )
				return (Key::key_t)( Key::Num0 + code - '0' );
		}

		return Key::Unknown;
	}
}

#endif