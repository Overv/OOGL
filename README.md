# OOGL

OOGL (Object-oriented OpenGL) is a C++ library that wraps the functionality of the OpenGL API in a more object-oriented package. It additionally includes various classes and functions for 3D math, loading models and textures and creating a window and OpenGL context.

**Disclaimer:** This library is currently not ready to be used in a real project.

## Sample

	#include <GL/OOGL.hpp>
	#include <ctime>
	 
	int main()
	{
		GL::Window window( 800, 600, "OpenGL Window", GL::WindowStyle::Close );
		GL::Context& gl = window.GetContext();
		gl.SetVerticalSync( false );

		GL::Shader vert( GL::ShaderType::Vertex, "#version 150\nin vec2 position; void main() { gl_Position = vec4( position, 0.0, 1.0 ); }" );
		GL::Shader frag( GL::ShaderType::Fragment, "#version 150\nout vec4 outColor; uniform float red; void main() { outColor = vec4( red, 0.0, 0.0, 1.0 ); }" );
		GL::Program program( vert, frag );

		float vertices[] = {
			 0.0f,  0.5f,
			 0.5f, -0.5f,
			-0.5f, -0.5f
		};
		GL::VertexBuffer vbo( vertices, sizeof( vertices ), GL::BufferUsage::StaticDraw );
		
		GL::VertexArray vao;
		vao.BindAttribute( program.GetAttribute( "position" ), vbo, GL::Type::Float, 2, 0, 0 );

		GL::Event ev;
		while ( window.IsOpen() )
		{
			while ( window.GetEvent( ev ) );

			gl.Clear();
			
			program.SetUniform( program.GetUniform( "red" ), sin( clock() / 200.0f ) * 0.5f + 0.5f );
			gl.DrawArrays( vao, GL::Primitive::Triangle, 0, 3 );

			window.Present();
		}

		return 0;
	}

To compile after building OOGL:

	g++ main.cpp -o main -I OOGL/include OOGL/bin/OOGL.a -lX11 -lXrandr -lGL

## License

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