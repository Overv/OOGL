//
//  Context_OSX.cpp
//  OOGL
//
//  Created by Jack Karamanian on 8/4/12.
//  Copyright (c) 2012 Jack Karamanian. All rights reserved.
//

#include <GL/GL/Context.hpp>
#include <OpenGL/OpenGL.h>
#include <Cocoa/Cocoa.h>

namespace GL {
    Context::Context( uchar color, uchar depth, uchar stencil, uint antialias ){
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
        owned = true;
    }
    
    Context::Context()
	{
		
		owned = false;
        
		glGetIntegerv( GL_VIEWPORT, (GLint*)&defaultViewport );
        
		//gettimeofday( &timeOffset, NULL );
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
}
