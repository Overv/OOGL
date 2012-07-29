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

#ifndef OOGL_MESH_HPP
#define OOGL_MESH_HPP

#include <GL/Util/Image.hpp>
#include <GL/Math/Vec3.hpp>
#include <GL/Math/Vec2.hpp>
#include <vector>

namespace GL
{
	/*
		Internal vertex class
	*/
	struct Vertex
	{
		Vec3 Pos;
		Vec2 Tex;
		Vec3 Normal;
	};

	/*
		3D mesh container
	*/
	class Mesh
	{
	public:
		Mesh( const std::string& filename );

		const Vertex* Vertices() const;
		int VertexCount() const;

	private:
		std::vector<Vertex> vertices;
	};
}

#endif