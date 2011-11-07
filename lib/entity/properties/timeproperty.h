/*
 * timeproperty.h
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#ifndef TIMEPROPERTY_H_
#define TIMEPROPERTY_H_

#include <entity/property>
#include <entity/entity>
#include <system/common>
#include <map>

#define PROPERTY_TIME_NAME "time"

namespace ice
{

class TimeProperty : public Property
{
protected:
	typedef std::map< EntityKey , Time > TimeType;
	TimeType timeData;
public:
	TimeProperty();
	virtual ~TimeProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	Time& get( EntityKey key );
	std::map< EntityKey , Time >& getTime();
};

} /* namespace ice */
#endif /* TIMEPROPERTY_H_ */
