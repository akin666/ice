/*
 * iceapplication.h
 *
 *  Created on: 26.10.2011
 *      Author: akin
 */

#ifndef ICEAPPLICATION_H_
#define ICEAPPLICATION_H_

#include <system/application>
#include <system/clock>

namespace ice
{
	class IceApplication : public Application
	{
	protected:
		Pipeline pipeline;
		ThreadPool pool;
		Clock clock;

		Log mlog;

		unsigned int state;
	public:
		IceApplication( int argc , char *argv[] );
		virtual ~IceApplication();

		void initialize( std::string logProtocol , unsigned int pool_worker_count );

		virtual void suspend();
		virtual void resume();
		virtual void kill();
		virtual void restart();
		virtual void log( std::string msg );

		virtual Time getTime();
		virtual unsigned int getUnixTime();

		virtual ThreadPool& getThreadPool();
		virtual Pipeline& getPipeline();
		virtual Log& getLog();

		virtual bool shouldExit();
		virtual bool shouldRestart();
	};
} /* namespace ice */
#endif /* ICEAPPLICATION_H_ */
