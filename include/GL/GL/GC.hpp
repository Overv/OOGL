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

#ifndef OOGL_GC_HPP
#define OOGL_GC_HPP

#include <GL/Platform.hpp>
#include <cstdio> // temp
#include <map>

namespace GL
{
	/*
		OpenGL object creation/destruction function prototypes
	*/
	typedef void ( APIENTRYP createFunc ) ( GLsizei, GLuint* );
	typedef void ( APIENTRYP deleteFunc ) ( GLsizei, const GLuint* );
	typedef void ( APIENTRYP deleteFunc2 ) ( GLuint );

	/*
		OpenGL object garbage collector
	*/
	class GC
	{
	public:		
		void Create( GLuint& obj, createFunc c, deleteFunc d )
		{
			c( 1, &obj );
			refs.insert( std::pair<GLuint, uint>( obj, 1 ) );
			
			this->d = d;
			this->d2 = 0;

			printf( "%p [C] (%d)\n", this, obj );
		}

		int Create( const GLuint& obj, deleteFunc2 d2 )
		{
			refs.insert( std::pair<GLuint, uint>( obj, 1 ) );

			this->d = 0;
			this->d2 = d2;

			printf( "%p [C2] (%d)\n", this, obj );
			
			return obj;
		}

		void Copy( const GLuint& from, GLuint& to, bool destructive = false )
		{
			if ( destructive )
				Destroy( to );

			to = from;
			refs[from]++;
		}

		void Destroy( GLuint& obj )
		{
			if ( --refs[obj] == 0 )
			{
				if ( d != 0 ) { d( 1, &obj ); printf( "%p [D] (%d)\n", this, obj ); } else { d2( obj ); printf( "%p [D2] (%d)\n", this, obj ); }
				refs.erase( obj );
			}
		}

	private:
		std::map<GLuint, uint> refs;
		deleteFunc d;
		deleteFunc2 d2;
	};
}

#endif