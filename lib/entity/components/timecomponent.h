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
#include <system/common>
#include <system/clock>
#include <deque>
#include <entity/properties/timeproperty.h>
#include "timework.h"

namespace ice
{

class TimeComponent : public CCComponent
{
public:
	const static std::string KEY;
protected:
	std::deque<EntityKey> entities;

	Clock clock;
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
	TimeComponent() throw (ComponentException);
	virtual ~TimeComponent();

	virtual void attach( Entity& entity ) throw (ComponentException);
	virtual void detach( Entity& entity ) throw (ComponentException);

	virtual void start() throw (ComponentException);
};

} /* namespace ice */
#endif /* TIMECOMPONENT_H_ */
