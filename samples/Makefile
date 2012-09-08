all: ../bin ../bin/Triangle ../bin/StencilReflection ../bin/ShadowMapping ../bin/TransformFeedback

../bin/Triangle: Triangle/main.cpp
	g++ Triangle/main.cpp -o ../bin/Triangle -I ../include ../lib/OOGL.a -lX11 -lXrandr -lGL -std=c++0x

../bin/StencilReflection: StencilReflection/main.cpp
	g++ StencilReflection/main.cpp -o ../bin/StencilReflection -I ../include ../lib/OOGL.a -lX11 -lXrandr -lGL -std=c++0x
	cp StencilReflection/tank.obj ../bin/tank.obj
	cp StencilReflection/platform.obj ../bin/platform.obj
	cp StencilReflection/tank.jpg ../bin/tank.jpg
	cp StencilReflection/platform.png ../bin/platform.png

../bin/ShadowMapping: ShadowMapping/main.cpp
	g++ ShadowMapping/main.cpp -o ../bin/ShadowMapping -I ../include ../lib/OOGL.a -lX11 -lXrandr -lGL -std=c++0x
	cp ShadowMapping/scene.obj ../bin/scene.obj
	cp ShadowMapping/scene.png ../bin/scene.png

../bin/TransformFeedback: TransformFeedback/main.cpp
	g++ TransformFeedback/main.cpp -o ../bin/TransformFeedback -I ../include ../lib/OOGL.a -lX11 -lXrandr -lGL -std=c++0x

../bin:
	mkdir ../bin

clean:
	rm ../bin -rf
