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

#ifndef OOGL_VEC2_HPP
#define OOGL_VEC2_HPP

namespace GL
{
	/*
		2D vector
	*/
	class Vec2
	{
	public:
		Vec2( float x = 0.0f, float y = 0.0f ) : X( x ), Y( y ) {}

		Vec2& operator+=( const Vec2& v );
		Vec2& operator-=( const Vec2& v );

		const Vec2 operator+( const Vec2& v ) const;
		const Vec2 operator-( const Vec2& v ) const;

		friend Vec2 operator*( const Vec2& v, float n );
		friend Vec2 operator*( float n, const Vec2& v );

		friend Vec2 operator/( const Vec2& v, float n );
		friend Vec2 operator/( float n, const Vec2& v );

		float Dot( const Vec2& v ) const;
		float Angle( const Vec2& v ) const;

		float LengthSqr() const;
		float Length() const;
		float Distance( const Vec2& v ) const;

		const Vec2 Normal() const;

		float X, Y;
	};
}

#endif