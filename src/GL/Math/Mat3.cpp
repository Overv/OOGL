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

#include <GL/Math/Mat3.hpp>
#include <cmath>

namespace GL
{
	Mat3::Mat3()
	{
		*this = Mat3(
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		);
	}

	Mat3::Mat3( float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22 )
	{
		m[0] = v00; m[3] = v01; m[6] = v02; 
		m[1] = v10; m[4] = v11; m[7] = v12;
		m[2] = v20; m[5] = v21; m[8] = v22;
	}

	const Mat3 Mat3::operator*( const Mat3& mat )
	{
		return Mat3(
			mat.m[0]*m[0]+mat.m[1]*m[3]+mat.m[2]*m[6], mat.m[3]*m[0]+mat.m[4]*m[3]+mat.m[5]*m[6], mat.m[6]*m[0]+mat.m[7]*m[3]+mat.m[8]*m[6],
			mat.m[0]*m[1]+mat.m[1]*m[4]+mat.m[2]*m[7], mat.m[3]*m[1]+mat.m[4]*m[4]+mat.m[5]*m[7], mat.m[6]*m[1]+mat.m[7]*m[4]+mat.m[8]*m[7],
			mat.m[0]*m[2]+mat.m[1]*m[5]+mat.m[2]*m[8], mat.m[3]*m[2]+mat.m[4]*m[5]+mat.m[5]*m[8], mat.m[6]*m[2]+mat.m[7]*m[5]+mat.m[8]*m[8]
		);
	}

	const Vec2 Mat3::operator*( const Vec2& v )
	{
		return Vec2(
			m[0]*v.X + m[3]*v.Y + m[6],
			m[1]*v.X + m[4]*v.Y + m[7]
		);
	}

	Mat3& Mat3::Translate( const Vec2& v )
	{
		return *this = *this * Mat3(
			1, 0, v.X,
			0, 1, v.Y,
			0, 0, 1
		);
	}

	Mat3& Mat3::Scale( const Vec2& v )
	{
		return *this = *this * Mat3(
			v.X, 0, 0,
			0, v.Y, 0,
			0, 0, 1
		);
	}

	Mat3& Mat3::Rotation( float ang )
	{
		return *this = *this * Mat3(
			cos( ang ), -sin( ang ), 0,
			sin( ang ), cos( ang ), 0,
			0, 0, 1
		);
	}

	Mat3 Mat3::Transpose() const
	{
		Mat3 res;

		res.m[0] = m[0];
		res.m[1] = m[3];
		res.m[2] = m[6];

		res.m[3] = m[1];
		res.m[4] = m[4];
		res.m[5] = m[7];

		res.m[6] = m[2];
		res.m[7] = m[5];
		res.m[8] = m[8];

		return res;
	}

	float Mat3::Determinant() const
	{
		return m[0] * ( m[8] * m[4] - m[5] * m[7] ) + m[1] * ( -m[8] * m[3] + m[5] * m[6] ) + m[2] * ( m[7] * m[3] - m[4] * m[6] );
	}

	Mat3 Mat3::Inverse() const
	{
		float det = Determinant();

		Mat3 res;

		res.m[0] = ( m[8] * m[4] - m[5] * m[7] ) / det;
        res.m[1] = ( -m[8] * m[1] + m[2] * m[7] ) / det;
        res.m[2] = ( m[5] * m[1] - m[2] * m[4] ) / det;
        res.m[3] = ( -m[8] * m[3] + m[5] * m[6] ) / det;
        res.m[4] = ( m[8] * m[0] - m[2] * m[6] ) / det;
        res.m[5] = ( -m[5] * m[0] + m[2] * m[3] ) / det;
        res.m[6] = ( m[7] * m[3] - m[4] * m[6] ) / det;
        res.m[7] = ( -m[7] * m[0] + m[1] * m[6] ) / det;
        res.m[8] = ( m[4] * m[0] - m[1] * m[3] ) / det;

		return res;
	}
}