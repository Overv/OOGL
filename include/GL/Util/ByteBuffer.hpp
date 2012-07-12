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

#ifndef OOGL_BYTEBUFFER_HPP
#define OOGL_BYTEBUFFER_HPP

#include <GL/Platform.hpp>
#include <vector>

namespace GL
{
	/*
		Byte reader
	*/
	class ByteReader
	{
	public:
		ByteReader( uint length, bool littleEndian ) : buffer( new uchar[length] ), length( length ), ptr( 0 ), littleEndian( littleEndian ) {}
		~ByteReader() { delete [] buffer; }

		uchar* Data() { return buffer; }

		void Advance( uint count ) { ptr += count; }
		void Move( uint location ) { ptr = location; }

		uchar PeekByte( uint offset = 0 ) { return buffer[ptr+offset]; }

		uchar ReadUbyte()
		{
			uchar val = buffer[ptr];
			ptr++;
			return val;
		}

		ushort ReadUshort()
		{
			ushort val;
			if ( littleEndian ) val = buffer[ptr+0] + ( buffer[ptr+1] << 8 );
			else val = buffer[ptr+1] + ( buffer[ptr+0] << 8 );
			ptr += 2;
			return val;
		}

		uint ReadUint()
		{
			uint val;
			if ( littleEndian ) val = buffer[ptr+0] + ( buffer[ptr+1] << 8 ) + ( buffer[ptr+2] << 16 ) + ( buffer[ptr+3] << 24 );
			else val = buffer[ptr+3] + ( buffer[ptr+2] << 8 ) + ( buffer[ptr+1] << 16 ) + ( buffer[ptr+0] << 24 );
			ptr += 4;
			return val;
		}

		int ReadInt()
		{
			uint val = ReadUint();
			if ( val <= INT_MAX )
				return val;
			else
				return INT_MIN + val - INT_MAX - 1;
		}

	private:
		uchar* buffer;
		uint length;
		uint ptr;
		bool littleEndian;
	};

	/*
		Byte writer
	*/
	class ByteWriter
	{
	public:
		ByteWriter( bool littleEndian ) : littleEndian( littleEndian ) {};

		uchar* Data() { return &buffer[0]; }
		uint Length() { return buffer.size(); }

		void Pad( uint count )
		{
			for ( uint i = 0; i < count; i++ )
				buffer.push_back( 0 );
		}

		void WriteUbyte( uchar val )
		{
			buffer.push_back( val );
		}
	
		void WriteUshort( ushort val )
		{
			if ( littleEndian ) {
				buffer.push_back( val & 0x00FF );
				buffer.push_back( ( val & 0xFF00 ) >> 8 );
			} else {
				buffer.push_back( ( val & 0xFF00 ) >> 8 );
				buffer.push_back( val & 0x00FF );
			}
		}

		void WriteUint( uint val )
		{
			if ( littleEndian ) {
				buffer.push_back( val & 0x000000FF );
				buffer.push_back( ( val & 0x0000FF00 ) >> 8 );
				buffer.push_back( ( val & 0x00FF0000 ) >> 16 );
				buffer.push_back( ( val & 0xFF000000 ) >> 24 );
			} else {
				buffer.push_back( ( val & 0xFF000000 ) >> 24 );
				buffer.push_back( ( val & 0x00FF0000 ) >> 16 );
				buffer.push_back( ( val & 0x0000FF00 ) >> 8 );
				buffer.push_back( val & 0x000000FF );
			}
		}

	private:
		std::vector<uchar> buffer;
		bool littleEndian;
	};
}

#endif