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

#include <GL/GL/Program.hpp>
#include <vector>

namespace GL
{
	Program::Program()
	{
		id = glCreateProgram();
	}

	Program::Program( const Shader& vertex, const Shader& fragment )
	{
		id = glCreateProgram();
		Attach( vertex );
		Attach( fragment );
		Link();
		glUseProgram( id );
	}

	Program::~Program()
	{
		glDeleteProgram( id );
	}

	Program::operator GLuint() const
	{
		return id;
	}

	void Program::Attach( const Shader& shader )
	{
		glAttachShader( id, shader );
	}

	void Program::Link()
	{
		GLint res;

		glLinkProgram( id );
		glGetProgramiv( id, GL_LINK_STATUS, &res );

		if ( res == GL_FALSE )
			throw LinkException( GetInfoLog() );
	}

	std::string Program::GetInfoLog()
	{
		GLint res;
		glGetProgramiv( id, GL_INFO_LOG_LENGTH, &res );

		if ( res > 0 )
		{
			std::vector<char> infoLog( res );
			glGetProgramInfoLog( id, res, &res, &infoLog[0] );

			return &infoLog[0];
		} else {
			return "";
		}
	}

	Attribute Program::GetAttribute( const std::string& name )
	{
		return glGetAttribLocation( id, name.c_str() );
	}

	Uniform Program::GetUniform( const std::string& name )
	{
		return glGetUniformLocation( id, name.c_str() );
	}

	void Program::SetUniform( const Uniform& uniform, float value )
	{
		glUniform1f( uniform, value );
	}

	void Program::SetUniform( const Uniform& uniform, const Vec2& value )
	{
		glUniform2f( uniform, value.X, value.Y );
	}

	void Program::SetUniform( const Uniform& uniform, const Vec3& value )
	{
		glUniform3f( uniform, value.X, value.Y, value.Z );
	}

	void Program::SetUniformMatrix( const Uniform& uniform, const Mat3& value )
	{
		glUniformMatrix3fv( uniform, 1, GL_FALSE, value.m );
	}

	void Program::SetUniformMatrix( const Uniform& uniform, const Mat4& value )
	{
		glUniformMatrix4fv( uniform, 1, GL_FALSE, value.m );
	}
}