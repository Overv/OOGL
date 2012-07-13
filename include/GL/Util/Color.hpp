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

#ifndef OOGL_COLOR_HPP
#define OOGL_COLOR_HPP

#include <GL/Platform.hpp>
#include <GL/Math/Vec3.hpp>
#include <GL/Math/Vec4.hpp>

namespace GL
{
	/*
		Color
	*/
	class Color
	{
	public:
		Color( uchar r = 0, uchar g = 0, uchar b = 0, uchar a = 255 ) : R( r ), G( g ), B( b ), A( a ) {}
		explicit Color( const Vec3& vec ) : R( (uchar)( 255 * vec.X ) ), G( (uchar)( 255 * vec.Y ) ), B( (uchar)( 255 * vec.Z ) ), A( 255 ) {}
		explicit Color( const Vec4& vec ) : R( (uchar)( 255 * vec.X ) ), G( (uchar)( 255 * vec.Y ) ), B( (uchar)( 255 * vec.Z ) ), A( (uchar)( 255 * vec.W ) ) {}
		
		inline Vec3 toVec3() const 
		{
			return Vec3(R / 255.0f, G / 255.0f, B / 255.0f);
		}

		inline Vec4 toVec4() const 
		{
			return Vec4(R / 255.0f, G / 255.0f, B / 255.0f, A / 255.0f);
		}


		uchar R, G, B, A;
	};
}

#endif