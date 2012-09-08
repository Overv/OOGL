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

#include <GL/GL/Context.hpp>
#include <GL/GL/Extensions.hpp>

namespace GL
{
	void Context::Enable( Capability::capability_t capability )
	{
		glEnable( capability );
	}

	void Context::Disable( Capability::capability_t capability )
	{
		glDisable( capability );
	}

	void Context::ClearColor( const Color& col )
	{
		glClearColor( col.R / 255.0f, col.G / 255.0f, col.B / 255.0f, col.A / 255.0f );
	}

	void Context::Clear( Buffer::buffer_t buffers )
	{
		glClear( buffers );
	}

	void Context::DepthMask( bool writeEnabled )
	{
		glDepthMask( writeEnabled ? GL_TRUE : GL_FALSE );
	}

	void Context::StencilMask( bool writeEnabled )
	{
		glStencilMask( writeEnabled ? ~0 : 0 );
	}

	void Context::StencilMask( uint mask )
	{
		glStencilMask( mask );
	}

	void Context::StencilFunc( TestFunction::test_function_t function, int reference, uint mask )
	{
		glStencilFunc( function, reference, mask );
	}

	void Context::StencilOp( StencilAction::stencil_action_t fail, StencilAction::stencil_action_t zfail, StencilAction::stencil_action_t pass )
	{
		glStencilOp( fail, zfail, pass );
	}

	void Context::UseProgram( const Program& program )
	{
		glUseProgram( program );
	}

	void Context::BindTexture( const Texture& texture, uchar unit )
	{
		glActiveTexture( GL_TEXTURE0 + unit );
		glBindTexture( GL_TEXTURE_2D, texture );
	}

	void Context::BindFramebuffer( const Framebuffer& framebuffer )
	{
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, framebuffer );
		
		// Set viewport to frame buffer size
		GLint obj, width, height;
		glGetFramebufferAttachmentParameteriv( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &obj );

		GLint res; glGetIntegerv( GL_TEXTURE_BINDING_2D, &res );
			glBindTexture( GL_TEXTURE_2D, obj );
			glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width );
			glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height );
		glBindTexture( GL_TEXTURE_2D, res );

		glViewport( 0, 0, width, height );
	}

	void Context::BindFramebuffer()
	{
		glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

		// Set viewport to default frame buffer size
		glViewport( defaultViewport[0], defaultViewport[1], defaultViewport[2], defaultViewport[3] );
	}

	void Context::BeginTransformFeedback( Primitive::primitive_t mode )
	{
		glBeginTransformFeedback( mode );
	}

	void Context::EndTransformFeedback()
	{
		glEndTransformFeedback();
	}

	void Context::DrawArrays( const VertexArray& vao, Primitive::primitive_t mode, uint offset, uint vertices )
	{
		glBindVertexArray( vao );
		glDrawArrays( mode, offset, vertices );
	}

	void Context::DrawElements( const VertexArray& vao, Primitive::primitive_t mode, intptr_t offset, uint count, uint type )
	{
		glBindVertexArray( vao );
		glDrawElements( mode, count, type, (const GLvoid*)offset );
	}

	Context Context::UseExistingContext()
	{
		return Context();
	}
}