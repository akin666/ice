/*
 * uiparent.h
 *
 *  Created on: 2.8.2011
 *      Author: akin
 */

#ifndef UIPARENT_H_
#define UIPARENT_H_

namespace ice
{
	class UIComponent;

	class UIParent
	{
	public:
		UIParent();
		virtual ~UIParent();

		virtual void addChild( UIComponent *child ) = 0;
		virtual void removeChild( UIComponent *child ) = 0;
		virtual void clearChilds() = 0;
	};
} /* namespace ice */
#endif /* UIPARENT_H_ */
