/*
 * componentnode.cpp
 *
 *  Created on: 22.10.2011
 *      Author: akin
 */

#include "componentnode"
#include <iostream>
#include "component"

namespace ice
{

ComponentNode::ComponentNode( Component *component )
: current(*component),
  finishQueu(NULL),
  running( false )
{
	component->setComponentNode( this );
}

ComponentNode::ComponentNode( ComponentNode& other )
: current( other.current ),
  finishQueu( other.finishQueu ),
  dependencies( other.dependencies ),
  childs( other.childs ),
  time( other.time )
{
}

ComponentNode::~ComponentNode()
{
}

void ComponentNode::componentStart( TQue<ComponentNode*>& target , unsigned int start , unsigned int end )
{
	running = true;
	time = start;

	endTime = end;
	finishQueu = &target;
	current.execute();
}

bool ComponentNode::isRunning()
{
	return running;
}

Component& ComponentNode::getComponent()
{
	return current;
}

void ComponentNode::componentFinished()
{
	running = false;
	time = endTime;
	if( finishQueu != NULL )
	{
		finishQueu->push( this );
	}
}

} /* namespace ice */
