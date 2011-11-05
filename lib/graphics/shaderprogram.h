/*
 * shaderprogram.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <iostream>
#include <vector>
#include <map>
#include "shader.h"
#include "uniform.h"
#include "attribute.h"

namespace ice
{
	class ShaderProgram
	{
	protected:
		std::map< std::string , Attribute *> attributes;
		std::map< std::string , Uniform *> uniforms;

		bool linking;
		unsigned int m_id;
	public:
		ShaderProgram();
		virtual ~ShaderProgram();

		unsigned int getId();

		Attribute *insertAttribute( std::string key );
		Uniform *insertUniform( std::string key );

		Attribute *getAttribute( std::string key );
		Uniform *getUniform( std::string key );

		void bind();
		static void bindDefault();

		// Shader creation functionality:
		void attach( Shader *piece );
		void link();

		std::string getError();

		bool linked();
	};
}

#endif /* SHADERPROGRAM_H_ */
