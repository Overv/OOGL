#include <GL/OOGL.hpp>

int main()
{
    GL::Window window(800, 600, "OpenGL Window", GL::WindowStyle::Close);
    GL::Context& gl = window.GetContext();

	// Vertex shader
	GL::Shader vert( GL::ShaderType::Vertex, GLSL(
		in vec2 inPos;
		out vec2 outPos;
		void main() {
			outPos = inPos + vec2(0.1, 0.1);
		}
	));

	// Program
	const char* varyings[] = {"outPos"};
	GL::Program program;
	program.Attach(vert);
	program.TransformFeedbackVaryings(varyings, 1);
	program.Link();
	gl.UseProgram(program);

	// Vertex array
	GL::VertexArray vao;

	// Input
	float vertices[] = {
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f
	};
	GL::VertexBuffer inBuffer(vertices, sizeof(vertices), GL::BufferUsage::StaticDraw);
	vao.BindAttribute(0, inBuffer, GL::Type::Float, 2, 0, 0);

	// Output
	GL::VertexBuffer outBuffer(nullptr, sizeof(vertices), GL::BufferUsage::StaticDraw);
	vao.BindTransformFeedback(0, outBuffer);

	bool once = true;

    GL::Event ev;
    while (window.IsOpen())
    {
        while (window.GetEvent(ev));

		if (once) {
			gl.Enable(GL::Capability::RasterizerDiscard);

			gl.BeginTransformFeedback(GL::Primitive::Points);
				gl.DrawArrays(vao, GL::Primitive::Points, 0, 3);
			gl.EndTransformFeedback();
		
			gl.Disable(GL::Capability::RasterizerDiscard);

			float result[6];
			outBuffer.GetSubData(result, 0, sizeof(vertices));
			printf("%f, %f\n%f, %f\n%f, %f\n", result[0], result[1], result[2], result[3], result[4], result[5]);

			once = false;
		}

        window.Present();
    }

    return 0;
}
