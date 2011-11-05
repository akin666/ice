/*
 * componentwork.cpp
 *
 *  Created on: 30.10.2011
 *      Author: akin
 */

#include "componentwork"
#include "cccomponent"

namespace ice
{

ComponentWork::ComponentWork( CCComponent& parent )
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

