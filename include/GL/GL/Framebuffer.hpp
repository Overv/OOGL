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

#ifndef OOGL_FBO_HPP
#define OOGL_FBO_HPP

#include <GL/GL/Texture.hpp>
#include <GL/GL/Renderbuffer.hpp>

namespace GL
{
	/*
		Exceptions
	*/
	class FramebufferException : public std::exception 
	{
		virtual const char* what() const throw()
		{
			return "Framebuffer could not be created!";
		}
	};

	/*
		Frame buffer
	*/
	class Framebuffer
	{
	public:
		Framebuffer( const Framebuffer& other );
		Framebuffer( uint width, uint height, uchar color = 32, uchar depth = 24 );
		~Framebuffer();

		operator GLuint() const;
		const Framebuffer& operator=( const Framebuffer& other );

		const Texture& GetTexture();
		const Texture& GetDepthTexture();

	private:
		static GC gc;
		GLuint obj;
		Texture texColor;
		Texture texDepth;
	};
}

#endif