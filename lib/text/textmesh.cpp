/*
 * textmesh.cpp
 *
 *  Created on: 5.8.2011
 *      Author: akin
 */

#include "textmesh.h"
#include <system/global>
#include <graphics/viewport.h>

namespace ice
{

	TextMesh::TextMesh()
	{
	}

	TextMesh::~TextMesh()
	{
	}

	void TextMesh::draw( glm::mat4x4& model )
	{
		if( shader != NULL )
		{
			Viewport *ui = Global<Viewport>::get("UI");
			if( ui == NULL )
			{
				return;
			}

			shader->bind();

			// set matrixes.
			modelo->set( model );
			lense->set( ui->getProjectionMatrix() );
			texMatrix->set( font->getTextureMatrix() );

			vertex->enable();
			coordinates->enable();
			vertexColor->enable();

			tex->bindTexture( 0 , font->getTexture().getTextureId() );

			vertexBuffer.bind( Graphics::arrayBuffer );
			vertex->setPointer( 3 , GL_FLOAT , 0 );

			textureBuffer.bind( Graphics::arrayBuffer );
			coordinates->setPointer( 2 , GL_FLOAT , 0 );

			colorBuffer.bind( Graphics::arrayBuffer );
			vertexColor->setPointer( 4 , GL_FLOAT , 0 );

			glDrawArrays( GL_TRIANGLES , 0 , vertexCount );
		}
	}

	void TextMesh::setShader( ShaderProgram *prog )
	{
		shader = prog;

		if( shader != NULL )
		{
			lense =  shader->getUniform( "lense" );
			modelo = shader->getUniform( "model" );
			tex = shader->getUniform( "tex" );
			texMatrix = shader->getUniform( "texMatrix" );

			vertex = shader->getAttribute( "vertex" );
			vertexColor = shader->getAttribute( "vertexColor" );
			coordinates = shader->getAttribute( "coordinates" );

			if( lense == NULL ||
				modelo == NULL ||
				tex == NULL ||
				vertex == NULL ||
				vertexColor == NULL ||
				coordinates == NULL )
			{
				shader = NULL;
				std::cout << "One or more shader attributes missing for simplemesh" << std::endl;
			}
		}
	}

	void TextMesh::apply()
	{
		vertexCount = vertexes.size();

		vertexBuffer.set(
				vertexCount * sizeof(glm::vec3) ,
				&vertexes[0],
				Graphics::gpu,
				Graphics::once );

		textureBuffer.set(
				vertexCount * sizeof(glm::vec2) ,
				&textureCoordinates[0],
				Graphics::gpu,
				Graphics::once );

		colorBuffer.set(
				vertexCount * sizeof(glm::vec4) ,
				&colors[0],
				Graphics::gpu,
				Graphics::once );
	}
}
