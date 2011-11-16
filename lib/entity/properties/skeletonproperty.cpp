/*
 * skeletonproperty.cpp
 *
 *  Created on: 16.11.2011
 *      Author: akin
 */

#include "skeletonproperty.h"

namespace ice
{
const std::string SkeletonProperty::KEY("skeleton");

SkeletonProperty::SkeletonProperty()
: Property( KEY )
{
}

SkeletonProperty::~SkeletonProperty()
{
}

void SkeletonProperty::attach( Entity& entity )
{
}

void SkeletonProperty::detach( Entity& entity )
{
}

} /* namespace ice */
