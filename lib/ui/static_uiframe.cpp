/*
 * static_uiview.cpp
 *
 *  Created on: 21.7.2011
 *      Author: akin
 */


#include "uiframe.h"
#include <iostream>

namespace ice
{
	UIFrame *UIFrame::current = NULL;

	bool UIFrame::hasCurrent()
	{
		return current != NULL;
	}

	UIFrame *UIFrame::getCurrent()
	{
		return current;
	}

	void UIFrame::setCurrent( UIFrame *frame )
	{
		current = frame;
	}
}
