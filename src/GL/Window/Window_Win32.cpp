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

	bool Window::GetEvent( Event& event )
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
		
		event = events.front();
		events.pop();

		return true;
	}

	LRESULT Window::WindowEvent( UINT msg, WPARAM wParam, LPARAM lParam )
	{
		Event windowEvent;
		windowEvent.Type = 0;

		// Translate message to Event
		switch ( msg )
		{
		case WM_CLOSE:
			open = false;
			DestroyWindow( window );
			break;

		case WM_SIZE:
			if ( events.empty() || events.back().Type != EventType::Resize )
				windowEvent.Type = EventType::Resize;
			break;

		case WM_MOVE:
			if ( events.empty() || events.back().Type != EventType::Move )
				windowEvent.Type = EventType::Move;
			break;

		case WM_ACTIVATE:
			if ( wParam == WA_INACTIVE ) {
				windowEvent.Type = EventType::Blur;
				focus = false;
			} else {
				windowEvent.Type = EventType::Focus;
				focus = true;
			}
			break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			windowEvent.Type = EventType::KeyDown;
			break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
			windowEvent.Type = EventType::KeyUp;
			break;

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			windowEvent.Type = EventType::MouseDown;
			break;

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			windowEvent.Type = EventType::MouseUp;
			break;

		case WM_MOUSEWHEEL:
			windowEvent.Type = EventType::MouseWheel;
			break;

		case WM_MOUSEMOVE:
			windowEvent.Type = EventType::MouseMove;
			break;

		default:
			return DefWindowProc( window, msg, wParam, lParam );
		}

		// Add event to internal queue
		if ( windowEvent.Type != 0 )
			events.push( windowEvent );

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