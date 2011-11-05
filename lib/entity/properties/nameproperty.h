/*
 * nameproperty.h
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#ifndef NAMEPROPERTY_H_
#define NAMEPROPERTY_H_

#include <entity/component>
#include <entity/property>
#include <entity/entity>
#include <string>
#include <map>

#define PROPERTY_NAME_NAME "name"

namespace ice
{

class NameProperty : public Property
{
protected:
	typedef std::map< EntityKey , std::string > NameType;
	NameType names;
public:
	NameProperty();
	virtual ~NameProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	std::string get( EntityKey entity );
};

} /* namespace ice */
#endif /* NAMEPROPERTY_H_ */
