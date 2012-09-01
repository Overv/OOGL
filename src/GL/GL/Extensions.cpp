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

#include <GL/GL/Extensions.hpp>

#if defined( OOGL_PLATFORM_WINDOWS )
	WGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB;
	WGLCHOOSEPIXELFORMATARB wglChoosePixelFormatARB;
	WGLSWAPINTERVALEXT wglSwapIntervalEXT;
#elif defined( OOGL_PLATFORM_LINUX )
	GLXCREATECONTEXTATTRIBSARB glXCreateContextAttribsARB;
	GLXSWAPINTERVALSGI glXSwapIntervalSGI;
#endif

GLCOMPILESHADER glCompileShader;
GLCREATESHADER glCreateShader;
GLDELETESHADER glDeleteShader;
GLGETSHADERIV glGetShaderiv;
GLGETSHADERINFOLOG glGetShaderInfoLog;
GLSHADERSOURCE glShaderSource;

GLCREATEPROGRAM glCreateProgram;
GLDELETEPROGRAM glDeleteProgram;
GLUSEPROGRAM glUseProgram;
GLATTACHSHADER glAttachShader;
GLLINKPROGRAM glLinkProgram;
GLGETPROGRAMIV glGetProgramiv;
GLGETPROGRAMINFOLOG glGetProgramInfoLog;
GLGETATTRIBLOCATION glGetAttribLocation;
GLGETUNIFORMLOCATION glGetUniformLocation;

GLUNIFORM1F glUniform1f;
GLUNIFORM2F glUniform2f;
GLUNIFORM3F glUniform3f;
GLUNIFORM4F glUniform4f;
GLUNIFORM1I glUniform1i;
GLUNIFORM2I glUniform2i;
GLUNIFORM3I glUniform3i;
GLUNIFORM4I glUniform4i;
GLUNIFORM1UI glUniform1ui;
GLUNIFORM2UI glUniform2ui;
GLUNIFORM3UI glUniform3ui;
GLUNIFORM4UI glUniform4ui;
GLUNIFORM1FV glUniform1fv;
GLUNIFORM2FV glUniform2fv;
GLUNIFORM3FV glUniform3fv;
GLUNIFORM4FV glUniform4fv;
GLUNIFORM1IV glUniform1iv;
GLUNIFORM2IV glUniform2iv;
GLUNIFORM3IV glUniform3iv;
GLUNIFORM4IV glUniform4iv;
GLUNIFORM1UIV glUniform1uiv;
GLUNIFORM2UIV glUniform2uiv;
GLUNIFORM3UIV glUniform3uiv;
GLUNIFORM4UIV glUniform4uiv;
GLUNIFORMMATRIX2FV glUniformMatrix2fv;
GLUNIFORMMATRIX3FV glUniformMatrix3fv;
GLUNIFORMMATRIX4FV glUniformMatrix4fv;
GLUNIFORMMATRIX2X3FV glUniformMatrix2x3fv;
GLUNIFORMMATRIX3X2FV glUniformMatrix3x2fv;
GLUNIFORMMATRIX2X4FV glUniformMatrix2x4fv;
GLUNIFORMMATRIX4X2FV glUniformMatrix4x2fv;
GLUNIFORMMATRIX3X4FV glUniformMatrix3x4fv;
GLUNIFORMMATRIX4X3FV glUniformMatrix4x3fv;

GLGENBUFFERS glGenBuffers;
GLDELETEBUFFERS glDeleteBuffers;
GLBINDBUFFER glBindBuffer;
GLBUFFERDATA glBufferData;
GLBUFFERSUBDATA glBufferSubData;
GLGETBUFFERSUBDATA glGetBufferSubData;

GLGENVERTEXARRAYS glGenVertexArrays;
GLDELETEVERTEXARRAYS glDeleteVertexArrays;
GLBINDVERTEXARRAY glBindVertexArray;

GLENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray;
GLVERTEXATTRIBPOINTER glVertexAttribPointer;

GLGENERATEMIPMAP glGenerateMipmap;

#ifndef GL_VERSION_1_3
	GLACTIVETEXTURE glActiveTexture;
#endif

GLGENFRAMEBUFFERS glGenFramebuffers;
GLDELETEFRAMEBUFFERS glDeleteFramebuffers;
GLFRAMEBUFFERTEXTURE2D glFramebufferTexture2D;
GLFRAMEBUFFERRENDERBUFFER glFramebufferRenderbuffer;
GLBINDFRAMEBUFFER glBindFramebuffer;
GLGETFRAMEBUFFERATTACHMENTPARAMETERIV glGetFramebufferAttachmentParameteriv;
GLCHECKFRAMEBUFFERSTATUS glCheckFramebufferStatus;

GLGENRENDERBUFFERS glGenRenderbuffers;
GLDELETERENDERBUFFERS glDeleteRenderbuffers;
GLRENDERBUFFERSTORAGE glRenderbufferStorage;
GLBINDRENDERBUFFER glBindRenderbuffer;

GLTRANSFORMFEEDBACKVARYINGS glTransformFeedbackVaryings;
GLBINDBUFFERBASE glBindBufferBase;
GLBEGINTRANSFORMFEEDBACK glBeginTransformFeedback;
GLENDTRANSFORMFEEDBACK glEndTransformFeedback;

namespace GL
{
	bool extensionsLoaded = false;

	inline void* LoadExtension( const char* name )
	{
#if defined( OOGL_PLATFORM_WINDOWS )
		return wglGetProcAddress( name );
#elif defined( OOGL_PLATFORM_LINUX )
		return (void*)glXGetProcAddress( (const GLubyte*)name );
#endif
	}

