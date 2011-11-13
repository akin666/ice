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

namespace ice
{

class NameProperty : public Property
{
public:
	const static std::string KEY;
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
