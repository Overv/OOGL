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
#define GL_GEOMETRY_SHADER 0x8DD9
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
typedef void ( APIENTRYP GLUSEPROGRAM ) ( GLuint program );
extern GLUSEPROGRAM glUseProgram;
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
typedef GLint ( APIENTRYP GLGETUNIFORMLOCATION ) ( GLuint program, const GLchar* name );
extern GLGETUNIFORMLOCATION glGetUniformLocation;

/*
	Uniforms
*/

typedef void ( APIENTRYP GLUNIFORM1F ) ( GLint location, GLfloat v0 );
extern GLUNIFORM1F glUniform1f;
typedef void ( APIENTRYP GLUNIFORM2F ) ( GLint location, GLfloat v0, GLfloat v1 );
extern GLUNIFORM2F glUniform2f;
typedef void ( APIENTRYP GLUNIFORM3F ) ( GLint location, GLfloat v0, GLfloat v1, GLfloat v2 );
extern GLUNIFORM3F glUniform3f;
typedef void ( APIENTRYP GLUNIFORM4F ) ( GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 );
extern GLUNIFORM4F glUniform4f;
typedef void ( APIENTRYP GLUNIFORM1I ) ( GLint location, GLint v0 );
extern GLUNIFORM1I glUniform1i;
typedef void ( APIENTRYP GLUNIFORM2I ) ( GLint location, GLint v0, GLint v1 );
extern GLUNIFORM2I glUniform2i;
typedef void ( APIENTRYP GLUNIFORM3I ) ( GLint location, GLint v0, GLint v1, GLint v2 );
extern GLUNIFORM3I glUniform3i;
typedef void ( APIENTRYP GLUNIFORM4I ) ( GLint location, GLint v0, GLint v1, GLint v2, GLint v3 );
extern GLUNIFORM4I glUniform4i;
typedef void ( APIENTRYP GLUNIFORM1UI ) ( GLuint location, GLuint v0 );
extern GLUNIFORM1UI glUniform1ui;
typedef void ( APIENTRYP GLUNIFORM2UI ) ( GLuint location, GLuint v0, GLuint v1 );
extern GLUNIFORM2UI glUniform2ui;
typedef void ( APIENTRYP GLUNIFORM3UI ) ( GLuint location, GLuint v0, GLuint v1, GLuint v2 );
extern GLUNIFORM3UI glUniform3ui;
typedef void ( APIENTRYP GLUNIFORM4UI ) ( GLuint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3 );
extern GLUNIFORM4UI glUniform4ui;
typedef void ( APIENTRYP GLUNIFORM1FV ) ( GLint location, GLsizei count, const GLfloat* value );
extern GLUNIFORM1FV glUniform1fv;
typedef void ( APIENTRYP GLUNIFORM2FV ) ( GLint location, GLsizei count, const GLfloat* value );
extern GLUNIFORM2FV glUniform2fv;
typedef void ( APIENTRYP GLUNIFORM3FV ) ( GLint location, GLsizei count, const GLfloat* value );
extern GLUNIFORM3FV glUniform3fv;
typedef void ( APIENTRYP GLUNIFORM4FV ) ( GLint location, GLsizei count, const GLfloat* value );
extern GLUNIFORM4FV glUniform4fv;
typedef void ( APIENTRYP GLUNIFORM1IV ) ( GLint location, GLsizei count, const GLint* value );
extern GLUNIFORM1IV glUniform1iv;
typedef void ( APIENTRYP GLUNIFORM2IV ) ( GLint location, GLsizei count, const GLint* value );
extern GLUNIFORM2IV glUniform2iv;
typedef void ( APIENTRYP GLUNIFORM3IV ) ( GLint location, GLsizei count, const GLint* value );
extern GLUNIFORM3IV glUniform3iv;
typedef void ( APIENTRYP GLUNIFORM4IV ) ( GLint location, GLsizei count, const GLint* value );
extern GLUNIFORM4IV glUniform4iv;
typedef void ( APIENTRYP GLUNIFORM1UIV ) ( GLuint location, GLsizei count, const GLuint* value );
extern GLUNIFORM1UIV glUniform1uiv;
typedef void ( APIENTRYP GLUNIFORM2UIV ) ( GLuint location, GLsizei count, const GLuint* value );
extern GLUNIFORM2UIV glUniform2uiv;
typedef void ( APIENTRYP GLUNIFORM3UIV ) ( GLuint location, GLsizei count, const GLuint* value );
extern GLUNIFORM3UIV glUniform3uiv;
typedef void ( APIENTRYP GLUNIFORM4UIV ) ( GLuint location, GLsizei count, const GLuint* value );
extern GLUNIFORM4UIV glUniform4uiv;
typedef void ( APIENTRYP GLUNIFORMMATRIX2FV ) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern GLUNIFORMMATRIX2FV glUniformMatrix2fv;
typedef void ( APIENTRYP GLUNIFORMMATRIX3FV ) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern GLUNIFORMMATRIX3FV glUniformMatrix3fv;
typedef void ( APIENTRYP GLUNIFORMMATRIX4FV ) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern GLUNIFORMMATRIX4FV glUniformMatrix4fv;
typedef void ( APIENTRYP GLUNIFORMMATRIX2X3FV ) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern GLUNIFORMMATRIX2X3FV glUniformMatrix2x3fv;
typedef void ( APIENTRYP GLUNIFORMMATRIX3X2FV ) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern GLUNIFORMMATRIX3X2FV glUniformMatrix3x2fv;
typedef void ( APIENTRYP GLUNIFORMMATRIX2X4FV ) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern GLUNIFORMMATRIX2X4FV glUniformMatrix2x4fv;
typedef void ( APIENTRYP GLUNIFORMMATRIX4X2FV ) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern GLUNIFORMMATRIX4X2FV glUniformMatrix4x2fv;
typedef void ( APIENTRYP GLUNIFORMMATRIX3X4FV ) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern GLUNIFORMMATRIX3X4FV glUniformMatrix3x4fv;
typedef void ( APIENTRYP GLUNIFORMMATRIX4X3FV ) ( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
extern GLUNIFORMMATRIX4X3FV glUniformMatrix4x3fv;

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
typedef void ( APIENTRYP GLGETBUFFERSUBDATA ) ( GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data );
extern GLGETBUFFERSUBDATA glGetBufferSubData;

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
	Textures
*/

#define GL_TEXTURE_WRAP_R 0x8072

#define GL_CLAMP_TO_EDGE 0x812F
#define GL_CLAMP_TO_BORDER 0x812D
#define GL_MIRRORED_REPEAT 0x8370

#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF

typedef void ( APIENTRYP GLGENERATEMIPMAP ) ( GLenum target );
extern GLGENERATEMIPMAP glGenerateMipmap;

#ifndef GL_VERSION_1_3
	typedef void ( APIENTRYP GLACTIVETEXTURE ) ( GLenum texture );
	extern GLACTIVETEXTURE glActiveTexture;
#endif

/*
	Data types
*/

#define GL_UNSIGNED_BYTE_3_3_2 0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#define GL_UNSIGNED_INT_8_8_8_8 0x8035
#define GL_UNSIGNED_INT_10_10_10_2 0x8036
#define GL_UNSIGNED_BYTE_2_3_3_REV 0x8362
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV 0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV 0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV 0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV 0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368

#define GL_COMPRESSED_RED 0x8225
#define GL_COMPRESSED_RG 0x8226
#define GL_COMPRESSED_RED_RGTC1 0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1 0x8DBC
#define GL_COMPRESSED_RG_RGTC2 0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2 0x8DBE
#define GL_COMPRESSED_RGB 0x84ED
#define GL_COMPRESSED_RGBA 0x84EE
#define GL_SRGB 0x8C40
#define GL_SRGB8 0x8C41
#define GL_SRGB_ALPHA 0x8C42
#define GL_SRGB8_ALPHA8 0x8C43
#define GL_COMPRESSED_SRGB 0x8C48
#define GL_COMPRESSED_SRGB_ALPHA 0x8C49
#define GL_DEPTH_STENCIL 0x84F9
#define GL_DEPTH24_STENCIL8 0x88F0
#define GL_DEPTH_COMPONENT32F 0x8CAC
#define GL_DEPTH32F_STENCIL8 0x8CAD
#define GL_DEPTH_COMPONENT16 0x81A5
#define GL_DEPTH_COMPONENT24 0x81A6
#define GL_DEPTH_COMPONENT32 0x81A7
#define GL_RG 0x8227
#define GL_R8 0x8229
#define GL_R16 0x822A
#define GL_RG8 0x822B
#define GL_RG16 0x822C
#define GL_R16F 0x822D
#define GL_R32F 0x822E
#define GL_RG16F 0x822F
#define GL_RG32F 0x8230
#define GL_R8I 0x8231
#define GL_R8UI 0x8232
#define GL_R16I 0x8233
#define GL_R16UI 0x8234
#define GL_R32I 0x8235
#define GL_R32UI 0x8236
#define GL_RG8I 0x8237
#define GL_RG8UI 0x8238
#define GL_RG16I 0x8239
#define GL_RG16UI 0x823A
#define GL_RG32I 0x823B
#define GL_RG32UI 0x823C
#define GL_RG_SNORM 0x8F91
#define GL_RGB_SNORM 0x8F92
#define GL_RGBA_SNORM 0x8F93
#define GL_R8_SNORM 0x8F94
#define GL_RG8_SNORM 0x8F95
#define GL_RGB8_SNORM 0x8F96
#define GL_RGBA8_SNORM 0x8F97
#define GL_R16_SNORM 0x8F98
#define GL_RG16_SNORM 0x8F99
#define GL_RGB16_SNORM 0x8F9A
#define GL_RGBA16_SNORM 0x8F9B
#define GL_RGBA32F 0x8814
#define GL_RGB32F 0x8815
#define GL_RGBA16F 0x881A
#define GL_RGB16F 0x881B
#define GL_RGBA32UI 0x8D70
#define GL_RGB32UI 0x8D71
#define GL_RGBA16UI 0x8D76
#define GL_RGB16UI 0x8D77
#define GL_RGBA8UI 0x8D7C
#define GL_RGB8UI 0x8D7D
#define GL_RGBA32I 0x8D82
#define GL_RGB32I 0x8D83
#define GL_RGBA16I 0x8D88
#define GL_RGB16I  0x8D89
#define GL_RGBA8I 0x8D8E
#define GL_RGB8I 0x8D8F
#define GL_RGB9_E5 0x8C3D
#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1

/*
	Frame buffers
*/

#define GL_DRAW_FRAMEBUFFER 0x8CA9

#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_COLOR_ATTACHMENT1 0x8CE1
#define GL_COLOR_ATTACHMENT2 0x8CE2
#define GL_COLOR_ATTACHMENT3 0x8CE3
#define GL_COLOR_ATTACHMENT4 0x8CE4
#define GL_COLOR_ATTACHMENT5 0x8CE5
#define GL_COLOR_ATTACHMENT6 0x8CE6
#define GL_COLOR_ATTACHMENT7 0x8CE7
#define GL_COLOR_ATTACHMENT8 0x8CE8
#define GL_COLOR_ATTACHMENT9 0x8CE9
#define GL_COLOR_ATTACHMENT10 0x8CEA
#define GL_COLOR_ATTACHMENT11 0x8CEB
#define GL_COLOR_ATTACHMENT12 0x8CEC
#define GL_COLOR_ATTACHMENT13 0x8CED
#define GL_COLOR_ATTACHMENT14 0x8CEE
#define GL_COLOR_ATTACHMENT15 0x8CEF
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_STENCIL_ATTACHMENT 0x8D20

#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1

#define GL_FRAMEBUFFER_BINDING 0x8CA6
#define GL_DRAW_FRAMEBUFFER_BINDING GL_FRAMEBUFFER_BINDING
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5

typedef void ( APIENTRYP GLGENFRAMEBUFFERS ) ( GLsizei n, GLuint* framebuffers );
extern GLGENFRAMEBUFFERS glGenFramebuffers;
typedef void ( APIENTRYP GLDELETEFRAMEBUFFERS ) ( GLsizei n, const GLuint* framebuffers );
extern GLDELETEFRAMEBUFFERS glDeleteFramebuffers;
typedef void ( APIENTRYP GLFRAMEBUFFERTEXTURE2D ) ( GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level );
extern GLFRAMEBUFFERTEXTURE2D glFramebufferTexture2D;
typedef void ( APIENTRYP GLFRAMEBUFFERRENDERBUFFER ) ( GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer );
extern GLFRAMEBUFFERRENDERBUFFER glFramebufferRenderbuffer;
typedef void ( APIENTRYP GLBINDFRAMEBUFFER ) ( GLenum target, GLuint framebuffer );
extern GLBINDFRAMEBUFFER glBindFramebuffer;
typedef void ( APIENTRYP GLGETFRAMEBUFFERATTACHMENTPARAMETERIV ) ( GLenum target, GLenum attachment, GLenum pname, GLint* params );
extern GLGETFRAMEBUFFERATTACHMENTPARAMETERIV glGetFramebufferAttachmentParameteriv;
typedef GLenum ( APIENTRYP GLCHECKFRAMEBUFFERSTATUS ) ( GLenum target );
extern GLCHECKFRAMEBUFFERSTATUS glCheckFramebufferStatus;

/*
	Render buffers
*/

#define GL_RENDERBUFFER 0x8D41
#define GL_MAX_RENDERBUFFER_SIZE 0x84E8

typedef void ( APIENTRYP GLGENRENDERBUFFERS ) ( GLsizei n, GLuint* renderbuffers );
extern GLGENRENDERBUFFERS glGenRenderbuffers;
typedef void ( APIENTRYP GLDELETERENDERBUFFERS ) ( GLsizei n, const GLuint* renderbuffers );
extern GLDELETERENDERBUFFERS glDeleteRenderbuffers;
typedef void ( APIENTRYP GLRENDERBUFFERSTORAGE ) ( GLenum target, GLenum internalformat, GLsizei width, GLsizei height );
extern GLRENDERBUFFERSTORAGE glRenderbufferStorage;
typedef void ( APIENTRYP GLBINDRENDERBUFFER ) ( GLenum target, GLuint renderbuffer );
extern GLBINDRENDERBUFFER glBindRenderbuffer;

/*
	Stencil test
*/

#define GL_INCR_WRAP 0x8507
#define GL_DECR_WRAP 0x8508

/*
	Transform feedback
*/

#define GL_INTERLEAVED_ATTRIBS 0x8C8C

#define GL_RASTERIZER_DISCARD 0x8C89

#define GL_TRANSFORM_FEEDBACK_BUFFER 0x8C8E

typedef void ( APIENTRYP GLTRANSFORMFEEDBACKVARYINGS ) ( GLuint program, GLsizei count, const char** varyings, GLenum bufferMode );
extern GLTRANSFORMFEEDBACKVARYINGS glTransformFeedbackVaryings;
typedef void ( APIENTRYP GLBINDBUFFERBASE ) ( GLenum target, GLuint index, GLuint buffer );
extern GLBINDBUFFERBASE glBindBufferBase;
typedef void ( APIENTRYP GLBEGINTRANSFORMFEEDBACK ) ( GLenum primitiveMode );
extern GLBEGINTRANSFORMFEEDBACK glBeginTransformFeedback;
typedef void ( APIENTRYP GLENDTRANSFORMFEEDBACK ) ();
extern GLENDTRANSFORMFEEDBACK glEndTransformFeedback;

/*
	Extension loader
*/

namespace GL
{
	extern void LoadExtensions();
}

#endif