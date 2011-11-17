/*
 * mesh.h
 *
 *  Created on: 17.11.2011
 *      Author: akin
 */

#ifndef MESH_H_
#define MESH_H_

#include <glm/glm>
#include "graphics.h"

namespace ice
{
	// Base type
	class MeshData
	{
	protected:
		typedef glm::vec3 VertexType;
		typedef glm::vec2 TextureType;
		typedef glm::vec3 NormalType;
		typedef glm::vec4 ColorType;

		VertexType *vertexCoordinates;
		TextureType *textureCoordinates;
		NormalType *normalCoordinates;
		ColorType *colorCoordinates;

		int count;
	public:
		MeshData();
		MeshData( const MeshData& other );
		virtual ~MeshData();
		virtual void clear();
		void copy( const MeshData& other );
	};

	// Base type
	class MeshIndex
	{
	protected:
		typedef unsigned short IndexType;
		IndexType *indexArray;

		int count;
		Graphics::Primitives type;
	public:
		MeshIndex();
		MeshIndex( const MeshIndex& other );
		virtual ~MeshIndex();
		virtual void clear();
		void copy( const MeshIndex& other );
	};

	// Simple mesh type, that contains all the stuff to
	// create something simple from one type of data.
	class Mesh : public MeshData , public MeshIndex
	{
	public:
		Mesh();
		Mesh( const Mesh& other );
		virtual ~Mesh();
		virtual void clear();
		void copy( const Mesh& other );
	};

	// Mesh group.
	// Single package of MeshData
	// combined with MeshPart, creates more complex Mesh
	// than the Mesh class.
	class MeshGroup : public MeshData
	{
	public:
		MeshGroup();
		MeshGroup( const MeshGroup& other );
		virtual ~MeshGroup();
		virtual void clear();
		void copy( const MeshGroup& other );
	};

	class MeshPart : public MeshIndex
	{
	public:
		MeshPart();
		MeshPart( const MeshPart& other );
		virtual ~MeshPart();
		virtual void clear();
		void copy( const MeshPart& other );
	};
} /* namespace ice */
#endif /* MESH_H_ */
