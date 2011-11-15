/*
 * materialproperty.h
 *
 *  Created on: 16.11.2011
 *      Author: akin
 */

#ifndef MATERIALPROPERTY_H_
#define MATERIALPROPERTY_H_

#include <entity/property>
#include <entity/entity>
#include <map>

namespace ice
{

class MaterialProperty : public Property
{
public:
	const static std::string KEY;
public:
	class Data {
	public:
	};
protected:
	typedef std::map<EntityKey , Data> MaterialData;
	MaterialData data;
public:
	MaterialProperty();
	virtual ~MaterialProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );
};

} /* namespace ice */
#endif /* MATERIALPROPERTY_H_ */
