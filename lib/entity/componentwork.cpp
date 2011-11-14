/*
 * componentwork.cpp
 *
 *  Created on: 30.10.2011
 *      Author: akin
 */

#include "componentwork"
#include "component"

namespace ice
{

ComponentWork::ComponentWork( Component& parent )
: parent(parent)
{
}

ComponentWork::~ComponentWork()
{
}

void ComponentWork::end()
{
	parent.finished( *this );
}

} /* namespace ice */

