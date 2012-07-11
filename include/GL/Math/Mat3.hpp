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

#ifndef OOGL_MAT3_HPP
#define OOGL_MAT3_HPP

#include <GL/Math/Vec2.hpp>

namespace GL
{
	/*
		3-by-3 Matrix
	*/
	class Mat3
	{
	public:
		Mat3();
		Mat3(
			float v00, float v01, float v02,
			float v10, float v11, float v12,
			float v20, float v21, float v22
		);

		const Mat3 operator*( const Mat3& mat );
		const Vec2 operator*( const Vec2& v );

		Mat3& Translate( const Vec2& v );
		Mat3& Scale( const Vec2& v );
		Mat3& Rotation( float ang );

		Mat3 Transpose() const;

		float Determinant() const;
		Mat3 Inverse() const;
		
		float m[9];
	};
}

#endif