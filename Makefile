# Parameters

CC = g++
CCFLAGS = -O3 -Wall -Wextra -Werror

# Final library

bin/OOGL.a: bin/Mat3.o bin/Mat4.o bin/Vec2.o bin/Vec3.o bin/Window.o bin/Window_X11.o
	ar rcs bin/OOGL.a bin/Mat3.o bin/Mat4.o bin/Vec2.o bin/Vec3.o bin/Window.o bin/Window_X11.o

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

# Clean
clean:
	rm -rf bin/*