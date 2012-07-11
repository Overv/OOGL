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

#pragma once

#ifndef OOGL_EXTENSIONS_HPP
#define OOGL_EXTENSIONS_HPP

#include <GL/Platform.hpp>

/*
	OpenGL context creation/configuration
*/

#if defined( OOGL_PLATFORM_WINDOWS )
	#define APIENTRYP WINAPI *
	typedef ptrdiff_t GLsizeiptr;
	typedef ptrdiff_t GLintptr;
	typedef char GLchar;
	
	#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
	#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
	#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
	#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

	#define WGL_DRAW_TO_WINDOW_ARB 0x2001
	#define WGL_SUPPORT_OPENGL_ARB 0x2010
	#define WGL_DOUBLE_BUFFER_ARB 0x2011
	#define WGL_PIXEL_TYPE_ARB 0x2013
	#define WGL_COLOR_BITS_ARB 0x2014
	#define WGL_DEPTH_BITS_ARB 0x2022
	#define WGL_STENCIL_BITS_ARB 0x2023
	#define WGL_SAMPLE_BUFFERS_ARB 0x2041
	#define WGL_SAMPLES_ARB 0x2042
	#define WGL_TYPE_RGBA_ARB 0x202B

	typedef HGLRC ( WINAPI * WGLCREATECONTEXTATTRIBSARB ) ( HDC hDC, HGLRC hShareContext, const int* attribList );
	extern WGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB;
	typedef BOOL ( WINAPI * WGLCHOOSEPIXELFORMATARB ) ( HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats );
	extern WGLCHOOSEPIXELFORMATARB wglChoosePixelFormatARB;
	typedef BOOL ( WINAPI * WGLSWAPINTERVALEXT ) ( int interval );
	extern WGLSWAPINTERVALEXT wglSwapIntervalEXT;
#elif defined( OOGL_PLATFORM_LINUX )
	#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
	#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
	#define GLX_CONTEXT_PROFILE_MASK_ARB 0x9126
	#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

	typedef GLXContext ( * GLXCREATECONTEXTATTRIBSARB ) ( Display* dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int* attrib_list );
	extern GLXCREATECONTEXTATTRIBSARB glXCreateContextAttribsARB;
	typedef int ( * GLXSWAPINTERVALSGI ) ( int interval );
	extern GLXSWAPINTERVALSGI glXSwapIntervalSGI;
#endif

/*
	Return values/parameters
*/

#define GL_MAJOR_VERSION 0x821B
#define GL_MINOR_VERSION 0x821C

/*
	Shaders
*/

#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPILE_STATUS 0x8B81
#define GL_INFO_LOG_LENGTH 0x8B84

typedef void ( APIENTRYP GLCOMPILESHADER ) ( GLuint shader );
extern GLCOMPILESHADER glCompileShader;
typedef GLuint ( APIENTRYP GLCREATESHADER ) ( GLenum type );
extern GLCREATESHADER glCreateShader;
typedef void ( APIENTRYP GLDELETESHADER ) ( GLuint shader );
extern GLDELETESHADER glDeleteShader;
typedef void ( APIENTRYP GLGETSHADERIV ) ( GLuint shader, GLenum pname, GLint* params );
extern GLGETSHADERIV glGetShaderiv;
typedef void ( APIENTRYP GLGETSHADERINFOLOG ) ( GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog );
extern GLGETSHADERINFOLOG glGetShaderInfoLog;
typedef void ( APIENTRYP GLSHADERSOURCE ) ( GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length );
extern GLSHADERSOURCE glShaderSource;

#define GL_LINK_STATUS 0x8B82

typedef GLuint ( APIENTRYP GLCREATEPROGRAM ) ( void );
extern GLCREATEPROGRAM glCreateProgram;
typedef void ( APIENTRYP GLDELETEPROGRAM ) ( GLuint program );
extern GLDELETEPROGRAM glDeleteProgram;
typedef void ( APIENTRYP GLATTACHSHADER ) ( GLuint program, GLuint shader );
extern GLATTACHSHADER glAttachShader;
typedef void ( APIENTRYP GLLINKPROGRAM ) ( GLuint program );
extern GLLINKPROGRAM glLinkProgram;
typedef void ( APIENTRYP GLGETPROGRAMIV ) ( GLuint program, GLenum pname, GLint* params );
extern GLGETPROGRAMIV glGetProgramiv;
typedef void ( APIENTRYP GLGETPROGRAMINFOLOG ) ( GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog );
extern GLGETPROGRAMINFOLOG glGetProgramInfoLog;
typedef GLint ( APIENTRYP GLGETATTRIBLOCATION ) ( GLuint program, const GLchar* name );
extern GLGETATTRIBLOCATION glGetAttribLocation;

/*
	VBOs
*/

#define GL_STREAM_DRAW 0x88E0
#define GL_STREAM_READ 0x88E1
#define GL_STREAM_COPY 0x88E2
#define GL_STATIC_DRAW 0x88E4
#define GL_STATIC_READ 0x88E5
#define GL_STATIC_COPY 0x88E6
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_DYNAMIC_READ 0x88E9
#define GL_DYNAMIC_COPY 0x88EA

#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893

typedef void ( APIENTRYP GLGENBUFFERS ) ( GLsizei n, GLuint* buffers );
extern GLGENBUFFERS glGenBuffers;
typedef void ( APIENTRYP GLDELETEBUFFERS ) ( GLsizei n, const GLuint* buffers );
extern GLDELETEBUFFERS glDeleteBuffers;
typedef void ( APIENTRYP GLBINDBUFFER )  ( GLenum target, GLuint buffer );
extern GLBINDBUFFER glBindBuffer;
typedef void ( APIENTRYP GLBUFFERDATA ) ( GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage );
extern GLBUFFERDATA glBufferData;
typedef void ( APIENTRYP GLBUFFERSUBDATA ) ( GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data );
extern GLBUFFERSUBDATA glBufferSubData;

/*
	VAOs
*/

typedef void ( APIENTRYP GLGENVERTEXARRAYS ) ( GLsizei n, GLuint* arrays );
extern GLGENVERTEXARRAYS glGenVertexArrays;
typedef void ( APIENTRYP GLDELETEVERTEXARRAYS ) ( GLsizei n, const GLuint* arrays );
extern GLDELETEVERTEXARRAYS glDeleteVertexArrays;
typedef void ( APIENTRYP GLBINDVERTEXARRAY ) ( GLuint array );
extern GLBINDVERTEXARRAY glBindVertexArray;

typedef void ( APIENTRYP GLENABLEVERTEXATTRIBARRAY ) ( GLuint index );
extern GLENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray;
typedef void ( APIENTRYP GLVERTEXATTRIBPOINTER ) ( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer );
extern GLVERTEXATTRIBPOINTER glVertexAttribPointer;

/*
	Extension loader
*/

namespace GL
{
	extern void LoadExtensions();
}

#endif