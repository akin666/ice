/*
 * logserver.h
 *
 *  Created on: 1.10.2011
 *      Author: akin
 */

#ifndef LOGSERVER_H_
#define LOGSERVER_H_

#include <string>

namespace ice
{

class LogServer
{
protected:
	void *server;
public:
	LogServer();
	virtual ~LogServer();

	void init( std::string filename , std::string protocol );
	void kill();
};

} /* namespace ice */
#endif /* LOGSERVER_H_ */
