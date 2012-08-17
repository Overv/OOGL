//
//  Window_OSX.mm
//  OOGL
//
//  Created by Jack Karamanian on 8/4/12.
//  Copyright (c) 2012 Jack Karamanian. All rights reserved.
//
#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>
#include <GL/Window/Window.hpp>

#ifdef OOGL_PLATFORM_OSX

namespace GL {
    GL::Key::key_t TranslateMacKeycode(ushort code);
    
    // A class to interact with the private state of a Window.
    class WindowInterface
    {
        GL::Window *window;
    public:
        WindowInterface(GL::Window *window)
        {
            this->window = window;
        }
        
        void SendEvent(GL::Event ev)
        {
            window->SendEvent(ev);
        }
        
        void Close()
        {
            window->SendEvent({.Type = GL::Event::Close});
            window->open = false;
        }
    };
}

@interface OOGLView: NSOpenGLView

-(id)initWithOOGLWindow:(GL::Window*)window;

@end

@implementation OOGLView {
    GL::WindowInterface *windowInterface;
}

-(id)initWithOOGLWindow:(GL::Window*)window {
    self = [super init];
    
    if (self) {
        windowInterface = new GL::WindowInterface(window);
    }
    
    return self;
}

-(void)keyUp:(NSEvent *)theEvent {
    GL::Event ev;
    ev.Type        = GL::Event::event_t::KeyUp;
    ev.Key.Code    = GL::TranslateMacKeycode(theEvent.keyCode);
    ev.Key.Shift   = theEvent.modifierFlags & NSShiftKeyMask;
    ev.Key.Alt     = theEvent.modifierFlags & NSAlternateKeyMask;
    ev.Key.Control = theEvent.modifierFlags & NSControlKeyMask;
    
    windowInterface->SendEvent(ev);

}

-(void)keyDown:(NSEvent *)theEvent {
    GL::Event ev;
    ev.Type        = GL::Event::event_t::KeyDown;
    ev.Key.Code    = GL::TranslateMacKeycode(theEvent.keyCode);
    ev.Key.Shift   = theEvent.modifierFlags & NSShiftKeyMask;
    ev.Key.Alt     = theEvent.modifierFlags & NSAlternateKeyMask;
    ev.Key.Control = theEvent.modifierFlags & NSControlKeyMask;
    
    windowInterface->SendEvent(ev);
    
}

-(void)mouseMoved:(NSEvent *)theEvent {
    GL::Event ev;
    ev.Type        = GL::Event::event_t::MouseMove;
    ev.Mouse.X     = [self.window mouseLocationOutsideOfEventStream].x;
    ev.Mouse.Y     = [self.window mouseLocationOutsideOfEventStream].y;
    ev.Mouse.Delta = theEvent.scrollingDeltaY;
    
    windowInterface->SendEvent(ev);
    
}

-(void)mouseUp:(NSEvent *)theEvent {
    // TODO: Add buttons.
    GL::Event ev;
    ev.Type        = GL::Event::event_t::MouseUp;
    ev.Mouse.X     = [self.window mouseLocationOutsideOfEventStream].x;
    ev.Mouse.Y     = [self.window mouseLocationOutsideOfEventStream].y;
    ev.Mouse.Delta = theEvent.scrollingDeltaY;
    
    windowInterface->SendEvent(ev);

}


-(void)mouseDown:(NSEvent *)theEvent {
    GL::Event ev;
    ev.Type        = GL::Event::event_t::MouseDown;
    ev.Mouse.X     = [self.window mouseLocationOutsideOfEventStream].x;
    ev.Mouse.Y     = [self.window mouseLocationOutsideOfEventStream].y;
    ev.Mouse.Delta = theEvent.scrollingDeltaY;
    
    windowInterface->SendEvent(ev);
}

-(BOOL)canBecomeKeyView {
    return YES;
}

-(void)dealloc {
    delete windowInterface;
}

