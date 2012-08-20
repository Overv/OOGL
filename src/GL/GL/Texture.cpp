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

#include <GL/GL/Texture.hpp>

#define PUSHSTATE() GLint restoreId; glGetIntegerv( GL_TEXTURE_BINDING_2D, &restoreId );
#define POPSTATE() glBindTexture( GL_TEXTURE_2D, restoreId );

namespace GL
{
	Texture::Texture()
	{
		gc.Create( obj, glGenTextures, glDeleteTextures );
	}

	Texture::Texture( const Texture& other )
	{
		gc.Copy( other.obj, obj );
	}

	Texture::Texture( const Image& image, InternalFormat::internal_format_t internalFormat )
	{
		PUSHSTATE()

		gc.Create( obj, glGenTextures, glDeleteTextures );
		glBindTexture( GL_TEXTURE_2D, obj );
		
		glTexImage2D( GL_TEXTURE_2D, 0, internalFormat, image.GetWidth(), image.GetHeight(), 0, Format::RGBA, DataType::UnsignedByte, image.GetPixels() );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glGenerateMipmap( GL_TEXTURE_2D );

		POPSTATE()
	}

	Texture::~Texture()
	{
		gc.Destroy( obj );
	}

	Texture::operator GLuint() const
	{
		return obj;
	}

	const Texture& Texture::operator=( const Texture& other )
	{
		gc.Copy( other.obj, obj, true );
		return *this;
	}

	void Texture::Image2D( const GLvoid* data, DataType::data_type_t type, Format::format_t format, uint width, uint height, InternalFormat::internal_format_t internalFormat )
	{
		PUSHSTATE()

		glBindTexture( GL_TEXTURE_2D, obj );
		glTexImage2D( GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data );

		POPSTATE()
	}

	void Texture::SetWrapping( Wrapping::wrapping_t s )
	{
		PUSHSTATE()

		glBindTexture( GL_TEXTURE_2D, obj );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s );

		glBindTexture( GL_TEXTURE_2D, restoreId );

		POPSTATE()
	}

	void Texture::SetWrapping( Wrapping::wrapping_t s, Wrapping::wrapping_t t )
	{
		PUSHSTATE()

		glBindTexture( GL_TEXTURE_2D, obj );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t );

		glBindTexture( GL_TEXTURE_2D, restoreId );

		POPSTATE()
	}

	void Texture::SetWrapping( Wrapping::wrapping_t s, Wrapping::wrapping_t t, Wrapping::wrapping_t r )
	{
		PUSHSTATE()

		glBindTexture( GL_TEXTURE_2D, obj );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, r );

		POPSTATE()
	}

	void Texture::SetFilters( Filter::filter_t min, Filter::filter_t mag )
	{
		PUSHSTATE()

		glBindTexture( GL_TEXTURE_2D, obj );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag );

		POPSTATE()
	}

	void Texture::SetBorderColor( const Color& color )
	{
		PUSHSTATE()

		glBindTexture( GL_TEXTURE_2D, obj );
		float col[4] = { color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f };
		glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, col );

		POPSTATE()
	}
	
	void Texture::GenerateMipmaps()
	{
		PUSHSTATE()

		glBindTexture( GL_TEXTURE_2D, obj );
		glGenerateMipmap( GL_TEXTURE_2D );

		POPSTATE()
	}

	GC Texture::gc;
}