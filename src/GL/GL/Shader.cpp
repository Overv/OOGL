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

#include <GL/GL/Shader.hpp>
#include <vector>

namespace GL
{
	Shader::Shader( uint shader )
	{
		id = glCreateShader( shader );
	}

	Shader::Shader( uint shader, const std::string& code )
	{
		id = glCreateShader( shader );
		Source( code );
		Compile();
	}

	Shader::~Shader()
	{
		glDeleteShader( id );
	}

	Shader::operator GLuint() const
	{
		return id;
	}

	void Shader::Source( const std::string& code )
	{
		const char* c = code.c_str();
		glShaderSource( id, 1, &c, NULL );
	}

	void Shader::Compile()
	{
		GLint res;

		glCompileShader( id );
		glGetShaderiv( id, GL_COMPILE_STATUS, &res );

		if ( res == GL_FALSE )
			throw CompileException( GetInfoLog() );
	}

	std::string Shader::GetInfoLog()
	{
		GLint res;
		glGetShaderiv( id, GL_INFO_LOG_LENGTH, &res );

		if ( res > 0 )
		{
			std::vector<char> infoLog( res );
			glGetShaderInfoLog( id, res, &res, &infoLog[0] );

			return &infoLog[0];
		} else {
			return "";
		}
	}
}