@end

@interface OOGLAppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>

-(id)initWithOOGLWindow:(GL::Window*) window;

@end

@implementation OOGLAppDelegate {
    GL::WindowInterface *windowInterface;
}

-(id)initWithOOGLWindow:(GL::Window *)window {
    self = [super init];
    
    if (self) {
        windowInterface = new GL::WindowInterface(window);
    }
    
    return self;
}
-(void)applicationDidHide:(NSNotification *)notification {
   
}
-(void)windowWillClose:(NSNotification *)notification {
    windowInterface->Close();
}

-(void)dealloc {
    delete windowInterface;
}

@end

namespace GL {
    
    Window::Window( uint width, uint height, const std::string& title, WindowStyle::window_style_t style )
    {
        open = true;
        delegate = [[OOGLAppDelegate alloc] initWithOOGLWindow:this];
        
        // Initialize the shared NSApplication
        [NSApplication sharedApplication];
        [NSApp setDelegate:delegate];
        [NSApp activateIgnoringOtherApps:YES];
        
        // Thank you GLFW.
        ProcessSerialNumber psn = { 0, kCurrentProcess };
        TransformProcessType(&psn, kProcessTransformToForegroundApplication);
        
        SetFrontProcess(&psn);
        
        context = nullptr;
        NSRect rect = NSMakeRect(0, 0, width, height);
        NSUInteger styleMask = NSTitledWindowMask | NSClosableWindowMask;
        
        
        window =  [[NSWindow alloc] initWithContentRect:rect styleMask:styleMask backing: NSBackingStoreBuffered   defer:NO];
        [window setDelegate:delegate];
        [window setAcceptsMouseMovedEvents:YES];
                [window setIsVisible:YES];
        
        [window setTitle:@(title.c_str())];
        
        NSOpenGLContext *ctxt = GetContext().GetNSOpenGLContext();
        OOGLView *glView = [[OOGLView alloc] initWithOOGLWindow:this];
        glView.openGLContext = ctxt;
        
        [window setContentView:glView];
        [window makeFirstResponder:glView];
        [window makeKeyAndOrderFront:nil];
        [window makeKeyWindow];
    }
    
    Window::~Window()
    {
        delete context;
    }
    
    void Window::SetPos(int x, int y)
    {
        [window setPosition:CGPointMake(x, y)];
    }
    
    void Window::SetSize(uint width, uint height)
    {
       [window setSize:NSMakeSize(width, height)];
    }
    
    void Window::SetTitle(const std::string &title)
    {
        [window setTitle:@(title.c_str())];
    }
    
    void Window::SetVisible(bool visible)
    {
        [window setVisible:visible];
    }
    
    void Window::Close()
    {
        [window setVisible:NO];
        this->open = false;
    }
    
    bool Window::GetEvent(GL::Event &ev)
    {
        NSEvent *event = nil;
        do {
            event = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:YES];
            
            [NSApp sendEvent:event];
            [NSApp updateWindows];
        } while (event);
        
		// Return oldest event - if available
		if ( events.empty() ) return false;
		
		ev = events.front();
		events.pop();
        
		return true;
    }
    
    void Window::SendEvent(GL::Event event)
    {
        events.push(event);
    }
    
    Context& Window::GetContext(uchar color, uchar depth, uchar stencil, uchar antialias)
    {
        if ( context )
			return *context;
		else
			return *( context = new Context( color, depth, stencil, antialias) );
    }
    
    void Window::Present()
    {
        context->Activate();

        [context->GetNSOpenGLContext() flushBuffer];
    }
    
    
}

