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

#ifndef OOGL_EXTENSIONS_HPP
#define OOGL_EXTENSIONS_HPP

#include <GL/Platform.hpp>

namespace GL
{
	/*
		OpenGL context creation
	*/

#if defined( OOGL_PLATFORM_WINDOWS )
	const uint WGL_CONTEXT_MAJOR_VERSION_ARB = 0x2091;
	const uint WGL_CONTEXT_MINOR_VERSION_ARB = 0x2092;
	const uint WGL_CONTEXT_PROFILE_MASK_ARB = 0x9126;
	const uint WGL_CONTEXT_CORE_PROFILE_BIT_ARB = 0x00000001;

	typedef HGLRC ( WINAPI * WGLCREATECONTEXTATTRIBSARB ) ( HDC hDC, HGLRC hShareContext, const int *attribList );
#endif
}

#endif