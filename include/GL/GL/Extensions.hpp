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
	#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
	#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
	#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
	#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

	#define WGL_DRAW_TO_WINDOW_ARB 0x2001
	#define WGL_SUPPORT_OPENGL_ARB 0x2010
	#define WGL_DOUBLE_BUFFER_ARB 0x2011
	#define WGL_PIXEL_TYPE_ARB 0x2013
	#define WGL_COLOR_BITS_ARB 0x2014
	#define WGL_DEPTH_BITS_ARB 0x2022
	#define WGL_STENCIL_BITS_ARB 0x2023
	#define WGL_SAMPLE_BUFFERS_ARB 0x2041
	#define WGL_SAMPLES_ARB 0x2042
	#define WGL_TYPE_RGBA_ARB 0x202B

	typedef HGLRC ( WINAPI * WGLCREATECONTEXTATTRIBSARB ) ( HDC hDC, HGLRC hShareContext, const int* attribList );
	extern WGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB;
	typedef int ( WINAPI * WGLCHOOSEPIXELFORMATARB ) ( HDC hdc, const int* intAttribs, const float* floatAttribs, unsigned int maxFormats, int* formats, unsigned int* formatCount );
	extern WGLCHOOSEPIXELFORMATARB wglChoosePixelFormatARB;
	typedef int ( WINAPI * WGLSWAPINTERVALEXT ) ( int interval );
	extern WGLSWAPINTERVALEXT wglSwapIntervalEXT;
#elif defined( OOGL_PLATFORM_LINUX )
	#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
	#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
	#define GLX_CONTEXT_PROFILE_MASK_ARB 0x9126
	#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

	typedef GLXContext ( * GLXCREATECONTEXTATTRIBSARB ) ( Display* display, GLXFBConfig config, GLXContext share_context, Bool direct, const int* attribs );
	extern GLXCREATECONTEXTATTRIBSARB glXCreateContextAttribsARB;
	typedef int ( * GLXSWAPINTERVALSGI ) ( int interval );
	extern GLXSWAPINTERVALSGI glXSwapIntervalSGI;
#endif

/*
	Return values/parameters
*/

#define GL_MAJOR_VERSION 0x821B
#define GL_MINOR_VERSION 0x821C

/*
	Extension loader
*/

namespace GL
{
	extern void LoadExtensions();
}

#endif