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
		obj = gc.Create( glCreateProgram(), glDeleteProgram );
	}

	Program::Program( const Program& other )
	{
		gc.Copy( other.obj, obj );
	}

	Program::Program( const Shader& vertex )
	{
		obj = gc.Create( glCreateProgram(), glDeleteProgram );
		Attach( vertex );
		Link();
		glUseProgram( obj );
	}

	Program::Program( const Shader& vertex, const Shader& fragment )
	{
		obj = gc.Create( glCreateProgram(), glDeleteProgram );
		Attach( vertex );
		Attach( fragment );
		Link();
		glUseProgram( obj );
	}

	Program::Program( const Shader& vertex, const Shader& fragment, const Shader& geometry )
	{
		obj = gc.Create( glCreateProgram(), glDeleteProgram );
		Attach( vertex );
		Attach( fragment );
		Attach( geometry );
		Link();
		glUseProgram( obj );
	}

	Program::~Program()
	{
		gc.Destroy( obj );
	}

	Program::operator GLuint() const
	{
		return obj;
	}

	const Program& Program::operator=( const Program& other )
	{
		gc.Copy( other.obj, obj, true );
		return *this;
	}

	void Program::Attach( const Shader& shader )
	{
		glAttachShader( obj, shader );
	}

	void Program::TransformFeedbackVaryings( const char** varyings, uint count )
	{
		glTransformFeedbackVaryings( obj, count, varyings, GL_INTERLEAVED_ATTRIBS );
	}

	void Program::Link()
	{
		GLint res;

		glLinkProgram( obj );
		glGetProgramiv( obj, GL_LINK_STATUS, &res );

		if ( res == GL_FALSE )
			throw LinkException( GetInfoLog() );
	}

	std::string Program::GetInfoLog()
	{
		GLint res;
		glGetProgramiv( obj, GL_INFO_LOG_LENGTH, &res );

		if ( res > 0 )
		{
			std::string infoLog( res, 0 );
			glGetProgramInfoLog( obj, res, &res, &infoLog[0] );
			return infoLog;
		} else {
			return "";
		}
	}

	Attribute Program::GetAttribute( const std::string& name )
	{
		return glGetAttribLocation( obj, name.c_str() );
	}

	Uniform Program::GetUniform( const std::string& name )
	{
		return glGetUniformLocation( obj, name.c_str() );
	}

	void Program::SetUniform( const Uniform& uniform, int value )
	{
		glUniform1i( uniform, value );
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

	void Program::SetUniform( const Uniform& uniform, const Vec4& value )
	{
		glUniform4f( uniform, value.X, value.Y, value.Z, value.W );
	}

	void Program::SetUniform( const Uniform& uniform, const float* values, uint count )
	{
		glUniform1fv( uniform, count, values );
	}

	void Program::SetUniform( const Uniform& uniform, const Vec2* values, uint count )
	{
		glUniform2fv( uniform, count, (float*)values );
	}

	void Program::SetUniform( const Uniform& uniform, const Vec3* values, uint count )
	{
		glUniform3fv( uniform, count, (float*)values );
	}

	void Program::SetUniform( const Uniform& uniform, const Vec4* values, uint count )
	{
		glUniform4fv( uniform, count, (float*)values );
	}

	void Program::SetUniform( const Uniform& uniform, const Mat3& value )
	{
		glUniformMatrix3fv( uniform, 1, GL_FALSE, value.m );
	}

	void Program::SetUniform( const Uniform& uniform, const Mat4& value )
	{
		glUniformMatrix4fv( uniform, 1, GL_FALSE, value.m );
	}

	GC Program::gc;
}