/*
 * entitytemplate.h
 *
 *  Created on: 9.11.2011
 *      Author: akin
 */

#ifndef ICE_ENTITYTEMPLATE_H_
#define ICE_ENTITYTEMPLATE_H_

#include "entity"

namespace ice
{
	class EntityTemplate
	{
	protected:
		static unsigned int s_id;
		static unsigned int genId();
		unsigned int sm_id;

		std::string name;
	public:
		EntityTemplate( std::string name = "" );
		virtual ~EntityTemplate();

		std::string getName();
		unsigned int getId() const;

		Entity create();
		virtual void attach( Entity& entity );
	};
} /* namespace ice */
#endif /* ENTITYTEMPLATE_H_ */
