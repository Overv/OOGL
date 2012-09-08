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

#ifndef OOGL_SHADER_HPP
#define OOGL_SHADER_HPP

#include <GL/Platform.hpp>
#include <GL/GL/GC.hpp>
#include <GL/GL/Extensions.hpp>
#include <exception>
#include <string>

#define GLSL( x ) "#version 150\n" #x

namespace GL
{
	/*
		Shader type
	*/
	namespace ShaderType
	{
		enum shader_type_t 
		{
			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER,
			Geometry = GL_GEOMETRY_SHADER
		};
	}

	/*
		Exceptions
	*/
	class CompileException : public std::exception 
	{
	public:
		CompileException( const std::string& str ) throw() : infoLog( str ) {}
		~CompileException() throw() {}

		virtual const char* what() const throw()
		{
			return infoLog.c_str();
		}

	private:
		std::string infoLog;
	};

	/*
		Shader
	*/
	class Shader
	{
	public:
		Shader( const Shader& other );
		Shader( ShaderType::shader_type_t type );
		Shader( ShaderType::shader_type_t type, const std::string& code );

		~Shader();

		operator GLuint() const;
		const Shader& operator=( const Shader& other );

		void Source( const std::string& code );
		void Compile();

		std::string GetInfoLog();

	private:
		static GC gc;
		GLuint obj;
	};
}

#endif