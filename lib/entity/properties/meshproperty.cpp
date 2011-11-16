/*
 * meshproperty.cpp
 *
 *  Created on: 16.11.2011
 *      Author: akin
 */

#include "meshproperty.h"

namespace ice
{
const std::string MeshProperty::KEY("mesh");

MeshProperty::MeshProperty()
: Property( KEY )
{
}

MeshProperty::~MeshProperty()
{
}

void MeshProperty::attach( Entity& entity )
{
}

void MeshProperty::detach( Entity& entity )
{
}

} /* namespace ice */
