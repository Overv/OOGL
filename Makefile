# Parameters

CC = g++
CCFLAGS = -O3 -Wall -Wextra -Werror

# Final library

bin/OOGL.a: bin/Mat3.o bin/Mat4.o bin/Vec2.o bin/Vec3.o bin/Window.o bin/Window_X11.o bin/Extensions.o bin/Context.o bin/Context_X11.o bin/Shader.o bin/Program.o bin/VertexBuffer.o bin/VertexArray.o
	ar rcs bin/OOGL.a bin/Mat3.o bin/Mat4.o bin/Vec2.o bin/Vec3.o bin/Window.o bin/Window_X11.o bin/Extensions.o bin/Context.o bin/Context_X11.o bin/Shader.o bin/Program.o bin/VertexBuffer.o bin/VertexArray.o

# 3D Math

bin/Mat3.o: src/GL/Math/Mat3.cpp
	$(CC) $(CCFLAGS) -c src/GL/Math/Mat3.cpp -o bin/Mat3.o -I include

bin/Mat4.o: src/GL/Math/Mat4.cpp
	$(CC) $(CCFLAGS) -c src/GL/Math/Mat4.cpp -o bin/Mat4.o -I include

bin/Vec2.o: src/GL/Math/Vec2.cpp
	$(CC) $(CCFLAGS) -c src/GL/Math/Vec2.cpp -o bin/Vec2.o -I include

bin/Vec3.o: src/GL/Math/Vec3.cpp
	$(CC) $(CCFLAGS) -c src/GL/Math/Vec3.cpp -o bin/Vec3.o -I include

# Window

bin/Window.o: src/GL/Window/Window.cpp
	$(CC) $(CCFLAGS) -c src/GL/Window/Window.cpp -o bin/Window.o -I include

bin/Window_X11.o: src/GL/Window/Window_X11.cpp
	$(CC) $(CCFLAGS) -c src/GL/Window/Window_X11.cpp -o bin/Window_X11.o -I include

# OpenGL

bin/Extensions.o: src/GL/GL/Extensions.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Extensions.cpp -o bin/Extensions.o -I include

bin/Context.o: src/GL/GL/Context.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Context.cpp -o bin/Context.o -I include

bin/Context_X11.o: src/GL/GL/Context_X11.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Context_X11.cpp -o bin/Context_X11.o -I include

bin/Shader.o: src/GL/GL/Shader.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Shader.cpp -o bin/Shader.o -I include

bin/Program.o: src/GL/GL/Program.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Program.cpp -o bin/Program.o -I include

bin/VertexBuffer.o: src/GL/GL/VertexBuffer.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/VertexBuffer.cpp -o bin/VertexBuffer.o -I include

bin/VertexArray.o: src/GL/GL/VertexArray.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/VertexArray.cpp -o bin/VertexArray.o -I include


# Clean
clean:
	rm -rf bin/*
