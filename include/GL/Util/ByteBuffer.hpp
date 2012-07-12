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

namespace GL
{
	/*
		Byte buffer
	*/
	class ByteBuffer
	{
	public:
		ByteBuffer( uint length ) : buffer( new uchar[length] ), length( length ), ptr( 0 ), littleEndian( true ) {}
		~ByteBuffer() { delete [] buffer; }

		uchar* Data() { return buffer; }

		void SetEndianness( bool littleEndian ) { this->littleEndian = littleEndian; };

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
			if ( littleEndian ) val = buffer[ptr+0] + buffer[ptr+1]*256;
			else val = buffer[ptr+1] + buffer[ptr+0]*256;
			ptr += 2;
			return val;
		}

		uint ReadUint()
		{
			uint val;
			if ( littleEndian ) val = buffer[ptr+0] + buffer[ptr+1]*256 + buffer[ptr+2]*65536 + buffer[ptr+3]*16777216;
			else val = buffer[ptr+3] + buffer[ptr+2]*256 + buffer[ptr+1]*65536 + buffer[ptr+0]*16777216;
			ptr += 4;
			return val;
		}

		int ReadInt()
		{
			int val;
			if ( littleEndian ) val = buffer[ptr+0] + buffer[ptr+1]*256 + buffer[ptr+2]*65536 + buffer[ptr+3]*16777216;
			else val = buffer[ptr+3] + buffer[ptr+2]*256 + buffer[ptr+1]*65536 + buffer[ptr+0]*16777216;
			ptr += 4;
			return val;
		}

	private:
		uchar* buffer;
		uint length;
		uint ptr;
		bool littleEndian;
	};
}

#endif