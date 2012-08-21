all: ../bin ../bin/Triangle ../bin/StencilReflection ../bin/ShadowMapping

../bin/Triangle: Triangle/main.cpp
	clang++ Triangle/main.cpp -o ../bin/Triangle -I ../include ../lib/OOGL.a -framework Cocoa -framework OpenGL -std=c++0x -stdlib=libc++

../bin/StencilReflection: StencilReflection/main.cpp
	clang++ StencilReflection/main.cpp -o ../bin/StencilReflection -I ../include ../lib/OOGL.a -framework Cocoa -framework OpenGL -std=c++0x  -stdlib=libc++ -g
	cp StencilReflection/tank.obj ../bin/tank.obj
	cp StencilReflection/platform.obj ../bin/platform.obj
	cp StencilReflection/tank.jpg ../bin/tank.jpg
	cp StencilReflection/platform.png ../bin/platform.png
	
../bin/ShadowMapping: ShadowMapping/main.cpp
	clang++ ShadowMapping/main.cpp -o ../bin/ShadowMapping -I ../include ../lib/OOGL.a -framework Cocoa -framework OpenGL -std=c++0x  -stdlib=libc++
	cp ShadowMapping/scene.obj ../bin/scene.obj
	cp ShadowMapping/scene.png ../bin/scene.png
	
../bin:
	mkdir ../bin

clean:
	rm ../bin -rf
