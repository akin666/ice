/*
 * entity.h
 *
 *  Created on: 14.10.2011
 *      Author: akin
 */

#ifndef ICE_ENTITY_H_
#define ICE_ENTITY_H_

namespace ice
{
	typedef unsigned int EntityKey;

	class Entity
	{
	protected:
		static unsigned int s_id;
		static unsigned int genId();
	public:
		Entity();
		Entity( const Entity& other );
		Entity( EntityKey key );
		virtual ~Entity();

		EntityKey id;
	};
} /* namespace ice */
#endif /* ENTITY_H_ */
