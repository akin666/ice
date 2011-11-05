/*
 * viewcontainer.cpp
 *
 *  Created on: 22.7.2011
 *      Author: akin
 */

#include "uicontainer.h"
#include <iterator>

namespace ice
{
	UIContainer::UIContainer()
	{
	}

	UIContainer::~UIContainer()
	{
	}

	void UIContainer::addChild( UIComponent *child )
	{
		if( child == NULL )
		{
			return;
		}
		if( child->hasParent()  )
		{
			child->clearParent();
		}

		childs.push_front( child );
		child->setParent( this );

		if( shader != NULL && child->getShader() == NULL )
		{
			child->setShader( shader );
		}
	}

	void UIContainer::removeChild( UIComponent *child )
	{
		for( std::list< UIComponent *>::iterator iter = childs.begin() ; iter != childs.end() ; ++iter )
		{
			if( (*iter) == child )
			{
				childs.erase( iter );
				delete child;
				break;
			}
		}
	}

	void UIContainer::clearChilds()
	{
		childs.clear();
	}

	void UIContainer::setFocus( UIComponent *child )
	{
		if( child == NULL )
		{
			return;
		}

		for( std::list< UIComponent *>::iterator iter = childs.begin() ; iter != childs.end() ; ++iter )
		{
			if( (*iter) == child )
			{
				childs.erase( iter );
				break;
			}
		}
		childs.push_front( child );
	}

	void UIContainer::letChildRender( glm::vec2& pos )
	{
		// Reverse iterator goes, from Bottom to Top
		pos += position;
		for( std::list< UIComponent *>::reverse_iterator iter = childs.rbegin() ; iter != childs.rend() ; ++iter )
		{
			(*iter)->render( pos );
		}
		pos -= position;
	}

	bool UIContainer::letChildHandleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state )
	{
		// Froward iterator, goes from Top to Bottom
		bool handled = false;

		pos += position;
		for( std::list< UIComponent *>::iterator iter = childs.begin() ; iter != childs.end() ; ++iter )
		{
			// go reverse, this should be the topmost visible.
			if( (*iter)->handleClickEvent( pos , mouse , button , state ) )
			{
				// Bring the element to top!
				// (if its not on the top)
				if( childs.front() != (*iter) )
				{
					UIComponent *tmp = *iter;
					childs.erase( iter );
					childs.push_front( tmp );
				}
				handled = true;
				break;
			}
		}
		pos -= position;

		return handled;
	}

	bool UIContainer::letChildHandleMoveEvent( glm::vec2& pos , const Mouse& mouse )
	{
		bool ret = false;

		pos += position;
		for( std::list< UIComponent *>::iterator iter = childs.begin() ; iter != childs.end() ; ++iter )
		{
			if( (*iter)->handleMoveEvent( pos , mouse ) ) // Y Bottom
			{
				// go reverse, this should be the topmost visible.
				ret = true;
				break;
			}
		}
		pos -= position;

		return ret;
	}

	void UIContainer::render( glm::vec2& pos )
	{
		if( !visible )
		{
			return;
		}

		letChildRender( pos );
	}

	bool UIContainer::handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state )
	{
		if( !visible )
		{
			return false;
		}

		return letChildHandleClickEvent( pos , mouse , button , state );
	}

	bool UIContainer::handleMoveEvent( glm::vec2& pos , const Mouse& mouse )
	{
		if( !visible )
		{
			return false;
		}

		return letChildHandleMoveEvent( pos , mouse );
	}

	void UIContainer::setVisible( bool state )
	{
		for( std::list< UIComponent *>::iterator iter = childs.begin() ; iter != childs.end() ; ++iter )
		{
			(*iter)->setVisible( state );
		}
		visible = state;
	}

	void UIContainer::setShader( ShaderProgram *val )
	{
		for( std::list< UIComponent *>::iterator iter = childs.begin() ; iter != childs.end() ; ++iter )
		{
			(*iter)->setShader( val );
		}
		shader = val;
	}
}
