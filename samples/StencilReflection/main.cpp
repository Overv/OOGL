#include <GL/OOGL.hpp>

int main()
{
	GL::Window window( 800, 600, "OpenGL Window", GL::WindowStyle::Close );
	GL::Context& gl = window.GetContext( 24, 24, 8, 4 );
	gl.Enable( GL::Capability::DepthTest );

	// Shader
	GL::Shader vert( GL::ShaderType::Vertex, GLSL(
		in vec3 position;
		in vec2 coords;
		out vec2 Coords;
		uniform mat4 trans;
		void main() {
			Coords = coords;
			gl_Position = trans * vec4( position, 1.0 );
		}
	) );
	GL::Shader frag( GL::ShaderType::Fragment, GLSL(
		in vec2 Coords;
		out vec4 outColor;
		uniform sampler2D tex;
		uniform float transparency;
		void main()
		{
			outColor = transparency * texture( tex, Coords );
		}
	) );
	GL::Program program( vert, frag );

	// Load models
	GL::Mesh meshTank( "tank.obj" );
	GL::VertexBuffer vboTank( meshTank, GL::BufferUsage::StaticDraw, [] ( const GL::Vertex& v, GL::VertexDataBuffer& data )
	{
		data.Vec3( v.Pos );
		data.Vec2( v.Tex );
	} );

	GL::Mesh meshPlatform( "platform.obj" );
	GL::VertexBuffer vboPlatform( meshPlatform, GL::BufferUsage::StaticDraw, [] ( const GL::Vertex& v, GL::VertexDataBuffer& data )
	{
		data.Vec3( v.Pos );
		data.Vec2( v.Tex );
	} );

	// Load textures
	GL::Image imTank( "tank.jpg" );
	GL::Image imPlatform( "platform.png" );
	GL::Texture texTank( imTank );
	GL::Texture texPlatform( imPlatform );
	gl.BindTexture( texTank, 0 );
	gl.BindTexture( texPlatform, 1 );

	// VAOs
	GL::VertexArray vaoTank;
	vaoTank.BindAttribute( program.GetAttribute( "position" ), vboTank, GL::Type::Float, 3, 5 * sizeof( float ), 0 );
	vaoTank.BindAttribute( program.GetAttribute( "coords" ), vboTank, GL::Type::Float, 2, 5 * sizeof( float ), 3 * sizeof( float ) );

	GL::VertexArray vaoPlatform;
	vaoPlatform.BindAttribute( program.GetAttribute( "position" ), vboPlatform, GL::Type::Float, 3, 5 * sizeof( float ), 0 );
	vaoPlatform.BindAttribute( program.GetAttribute( "coords" ), vboPlatform, GL::Type::Float, 2, 5 * sizeof( float ), 3 * sizeof( float ) );
	
	// Transformation
	GL::Mat4 view = GL::Mat4::LookAt( GL::Vec3( 160, 160, 120 ), GL::Vec3( 0, 0, 50 ), GL::Vec3( 0, 0, 1 ) );
	GL::Mat4 proj = GL::Mat4::Perspective( GL::Rad( 60 ), 800.0f / 600.0f, 0.1f, 1000.0f );

	// Main loop
	GL::Event ev;
	while ( window.IsOpen() )
	{
		while ( window.GetEvent( ev ) )
        {
            if( ev.Type == GL::Event::KeyDown && ev.Key.Code == GL::Key::Escape )
            {
                window.Close();
            }
        }

		gl.ClearColor( GL::Color( 255, 255, 255, 255 ) );

		// Set up transformations
		GL::Mat4 model;
		model.RotateZ( gl.Time() );
		program.SetUniform( program.GetUniform( "trans" ), proj * view * model );

		// Draw normal tank
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		program.SetUniform( program.GetUniform( "tex" ), 0 );
		program.SetUniform( program.GetUniform( "transparency" ), 1.0f );
		gl.DrawArrays( vaoTank, GL::Primitive::Triangles, 0, meshTank.VertexCount() );

		// Draw platform
		gl.Enable( GL::Capability::StencilTest );
		gl.DepthMask( false );
		gl.StencilFunc( GL::TestFunction::Always, 1 );
		gl.StencilOp( GL::StencilAction::Keep, GL::StencilAction::Keep, GL::StencilAction::Replace );
		gl.StencilMask( true );
		gl.Clear( GL::Buffer::Stencil );

		program.SetUniform( program.GetUniform( "tex" ), 1 );
		program.SetUniform( program.GetUniform( "transparency" ), 1.0f );
		gl.DrawArrays( vaoPlatform, GL::Primitive::Triangles, 0, meshPlatform.VertexCount() );
		
		// Draw upside down tank
		model.Scale( GL::Vec3( 1, 1, -1 ) );
		program.SetUniform( program.GetUniform( "trans" ), proj * view * model );

		gl.DepthMask( true );
		gl.StencilMask( false );
		gl.StencilFunc( GL::TestFunction::Equal, 1 );

		program.SetUniform( program.GetUniform( "tex" ), 0 );
		program.SetUniform( program.GetUniform( "transparency" ), 0.4f );
		gl.DrawArrays( vaoTank, GL::Primitive::Triangles, 0, meshTank.VertexCount() );

		gl.Disable( GL::Capability::StencilTest );
		
		window.Present();
	}

    return 0;
}
