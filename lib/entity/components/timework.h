/*
 * timework.h
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#ifndef TIMEWORK_H_
#define TIMEWORK_H_

#include <entity/componentwork>

namespace ice
{

class TimeWork : public ComponentWork
{
public:
	TimeWork( Component& parent );
	virtual ~TimeWork();

	virtual bool begin();
	virtual void run();
};

} /* namespace ice */
#endif /* TIMEWORK_H_ */
