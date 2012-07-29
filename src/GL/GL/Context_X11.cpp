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

#ifdef OOGL_PLATFORM_LINUX

#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace GL
{
	// Stub error handler for surpressing undesired Xlib errors
	typedef int ( * XERRORHANDLER ) ( Display*, XErrorEvent* );
	int XErrorSurpressor( Display* display, XErrorEvent* ev )
	{
		return 0;
	}

	Context::Context( uchar color, uchar depth, uchar stencil, uint antialias, Display* display, int screen, ::Window window )
	{
		// Load OpenGL extensions
		LoadExtensions();

		// Choose an appropriate config
		const int pixelAttribs[] = {
			GLX_X_RENDERABLE, GL_TRUE,
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_DOUBLEBUFFER, GL_TRUE,
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
			GLX_BUFFER_SIZE, color,
			GLX_DEPTH_SIZE, depth,
			GLX_STENCIL_SIZE, stencil,
			GLX_SAMPLE_BUFFERS, antialias > 1 ? GL_TRUE : GL_FALSE,
			GLX_SAMPLES, antialias > 1 ? (int)antialias : 0,
			0
		};

		int configCount;
		GLXFBConfig* configs = glXChooseFBConfig( display, screen, pixelAttribs, &configCount );
		if ( configCount == 0 ) throw PixelFormatException();
		GLXFBConfig config = configs[0];
		XFree( configs );

		// Create OpenGL 3.2 context
		int attribs[] = {
			GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
			GLX_CONTEXT_MINOR_VERSION_ARB, 2,
			GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		
		XERRORHANDLER oldHandler = XSetErrorHandler( &XErrorSurpressor );
			context = glXCreateContextAttribsARB( display, config, NULL, GL_TRUE, attribs );
			if ( !context ) throw VersionException();
		XSetErrorHandler( oldHandler );

		// Activate context
		glXMakeCurrent( display, window, context );

		this->display = display;
		this->window = window;
		this->owned = true;

		glGetIntegerv( GL_VIEWPORT, (GLint*)&defaultViewport );

		gettimeofday( &timeOffset, NULL );
	}

	Context::~Context()
	{
		if ( !owned ) return;

		glXMakeCurrent( display, 0, NULL );
		glXDestroyContext( display, context );
	}

	void Context::Activate()
	{
		if ( owned && glXGetCurrentContext() != context ) glXMakeCurrent( display, window, context );
	}

	void Context::SetVerticalSync( bool enabled )
	{
		glXSwapIntervalSGI( enabled ? 1 : 0 );
	}

	float Context::Time()
	{
		timeval time;
		gettimeofday( &time, NULL );

		return time.tv_sec - timeOffset.tv_sec + ( time.tv_usec - timeOffset.tv_usec ) / 1000000.0f;
	}

	Context::Context()
	{
		// Prepare class for using unowned context (i.e. created by external party)
		LoadExtensions();
		owned = false;

		glGetIntegerv( GL_VIEWPORT, (GLint*)&defaultViewport );

		gettimeofday( &timeOffset, NULL );
	}
}

#endif
