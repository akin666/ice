/*
 * positionproperty.h
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#ifndef POSITIONPROPERTY_H_
#define POSITIONPROPERTY_H_

#include <entity/property>
#include <entity/entity>
#include <glm/glm>
#include <map>

namespace ice
{

class PositionProperty : public Property
{
public:
	const static std::string KEY;
public:
	class Data {
	public:
		glm::vec3 position;
		glm::quat orientation;
	};
protected:
	typedef std::map< EntityKey , Data > PositionType;
	PositionType position;
	Data tmp;
public:
	PositionProperty();
	virtual ~PositionProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	// Property specific methods.
	Data& get( EntityKey entity );
};

} /* namespace ice */
#endif /* POSITIONPROPERTY_H_ */
