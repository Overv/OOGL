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

#include <GL/GL/VertexBuffer.hpp>
#include <vector>

namespace GL
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers( 1, &id );
	}

	VertexBuffer::VertexBuffer( const void* data, size_t length, uint usage )
	{
		glGenBuffers( 1, &id );
		Data( data, length, usage );
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers( 1, &id );
	}

	VertexBuffer::operator GLuint() const
	{
		return id;
	}

	void VertexBuffer::Data( const void* data, size_t length, uint usage )
	{
		glBindBuffer( GL_ARRAY_BUFFER, id );
		glBufferData( GL_ARRAY_BUFFER, length, data, usage );
	}

	void VertexBuffer::SubData( const void* data, size_t offset, size_t length )
	{
		glBindBuffer( GL_ARRAY_BUFFER, id );
		glBufferSubData( GL_ARRAY_BUFFER, offset, length, data );
	}
}