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

#include <GL/Math/Vec4.hpp>
#include <cmath>

namespace GL
{
	Vec4& Vec4::operator+=( const Vec4& v )
	{
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		W += v.W;
		return *this;
	}

	Vec4& Vec4::operator-=( const Vec4& v )
	{
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
		W -= v.W;
		return *this;
	}

	const Vec4 Vec4::operator+( const Vec4& v ) const
	{
		return Vec4( X + v.X, Y + v.Y, Z + v.Z, W + v.W );
	}

	const Vec4 Vec4::operator-( const Vec4& v ) const
	{
		return Vec4( X - v.X, Y - v.Y, Z - v.Z, W - v.W );
	}

	Vec4 operator*( const Vec4& v, float n )
	{
		return Vec4( v.X * n, v.Y * n, v.Z * n, v.W * n );
	}

	Vec4 operator*( float n, const Vec4& v )
	{
		return Vec4( v.X * n, v.Y * n, v.Z * n, v.W * n );
	}

	Vec4 operator/( const Vec4& v, float n )
	{
		return Vec4( v.X / n, v.Y / n, v.Z / n, v.W / n );
	}

	Vec4 operator/( float n, const Vec4& v )
	{
		return Vec4( v.X / n, v.Y / n, v.Z / n, v.W / n );
	}
}