	void LoadExtensions()
	{
		if ( extensionsLoaded ) return;
		extensionsLoaded = true;

#if defined( OOGL_PLATFORM_WINDOWS )
		wglCreateContextAttribsARB = (WGLCREATECONTEXTATTRIBSARB)LoadExtension( "wglCreateContextAttribsARB" );
		wglChoosePixelFormatARB = (WGLCHOOSEPIXELFORMATARB)LoadExtension( "wglChoosePixelFormatARB" );
		wglSwapIntervalEXT = (WGLSWAPINTERVALEXT)LoadExtension( "wglSwapIntervalEXT" );
#elif defined( OOGL_PLATFORM_LINUX )
		glXCreateContextAttribsARB = (GLXCREATECONTEXTATTRIBSARB)LoadExtension( "glXCreateContextAttribsARB" );
		glXSwapIntervalSGI = (GLXSWAPINTERVALSGI)LoadExtension( "glXSwapIntervalSGI" );
#endif

		glCompileShader = (GLCOMPILESHADER)LoadExtension( "glCompileShader" );
		glCreateShader = (GLCREATESHADER)LoadExtension( "glCreateShader" );
		glDeleteShader = (GLDELETESHADER)LoadExtension( "glDeleteShader" );
		glGetShaderiv = (GLGETSHADERIV)LoadExtension( "glGetShaderiv" );
		glGetShaderInfoLog = (GLGETSHADERINFOLOG)LoadExtension( "glGetShaderInfoLog" );
		glShaderSource = (GLSHADERSOURCE)LoadExtension( "glShaderSource" );

		glCreateProgram = (GLCREATEPROGRAM)LoadExtension( "glCreateProgram" );
		glDeleteProgram = (GLDELETEPROGRAM)LoadExtension( "glDeleteProgram" );
		glUseProgram = (GLUSEPROGRAM)LoadExtension( "glUseProgram" );
		glAttachShader = (GLATTACHSHADER)LoadExtension( "glAttachShader" );
		glLinkProgram = (GLLINKPROGRAM)LoadExtension( "glLinkProgram" );
		glGetProgramiv = (GLGETPROGRAMIV)LoadExtension( "glGetProgramiv" );
		glGetProgramInfoLog = (GLGETPROGRAMINFOLOG)LoadExtension( "glGetProgramInfoLog" );
		glGetAttribLocation = (GLGETATTRIBLOCATION)LoadExtension( "glGetAttribLocation" );
		glGetUniformLocation = (GLGETUNIFORMLOCATION)LoadExtension( "glGetUniformLocation" );

		glUniform1f = (GLUNIFORM1F)LoadExtension( "glUniform1f" );
		glUniform2f = (GLUNIFORM2F)LoadExtension( "glUniform2f" );
		glUniform3f = (GLUNIFORM3F)LoadExtension( "glUniform3f" );
		glUniform4f = (GLUNIFORM4F)LoadExtension( "glUniform4f" );
		glUniform1i = (GLUNIFORM1I)LoadExtension( "glUniform1i" );
		glUniform2i = (GLUNIFORM2I)LoadExtension( "glUniform2i" );
		glUniform3i = (GLUNIFORM3I)LoadExtension( "glUniform3i" );
		glUniform4i = (GLUNIFORM4I)LoadExtension( "glUniform4i" );
		glUniform1ui = (GLUNIFORM1UI)LoadExtension( "glUniform1ui" );
		glUniform2ui = (GLUNIFORM2UI)LoadExtension( "glUniform2ui" );
		glUniform3ui = (GLUNIFORM3UI)LoadExtension( "glUniform3ui" );
		glUniform4ui = (GLUNIFORM4UI)LoadExtension( "glUniform4ui" );
		glUniform1fv = (GLUNIFORM1FV)LoadExtension( "glUniform1fv" );
		glUniform2fv = (GLUNIFORM2FV)LoadExtension( "glUniform2fv" );
		glUniform3fv = (GLUNIFORM3FV)LoadExtension( "glUniform3fv" );
		glUniform4fv = (GLUNIFORM4FV)LoadExtension( "glUniform4fv" );
		glUniform1iv = (GLUNIFORM1IV)LoadExtension( "glUniform1iv" );
		glUniform2iv = (GLUNIFORM2IV)LoadExtension( "glUniform2iv" );
		glUniform3iv = (GLUNIFORM3IV)LoadExtension( "glUniform3iv" );
		glUniform4iv = (GLUNIFORM4IV)LoadExtension( "glUniform4iv" );
		glUniform1uiv = (GLUNIFORM1UIV)LoadExtension( "glUniform1uiv" );
		glUniform2uiv = (GLUNIFORM2UIV)LoadExtension( "glUniform2uiv" );
		glUniform3uiv = (GLUNIFORM3UIV)LoadExtension( "glUniform3uiv" );
		glUniform4uiv = (GLUNIFORM4UIV)LoadExtension( "glUniform4uiv" );
		glUniformMatrix2fv = (GLUNIFORMMATRIX2FV)LoadExtension( "glUniformMatrix2fv" );
		glUniformMatrix3fv = (GLUNIFORMMATRIX3FV)LoadExtension( "glUniformMatrix3fv" );
		glUniformMatrix4fv = (GLUNIFORMMATRIX4FV)LoadExtension( "glUniformMatrix4fv" );
		glUniformMatrix2x3fv = (GLUNIFORMMATRIX2X3FV)LoadExtension( "glUniformMatrix2x3fv" );
		glUniformMatrix3x2fv = (GLUNIFORMMATRIX3X2FV)LoadExtension( "glUniformMatrix3x2fv" );
		glUniformMatrix2x4fv = (GLUNIFORMMATRIX2X4FV)LoadExtension( "glUniformMatrix2x4fv" );
		glUniformMatrix4x2fv = (GLUNIFORMMATRIX4X2FV)LoadExtension( "glUniformMatrix4x2fv" );
		glUniformMatrix3x4fv = (GLUNIFORMMATRIX3X4FV)LoadExtension( "glUniformMatrix3x4fv" );
		glUniformMatrix4x3fv = (GLUNIFORMMATRIX4X3FV)LoadExtension( "glUniformMatrix4x3fv" );

		glGenBuffers = (GLGENBUFFERS)LoadExtension( "glGenBuffers" );
		glDeleteBuffers = (GLDELETEBUFFERS)LoadExtension( "glDeleteBuffers" );
		glBindBuffer = (GLBINDBUFFER)LoadExtension( "glBindBuffer" );
		glBufferData = (GLBUFFERDATA)LoadExtension( "glBufferData" );
		glBufferSubData = (GLBUFFERSUBDATA)LoadExtension( "glBufferSubData" );
		glGetBufferSubData = (GLGETBUFFERSUBDATA)LoadExtension( "glGetBufferSubData" );

		glGenVertexArrays = (GLGENVERTEXARRAYS)LoadExtension( "glGenVertexArrays" );
		glDeleteVertexArrays = (GLDELETEVERTEXARRAYS)LoadExtension( "glDeleteVertexArrays" );
		glBindVertexArray = (GLBINDVERTEXARRAY)LoadExtension( "glBindVertexArray" );

		glEnableVertexAttribArray = (GLENABLEVERTEXATTRIBARRAY)LoadExtension( "glEnableVertexAttribArray" );
		glVertexAttribPointer = (GLVERTEXATTRIBPOINTER)LoadExtension( "glVertexAttribPointer" );

		glGenerateMipmap = (GLGENERATEMIPMAP)LoadExtension( "glGenerateMipmap" );

		#ifndef GL_VERSION_1_3
			glActiveTexture = (GLACTIVETEXTURE)LoadExtension( "glActiveTexture" );
		#endif

		glGenFramebuffers = (GLGENFRAMEBUFFERS)LoadExtension( "glGenFramebuffers" );
		glDeleteFramebuffers = (GLDELETEFRAMEBUFFERS)LoadExtension( "glDeleteFramebuffers" );
		glFramebufferTexture2D = (GLFRAMEBUFFERTEXTURE2D)LoadExtension( "glFramebufferTexture2D" );
		glFramebufferRenderbuffer = (GLFRAMEBUFFERRENDERBUFFER)LoadExtension( "glFramebufferRenderbuffer" );
		glBindFramebuffer = (GLBINDFRAMEBUFFER)LoadExtension( "glBindFramebuffer" );
		glGetFramebufferAttachmentParameteriv = (GLGETFRAMEBUFFERATTACHMENTPARAMETERIV)LoadExtension( "glGetFramebufferAttachmentParameteriv" );
		glCheckFramebufferStatus = (GLCHECKFRAMEBUFFERSTATUS)LoadExtension( "glCheckFramebufferStatus" );

		glGenRenderbuffers = (GLGENRENDERBUFFERS)LoadExtension( "glGenRenderbuffers" );
		glDeleteRenderbuffers = (GLDELETERENDERBUFFERS)LoadExtension( "glDeleteRenderbuffers" );
		glRenderbufferStorage = (GLRENDERBUFFERSTORAGE)LoadExtension( "glRenderbufferStorage" );
		glBindRenderbuffer = (GLBINDRENDERBUFFER)LoadExtension( "glBindRenderbuffer" );

		glTransformFeedbackVaryings = (GLTRANSFORMFEEDBACKVARYINGS)LoadExtension( "glTransformFeedbackVaryings" );
		glBindBufferBase = (GLBINDBUFFERBASE)LoadExtension( "glBindBufferBase" );
		glBeginTransformFeedback = (GLBEGINTRANSFORMFEEDBACK)LoadExtension( "glBeginTransformFeedback" );
		glEndTransformFeedback = (GLENDTRANSFORMFEEDBACK)LoadExtension( "glEndTransformFeedback" );
	}
}