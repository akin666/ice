/*
 * concurrentcomponent.h
 *
 *  Created on: 30.10.2011
 *      Author: akin
 */

#ifndef ICE_CONCURRENTCOMPONENT_H_
#define ICE_CONCURRENTCOMPONENT_H_

#include "component"
#include "componentwork"

namespace ice
{
	class CCComponent : public Component
	{
	protected:
		unsigned int concurrent_reference_counting;
	public:
		CCComponent( std::string name ) throw (ComponentException);
		virtual ~CCComponent();

		void schedule( ComponentWork& work ) throw (ComponentException);
		void finished( ComponentWork& work );
	};
} /* namespace ice */
#endif /* CONCURRENTCOMPONENT_H_ */
