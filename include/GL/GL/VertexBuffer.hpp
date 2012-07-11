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

#ifndef OOGL_VERTEXBUFFER_HPP
#define OOGL_VERTEXBUFFER_HPP

#include <GL/Platform.hpp>
#include <GL/GL/Extensions.hpp>

namespace GL
{
	/*
		Buffer usage types
	*/
	namespace BufferUsage
	{
		const uint StreamDraw = GL_STREAM_DRAW;
		const uint StreamRead = GL_STREAM_READ;
		const uint StreamCopy = GL_STREAM_COPY;
		const uint StaticDraw = GL_STATIC_DRAW;
		const uint StaticRead = GL_STATIC_READ;
		const uint StaticCopy = GL_STATIC_COPY;
		const uint DynamicDraw = GL_DYNAMIC_DRAW;
		const uint DynamicRead = GL_DYNAMIC_READ;
		const uint DynamicCopy = GL_DYNAMIC_COPY;
	}

	/*
		Vertex Buffer
	*/
	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer( const void* data, size_t length, uint usage );

		~VertexBuffer();

		operator GLuint() const;

		void Data( const void* data, size_t length, uint usage );
		void SubData( const void* data, size_t offset, size_t length );

	private:
		GLuint id;
	};
}

#endif