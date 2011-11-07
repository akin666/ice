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
#include "graphicsexception"

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

		Attribute *insertAttribute( std::string key ) throw (GraphicsException);
		Uniform *insertUniform( std::string key ) throw (GraphicsException);

		Attribute *getAttribute( std::string key ) throw (GraphicsException);
		Uniform *getUniform( std::string key ) throw (GraphicsException);

		void bind() throw (GraphicsException);
		static void bindDefault();

		// Shader creation functionality:
		void attach( Shader *piece ) throw (GraphicsException);
		void link() throw (GraphicsException);

		std::string getError();

		bool linked();
	};
}

#endif /* SHADERPROGRAM_H_ */
