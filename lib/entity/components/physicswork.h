/*
 * physicswork.h
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#ifndef PHYSICSWORK_H_
#define PHYSICSWORK_H_

#include <entity/componentwork>

namespace ice
{

class PhysicsWork : public ComponentWork
{
public:
	PhysicsWork( CCComponent& parent );
	virtual ~PhysicsWork();

	virtual bool begin();
	virtual void run();
};

} /* namespace ice */
#endif /* PHYSICSWORK_H_ */
