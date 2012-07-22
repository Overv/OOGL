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

#include <GL/GL/Framebuffer.hpp>

#define PUSHSTATE() GLint restoreId; glGetIntegerv( GL_DRAW_FRAMEBUFFER_BINDING, &restoreId );
#define POPSTATE() glBindFramebuffer( GL_DRAW_FRAMEBUFFER, restoreId );

namespace GL
{
	Framebuffer::Framebuffer( const Framebuffer& other )
	{
		gc.Copy( other.obj, obj );
		color = other.color;
		depth = other.depth;
	}

	Framebuffer::Framebuffer( uint width, uint height )
	{
		PUSHSTATE()
		
		gc.Create( obj, glGenFramebuffers, glDeleteFramebuffers );
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, obj );
		
		// Create renderbuffer to hold depth buffer
		depth.Storage( width, height, InternalFormat::DepthComponent );
		glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth );

		// Create texture to hold color buffer
		color.Image2D( 0, DataType::UnsignedByte, Format::RGBA, width, height, InternalFormat::RGBA );
		glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0 );

		// Check
		if ( glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
			throw FramebufferException();
		
		POPSTATE()
	}

	Framebuffer::~Framebuffer()
	{
		gc.Destroy( obj );
	}

	Framebuffer::operator GLuint() const
	{
		return obj;
	}

	const Framebuffer& Framebuffer::operator=( const Framebuffer& other )
	{
		gc.Copy( other.obj, obj, true );
		color = other.color;
		depth = other.depth;
		
		return *this;
	}

	const Texture& Framebuffer::GetTexture()
	{
		return color;
	}

	GC Framebuffer::gc;
}