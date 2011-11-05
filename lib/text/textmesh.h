/*
 * textmesh.h
 *
 *  Created on: 5.8.2011
 *      Author: akin
 */

#ifndef TEXTMESH_H_
#define TEXTMESH_H_

#include <graphics/shaderprogram.h>
#include <graphics/uniform.h>
#include <graphics/attribute.h>
#include <graphics/bufferobject.h>
#include <font/font.h>
#include <vector>
#include <glm/glm>

namespace ice
{
	class TextMesh
	{
	protected:
		ShaderProgram *shader;

		Uniform *tex;
		Uniform *modelo;
		Uniform *lense;
		Uniform *texMatrix;

		Attribute *vertex;
		Attribute *vertexColor;
		Attribute *coordinates;

		BufferObject vertexBuffer;
		BufferObject textureBuffer;
		BufferObject colorBuffer;
		int vertexCount;
	public:
		Font *font;

		std::vector< glm::vec3 > vertexes;
		std::vector< glm::vec2 > textureCoordinates;
		std::vector< Color<float> > colors;

		TextMesh();
		virtual ~TextMesh();

		void setShader( ShaderProgram *prog );

		void draw( glm::mat4x4& model );

		void apply();
	};
} /* namespace ice */
#endif /* TEXTMESH_H_ */
