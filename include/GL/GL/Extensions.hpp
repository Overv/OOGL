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

/*
	OpenGL context creation/configuration
*/

#if defined( OOGL_PLATFORM_WINDOWS )
	const unsigned int WGL_CONTEXT_MAJOR_VERSION_ARB = 0x2091;
	const unsigned int WGL_CONTEXT_MINOR_VERSION_ARB = 0x2092;
	const unsigned int WGL_CONTEXT_PROFILE_MASK_ARB = 0x9126;
	const unsigned int WGL_CONTEXT_CORE_PROFILE_BIT_ARB = 0x00000001;

	const unsigned int WGL_DRAW_TO_WINDOW_ARB = 0x2001;
	const unsigned int WGL_SUPPORT_OPENGL_ARB = 0x2010;
	const unsigned int WGL_DOUBLE_BUFFER_ARB = 0x2011;
	const unsigned int WGL_PIXEL_TYPE_ARB = 0x2013;
	const unsigned int WGL_COLOR_BITS_ARB = 0x2014;
	const unsigned int WGL_DEPTH_BITS_ARB = 0x2022;
	const unsigned int WGL_STENCIL_BITS_ARB = 0x2023;
	const unsigned int WGL_SAMPLE_BUFFERS_ARB = 0x2041;
	const unsigned int WGL_SAMPLES_ARB = 0x2042;
	const unsigned int WGL_TYPE_RGBA_ARB = 0x202B;

	typedef HGLRC ( WINAPI * WGLCREATECONTEXTATTRIBSARB ) ( HDC hDC, HGLRC hShareContext, const int* attribList );
	extern WGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB;
	typedef int ( WINAPI * WGLCHOOSEPIXELFORMATARB ) ( HDC hdc, const int* intAttribs, const float* floatAttribs, unsigned int maxFormats, int* formats, unsigned int* formatCount );
	extern WGLCHOOSEPIXELFORMATARB wglChoosePixelFormatARB;
	typedef int ( WINAPI * WGLSWAPINTERVALEXT ) ( int interval );
	extern WGLSWAPINTERVALEXT wglSwapIntervalEXT;
#endif

/*
	Return values/parameters
*/

const unsigned int GL_MAJOR_VERSION = 0x821B;
const unsigned int GL_MINOR_VERSION = 0x821C;

/*
	Extension loader
*/

namespace GL
{
	extern void LoadExtensions();
}

#endif