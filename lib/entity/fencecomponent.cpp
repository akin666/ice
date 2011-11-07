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

void FenceComponent::addDependencyTo( std::string name ) throw (ComponentException)
{
	addDependency( name );
}

void FenceComponent::addDependencyTo( Component& c ) throw (ComponentException)
{
	addDependency( c.getName() );
}

void FenceComponent::attach( Entity& entity ) throw (ComponentException)
{
}

void FenceComponent::detach( Entity& entity ) throw (ComponentException)
{
}

} /* namespace ice */
