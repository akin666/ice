/*
 * fencecomponent.cpp
 *
 *  Created on: 31.10.2011
 *      Author: akin
 */

#include "fencecomponent"

namespace ice
{

FenceComponent::FenceComponent( std::string name )
: Component( name )
{
}

FenceComponent::~FenceComponent()
{
}

void FenceComponent::addDependencyTo( std::string name )
{
	addDependency( name );
}

void FenceComponent::addDependencyTo( Component& c )
{
	addDependency( c.getName() );
}

void FenceComponent::attach( Entity& entity )
{
}

void FenceComponent::detach( Entity& entity )
{
}

} /* namespace ice */
