/*
 * componentnet.cpp
 *
 *  Created on: 19.10.2011
 *      Author: akin
 */

#include "componentnet"
#include "componentnode"

namespace ice
{

ComponentNet::ComponentNet()
{
}

ComponentNet::~ComponentNet()
{
}

void ComponentNet::removeFromRoot( ComponentNode *node )
{
	for( std::deque<ComponentNode*>::iterator iter = roots.begin() ; iter != roots.end() ; ++iter )
	{
		if( *iter == node )
		{
			roots.erase( iter );
			return;
		}
	}
}

void ComponentNet::addToRoot( ComponentNode *node )
{
	if( node->dependencies.size() == 0 )
	{
		// no parent.
		roots.push_back( node );
	}
}

void ComponentNet::resetTime( Time time )
{
	for( std::deque<ComponentNode*>::iterator iter = nodes.begin() ; iter != nodes.end() ; ++iter )
	{
		(*iter)->time = time;
	}
}

void ComponentNet::add( Component *component )
{
	if( component == NULL )
	{
		return;
	}
	// already has it
	if( nodes_str.find( component->getName() ) != nodes_str.end() )
	{
		return;
	}

	ComponentNode *node = new ComponentNode( component );
	node->time = NODE_NULL;

	std::set<std::string> list;
	component->getDependencyList( list );

	// Seek Parent dependencies.
	// If found, link em.
	std::map<std::string , ComponentNode*>::iterator citer;
	for( std::set<std::string>::iterator iter = list.begin() ; iter != list.end() ; ++iter )
	{
		citer = nodes_str.find( *iter );

		if( citer != nodes_str.end() )
		{
			// found!
			node->dependencies.push_back( citer->second );
			citer->second->childs.push_back( node );
		}
	}

	// Seek child dependencies.
	// If found, link em.
	std::string name = component->getName();
	ComponentNode *current;
	for( std::deque<ComponentNode*>::iterator iter = nodes.begin() ; iter != nodes.end() ; ++iter )
	{
		current = *iter;

		// Reuse list..
		current->getComponent().getDependencyList( list );

		// No dependency?
		if( list.find( name ) == list.end() )
		{
			continue;
		}

		// Dependency, link em.
		current->dependencies.push_back( node );
		node->childs.push_back( current );

		if( current->dependencies.size() == 1 )
		{
			// First parent! Remove from root!
			removeFromRoot( current );
		}
	}

	nodes.push_back( node );

	// try to add as root element..
	addToRoot( node );

	resetTime( 0 );
}

void ComponentNet::addNoSort( Component *component )
{
	// todo
	add( component );
}

void ComponentNet::sort()
{
	// todo
}

void ComponentNet::getRoot( std::deque<ComponentNode*>& root )
{
	root = roots;
}

} /* namespace ice */
