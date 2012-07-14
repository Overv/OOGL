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

#ifndef OOGL_TEXTURE_HPP
#define OOGL_TEXTURE_HPP

#include <GL/Platform.hpp>
#include <GL/GL/Extensions.hpp>
#include <GL/Util/Image.hpp>

namespace GL
{
	/*
		Texture data types
	*/
	namespace DataType
	{
		enum data_type_t
		{
			// TODO: Fill in
		};
	}

	/*
		Texture data formats
	*/
	namespace Format
	{
		enum format_t
		{
			Red,
			RB,
			RGB,
			BGR,
			RGBA,
			BGRA
		};
	}

	/*
		Internal texture formats
	*/
	namespace InternalFormat
	{
		enum internal_format_t
		{
			// TODO: Fill in
		};
	}

	/*
		Wrapping types
	*/
	namespace Wrapping
	{
		enum wrapping_t
		{
			ClampEdge = GL_CLAMP_TO_EDGE,
			ClampBorder = GL_CLAMP_TO_BORDER,
			Repeat = GL_REPEAT,
			MirroredRepeat = GL_MIRRORED_REPEAT
		};
	}

	/*
		Filter types
	*/
	namespace Filter
	{
		enum filter_t
		{
			Nearest = GL_NEAREST,
			Linear = GL_LINEAR,
			NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
			LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
			NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
			LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
		};
	}

	/*
		Texture
	*/
	class Texture
	{
	public:
		Texture();
		Texture( const Image& image );

		~Texture();

		operator GLuint() const;

		void Image1D( const GLvoid* data, const DataType::data_type_t& type, const Format::format_t& format, uint length, const InternalFormat::internal_format_t& internalFormat );
		void Image2D( const GLvoid* data, const DataType::data_type_t& type, const Format::format_t& format, uint width, uint height, const InternalFormat::internal_format_t& internalFormat );
		void Image3D( const GLvoid* data, const DataType::data_type_t& type, const Format::format_t& format, uint width, uint height, uint depth, const InternalFormat::internal_format_t& internalFormat );
		
		void SetWrapping( const Wrapping::wrapping_t& s, const Wrapping::wrapping_t& t, const Wrapping::wrapping_t& r );
		void SetFilters( const Filter::filter_t& min, const Filter::filter_t& max );
		void SetBorderColor( const Color& color );

		void GenerateMipmaps();

	private:
		GLuint id;
	};
}

#endif