GL::Key::key_t GL::TranslateMacKeycode(ushort code)
{
    // Thank you for this extremely convienent
    // mac keycode table GLFW!
    static const GL::Key::key_t table[128] =
    {
        /* 00 */ GL::Key::key_t::A,
        /* 01 */ GL::Key::key_t::S,
        /* 02 */ GL::Key::key_t::D,
        /* 03 */ GL::Key::key_t::F,
        /* 04 */ GL::Key::key_t::H,
        /* 05 */ GL::Key::key_t::G,
        /* 06 */ GL::Key::key_t::Z,
        /* 07 */ GL::Key::key_t::X,
        /* 08 */ GL::Key::key_t::C,
        /* 09 */ GL::Key::key_t::V,
        /* 0a */ GL::Key::key_t::Unknown, // Grave accent?
        /* 0b */ GL::Key::key_t::B,
        /* 0c */ GL::Key::key_t::Q,
        /* 0d */ GL::Key::key_t::W,
        /* 0e */ GL::Key::key_t::E,
        /* 0f */ GL::Key::key_t::R,
        /* 10 */ GL::Key::key_t::Y,
        /* 11 */ GL::Key::key_t::T,
        /* 12 */ GL::Key::key_t::Num1,
        /* 13 */ GL::Key::key_t::Num2,
        /* 14 */ GL::Key::key_t::Num3,
        /* 15 */ GL::Key::key_t::Num4,
        /* 16 */ GL::Key::key_t::Num6,
        /* 17 */ GL::Key::key_t::Num5,
        /* 18 */ GL::Key::key_t::Equals,
        /* 19 */ GL::Key::key_t::Num9,
        /* 1a */ GL::Key::key_t::Num7,
        /* 1b */ GL::Key::key_t::Hyphen,
        /* 1c */ GL::Key::key_t::Num8,
        /* 1d */ GL::Key::key_t::Num0,
        /* 1e */ GL::Key::key_t::RightBracket,
        /* 1f */ GL::Key::key_t::O,
        /* 20 */ GL::Key::key_t::U,
        /* 21 */ GL::Key::key_t::LeftBracket,
        /* 22 */ GL::Key::key_t::I,
        /* 23 */ GL::Key::key_t::P,
        /* 24 */ GL::Key::key_t::Enter,
        /* 25 */ GL::Key::key_t::L,
        /* 26 */ GL::Key::key_t::J,
        /* 27 */ GL::Key::key_t::Quote, //Apostrophe
        /* 28 */ GL::Key::key_t::K,
        /* 29 */ GL::Key::key_t::Semicolon,
        /* 2a */ GL::Key::key_t::Backslash,
        /* 2b */ GL::Key::key_t::Comma,
        /* 2c */ GL::Key::key_t::Slash,
        /* 2d */ GL::Key::key_t::N,
        /* 2e */ GL::Key::key_t::M,
        /* 2f */ GL::Key::key_t::Period,
        /* 30 */ GL::Key::key_t::Tab,
        /* 31 */ GL::Key::key_t::Space,
        /* 32 */ GL::Key::key_t::Unknown, // World 1?
        /* 33 */ GL::Key::key_t::Backspace,
        /* 34 */ GL::Key::key_t::Unknown,
        /* 35 */ GL::Key::key_t::Escape,
        /* 36 */ GL::Key::key_t::Unknown, // Right super
        /* 37 */ GL::Key::key_t::Unknown, // Left super
        /* 38 */ GL::Key::key_t::Shift,   // Left shift
        /* 39 */ GL::Key::key_t::Unknown, // Caps lock
        /* 3a */ GL::Key::key_t::Alt,
        /* 3b */ GL::Key::key_t::Control, // Left control
        /* 3c */ GL::Key::key_t::Shift, // Right shift
        /* 3d */ GL::Key::key_t::Alt, //Right alt
        /* 3e */ GL::Key::key_t::Control, // Right control
        /* 3f */ GL::Key::key_t::Unknown, /* Function */
        /* 40 */ GL::Key::key_t::Unknown, // F17
        /* 41 */ GL::Key::key_t::Period, // Num-pad decimal
        /* 42 */ GL::Key::key_t::Unknown,
        /* 43 */ GL::Key::key_t::Multiply,
        /* 44 */ GL::Key::key_t::Unknown,
        /* 45 */ GL::Key::key_t::Add,
        /* 46 */ GL::Key::key_t::Unknown,
        /* 47 */ GL::Key::key_t::Unknown, /* Numlock. Really KeypadClear... */
        /* 48 */ GL::Key::key_t::Unknown, /* VolumeUp */
        /* 49 */ GL::Key::key_t::Unknown, /* VolumeDown */
        /* 4a */ GL::Key::key_t::Unknown, /* Mute */
        /* 4b */ GL::Key::key_t::Divide, // Keypad
        /* 4c */ GL::Key::key_t::Enter, // Keypad
        /* 4d */ GL::Key::key_t::Unknown,
        /* 4e */ GL::Key::key_t::Subtract, // Keypad
        /* 4f */ GL::Key::key_t::Unknown, // F18
        /* 50 */ GL::Key::key_t::Unknown, // F19
        /* 51 */ GL::Key::key_t::Equals, // Keypad
        /* 52 */ GL::Key::key_t::Numpad0,
        /* 53 */ GL::Key::key_t::Numpad1,
        /* 54 */ GL::Key::key_t::Numpad2,
        /* 55 */ GL::Key::key_t::Numpad3,
        /* 56 */ GL::Key::key_t::Numpad4,
        /* 57 */ GL::Key::key_t::Numpad5,
        /* 58 */ GL::Key::key_t::Numpad6,
        /* 59 */ GL::Key::key_t::Numpad7,
        /* 5a */ GL::Key::key_t::Unknown, // F20
        /* 5b */ GL::Key::key_t::Numpad8,
        /* 5c */ GL::Key::key_t::Numpad9,
        /* 5d */ GL::Key::key_t::Unknown,
        /* 5e */ GL::Key::key_t::Unknown,
        /* 5f */ GL::Key::key_t::Unknown,
        /* 60 */ GL::Key::key_t::F5,
        /* 61 */ GL::Key::key_t::F6,
        /* 62 */ GL::Key::key_t::F7,
        /* 63 */ GL::Key::key_t::F3,
        /* 64 */ GL::Key::key_t::F8,
        /* 65 */ GL::Key::key_t::F9,
        /* 66 */ GL::Key::key_t::Unknown,
        /* 67 */ GL::Key::key_t::F11,
        /* 68 */ GL::Key::key_t::Unknown,
        /* 69 */ GL::Key::key_t::Unknown, // F13
        /* 6a */ GL::Key::key_t::Unknown, // F16
        /* 6b */ GL::Key::key_t::Unknown, // F14
        /* 6c */ GL::Key::key_t::Unknown,
        /* 6d */ GL::Key::key_t::F10,
        /* 6e */ GL::Key::key_t::Unknown,
        /* 6f */ GL::Key::key_t::F12,
        /* 70 */ GL::Key::key_t::Unknown,
        /* 71 */ GL::Key::key_t::Unknown, // F15
        /* 72 */ GL::Key::key_t::Insert, /* Really Help... */
        /* 73 */ GL::Key::key_t::Home,
        /* 74 */ GL::Key::key_t::PageUp,
        /* 75 */ GL::Key::key_t::Delete,
        /* 76 */ GL::Key::key_t::F4,
        /* 77 */ GL::Key::key_t::End,
        /* 78 */ GL::Key::key_t::F2,
        /* 79 */ GL::Key::key_t::PageDown,
        /* 7a */ GL::Key::key_t::F1,
        /* 7b */ GL::Key::key_t::Left,
        /* 7c */ GL::Key::key_t::Right,
        /* 7d */ GL::Key::key_t::Down,
        /* 7e */ GL::Key::key_t::Up,
        /* 7f */ GL::Key::key_t::Unknown,
    };
    
    return table[code];
}

#endif
