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

#include <GL/Math/Mat4.hpp>
#include <cmath>

namespace GL
{
	Mat4::Mat4()
	{
		*this = Mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	Mat4::Mat4( float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20, float v21, float v22, float v23, float v30, float v31, float v32, float v33 )
	{
		m[0] = v00; m[4] = v01; m[8]  = v02; m[12] = v03;
		m[1] = v10; m[5] = v11; m[9]  = v12; m[13] = v13;
		m[2] = v20; m[6] = v21; m[10] = v22; m[14] = v23;
		m[3] = v30; m[7] = v31; m[11] = v32; m[15] = v33;
	}

	const Mat4 Mat4::operator*( const Mat4& mat )
	{
		return Mat4(
			m[0]*mat.m[0]+m[4]*mat.m[1]+m[8]*mat.m[2]+m[12]*mat.m[3], m[0]*mat.m[4]+m[4]*mat.m[5]+m[8]*mat.m[6]+m[12]*mat.m[7], m[0]*mat.m[8]+m[4]*mat.m[9]+m[8]*mat.m[10]+m[12]*mat.m[11], m[0]*mat.m[12]+m[4]*mat.m[13]+m[8]*mat.m[14]+m[12]*mat.m[15],
			m[1]*mat.m[0]+m[5]*mat.m[1]+m[9]*mat.m[2]+m[13]*mat.m[3], m[1]*mat.m[4]+m[5]*mat.m[5]+m[9]*mat.m[6]+m[13]*mat.m[7], m[1]*mat.m[8]+m[5]*mat.m[9]+m[9]*mat.m[10]+m[13]*mat.m[11], m[1]*mat.m[12]+m[5]*mat.m[13]+m[9]*mat.m[14]+m[13]*mat.m[15],
			m[2]*mat.m[0]+m[6]*mat.m[1]+m[10]*mat.m[2]+m[14]*mat.m[3], m[2]*mat.m[4]+m[6]*mat.m[5]+m[10]*mat.m[6]+m[14]*mat.m[7], m[2]*mat.m[8]+m[6]*mat.m[9]+m[10]*mat.m[10]+m[14]*mat.m[11], m[2]*mat.m[12]+m[6]*mat.m[13]+m[10]*mat.m[14]+m[14]*mat.m[15],
			m[3]*mat.m[0]+m[7]*mat.m[1]+m[11]*mat.m[2]+m[15]*mat.m[3], m[3]*mat.m[4]+m[7]*mat.m[5]+m[11]*mat.m[6]+m[15]*mat.m[7], m[3]*mat.m[8]+m[7]*mat.m[9]+m[11]*mat.m[10]+m[15]*mat.m[11], m[3]*mat.m[12]+m[7]*mat.m[13]+m[11]*mat.m[14]+m[15]*mat.m[15]
		);
	}

	const Vec3 Mat4::operator*( const Vec3& v )
	{
		return Vec3(
			m[0]*v.X + m[4]*v.Y + m[8]*v.Z + m[12],
			m[1]*v.X + m[5]*v.Y + m[9]*v.Z + m[13],
			m[2]*v.X + m[6]*v.Y + m[10]*v.Z + m[14]
		);
	}

	Mat4& Mat4::Translate( const Vec3& v )
	{
		return *this = *this * Mat4(
			1, 0, 0, v.X,
			0, 1, 0, v.Y,
			0, 0, 1, v.Z,
			0, 0, 0, 1
		);
	}

	Mat4& Mat4::Scale( const Vec3& v )
	{
		return *this = *this * Mat4(
			v.X, 0, 0, 0,
			0, v.Y, 0, 0,
			0, 0, v.Z, 0,
			0, 0, 0, 1
		);
	}

	Mat4& Mat4::RotateX( float ang )
	{
		return *this = *this * Mat4(
			1, 0, 0, 0,
			0, cos( ang ), -sin( ang ), 0,
			0, sin( ang ), cos( ang ), 0,
			0, 0, 0, 1
		);
	}

	Mat4& Mat4::RotateY( float ang )
	{
		return *this = *this * Mat4(
			cos( ang ), 0, sin( ang ), 0,
			0, 1, 0, 0,
			-sin( ang ), 0, cos( ang ), 0,
			0, 0, 0, 1
		);
	}

	Mat4& Mat4::RotateZ( float ang )
	{
		return *this = *this * Mat4(
			cos( ang ), -sin( ang ), 0, 0,
			sin( ang ), cos( ang ), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}
}