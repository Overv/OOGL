# Parameters

CC = g++
CCC = gcc
CCFLAGS = -O3 -Wall -Wextra -Werror -std=c++0x

# Final library

libjpeg = $(patsubst src/GL/Util/libjpeg/%.c,lib/%.o,$(wildcard src/GL/Util/libjpeg/*.c))
libpng = $(patsubst src/GL/Util/libpng/%.c,lib/%.o,$(wildcard src/GL/Util/libpng/*.c))
zlib = $(patsubst src/GL/Util/zlib/%.c,lib/%.o,$(wildcard src/GL/Util/zlib/*.c))

lib/OOGL.a: lib lib/Mat3.o lib/Mat4.o lib/Vec2.o lib/Vec3.o lib/Vec4.o lib/Window.o lib/Window_X11.o lib/Extensions.o lib/Context.o lib/Context_X11.o lib/Shader.o lib/Program.o lib/VertexBuffer.o lib/VertexArray.o lib/Texture.o lib/Renderbuffer.o lib/Framebuffer.o lib/Image.o lib/Mesh.o $(libjpeg) $(libpng) $(zlib)
	ar rcs lib/OOGL.a lib/Mat3.o lib/Mat4.o lib/Vec2.o lib/Vec3.o lib/Vec4.o lib/Window.o lib/Window_X11.o lib/Extensions.o lib/Context.o lib/Context_X11.o lib/Shader.o lib/Program.o lib/VertexBuffer.o lib/VertexArray.o lib/Texture.o lib/Renderbuffer.o lib/Framebuffer.o lib/Image.o lib/Mesh.o $(libjpeg) $(libpng) $(zlib)

# 3D Math

lib/Mat3.o: src/GL/Math/Mat3.cpp
	$(CC) $(CCFLAGS) -c src/GL/Math/Mat3.cpp -o lib/Mat3.o -I include

lib/Mat4.o: src/GL/Math/Mat4.cpp
	$(CC) $(CCFLAGS) -c src/GL/Math/Mat4.cpp -o lib/Mat4.o -I include

lib/Vec2.o: src/GL/Math/Vec2.cpp
	$(CC) $(CCFLAGS) -c src/GL/Math/Vec2.cpp -o lib/Vec2.o -I include

lib/Vec3.o: src/GL/Math/Vec3.cpp
	$(CC) $(CCFLAGS) -c src/GL/Math/Vec3.cpp -o lib/Vec3.o -I include

lib/Vec4.o: src/GL/Math/Vec4.cpp
	$(CC) $(CCFLAGS) -c src/GL/Math/Vec4.cpp -o lib/Vec4.o -I include

# Window

lib/Window.o: src/GL/Window/Window.cpp
	$(CC) $(CCFLAGS) -c src/GL/Window/Window.cpp -o lib/Window.o -I include

lib/Window_X11.o: src/GL/Window/Window_X11.cpp
	$(CC) $(CCFLAGS) -c src/GL/Window/Window_X11.cpp -o lib/Window_X11.o -I include

# OpenGL

lib/Extensions.o: src/GL/GL/Extensions.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Extensions.cpp -o lib/Extensions.o -I include

lib/Context.o: src/GL/GL/Context.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Context.cpp -o lib/Context.o -I include

lib/Context_X11.o: src/GL/GL/Context_X11.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Context_X11.cpp -o lib/Context_X11.o -I include

lib/Shader.o: src/GL/GL/Shader.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Shader.cpp -o lib/Shader.o -I include

lib/Program.o: src/GL/GL/Program.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Program.cpp -o lib/Program.o -I include

lib/VertexBuffer.o: src/GL/GL/VertexBuffer.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/VertexBuffer.cpp -o lib/VertexBuffer.o -I include

lib/VertexArray.o: src/GL/GL/VertexArray.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/VertexArray.cpp -o lib/VertexArray.o -I include

lib/Texture.o: src/GL/GL/Texture.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Texture.cpp -o lib/Texture.o -I include

lib/Renderbuffer.o: src/GL/GL/Renderbuffer.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Renderbuffer.cpp -o lib/Renderbuffer.o -I include

lib/Framebuffer.o: src/GL/GL/Framebuffer.cpp
	$(CC) $(CCFLAGS) -c src/GL/GL/Framebuffer.cpp -o lib/Framebuffer.o -I include

# Util

lib/Image.o: src/GL/Util/Image.cpp
	$(CC) $(CCFLAGS) -c src/GL/Util/Image.cpp -o lib/Image.o -I include -I src

lib/Mesh.o: src/GL/Util/Mesh.cpp
	$(CC) $(CCFLAGS) -c src/GL/Util/Mesh.cpp -o lib/Mesh.o -I include -I src

lib/%.o: src/GL/Util/libjpeg/%.c
	$(CCC) -O3 -c $< -o $(patsubst src/GL/Util/libjpeg/%.c,lib/%.o,$<)

lib/%.o: src/GL/Util/libpng/%.c
	$(CCC) -O3 -c $< -o $(patsubst src/GL/Util/libpng/%.c,lib/%.o,$<)

lib/%.o: src/GL/Util/zlib/%.c
	$(CCC) -O3 -c $< -o $(patsubst src/GL/Util/zlib/%.c,lib/%.o,$<)

# Binaries folder
lib:
	mkdir lib

# Clean
clean:
	rm -rf lib/*
