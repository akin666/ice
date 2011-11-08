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
	public:
		EntityTemplate();
		virtual ~EntityTemplate();

		Entity create();
		virtual void attach( Entity& entity );
	};
} /* namespace ice */
#endif /* ENTITYTEMPLATE_H_ */
