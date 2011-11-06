/*
 * zmqcontext.cpp
 *
 *  Created on: 27.10.2011
 *      Author: akin
 */

#include "zmqcontext"
#include <iostream>

namespace ice
{

ZMQContext *ZMQContext::singleton = NULL;
std::mutex ZMQContext::s_mutex;

ZMQContext& ZMQContext::getSingleton()
{
	if( singleton == NULL )
	{
		std::lock_guard<std::mutex> lock( s_mutex );
		if( singleton == NULL )
		{
			try {
				singleton = new ZMQContext;
			}
			catch( zmq::error_t& t )
			{
				std::cout << "ZMQContext failed: " << t.what() << std::endl;
			}
			catch( ... )
			{
				std::cout << "ZMQContext failed! Unknown reason." << std::endl;
			}
		}
	}
	return *singleton;
}

ZMQContext::ZMQContext()
: context(1)
{
}

ZMQContext::~ZMQContext()
{
}

zmq::context_t& ZMQContext::getContext()
{
	return context;
}


} /* namespace ice */
