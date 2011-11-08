/*
 * mutableentitytemplate.h
 *
 *  Created on: 9.11.2011
 *      Author: akin
 */

#ifndef ICE_MUTABLEENTITYTEMPLATE_H_
#define ICE_MUTABLEENTITYTEMPLATE_H_

#include "entitytemplate"
#include "component"
#include <deque>

namespace ice
{

class MutableEntityTemplate : public EntityTemplate
{
protected:
	std::deque<Component&> components;
	std::deque<EntityTemplate&> templates;
public:
	MutableEntityTemplate();
	virtual ~MutableEntityTemplate();

	void attach( Component& component );
	void attach( EntityTemplate& tpl );

	virtual void attach( Entity& entity );
};

} /* namespace ice */
#endif /* MUTABLEENTITYTEMPLATE_H_ */
