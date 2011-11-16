/*
 * skeletonproperty.h
 *
 *  Created on: 16.11.2011
 *      Author: akin
 */

#ifndef SKELETONPROPERTY_H_
#define SKELETONPROPERTY_H_

#include <entity/property>
#include <entity/entity>

namespace ice
{

class SkeletonProperty : public Property
{
public:
	const static std::string KEY;
public:
	SkeletonProperty();
	virtual ~SkeletonProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );
};

} /* namespace ice */
#endif /* SKELETONPROPERTY_H_ */
