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

#include <GL/GL/Context.hpp>
#include <GL/GL/Extensions.hpp>

#ifdef OOGL_PLATFORM_WINDOWS

namespace GL
{
	Context::Context( uchar color, uchar depth, uchar stencil, uint antialias, HDC dc )
	{
		// Create dummy window
		HWND dummyWindow = CreateWindowA( "STATIC", "", WS_POPUP | WS_DISABLED, 0, 0, 1, 1, NULL, NULL, GetModuleHandle( NULL ), NULL );
		HDC dummyDC = GetDC( dummyWindow );

		// Set dummy pixel format
		PIXELFORMATDESCRIPTOR dummyFormatDescriptor =
		{
			sizeof( dummyFormatDescriptor ), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA, color, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, depth, stencil, 0, PFD_MAIN_PLANE,
			0, 0, 0, 0
		};

		int dummyPixelFormat = ChoosePixelFormat( dummyDC, &dummyFormatDescriptor );
		SetPixelFormat( dummyDC, dummyPixelFormat, &dummyFormatDescriptor );

		// Create dummy context
		HGLRC dummyContext = wglCreateContext( dummyDC );
		wglMakeCurrent( dummyDC, dummyContext );

		int major, minor;
		glGetIntegerv( GL_MAJOR_VERSION, &major );
		glGetIntegerv( GL_MINOR_VERSION, &minor );
		if ( major < 3 || ( major == 3 && minor < 2 ) ) throw VersionException();

		// Load OpenGL extensions
		LoadExtensions();

		// Choose final pixel format
		const int pixelAttribs[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, color,
			WGL_DEPTH_BITS_ARB, depth,
			WGL_STENCIL_BITS_ARB, stencil,
			WGL_SAMPLE_BUFFERS_ARB, antialias > 1 ? GL_TRUE : GL_FALSE,
			WGL_SAMPLES_ARB, antialias > 1 ? antialias : 0,
			0
		};

		int pixelFormat;
		uint formatCount;
		wglChoosePixelFormatARB( dc, pixelAttribs, NULL, 1, &pixelFormat, &formatCount );
		if ( formatCount == 0 ) throw PixelFormatException();
		SetPixelFormat( dc, pixelFormat, &dummyFormatDescriptor );
		
		// Create OpenGL 3.2 context		
		int attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 2,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		
		context = wglCreateContextAttribsARB( dc, NULL, attribs );

		// Clean up
		wglMakeCurrent( dc, NULL );
		wglDeleteContext( dummyContext );
		wglMakeCurrent( dc, context );
		DestroyWindow( dummyWindow );

		this->dc = dc;
		this->owned = true;

		glGetIntegerv( GL_VIEWPORT, (GLint*)&defaultViewport );

		QueryPerformanceCounter( &timeOffset );
	}
	
	Context::~Context()
	{
		if ( !owned ) return;

		wglMakeCurrent( dc, NULL );
		wglDeleteContext( context );
	}

	void Context::Activate()
	{
		if ( owned && wglGetCurrentContext() != context ) wglMakeCurrent( dc, context );
	}

	void Context::SetVerticalSync( bool enabled )
	{
		wglSwapIntervalEXT( enabled ? 1 : 0 );
	}

	float Context::Time()
	{
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter( &time );
		QueryPerformanceFrequency( &freq );

		return ( ( time.QuadPart - timeOffset.QuadPart ) * 1000 / freq.QuadPart ) / 1000.0f;
	}

	Context::Context()
	{
		// Prepare class for using unowned context (i.e. created by external party)
		LoadExtensions();
		owned = false;

		glGetIntegerv( GL_VIEWPORT, (GLint*)&defaultViewport );

		QueryPerformanceCounter( &timeOffset );
	}
}

#endif