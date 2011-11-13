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

namespace ice
{

class TimeProperty : public Property
{
public:
	const static std::string KEY;
protected:
	typedef std::map< EntityKey , Time > TimeType;
	TimeType timeData;

	Time last;
	Time current;
	Time diff;
public:
	TimeProperty();
	virtual ~TimeProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	Time& get( EntityKey key );
	std::map< EntityKey , Time >& getTime();

	void setCurrentTime( Time time );

	Time getDiff();
	Time getNow();
	Time getPrevious();
};

} /* namespace ice */
#endif /* TIMEPROPERTY_H_ */
