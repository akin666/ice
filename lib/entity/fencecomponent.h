/*
 * fencecomponent.h
 *
 *  Created on: 31.10.2011
 *      Author: akin
 */

#ifndef ICE_FENCECOMPONENT_H_
#define ICE_FENCECOMPONENT_H_

#include "component"

#define COMPONENT_PREFENCE_NAME "prefence"
#define COMPONENT_MIDFENCE_NAME "midfence"
#define COMPONENT_POSTFENCE_NAME "postfence"

namespace ice
{
	class FenceComponent : public Component
	{
	public:
		FenceComponent( std::string name );
		virtual ~FenceComponent();

		void addDependencyTo( std::string name ) throw (ComponentException);
		void addDependencyTo( Component& c ) throw (ComponentException);

		virtual void attach( Entity& entity ) throw (ComponentException);
		virtual void detach( Entity& entity ) throw (ComponentException);
	};
} /* namespace ice */
#endif /* FENCECOMPONENT_H_ */

