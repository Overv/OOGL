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

#include <GL/GL/Renderbuffer.hpp>

namespace GL
{
	Renderbuffer::Renderbuffer()
	{
		gc.Create( obj, glGenRenderbuffers, glDeleteRenderbuffers );
	}

	Renderbuffer::Renderbuffer( const Renderbuffer& other )
	{
		gc.Copy( other.obj, obj );
	}

	Renderbuffer::Renderbuffer( uint width, uint height, InternalFormat::internal_format_t format )
	{
		gc.Create( obj, glGenRenderbuffers, glDeleteRenderbuffers );
		Storage( width, height, format );
	}

	Renderbuffer::~Renderbuffer()
	{
		gc.Destroy( obj );
	}

	Renderbuffer::operator GLuint() const
	{
		return obj;
	}

	const Renderbuffer& Renderbuffer::operator=( const Renderbuffer& other )
	{
		gc.Copy( other.obj, obj, true );
		return *this;
	}

	void Renderbuffer::Storage( uint width, uint height, InternalFormat::internal_format_t format )
	{
		glBindRenderbuffer( GL_RENDERBUFFER, obj );
		glRenderbufferStorage( GL_RENDERBUFFER, format, width, height );
	}

	GC Renderbuffer::gc;
}