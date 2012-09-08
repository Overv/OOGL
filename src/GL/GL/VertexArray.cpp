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

#include <GL/GL/VertexArray.hpp>

namespace GL
{
	VertexArray::VertexArray()
	{
		gc.Create( obj, glGenVertexArrays, glDeleteVertexArrays );
	}

	VertexArray::VertexArray( const VertexArray& other )
	{
		gc.Copy( other.obj, obj );
	}

	VertexArray::~VertexArray()
	{
		gc.Destroy( obj );
	}

	VertexArray::operator GLuint() const
	{
		return obj;
	}

	const VertexArray& VertexArray::operator=( const VertexArray& other )
	{
		gc.Copy( other.obj, obj, true );
		return *this;
	}

	void VertexArray::BindAttribute( const Attribute& attribute, const VertexBuffer& buffer, Type::type_t type, uint count, uint stride, intptr_t offset )
	{
		glBindVertexArray( obj );
		glBindBuffer( GL_ARRAY_BUFFER, buffer );
		glEnableVertexAttribArray( attribute );
		glVertexAttribPointer( attribute, count, type, GL_FALSE, stride, (const GLvoid*)offset );
	}

	void VertexArray::BindElements( const VertexBuffer& elements )
	{
		glBindVertexArray( obj );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, elements );
	}

	void VertexArray::BindTransformFeedback( uint index, const VertexBuffer& buffer )
	{
		glBindVertexArray( obj );
		glBindBufferBase( GL_TRANSFORM_FEEDBACK_BUFFER, index, buffer );
	}

	GC VertexArray::gc;
}