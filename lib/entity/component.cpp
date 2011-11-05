/*
 * component.cpp
 *
 *  Created on: 14.10.2011
 *      Author: akin
 */

#include "component"
#include "storage"
#include <vector>
#include <iterator>
#include "componentnode"

namespace ice
{

unsigned int Component::sm_id = 1;

unsigned int Component::getNewId()
{
	return sm_id++;
}

void Component::addDependency( std::string dependency )
{
	dependencies.insert( dependency );
}

// Generate list of components dependencies
void Component::getDependencyList( std::set<std::string>& list )
{
	list = dependencies;
}

// Figure out if this component can be before the linked component
bool Component::before( Component& component )
{
	std::string other = component.getName();
	for( std::set<std::string>::iterator iter = dependencies.begin() ; iter != dependencies.end() ; ++iter )
	{
		if( other == *iter )
		{
			return false;
		}
	}
	return true;
}

void Component::setPriority( unsigned int prio )
{
	// Priority 0 is unaccaptable,
	// if we calculate priorities using childs as weigths, this is a must.
	// eg. 1+1+1+1+1 tells the prioritizer to prio that against 1
	// rather than 0+0+0+0+0 against 0. so those with dependencies gets
	// prio over those with no dependencies.
	if( prio == 0 )
	{
		prio = 1;
	}
	priority = prio;
}

// Return components priority
unsigned int Component::getPriority()
{
	return priority;
}

Component::Component( std::string name , bool concurrent )
: id( getNewId() ),
  name( name ),
  concurrent( concurrent ),
  priority( 1 ),
  componentNode( NULL )
{
	Storage::add( this );
}

Component::~Component()
{
}

void Component::setComponentNode( ComponentNode *cn )
{
	componentNode = cn;
}

std::string Component::getName() const
{
	return name;
}

unsigned int Component::getId() const
{
	return id;
}

bool Component::isConcurrent()
{
	return concurrent;
}

void Component::start()
{
	finish();
}

void Component::finish()
{
	if( componentNode != NULL )
	{
		componentNode->componentFinished();
	}
}

} /* namespace ice */
