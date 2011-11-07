/*
 * shader.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <iostream>
#include "graphicsexception"

namespace ice
{
	class Shader
	{
	public:
		enum Type {
			UNKNOWN = 0,   // 0.0
			FRAGMENT = 1,  // 2.0
			VERTEX = 2,    // 2.0
			GEOMETRY = 3,  // 3.2
			CONTROL = 4,   // 4.0
			EVALUATION = 5 // 4.0
		};
	protected:
		Type m_type;
		unsigned int id;
	public:
		Shader();
		virtual ~Shader();

		void setType( Type type );
		void setTypeString( std::string type );

		unsigned int getId();

		bool load( const unsigned char *data , int length ) throw (GraphicsException);
	};
}

#endif /* SHADER_H_ */
