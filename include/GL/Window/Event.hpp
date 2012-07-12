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

#ifndef OOGL_EVENT_HPP
#define OOGL_EVENT_HPP

namespace GL
{
	/*
		Mouse button
	*/
	namespace MouseButton
	{
		enum mouse_button_t
		{
			Left,
			Right,
			Middle
		};
	}

	/*
		Mouse event
	*/
	struct MouseEvent
	{
		uint X, Y;
		union
		{
			int Delta;
			MouseButton::mouse_button_t Button;
		};
	};

	/*
		Keyboard keys
	*/
	namespace Key
	{
		enum key_t
		{
			Unknown,
			F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
			A, B, C, D, E, F, G, H, I, J, K, L,	M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
			LeftBracket, RightBracket, Semicolon, Comma, Period, Quote, Slash, Backslash, Tilde, Equals, Hyphen,
			Escape, Control, Shift, Alt, Space, Enter, Backspace, Tab, PageUp, PageDown, End, Home, Insert, Delete, Pause,
			Left, Right, Up, Down,
			Numpad0, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
			Add, Subtract, Multiply, Divide
		};
	}

	/*
		Keyboard event
	*/
	struct KeyEvent
	{
		Key::key_t Code;
		bool Alt;
		bool Control;
		bool Shift;
	};

	/*
		Window event
	*/
	struct WindowEvent
	{
		union { int X; uint Width; };
		union { int Y; uint Height; };
	};

	/*
		Event
	*/
	struct Event
	{
		enum event_t
		{
			Unknown,
			Close,
			Resize,
			Move,
			Focus,
			Blur,
			KeyDown,
			KeyUp,
			MouseDown,
			MouseUp,
			MouseWheel,
			MouseMove
		};

		event_t Type;

		union
		{
			MouseEvent Mouse;
			KeyEvent Key;
			WindowEvent Window;
		};
	};
}

#endif