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

#ifndef OOGL_PROGRAM_HPP
#define OOGL_PROGRAM_HPP

#include <GL/Platform.hpp>
#include <GL/GL/GC.hpp>
#include <GL/GL/Extensions.hpp>
#include <GL/GL/Shader.hpp>
#include <GL/Math/Mat3.hpp>
#include <GL/Math/Mat4.hpp>
#include <exception>
#include <string>

namespace GL
{
	/*
		Exceptions
	*/
	class LinkException : public std::exception 
	{
	public:
		LinkException( const std::string& str ) throw() : infoLog( str ) {}
		~LinkException() throw() {}

		virtual const char* what() const throw()
		{
			return infoLog.c_str();
		}

	private:
		std::string infoLog;
	};

	/*
		Program
	*/
	class Program
	{
	public:
		Program();
		Program( const Program& program );
		Program( const Shader& vertex );
		Program( const Shader& vertex, const Shader& fragment );
		Program( const Shader& vertex, const Shader& fragment, const Shader& geometry );

		~Program();

		operator GLuint() const;
		const Program& operator=( const Program& other );

		void Attach( const Shader& shader );
		void TransformFeedbackVaryings( const char** varyings, uint count );
		void Link();

		std::string GetInfoLog();

		Attribute GetAttribute( const std::string& name );
		Uniform GetUniform( const std::string& name );

		void SetUniform( const Uniform& uniform, int value );
		void SetUniform( const Uniform& uniform, float value );
		void SetUniform( const Uniform& uniform, const Vec2& value );
		void SetUniform( const Uniform& uniform, const Vec3& value );
		void SetUniform( const Uniform& uniform, const Vec4& value );
		void SetUniform( const Uniform& uniform, const float* values, uint count );
		void SetUniform( const Uniform& uniform, const Vec2* values, uint count );
		void SetUniform( const Uniform& uniform, const Vec3* values, uint count );
		void SetUniform( const Uniform& uniform, const Vec4* values, uint count );
		void SetUniform( const Uniform& uniform, const Mat3& value );
		void SetUniform( const Uniform& uniform, const Mat4& value );

	private:
		static GC gc;
		GLuint obj;
	};
}

#endif