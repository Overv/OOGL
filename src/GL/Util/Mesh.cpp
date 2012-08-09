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

#include <GL/Util/Mesh.hpp>
#include <GL/Math/Vec3.hpp>
#include <fstream>

namespace GL
{
	/*
		Internal OBJ parsing facilities
	*/
	enum mode
	{
		MODE_NONE,
		MODE_UNKNOWN,
		MODE_VERTEX,
		MODE_NORMAL,
		MODE_TEXTURE,
		MODE_FACE
	};

	struct face
	{
		int v1, v2, v3;
		int t1, t2, t3;
		int n1, n2, n3;
	};

	inline bool IS_SPACING( char c )
	{
		return c == ' ' || c == '\n' || c == '\t';
	}

	inline int readInt( char* buf, int& out )
	{
		// Determine length and sign of number
		int l = 0;
		bool neg = false;
		if ( buf[0] == '-' ) { neg = true; buf++; }
		while ( buf[l] >= '0' && buf[l] <= '9' ) l++;

		// Multiply each digit by the appropriate power of 10
		int n = 0;
		int p = 1;
		for ( int i = l - 1; i >= 0; i-- ) {
			n += ( buf[i] - '0' ) * p;
			p *= 10;
		}

		// Handle sign
		if ( neg ) {
			out = -n;
			l++;
		} else
			out = n;

		return l;
	}

	inline int readFloat( char* buf, float& out )
	{
		// Read natural part
		bool neg = buf[0] == '-';
		int nat, frac;
		int ln = readInt( buf, nat );

		// Read fractional part
		buf += ln + 1;
		int lf = readInt( buf, frac );
		int p = 1;
		for ( int i = 0; i < lf; i++ ) p *= 10;

		// Handle sign
		if ( neg )
			out = nat - frac / (float)p;
		else
			out = nat + frac / (float)p;

		return ln + lf + 1;
	}

	int readVector( char* buf, Vec3& out )
	{
		int i = 0;
		while ( IS_SPACING( *buf ) ) { buf++; i++; };
		buf += readFloat( buf, out.X );
		while ( IS_SPACING( *buf ) ) { buf++; i++; }
		buf += readFloat( buf, out.Y );
		while ( IS_SPACING( *buf ) ) { buf++; i++; }
		buf += readFloat( buf, out.Z );
		return i;
	}

	int readFace( char* buf, face& out )
	{
		int i = 0;
		while ( IS_SPACING( *buf ) ) { buf++; i++; };
		buf += readInt( buf, out.v1 ) + 1;
		buf += readInt( buf, out.t1 ) + 1;
		buf += readInt( buf, out.n1 ) + 1;
		while ( IS_SPACING( *buf ) ) { buf++; i++; }
		buf += readInt( buf, out.v2 ) + 1;
		buf += readInt( buf, out.t2 ) + 1;
		buf += readInt( buf, out.n2 ) + 1;
		while ( IS_SPACING( *buf ) ) { buf++; i++; }
		buf += readInt( buf, out.v3 ) + 1;
		buf += readInt( buf, out.t3 ) + 1;
		buf += readInt( buf, out.n3 ) + 1;
		return i;
	}

	Mesh::Mesh( const std::string& filename )
	{
		// Read file into memory
		std::ifstream file( filename.c_str(), std::ios::in | std::ios::ate );
		if ( !file.is_open() ) throw FileException();
		unsigned int fileLen = (unsigned int)file.tellg();
		file.seekg( 0, std::ios::beg );
		std::vector<char> buf( fileLen );
		file.read( &buf[0], fileLen );
		file.close();

		// Data
		int approxMem = 295 + fileLen / 1024 * 11;
		std::vector<Vec3> vectors; vectors.reserve( approxMem );
		std::vector<Vec3> normals; normals.reserve( approxMem );
		std::vector<Vec2> texcoords; texcoords.reserve( approxMem );
		vertices.reserve( approxMem );

		// Parser state
		bool inComment = false;
		int mode = MODE_NONE;
		Vec3 v3;
		face f;

		// Parse
		for ( unsigned int i = 0; i < fileLen; i++ )
		{
			// Ignore comment lines
			if ( buf[i] == '#' ) {
				inComment = true;
				continue;
			} else if ( inComment && buf[i] != '\n' ) {
				continue;
			} else if ( inComment && buf[i] == '\n' ) {
				inComment = false;
				continue;
			}

			// Find a command
			if ( mode == MODE_NONE && !IS_SPACING( buf[i] ) ) {
				if ( buf[i] == 'f' )
					mode = MODE_FACE;
				else if ( buf[i] == 'v' ) {
					if ( IS_SPACING( buf[i+1] ) )
						mode = MODE_VERTEX;
					else if ( buf[i+1] == 'n' )
						mode = MODE_NORMAL;
					else if ( buf[i+1] == 't' )
						mode = MODE_TEXTURE;
					i++;
				} else
					mode = MODE_UNKNOWN;
			} else if ( mode != MODE_NONE ) {
				switch ( mode )
				{
				case MODE_UNKNOWN:
					if ( buf[i] == '\n' )
						mode = MODE_NONE;
					break;

				case MODE_VERTEX:
					i += readVector( &buf[i], v3 );
					vectors.push_back( v3 );
					mode = MODE_NONE;
					break;

				case MODE_NORMAL:
					i += readVector( &buf[i], v3 );
					normals.push_back( v3 );
					mode = MODE_NONE;
					break;

				case MODE_TEXTURE:
					i += readVector( &buf[i], v3 );
					texcoords.push_back( Vec2( v3.X, v3.Y ) );
					mode = MODE_NONE;
					break;
			
				case MODE_FACE:
					i += readFace( &buf[i], f );
					
					Vertex vertex = {
						vectors[f.v1 - 1],
						texcoords[f.t1 - 1],
						normals[f.n1 - 1]
					};
					vertices.push_back( vertex );

					vertex.Pos = vectors[f.v2 - 1];
					vertex.Tex = texcoords[f.t2 - 1];
					vertex.Normal = normals[f.n2 - 1];
					vertices.push_back( vertex );

					vertex.Pos = vectors[f.v3 - 1];
					vertex.Tex = texcoords[f.t3 - 1];
					vertex.Normal = normals[f.n3 - 1];
					vertices.push_back( vertex );

					mode = MODE_NONE;
					break;
				}
			}
		}
	}

	const Vertex* Mesh::Vertices() const
	{
		return &vertices[0];
	}

	int Mesh::VertexCount() const
	{
		return vertices.size();
	}
}
