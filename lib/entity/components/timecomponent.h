/*
 * timecomponent.h
 *
 *  Created on: 31.10.2011
 *      Author: akin
 */

#ifndef TIMECOMPONENT_H_
#define TIMECOMPONENT_H_

#include <entity/cccomponent>
#include <entity/entity>
#include <datatypes/common.h>
#include <deque>
#include <entity/properties/timeproperty.h>
#include "timework.h"

#define COMPONENT_TIME_NAME "time"

namespace ice
{

class TimeComponent : public CCComponent
{
protected:
	std::deque<EntityKey> entities;

	TimeWork work;

	bool initialized;
	Time last;
	Time now;
	Time diff;

	TimeProperty *property;

	// EVIL! but, imagining that the work is just a package,
	// and this is the distributor. No need to save all data
	// twice or thrice.
	friend class TimeWork;
public:
	TimeComponent();
	virtual ~TimeComponent();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	virtual void start();
};

} /* namespace ice */
#endif /* TIMECOMPONENT_H_ */
