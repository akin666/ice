/*
 * forceproperty.h
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#ifndef FORCEPROPERTY_H_
#define FORCEPROPERTY_H_

#include <entity/property>
#include <entity/entity>
#include <glm/glm>
#include <map>

#define PROPERTY_FORCE_NAME "force"

namespace ice
{

class ForceProperty : public Property
{
public:
	class Data {
	public:
		glm::vec3 position;
		glm::quat orientation;
	};
protected:
	typedef std::map< EntityKey , Data > ForceType;
	ForceType forces;
	Data tmp;
public:
	ForceProperty();
	virtual ~ForceProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	// Property specific methods.
	Data& get( EntityKey entity );
};

} /* namespace ice */
#endif /* FORCEPROPERTY_H_ */
