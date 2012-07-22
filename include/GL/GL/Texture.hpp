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
#include <GL/GL/GC.hpp>
#include <GL/GL/Extensions.hpp>
#include <GL/Util/Image.hpp>

namespace GL
{
	/*
		Internal texture formats
	*/
	namespace InternalFormat
	{
		enum internal_format_t
		{
			CompressedRed = GL_COMPRESSED_RED,
			CompressedRedRGTC1 = GL_COMPRESSED_RED_RGTC1,
			CompressedRG = GL_COMPRESSED_RG,
			CompressedRGB = GL_COMPRESSED_RGB,
			CompressedRGBA = GL_COMPRESSED_RGBA,
			CompressedRGRGTC2 = GL_COMPRESSED_RG_RGTC2,
			CompressedSignedRedRGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
			CompressedSignedRGRGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2,
			CompressedSRGB = GL_COMPRESSED_SRGB,
			DepthStencil = GL_DEPTH_STENCIL,
			Depth24Stencil8 = GL_DEPTH24_STENCIL8,
			Depth32FStencil8 = GL_DEPTH32F_STENCIL8,
			DepthComponent = GL_DEPTH_COMPONENT,
			DepthComponent16 = GL_DEPTH_COMPONENT16,
			DepthComponent24 = GL_DEPTH_COMPONENT24,
			DepthComponent32F = GL_DEPTH_COMPONENT32F,
			R16F = GL_R16F,
			R16I = GL_R16I,
			R16SNorm = GL_R16_SNORM,
			R16UI = GL_R16UI,
			R32F = GL_R32F,
			R32I = GL_R32I,
			R32UI = GL_R32UI,
			R3G3B2 = GL_R3_G3_B2,
			R8 = GL_R8,
			R8I = GL_R8I,
			R8SNorm = GL_R8_SNORM,
			R8UI = GL_R8UI,
			Red = GL_RED,
			RG = GL_RG,
			RG16 = GL_RG16,
			RG16F = GL_RG16F,
			RG16SNorm = GL_RG16_SNORM,
			RG32F = GL_RG32F,
			RG32I = GL_RG32I,
			RG32UI = GL_RG32UI,
			RG8 = GL_RG8,
			RG8I = GL_RG8I,
			RG8SNorm = GL_RG8_SNORM,
			RG8UI = GL_RG8UI,
			RGB = GL_RGB,
			RGB10 = GL_RGB10,
			RGB10A2 = GL_RGB10_A2,
			RGB12 = GL_RGB12,
			RGB16 = GL_RGB16,
			RGB16F = GL_RGB16F,
			RGB16I = GL_RGB16I,
			RGB16UI = GL_RGB16UI,
			RGB32F = GL_RGB32F,
			RGB32I = GL_RGB32I,
			RGB32UI = GL_RGB32UI,
			RGB4 = GL_RGB4,
			RGB5 = GL_RGB5,
			RGB5A1 = GL_RGB5_A1,
			RGB8 = GL_RGB8,
			RGB8I = GL_RGB8I,
			RGB8UI = GL_RGB8UI,
			RGB9E5 = GL_RGB9_E5,
			RGBA = GL_RGBA,
			RGBA12 = GL_RGBA12,
			RGBA16 = GL_RGBA16,
			RGBA16F = GL_RGBA16F,
			RGBA16I = GL_RGBA16I,
			RGBA16UI = GL_RGBA16UI,
			RGBA2 = GL_RGBA2,
			RGBA32F = GL_RGBA32F,
			RGBA32I = GL_RGBA32I,
			RGBA32UI = GL_RGBA32UI,
			RGBA4 = GL_RGBA4,
			RGBA8 = GL_RGBA8,
			RGBA8UI = GL_RGBA8UI,
			SRGB8 = GL_SRGB8,
			SRGB8A8 = GL_SRGB8_ALPHA8,
			SRGBA = GL_SRGB_ALPHA
		};
	}

	/*
		Texture data formats
	*/
	namespace Format
	{
		enum format_t
		{
			Red = GL_RED,
			RGB = GL_RGB,
			BGR = GL_BGR,
			RGBA = GL_RGBA,
			BGRA = GL_BGRA
		};
	}

	/*
		Texture data types
	*/
	namespace DataType
	{
		enum data_type_t
		{
			Byte = GL_BYTE,
			UnsignedByte = GL_UNSIGNED_BYTE,
			Short = GL_SHORT,
			UnsignedShort = GL_UNSIGNED_SHORT,
			Int = GL_INT,
			UnsignedInt = GL_UNSIGNED_INT,
			Float = GL_FLOAT,
			Double = GL_DOUBLE,

			UnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2,
			UnsignedByte233Rev = GL_UNSIGNED_BYTE_2_3_3_REV,
			UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,
			UnsignedShort565Rev = GL_UNSIGNED_SHORT_5_6_5,
			UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
			UnsignedShort4444Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,
			UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,
			UnsignedShort1555Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV,
			UnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8,
			UnsignedInt8888Rev = GL_UNSIGNED_INT_8_8_8_8_REV,
			UnsignedInt101010102 = GL_UNSIGNED_INT_10_10_10_2
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
		Texture( const Texture& other );
		Texture( const Image& image, InternalFormat::internal_format_t internalFormat = InternalFormat::RGBA );

		~Texture();

		operator GLuint() const;
		const Texture& operator=( const Texture& other );
		
		void Image2D( const GLvoid* data, DataType::data_type_t type, Format::format_t format, uint width, uint height, InternalFormat::internal_format_t internalFormat );
		
		void SetWrapping( Wrapping::wrapping_t s );
		void SetWrapping( Wrapping::wrapping_t s, Wrapping::wrapping_t t );
		void SetWrapping( Wrapping::wrapping_t s, Wrapping::wrapping_t t, Wrapping::wrapping_t r );

		void SetFilters( Filter::filter_t min, Filter::filter_t mag );
		void SetBorderColor( const Color& color );

		void GenerateMipmaps();

	private:
		static GC gc;
		GLuint obj;
	};
}

#endif