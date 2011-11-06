/*
 * entityfactory.h
 *
 *  Created on: 2.11.2011
 *      Author: akin
 */

#ifndef ICE_ENTITYFACTORY_H_
#define ICE_ENTITYFACTORY_H_

#include "entity"
#include <string>

namespace ice
{
	class EntityFactory
	{
	public:
		static void create( Entity& entity , ... );
		static void createFromComponentPtr( Entity& entity , ... );
	};
} /* namespace ice */
#endif /* ENTITYFACTORY_H_ */
