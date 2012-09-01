#include <GL/OOGL.hpp>
#include <cmath>

int main()
{
	GL::Window window( 800, 600, "Shadow mapping" );
	GL::Context& gl = window.GetContext( 24, 24, 0, 4 );

	// Setup scene drawing
	GL::Mesh sceneMesh( "scene.obj" );
	GL::VertexBuffer sceneBuffer( sceneMesh, GL::BufferUsage::StaticDraw, [] ( const GL::Vertex& v, GL::VertexDataBuffer& data )
	{
		data.Vec3( v.Pos );
		data.Vec3( v.Normal );
		data.Vec2( v.Tex );
	} );

	GL::Image sceneImage( "scene.png" );
	GL::Texture sceneTexture( sceneImage );

	// Setup light shader
	GL::Shader lightVert( GL::ShaderType::Vertex, GLSL(
		in vec3 pos;
		uniform mat4 trans;
		void main() {
			gl_Position = trans * vec4( pos, 1.0 );
		}
	) );
	GL::Shader lightFrag( GL::ShaderType::Fragment, GLSL(
		out vec4 outColor;
		void main() {
			outColor = vec4( 1.0, 1.0, 1.0, 1.0 );
		}
	) );
	GL::Program lightProgram( lightVert, lightFrag );

	GL::VertexArray lightVAO;
	lightVAO.BindAttribute( lightProgram.GetAttribute( "pos" ), sceneBuffer, GL::Type::Float, 3, sizeof(float) * 8, 0 );

	// Setup normal shader
	GL::Shader normalVert( GL::ShaderType::Vertex, GLSL(
		in vec3 pos;
		in vec3 normal;
		in vec2 texcoord;
		out vec3 Pos;
		out vec3 Normal;
		out vec2 Texcoord;
		uniform mat4 trans;
		void main() {
			Pos = pos;
			Normal = normal;
			Texcoord = texcoord;
			gl_Position = trans * vec4( pos, 1.0 );
		}
	) );
	GL::Shader normalFrag( GL::ShaderType::Fragment, GLSL(
		in vec3 Pos;
		in vec3 Normal;
		in vec2 Texcoord;
		out vec4 outColor;
		uniform sampler2D texCrate;
		uniform sampler2D texLight;
		uniform mat4 lightTrans;
		uniform vec3 lightPos;
		void main() {
			// Read depth from shadowmap
			vec4 lightCoord = lightTrans * vec4( Pos, 1.0 );
			lightCoord.xyz = lightCoord.xyz / lightCoord.w;
			lightCoord.x = ( lightCoord.x + 1.0 ) / 2.0;
			lightCoord.y = ( lightCoord.y + 1.0 ) / 2.0;
			lightCoord.z = ( lightCoord.z + 1.0 ) / 2.0;

			float lightDepth = texture( texLight, lightCoord.xy ).z;
			
			// Determine if fragment is in shadow or determine diffuse lighting
			float diffuse = max( dot( Normal, normalize( lightPos - Pos ) ), 0 ) * 0.8 + 0.2;

			if ( lightDepth < lightCoord.z - 0.0001 )
				outColor = texture( texCrate, Texcoord ) * 0.2;
			else
				outColor = texture( texCrate, Texcoord ) * diffuse;
		}
	));
	GL::Program normalProgram( normalVert, normalFrag );

	GL::VertexArray normalVAO;
	normalVAO.BindAttribute( normalProgram.GetAttribute( "pos" ), sceneBuffer, GL::Type::Float, 3, sizeof(float) * 8, 0 );
	normalVAO.BindAttribute( normalProgram.GetAttribute( "normal" ), sceneBuffer, GL::Type::Float, 3, sizeof(float) * 8, sizeof(float) * 3 );
	normalVAO.BindAttribute( normalProgram.GetAttribute( "texcoord" ), sceneBuffer, GL::Type::Float, 2, sizeof(float) * 8, sizeof(float) * 6 );

	normalProgram.SetUniform( normalProgram.GetUniform( "texCrate" ), 0 );
	normalProgram.SetUniform( normalProgram.GetUniform( "texLight" ), 1 );

	// Prepare rendering
	GL::Framebuffer lightFBO( 4096, 4096 );

	gl.BindTexture( sceneTexture, 0 );
	gl.BindTexture( lightFBO.GetDepthTexture(), 1 );

	gl.Enable( GL::Capability::DepthTest );
	gl.Enable( GL::Capability::CullFace );

	gl.ClearColor( GL::Color( 10, 10, 10 ) );

	float yaw = 0;
	float lastMouseX;
	bool mouseDown = false;

	GL::Event ev;
	while (window.IsOpen()) {
		// Allow user to rotate scene with mouse
		while ( window.GetEvent( ev ) ) {
			if ( ev.Type == GL::Event::KeyUp && ev.Key.Code == GL::Key::Escape ) {
				window.Close();
			} else if ( ev.Type == GL::Event::MouseDown ) {
				mouseDown = true;
			} else if ( ev.Type == GL::Event::MouseUp ) {
				mouseDown = false;
			} else if ( ev.Type == GL::Event::MouseMove ) {
				if ( mouseDown ) {
					yaw += ( ev.Mouse.X - lastMouseX ) / 100.0f;
				}
				lastMouseX = ev.Mouse.X;
			}
		}

		// Draw crate from light view
		gl.BindFramebuffer( lightFBO );
		gl.Clear();

		gl.UseProgram( lightProgram );

		GL::Vec3 lightPos( cos( gl.Time() ) * 5, sin( gl.Time() ) * 5, 5.5 );
		GL::Mat4 view = GL::Mat4::LookAt( lightPos, GL::Vec3( 0, 0, 0 ), GL::Vec3( 0, 0, 1 ) );
		GL::Mat4 proj = GL::Mat4::Perspective( GL::Rad( 45 ), 1.0, 1.0f, 10.0f );
		GL::Mat4 lightTrans = proj * view;
		lightProgram.SetUniform( lightProgram.GetUniform( "trans" ), lightTrans );
		
		gl.DrawArrays( lightVAO, GL::Primitive::Triangles, 0, sceneMesh.VertexCount() );

		// Draw crate from eye view
		gl.BindFramebuffer();
		gl.Clear();

		gl.UseProgram( normalProgram );

		view = GL::Mat4::LookAt( GL::Vec3( 4, 3.8, 3.2 ), GL::Vec3( 0, 0, -0.2 ), GL::Vec3( 0, 0, 1 ) );
		view.RotateZ( yaw );
		proj = GL::Mat4::Perspective( GL::Rad( 45 ), 4.0f/3.0f, 1.0f, 10.0f );
		normalProgram.SetUniform( normalProgram.GetUniform("trans"), proj * view );
		normalProgram.SetUniform( normalProgram.GetUniform("lightTrans"), lightTrans );
		normalProgram.SetUniform( normalProgram.GetUniform("lightPos"), lightPos );
		
		gl.DrawArrays( normalVAO, GL::Primitive::Triangles, 0, sceneMesh.VertexCount() );

		// Show result
		window.Present();
	}

	return 0;
}
