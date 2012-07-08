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
	Context::Context( HDC dc )
	{
		// Set pixel format
		PIXELFORMATDESCRIPTOR formatDescriptor =
		{
			sizeof( formatDescriptor ), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0, PFD_MAIN_PLANE,
			0, 0, 0, 0
		};

		int pixelFormat = ChoosePixelFormat( dc, &formatDescriptor );
		SetPixelFormat( dc, pixelFormat, &formatDescriptor );

		// Create dummy context
		HGLRC dummyContext = wglCreateContext( dc );
		wglMakeCurrent( dc, dummyContext );

		// Create OpenGL 3.2 context		
		int attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 2,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		WGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB = (WGLCREATECONTEXTATTRIBSARB)wglGetProcAddress( "wglCreateContextAttribsARB" );
		context = wglCreateContextAttribsARB( dc, NULL, attribs );

		wglMakeCurrent( dc, NULL );
		wglDeleteContext( dummyContext );
		wglMakeCurrent( dc, context );

		this->dc = dc;
	}
	
	Context::~Context()
	{
		wglMakeCurrent( dc, NULL );
		wglDeleteContext( context );
	}
}

#endif