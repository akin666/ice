/*
 * application.h
 *
 *  Created on: 26.10.2011
 *      Author: akin
 */

#ifndef ICE_APPLICATION_H_
#define ICE_APPLICATION_H_

#include <iostream>
#include <vector>
#include "common"
#include <threadpool/threadpool>
#include <entity/pipeline>
#include <log/log>

namespace ice
{

class Application
{
protected:
	static Application *application;
	// members
	std::vector<std::string> arguments;

	void processArgs( int argc , char *argv[] );
public:
	Application();
	virtual ~Application();

	virtual void suspend() = 0;
	virtual void resume() = 0;
	virtual void kill() = 0;
	virtual void restart() = 0;
	virtual void log( std::string msg ) = 0;

	virtual Time getTime() = 0;
	virtual unsigned int getUnixTime() = 0;
	virtual ThreadPool& getThreadPool() = 0;
	virtual Pipeline& getPipeline() = 0;
        virtual Log& getLog() = 0;

	std::string getPath();
	void getArg( std::vector<std::string>& args );

	virtual bool shouldExit() = 0;
	virtual bool shouldRestart() = 0;

	static void set( Application *app );
	static Application *get();
};

} /* namespace ice */
#endif /* ICE_APPLICATION_H_ */
