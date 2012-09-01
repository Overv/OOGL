#include <GL/OOGL.hpp>

int main()
{
    GL::Window window( 800, 600, "OpenGL Window", GL::WindowStyle::Close );
    GL::Context& gl = window.GetContext();

    GL::Shader vert( GL::ShaderType::Vertex, "#version 150\nin vec2 position; void main() { gl_Position = vec4( position, 0.0, 1.0 ); }" );
    GL::Shader frag( GL::ShaderType::Fragment, "#version 150\nout vec4 outColor; void main() { outColor = vec4( 1.0, 0.0, 0.0, 1.0 ); }" );
    GL::Program program( vert, frag );

    float vertices[] = {
        -0.5f,  0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f
    };
    GL::VertexBuffer vbo( vertices, sizeof( vertices ), GL::BufferUsage::StaticDraw );

    GL::VertexArray vao;
    vao.BindAttribute( program.GetAttribute( "position" ), vbo, GL::Type::Float, 2, 0, 0 );

    GL::Event ev;
    while ( window.IsOpen() )
    {
        while ( window.GetEvent( ev ) );

        gl.Clear();

        gl.DrawArrays( vao, GL::Primitive::Triangles, 0, 3 );

        window.Present();
    }

    return 0;
}
