/*
 * meshproperty.h
 *
 *  Created on: 16.11.2011
 *      Author: akin
 */

#ifndef MESHPROPERTY_H_
#define MESHPROPERTY_H_

#include <entity/property>
#include <entity/entity>

namespace ice
{

class MeshProperty : public Property
{
public:
	const static std::string KEY;
public:
	MeshProperty();
	virtual ~MeshProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );
};

} /* namespace ice */
#endif /* MESHPROPERTY_H_ */
