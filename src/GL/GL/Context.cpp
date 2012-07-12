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

namespace GL
{
	void Context::ClearColor( float r, float g, float b, float a )
	{
		Activate();
		glClearColor( r, g, b, a );
	}

	void Context::Clear( Buffer::buffer_t buffers )
	{
		Activate();
		glClear( buffers );
	}

	void Context::Use( const Program& program )
	{
		glUseProgram( program );
	}

	void Context::DrawArrays( const VertexArray& vao, Primitive::primitive_t mode, uint offset, uint vertices )
	{
		glBindVertexArray( vao );
		glDrawArrays( mode, offset, vertices );
	}

	void Context::DrawElements( const VertexArray& vao, Primitive::primitive_t mode, intptr_t offset, uint count, uint type )
	{
		glBindVertexArray( vao );
		glDrawElements( mode, count, type, (const GLvoid*)offset );
	}
}