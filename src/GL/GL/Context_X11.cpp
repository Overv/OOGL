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

namespace GL
{
	Context::Context( uint color, uint depth, uint stencil, uint antialias, Display* display, int screen, ::Window window )
	{
		// Choose an appropriate config
		const int attribs[] = {
			0
		};
		int configCount;
		GLXFBConfig* configs = glXChooseFBConfig( display, screen, attribs, &configCount );
		XFree( configs );
	}

	Context::~Context()
	{
		// TODO
	}

	void Context::Activate()
	{
		// TODO
	}

	void Context::SetVerticalSync( bool enabled )
	{
		// TODO
	}
}

#endif