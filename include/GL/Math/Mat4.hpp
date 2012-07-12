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

#ifndef OOGL_MAT4_HPP
#define OOGL_MAT4_HPP

#include <GL/Math/Vec3.hpp>
#include <GL/Math/Vec4.hpp>

namespace GL
{
	/*
		4-by-4 Matrix
	*/
	class Mat4
	{
	public:
		Mat4();
		Mat4(
			float v00, float v01, float v02, float v03,
			float v10, float v11, float v12, float v13,
			float v20, float v21, float v22, float v23,
			float v30, float v31, float v32, float v33
		);

		const Mat4 operator*( const Mat4& mat ) const;
		const Vec3 operator*( const Vec3& v ) const;
		const Vec4 operator*( const Vec4& v ) const;

		Mat4& Translate( const Vec3& v );
		Mat4& Scale( const Vec3& v );

		Mat4& RotateX( float ang );
		Mat4& RotateY( float ang );
		Mat4& RotateZ( float ang );
		Mat4& Rotate( const Vec3& axis, float ang );

		Mat4 Transpose() const;

		// The implementations of the functions below are based on the awesome
		// glMatrix library developed by Brandon Jones and Colin MacKenzie IV

		float Determinant() const;
		Mat4 Inverse() const;

		static Mat4 Frustum( float left, float right, float bottom, float top, float near, float far );
		static Mat4 Perspective( float fovy, float aspect, float near, float far );
		static Mat4 Ortho( float left, float right, float bottom, float top, float near, float far );
		static Mat4 LookAt( const Vec3& eye, const Vec3& center, const Vec3& up );

		static Vec3 UnProject( const Vec3& vec, const Mat4& view, const Mat4& proj, const float viewport[] );
		static Vec3 Project( const Vec3& vec, const Mat4& view, const Mat4& proj, const float viewport[] );
		
		float m[16];
	};
}

#endif