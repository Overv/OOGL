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

#ifndef OOGL_CONTEXT_HPP
#define OOGL_CONTEXT_HPP

#include <GL/Platform.hpp>
#include <GL/GL/Program.hpp>
#include <GL/GL/VertexArray.hpp>
#include <GL/GL/Texture.hpp>
#include <GL/GL/Framebuffer.hpp>
#include <GL/Util/Color.hpp>
#include <exception>

// Xlib interference
#ifdef OOGL_PLATFORM_LINUX
#undef Always
#endif

namespace GL
{
	/*
		Buffer types
	*/
	namespace Buffer
	{
		enum buffer_t
		{
			Color = GL_COLOR_BUFFER_BIT,
			Depth = GL_DEPTH_BUFFER_BIT,
			Stencil = GL_STENCIL_BUFFER_BIT
		};

		inline buffer_t operator|( buffer_t lft, buffer_t rht )
		{
			return (buffer_t)( (int)lft | (int)rht );
		}
	}
	
	/*
		Drawing mode
	*/
	namespace Primitive
	{
		enum primitive_t
		{
			Triangles = GL_TRIANGLES,
			Lines = GL_LINES,
			Points = GL_POINTS,
		};
	}

	/*
		Capabilities to enable/disable
	*/
	namespace Capability
	{
		enum capability_t
		{
			DepthTest = GL_DEPTH_TEST,
			StencilTest = GL_STENCIL_TEST,
			CullFace = GL_CULL_FACE,
			RasterizerDiscard = GL_RASTERIZER_DISCARD
		};
	}

	/*
		Stencil test functions
	*/
	namespace TestFunction
	{
		enum test_function_t
		{
			Never = GL_NEVER,
			Less = GL_LESS,
			LessEqual = GL_LEQUAL,
			Greater = GL_GREATER,
			GreaterEqual = GL_GEQUAL,
			Equal = GL_EQUAL,
			NotEqual = GL_NOTEQUAL,
			Always = GL_ALWAYS
		};
	}

	/*
		Stencil operation
	*/
	namespace StencilAction
	{
		enum stencil_action_t
		{
			Keep = GL_KEEP,
			Zero = GL_ZERO,
			Replace = GL_REPLACE,
			Increase = GL_INCR,
			IncreaseWrap = GL_INCR_WRAP,
			Decrease = GL_DECR,
			DecreaseWrap = GL_DECR_WRAP,
			Invert = GL_INVERT
		};
	}

	/*
		Exceptions
	*/
	class VersionException : public std::exception 
	{
		virtual const char* what() const throw()
		{
			return "OpenGL 3.2 not supported!";
		}
	};
	class PixelFormatException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "No pixel format could be found with support for the specified buffer depths and anti-aliasing.";
		}
	};
	
	/*
		OpenGL context
	*/
	class Window;
	class Context
	{
	public:
		void Activate();
		
		void SetVerticalSync( bool enabled );

		void Enable( Capability::capability_t capability );
		void Disable( Capability::capability_t capability );

		void ClearColor( const Color& col );
		void Clear( Buffer::buffer_t buffers = Buffer::Color | Buffer::Depth );

		void DepthMask( bool writeEnabled );
		void StencilMask( bool writeEnabled );
		void StencilMask( uint mask );

		void StencilFunc( TestFunction::test_function_t function, int reference, uint mask = ~0 );
		void StencilOp( StencilAction::stencil_action_t fail, StencilAction::stencil_action_t zfail, StencilAction::stencil_action_t pass );

		void UseProgram( const Program& program );

		void BindTexture( const Texture& texture, uchar unit );
		
		void BindFramebuffer( const Framebuffer& framebuffer );
		void BindFramebuffer();

		void BeginTransformFeedback( Primitive::primitive_t mode );
		void EndTransformFeedback();

		void DrawArrays( const VertexArray& vao, Primitive::primitive_t mode, uint offset, uint vertices );
		void DrawElements( const VertexArray& vao, Primitive::primitive_t mode, intptr_t offset, uint count, uint type );

		float Time();

		static Context UseExistingContext();

		~Context();

	private:
		friend class Window;
		
		Context();

		bool owned;
		GLint defaultViewport[4];

#if defined( OOGL_PLATFORM_WINDOWS )
		Context( uchar color, uchar depth, uchar stencil, uint antialias, HDC dc );

		HDC dc;
		HGLRC context;

		LARGE_INTEGER timeOffset;
#elif defined( OOGL_PLATFORM_LINUX )
		Context( uchar color, uchar depth, uchar stencil, uint antialias, Display* display, int screen, ::Window window );

		GLXWindow glxWindow;
		GLXContext context;
		Display* display;
		::Window window;

		timeval timeOffset;
#endif
	};
}

#endif