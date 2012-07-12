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

#ifndef OOGL_IMAGE_HPP
#define OOGL_IMAGE_HPP

#include <GL/Platform.hpp>
#include <GL/Util/Color.hpp>
#include <GL/Util/ByteBuffer.hpp>
#include <string>
#include <exception>

namespace GL
{
	/*
		Supported image file formats
	*/
	namespace ImageFileFormat
	{
		enum image_file_format_t
		{
			BMP
		};
	}

	/*
		Exceptions
	*/
	class FileException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "File could not be opened!";
		}
	};
	class FormatException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Image file format not supported!";
		}
	};

	/*
		Image
	*/
	class Image
	{
	public:
		Image();

		Image( uint width, uint height, const Color& background );
		Image( uint width, uint height, uchar* pixels );
		Image( const std::string& filename );

		~Image();

		void Load( const std::string& filename );
		void Save( const std::string& filename, ImageFileFormat::image_file_format_t format );

		uint GetWidth() const;
		uint GetHeight() const;
		const Color* GetPixels() const;

		Color GetPixel( uint x, uint y ) const;
		void SetPixel( uint x, uint y, const Color& color );

	private:
		Color* image;
		uint width, height;
		
		void LoadBMP( ByteBuffer& data );
	};
}

#endif