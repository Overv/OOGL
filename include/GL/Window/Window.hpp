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

#pragma once

#ifndef OOGL_WINDOW_HPP
#define OOGL_WINDOW_HPP

#include <GL/Platform.hpp>
#include <GL/Window/Event.hpp>
#include <GL/GL/Context.hpp>
#include <string>
#include <cstring>
#include <queue>

namespace GL
{
	/*
		Window properties
	*/
	namespace WindowStyle
	{
		const ulong Base = 0;
		const ulong Resize = 1;
		const ulong Close = 2;
		const ulong Fullscreen = 4;
	}

	/*
		Window
	*/
	class Window
	{
	public:
		Window( uint width = 800, uint height = 600, const std::string& title = "Window", uint style = WindowStyle::Close );
		~Window();
		
		int GetX();
		int GetY();

		uint GetWidth();
		uint GetHeight();

		bool IsOpen();
		bool HasFocus();

		void SetPos( int x, int y );
		void SetSize( uint width, uint height );

		void SetTitle( const std::string& title );

		void SetVisible( bool visible );

		void Close();

		bool GetEvent( Event& ev );
		
		int GetMouseX();
		int GetMouseY();

		bool IsMouseButtonDown( uint button );
		bool IsKeyDown( uint key );

		Context& GetContext();
		void Present();

	private:
		uint width, height;
		int x, y;
		bool open, focus;
		std::queue<Event> events;

		uint mousex, mousey;
		bool mouse[3];
		bool keys[100];

		Context* context;

#if defined( OOGL_PLATFORM_WINDOWS )
		HWND window;
		DWORD style;

		LRESULT WindowEvent( UINT msg, WPARAM wParam, LPARAM lParam );
		static LRESULT CALLBACK WindowEventHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
#elif defined( OOGL_PLATFORM_LINUX )
		::Window window;
		Display* display;
		Atom close;
		bool fullscreen;
		int screen;
		int oldVideoMode;

		void EnableFullscreen( bool enabled, int width = 0, int height = 0 );
		void WindowEvent( const XEvent& event );
		static Bool CheckEvent( Display*, XEvent* event, XPointer userData );
#endif

		uint TranslateKey( uint code );
	};
}

#endif