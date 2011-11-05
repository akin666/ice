/*
 * testboxcomponent.h
 *
 *  Created on: 3.11.2011
 *      Author: akin
 */

#ifndef TESTBOXCOMPONENT_H_
#define TESTBOXCOMPONENT_H_

#include <entity/component>
#include <entity/entity>
#include <deque>
#include <entity/properties/positionproperty.h>

#define COMPONENT_TESTBOX_NAME "testbox"

namespace ice
{

class TestBoxComponent : public Component
{
protected:
	std::deque<EntityKey> entities;

	PositionProperty *positionProperty;

public:
	TestBoxComponent();
	virtual ~TestBoxComponent();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	virtual void start();
};

} /* namespace ice */
#endif /* TESTBOXCOMPONENT_H_ */
