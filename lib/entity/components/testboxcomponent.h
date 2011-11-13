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

namespace ice
{

class TestBoxComponent : public Component
{
public:
	const static std::string KEY;
protected:
	std::deque<EntityKey> entities;

	PositionProperty *positionProperty;

public:
	TestBoxComponent() throw (ComponentException);
	virtual ~TestBoxComponent();

	virtual void attach( Entity& entity ) throw (ComponentException);
	virtual void detach( Entity& entity ) throw (ComponentException);

	virtual void start() throw (ComponentException);
};

} /* namespace ice */
#endif /* TESTBOXCOMPONENT_H_ */
