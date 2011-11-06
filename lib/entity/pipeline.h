/*
 * pipeline.h
 *
 *  Created on: 14.10.2011
 *      Author: akin
 */

#ifndef ICE_PIPELINE_H_
#define ICE_PIPELINE_H_

#include <iostream>
#include <deque>
#include <iterator>
#include <fixes/thread>
#include "componentnet"
#include <threadpool/tque>
#include "pipelineexception"

namespace ice
{
	class Component;

	class Pipeline
	{
	private:
		ComponentNet net;
		std::mutex mutex;

		std::deque<ComponentNode*> temp;
		std::deque<ComponentNode*> nonConcurrent;
		std::deque<ComponentNode*> concurrent;
		TQue<ComponentNode*> waitingQue;
	public:
		Pipeline();
		virtual ~Pipeline();

		void attach( Component *component ) throw (PipelineException);
		void attachNoSort( Component *component ) throw (PipelineException);
		void sort( ) throw (PipelineException);

		// Run is the heart of the pipeline, it is essentially the main-loop.
		void run() throw (PipelineException);
	};
} /* namespace ice */
#endif /* PIPELINE_H_ */
