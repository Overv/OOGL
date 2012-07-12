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

namespace GL
{
	int Window::GetX()
	{
		return x;
	}

	int Window::GetY()
	{
		return y;
	}

	uint Window::GetWidth()
	{
		return width;
	}

	uint Window::GetHeight()
	{
		return height;
	}

	bool Window::IsOpen()
	{
		return open;
	}

	bool Window::HasFocus()
	{
		return focus;
	}

	int Window::GetMouseX()
	{
		return mousex;
	}

	int Window::GetMouseY()
	{
		return mousey;
	}

	bool Window::IsMouseButtonDown( MouseButton::mouse_button_t button )
	{
		if ( button >= sizeof( mouse ) / sizeof( bool ) ) return false;
		return mouse[button];
	}

	bool Window::IsKeyDown( Key::key_t key )
	{
		if ( key >= sizeof( keys ) / sizeof( bool ) ) return false;
		return keys[key];
	}
}