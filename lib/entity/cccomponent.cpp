/*
 * concurrentcomponent.cpp
 *
 *  Created on: 30.10.2011
 *      Author: akin
 */

#include "cccomponent"
#include <system/application>

namespace ice
{

CCComponent::CCComponent( std::string name )
: Component( name , true ),
  concurrent_reference_counting( 0 )
{
}

CCComponent::~CCComponent()
{
}

void CCComponent::schedule( ComponentWork& work )
{
	++concurrent_reference_counting;
	Application::get()->getThreadPool().schedule( &work );
}

void CCComponent::finished( ComponentWork& work )
{
	--concurrent_reference_counting;

	if( concurrent_reference_counting == 0 )
	{
		finish();
	}
}

} /* namespace ice */
