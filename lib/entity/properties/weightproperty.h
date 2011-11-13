/*
 * weightproperty.h
 *
 *  Created on: 2.11.2011
 *      Author: akin
 */

#ifndef WEIGHTPROPERTY_H_
#define WEIGHTPROPERTY_H_

#include <entity/property>
#include <entity/entity>
#include <system/common>
#include <map>

namespace ice
{

class WeightProperty : public Property
{
public:
	const static std::string KEY;
protected:
	typedef std::map< EntityKey , float > WeightType;
	WeightType weightData;
public:
	WeightProperty();
	virtual ~WeightProperty();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	float& get( EntityKey key );
	WeightType& getTime();
};

} /* namespace ice */
#endif /* WEIGHTPROPERTY_H_ */
