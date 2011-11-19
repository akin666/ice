/*
 * mesh.cpp
 *
 *  Created on: 17.11.2011
 *      Author: akin
 */

#include "mesh.h"
#include <iostream>
#include <cstring>

ice::MeshData::MeshData()
: vertexCoordinates( NULL ),
  textureCoordinates( NULL ),
  normalCoordinates( NULL ),
  colorCoordinates( NULL ),
  count( 0 )
{
}

ice::MeshData::MeshData(const MeshData & other)
: vertexCoordinates( NULL ),
  textureCoordinates( NULL ),
  normalCoordinates( NULL ),
  colorCoordinates( NULL ),
  count( other.count )
{
	copy( other );
}

ice::MeshData::~MeshData()
{
	ice::MeshData::clear();
}

void ice::MeshData::clear()
{
	if( vertexCoordinates != NULL ||
		textureCoordinates != NULL ||
		normalCoordinates != NULL ||
		colorCoordinates != NULL )
	{
		delete[] vertexCoordinates;
		delete[] textureCoordinates;
		delete[] normalCoordinates;
		delete[] colorCoordinates;

		vertexCoordinates = NULL;
		textureCoordinates = NULL;
		normalCoordinates = NULL;
		colorCoordinates = NULL;

		count = 0;
	}
}

void ice::MeshData::copy(const MeshData & other)
{
	if( other.count > 0 )
	{
		ice::MeshData::clear();
		count = other.count;

		vertexCoordinates = new VertexType[count];
		textureCoordinates = new TextureType[count];
		normalCoordinates = new NormalType[count];
		colorCoordinates = new ColorType[count];

		::memcpy( vertexCoordinates , other.vertexCoordinates , count * sizeof( VertexType ) );
		::memcpy( textureCoordinates , other.textureCoordinates , count * sizeof( TextureType ) );
		::memcpy( normalCoordinates , other.normalCoordinates , count * sizeof( NormalType ) );
		::memcpy( colorCoordinates , other.colorCoordinates , count * sizeof( ColorType ) );
	}
}





//////////////////////
// MeshDataBuffer
/////////////////////

ice::MeshDataBuffer::MeshDataBuffer()
: count( 0 )
{
}

ice::MeshDataBuffer::~MeshDataBuffer()
{
}




//////////////////////
// MeshIndex
/////////////////////

ice::MeshIndex::MeshIndex()
: indexArray( NULL ),
  count( 0 ),
  type( Graphics::triangles )
{
}

ice::MeshIndex::MeshIndex(const MeshIndex & other)
: indexArray( NULL ),
  count( other.count )
{
	copy( other );
}

ice::MeshIndex::~MeshIndex()
{
	ice::MeshIndex::clear();
}

void ice::MeshIndex::clear()
{
	if( indexArray != NULL )
	{
		delete[] indexArray;
		indexArray = NULL;
		count = 0;
	}
}

void ice::MeshIndex::copy(const MeshIndex & other)
{
	if( other.count > 0 )
	{
		ice::MeshIndex::clear();
		count = other.count;

		indexArray = new IndexType[count];

		::memcpy( indexArray , other.indexArray , count * sizeof( IndexType ) );
	}
}




//////////////////////
// MeshIndexBuffer
/////////////////////

ice::MeshIndexBuffer::MeshIndexBuffer()
: count( 0 ),
  type( Graphics::triangles )
{
}

ice::MeshIndexBuffer::~MeshIndexBuffer()
{
}

