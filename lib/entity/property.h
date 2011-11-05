/*
 * property.h
 *
 *  Created on: 14.10.2011
 *      Author: akin
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include <string>

namespace ice
{

class Entity;

class Property
{
protected:
	static unsigned int sm_id;
	static unsigned int getNewId();

	unsigned int id;
	std::string name;
public:
	Property( std::string name );
	virtual ~Property();

	std::string getName() const;
	unsigned int getId() const;

	virtual void attach( Entity& entity ) = 0;
	virtual void detach( Entity& entity ) = 0;
};

} /* namespace ice */
#endif /* PROPERTY_H_ */
