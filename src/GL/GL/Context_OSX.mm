/*
     Copyright (C) 2012 Jack Karamanian
     
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

#include <GL/GL/Context.hpp>
#include <Cocoa/Cocoa.h>
#include <sys/time.h>

namespace GL {
    
    Context::Context( uchar color, uchar depth, uchar stencil, uint antialias, id window )
    {
        owned = true;
        NSOpenGLPixelFormatAttribute params[] = {

            NSOpenGLPFAColorSize, color,
            NSOpenGLPFADepthSize, depth,
            NSOpenGLPFAStencilSize, stencil, 
            NSOpenGLPFASamples, antialias,
            NSOpenGLPFADoubleBuffer, 1,
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            0
        };
        
        NSOpenGLPixelFormat *format = [[NSOpenGLPixelFormat alloc] initWithAttributes:params];
        
        this->context = [[NSOpenGLContext alloc] initWithFormat:format shareContext:nil];
        [context makeCurrentContext];
        glViewport(0, 0, [window frame].size.width, [window frame].size.height);
        glGetIntegerv( GL_VIEWPORT, (GLint*)&defaultViewport );
        
        
        gettimeofday(&timeOffset, NULL);
    }
    
    Context::Context()
	{
		
		owned = false;
        // TODO: I don't know what to do here.
		glGetIntegerv( GL_VIEWPORT, (GLint*)&defaultViewport );
        
	}
    
    Context::~Context()
    {
        // TODO: Add teardown stuff
        // Does ARC clean up the context?
    }
    
    void Context::Activate()
    {
        if([NSOpenGLContext currentContext] != this->context)
            [context makeCurrentContext];
    }
    
    void Context::SetVerticalSync(bool enabled)
    {
        GLint sync = enabled ? 1 : 0;
        [[NSOpenGLContext currentContext] setValues:&sync forParameter:NSOpenGLCPSwapInterval];
    }
    
    float Context::Time()
    {
        timeval time;
		gettimeofday( &time, NULL );
        
		return time.tv_sec - timeOffset.tv_sec + ( time.tv_usec - timeOffset.tv_usec ) / 1000000.0f;
    }
}
