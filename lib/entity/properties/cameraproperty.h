/*
 * cameraproperty.h
 *
 *  Created on: 15.11.2011
 *      Author: akin
 */

#ifndef CAMERAPROPERTY_H_
#define CAMERAPROPERTY_H_

#include "positionproperty.h"
#include <glm/glm>

namespace ice
{

class CameraProperty : public Property
{
public:
	const static std::string KEY;
public:
	class Data {
	public:
		glm::mat4x4 lense;
	};
protected:
	PositionProperty *positionProperty;

	typedef std::map<EntityKey , Data> CameraData;
	CameraData data;

	Data tmp;
	EntityKey current;
public:
	CameraProperty();
	virtual ~CameraProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	void setCurrentCamera( Entity& entity );
	void setCurrentCamera( EntityKey& entity );

	Data& get( EntityKey key );
};

} /* namespace ice */
#endif /* CAMERAPROPERTY_H_ */
