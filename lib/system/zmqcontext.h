/*
 * zmqcontext.h
 *
 *  Created on: 27.10.2011
 *      Author: akin
 */

#ifndef ICE_ZMQCONTEXT_H_
#define ICE_ZMQCONTEXT_H_

#include <zmq.hpp>
#include <fixes/thread>

namespace ice
{

	class ZMQContext
	{
	protected:
		static ZMQContext *singleton;
		static std::mutex s_mutex;

		zmq::context_t context;
	public:
		ZMQContext();
		virtual ~ZMQContext();

		zmq::context_t& getContext();

		static ZMQContext& getSingleton();
	};

} /* namespace ice */
#endif /* ZMQCONTEXT_H_ */
