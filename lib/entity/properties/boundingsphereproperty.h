/*
 * boundingsphereproperty.h
 *
 *  Created on: 4.11.2011
 *      Author: akin
 */

#ifndef BOUNDINGSPHEREPROPERTY_H_
#define BOUNDINGSPHEREPROPERTY_H_

#include <entity/property>
#include <entity/entity>
#include <map>

#define PROPERTY_BOUNDING_SPHERE_NAME "boundingsphere"

namespace ice
{

class BoundingSphereProperty : public Property
{
protected:
	typedef std::map< EntityKey , float > SphereType;
	SphereType spheres;
public:
	BoundingSphereProperty();
	virtual ~BoundingSphereProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	// Property specific methods.
	float& get( EntityKey entity );
};

} /* namespace ice */
#endif /* BOUNDINGSPHEREPROPERTY_H_ */
