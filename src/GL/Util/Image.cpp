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

#include <GL/Util/Image.hpp>
#include <fstream>

namespace GL
{
	Image::Image()
	{
		image = 0;
		width = 0;
		height = 0;
	}

	Image::Image( uint width, uint height, const Color& background )
	{
		image = new Color[ width * height ];
		for ( uint i = 0; i < width * height; i++ )
			image[i] = background;

		this->width = width;
		this->height = height;
	}

	Image::Image( uint width, uint height, uchar* pixels )
	{
		image = new Color[ width * height ];

		for ( uint x = 0; x < width; x++ )
		{
			for ( uint y = 0; y < height; y++ )
			{
				uint o = ( x + y * width ) * sizeof( uchar );
				image[ x + y * width ] = Color( pixels[o+0], pixels[o+1], pixels[o+2], pixels[o+3] );
			}
		}

		this->width = width;
		this->height = height;
	}

	Image::Image( const std::string& filename )
	{
		image = 0;
		Load( filename );
	}

	Image::~Image()
	{
		if ( image ) delete [] image;
	}

	void Image::Load( const std::string& filename )
	{
		// Unload image
		if ( image ) delete [] image;
		image = 0;
		width = 0;
		height = 0;

		// Load data from file
		std::ifstream file( filename, std::ios::binary | std::ios::ate );
		if ( !file.is_open() ) throw FileException();

		uint fileSize = (uint)file.tellg();
		file.seekg( 0, std::ios::beg );

		ByteBuffer data( fileSize );
		file.read( (char*)data.Data(), fileSize );
		
		file.close();

		// Determine format and process
		if ( data.PeekByte( 0 ) == 'B' && data.PeekByte( 1 ) == 'M' )
			LoadBMP( data );
		else
			throw FormatException();
	}

	uint Image::GetWidth() const
	{
		return width;
	}

	uint Image::GetHeight() const
	{
		return height;
	}

	const Color* Image::GetPixels() const
	{
		return image;
	}

	Color Image::GetPixel( uint x, uint y ) const
	{
		if ( x >= width || y >= height ) return Color();
		return image[ x + y * width ];
	}

	void Image::SetPixel( uint x, uint y, const Color& color )
	{
		if ( x >= width || y >= height ) return;
		image[ x + y * width ] = color;
	}

	void Image::LoadBMP( ByteBuffer& data )
	{
		// Header
		data.Advance( 2 + 4 + 4 ); // Skip magic number, file size and application specific data
		uint pixelOffset = data.ReadUint();

		// DIB header
		if ( data.ReadUint() != 40 ) throw FormatException(); // Only version 1 is currently supported
		uint width = data.ReadUint();
		int rawHeight = data.ReadInt();
		uint height = abs( rawHeight );
		if ( width == 0 || height == 0 ) throw FormatException();
		if ( data.ReadUshort() != 1 ) throw FormatException(); // Image planes
		if ( data.ReadUshort() != 24 ) throw FormatException(); // Bits per pixel
		if ( data.ReadUint() != 0 ) throw FormatException(); // Compression
		data.Advance( 4 ); // Skip pixel array size (very unreliable, a value of 0 is not uncommon)
		data.Advance( 4 + 4 ); // Skip X/Y resolution
		if ( data.ReadUint() != 0 ) throw FormatException(); // Palette colors
		if ( data.ReadUint() != 0 ) throw FormatException(); // Important colors

		// Pixel data
		data.Move( pixelOffset );
		uint padding = ( width * 3 ) % 4;

		image = new Color[ width * height ];
		
		for ( uint y = 0; y < height; y++ )
		{
			for ( uint x = 0; x < width; x++ )
			{
				uint o = rawHeight > 0 ? x + ( height - y - 1 ) * width : x + y * width; // Flip image vertically if height is negative
				image[ o ] = Color( data.PeekByte( 2 ), data.PeekByte( 1 ), data.PeekByte( 0 ) ); // BGR byte order
				data.Advance( 3 );
				if ( x == width - 1 ) data.Advance( padding );
			}
		}

		this->width = width;
		this->height = height;
	}
}