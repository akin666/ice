/*
 * clientlog.cpp
 *
 *  Created on: 6.10.2011
 *      Author: akin
 */

#include "log"
#include <iostream>
#include <cstdio>
#include <sys/zmqcontext.h>

#define GET_LG ((LogClientEntity*)lg)

namespace ice
{

class LogClientEntity
{
protected:
	std::string protocol;
	zmq::socket_t *socket;
	bool established;
public:
	LogClientEntity();
	~LogClientEntity();

	void setConnectPoint( std::string point );

	void init();

	void send( unsigned char level , std::string msg );
};

LogClientEntity::LogClientEntity()
: socket(NULL),
  established( false )
{
}

LogClientEntity::~LogClientEntity()
{
}

void LogClientEntity::setConnectPoint( std::string point )
{
	this->protocol = point;
}

void LogClientEntity::init()
{
	if( socket == NULL )
	{
		try{
			zmq::context_t& context = ZMQContext::getSingleton().getContext();
			socket = new zmq::socket_t( context, ZMQ_PUSH);
			socket->connect( protocol.c_str() );
		}
		catch( zmq::error_t& t )
		{
			std::cout << "ClientLog failed: " << t.what() << std::endl;
			delete socket;
			socket = NULL;
		}
		catch( ... )
		{
			std::cout << "ClientLog failed! For unknown reason. " << protocol << std::endl;
			delete socket;
			socket = NULL;
		}
	}
}

void LogClientEntity::send( unsigned char level , std::string msg )
{
	if( socket == NULL )
	{
		return;
	}

	// MSG+NULL
	try {
		unsigned int total_size = msg.size() + 1;
		zmq::message_t request( total_size );
		memcpy( (void *)request.data() , msg.c_str() , msg.size() );

		if( !socket->send( request , ZMQ_DONTWAIT ) )
		{
			std::cout << "ClientLog Failed to send message: " << msg << std::endl;
		}
	}
	catch( ... )
	{
		std::cout << "ClientLog Error while sending message: " << msg << std::endl;
	}
}

Log::Log( )
: lg( NULL )
{
	if( lg == NULL )
	{
		LogClientEntity *lce = new LogClientEntity;
		lg = lce;
	}
}

Log::~Log( )
{
	kill();
}

void Log::setProtocol( std::string protocol )
{
	if( lg == NULL )
	{
		LogClientEntity *lce = new LogClientEntity;
		lg = lce;
	}
	GET_LG->setConnectPoint( protocol );
}

void Log::init()
{
	if( lg == NULL )
	{
		LogClientEntity *lce = new LogClientEntity;
		lg = lce;
	}
	GET_LG->init();

	fire( Notification , "Logger registered." );
}

void Log::kill()
{
	if( lg != NULL )
	{
		delete GET_LG;
		lg = NULL;
	}
}

void Log::fire( Level level , std::string data )
{
	if( lg == NULL )
	{
		std::cout << "Cant fire ClientLog, LG is NULL" << std::endl;
		return;
	}
	unsigned char lvl = (unsigned char)level;

	GET_LG->send(lvl,data);
}


} /* namespace ice */
