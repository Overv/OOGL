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

#include <GL/Math/Vec3.hpp>
#include <cmath>

namespace GL
{
	Vec3& Vec3::operator+=( const Vec3& v )
	{
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		return *this;
	}

	Vec3& Vec3::operator-=( const Vec3& v )
	{
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
		return *this;
	}

	const Vec3 Vec3::operator+( const Vec3& v ) const
	{
		return Vec3( X + v.X, Y + v.Y, Z + v.Z );
	}

	const Vec3 Vec3::operator-( const Vec3& v ) const
	{
		return Vec3( X - v.X, Y - v.Y, Z - v.Z );
	}

	Vec3 operator*( const Vec3& v, float n )
	{
		return Vec3( v.X * n, v.Y * n, v.Z * n );
	}

	Vec3 operator*( float n, const Vec3& v )
	{
		return Vec3( v.X * n, v.Y * n, v.Z * n );
	}

	Vec3 operator/( const Vec3& v, float n )
	{
		return Vec3( v.X / n, v.Y / n, v.Z / n );
	}

	Vec3 operator/( float n, const Vec3& v )
	{
		return Vec3( v.X / n, v.Y / n, v.Z / n );
	}

	const Vec3 Vec3::Cross( const Vec3& v ) const
	{
		return Vec3( Y*v.Z - Z*v.Y, Z*v.X - X*v.Z, X*v.Y - Y*v.X );
	}

	float Vec3::Dot( const Vec3& v ) const
	{
		return X * v.X + Y * v.Y + Z * v.Z;
	}

	float Vec3::Angle( const Vec3& v ) const
	{
		return acos( Dot( v ) / Length() / v.Length() );
	}

	float Vec3::LengthSqr() const
	{
		return X*X + Y*Y + Z*Z;
	}

	float Vec3::Length() const
	{
		return sqrt( X*X + Y*Y + Z*Z );
	}

	float Vec3::Distance( const Vec3& v ) const
	{
		return ( *this - v ).Length();
	}

	const Vec3 Vec3::Normal() const
	{
		return *this / Length();
	}
}