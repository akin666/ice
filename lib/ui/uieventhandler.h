/*
 * uieventhandler.h
 *
 *  Created on: 23.7.2011
 *      Author: akin
 */

#ifndef UIEVENTHANDLER_H_
#define UIEVENTHANDLER_H_

#include "mouse.h"

namespace ice
{
	class UIEventHandler
	{
	public:
		UIEventHandler();
		virtual ~UIEventHandler();

		virtual bool handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state ) = 0;
		virtual bool handleMoveEvent( glm::vec2& pos , const Mouse& mouse ) = 0;
	};
} /* namespace ice */
#endif /* UIEVENTHANDLER_H_ */
