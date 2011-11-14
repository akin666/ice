/*
 * componentwork.h
 *
 *  Created on: 30.10.2011
 *      Author: akin
 */

#ifndef ICE_COMPONENTWORK_H_
#define ICE_COMPONENTWORK_H_

#include <threadpool/work>

namespace ice
{
	class Component;

	class ComponentWork : public Work
	{
	protected:
		Component& parent;
	public:
		ComponentWork( Component& parent );
		virtual ~ComponentWork();

		virtual bool begin() = 0;
		virtual void run() = 0;
		virtual void end();
	};
} /* namespace ice */
#endif /* COMPONENTWORK_H_ */
