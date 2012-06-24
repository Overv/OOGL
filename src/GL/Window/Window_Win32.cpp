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
	Window::Window( uint width, uint height, const std::string& title, uint style )
	{
		WNDCLASS wc = { 0 };
		wc.lpfnWndProc = WindowEventHandler;
		wc.hInstance = GetModuleHandle( NULL );
		wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
		wc.hCursor = LoadCursor( NULL, IDC_ARROW );
		wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
		wc.lpszClassName = "OGLWINDOW";
		RegisterClass( &wc );
		
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
		HWND window = CreateWindow( "OGLWINDOW", title.c_str(), windowStyle, x, y, width, height, NULL, NULL, GetModuleHandle( NULL ), this );

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

		// Retrieve final window size
		RECT rect;
		GetClientRect( window, &rect );

		this->width = rect.right - rect.left;
		this->height = rect.bottom - rect.top;
		this->open = true;
		this->style = windowStyle;
	}

	Window::~Window()
	{
		if ( !open ) return;
		
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
		DestroyWindow( window );
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

	LRESULT Window::WindowEvent( UINT msg, WPARAM wParam, LPARAM lParam )
	{
		Event ev;
		ev.Type = 0;

		// Translate message to Event
		switch ( msg )
		{
		case WM_CLOSE:
			open = false;
			DestroyWindow( window );

			ev.Type = Event::Close;
			break;

		case WM_SIZE:
			if ( events.empty() ) {
				ev.Type = Event::Resize;
				ev.Window.Width = GET_X_LPARAM( lParam );
				ev.Window.Height = GET_Y_LPARAM( lParam );
			} else if ( events.back().Type == Event::Resize ) {
				events.back().Window.Width = GET_X_LPARAM( lParam );
				events.back().Window.Height = GET_Y_LPARAM( lParam );
			}
			break;

		case WM_MOVE:
			if ( events.empty() ) {
				ev.Type = Event::Move;
				ev.Window.X = GET_X_LPARAM( lParam );
				ev.Window.Y = GET_Y_LPARAM( lParam );
			} else if ( events.back().Type == Event::Move ) {
				events.back().Window.X = GET_X_LPARAM( lParam );
				events.back().Window.Y = GET_Y_LPARAM( lParam );
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
			ev.Key.Code = wParam;
			ev.Key.Alt = HIWORD( GetAsyncKeyState( VK_MENU ) ) != 0;
			ev.Key.Control = HIWORD( GetAsyncKeyState( VK_CONTROL ) ) != 0;
			ev.Key.Shift = HIWORD( GetAsyncKeyState( VK_SHIFT ) ) != 0;
			break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
			ev.Type = Event::KeyUp;
			ev.Key.Code = wParam;
			ev.Key.Alt = HIWORD( GetAsyncKeyState( VK_MENU ) ) != 0;
			ev.Key.Control = HIWORD( GetAsyncKeyState( VK_CONTROL ) ) != 0;
			ev.Key.Shift = HIWORD( GetAsyncKeyState( VK_SHIFT ) ) != 0;
			break;

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			if ( msg == WM_LBUTTONDOWN ) ev.Mouse.Button = MouseButton::Left;
			else if ( msg == WM_RBUTTONDOWN ) ev.Mouse.Button = MouseButton::Right;
			else if ( msg == WM_MBUTTONDOWN ) ev.Mouse.Button = MouseButton::Middle;

			ev.Type = Event::MouseDown;
			ev.Mouse.X = GET_X_LPARAM( lParam );
			ev.Mouse.Y = GET_Y_LPARAM( lParam );
			break;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			if ( msg == WM_LBUTTONUP ) ev.Mouse.Button = MouseButton::Left;
			else if ( msg == WM_LBUTTONUP ) ev.Mouse.Button = MouseButton::Right;
			else if ( msg == WM_LBUTTONUP ) ev.Mouse.Button = MouseButton::Middle;

			ev.Type = Event::MouseUp;
			ev.Mouse.X = GET_X_LPARAM( lParam );
			ev.Mouse.Y = GET_Y_LPARAM( lParam );
			break;

		case WM_MOUSEWHEEL:
			ev.Type = Event::MouseWheel;
			ev.Mouse.Delta = GET_WHEEL_DELTA_WPARAM( wParam );
			ev.Mouse.X = GET_X_LPARAM( lParam );
			ev.Mouse.Y = GET_Y_LPARAM( lParam );
			break;

		case WM_MOUSEMOVE:
			ev.Type = Event::MouseMove;
			ev.Mouse.X = GET_X_LPARAM( lParam );
			ev.Mouse.Y = GET_Y_LPARAM( lParam );
			break;

		default:
			return DefWindowProc( window, msg, wParam, lParam );
		}

		// Add event to internal queue
		if ( ev.Type != 0 )
			events.push( ev );

		return 0;
	}

	LRESULT CALLBACK Window::WindowEventHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		Window* window;

		if ( msg == WM_NCCREATE )
		{
			window = reinterpret_cast<Window*>( ((LPCREATESTRUCT)lParam)->lpCreateParams );
			window->window = hwnd;

			SetWindowLong( hwnd, GWL_USERDATA, reinterpret_cast<long>( window ) );

			return DefWindowProc( hwnd, msg, wParam, lParam );
		} else {
			window = reinterpret_cast<Window*>( GetWindowLong( hwnd, GWL_USERDATA ) );
		
			return window->WindowEvent( msg, wParam, lParam );
		}
	}
}

#endif