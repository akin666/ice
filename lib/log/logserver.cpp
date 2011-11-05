/*
 * logserver.cpp
 *
 *  Created on: 1.10.2011
 *      Author: akin
 */

#include "logserver"
#include <fixes/thread>
#include <cstdio>
#include <zmq.hpp>
#include <sys/zmqcontext.h>

namespace ice
{

class LogServerEntity
{
protected:
	std::string path;
	std::string protocol;
	std::thread *thread;

	std::mutex mutex;
	std::condition_variable condition;
	bool running;
public:
	LogServerEntity();
	~LogServerEntity();
	void setPath( std::string path );
	void setConnectPoint( std::string point );

	void operator()(); // Thread entry point..

	void kill();

	void run();
};

LogServerEntity::LogServerEntity()
: thread(NULL)
{
}

LogServerEntity::~LogServerEntity()
{
	kill();
}

void LogServerEntity::setPath( std::string path )
{
	this->path = path;
}

void LogServerEntity::setConnectPoint( std::string point )
{
	this->protocol = point;
}

void LogServerEntity::operator()()
{
	FILE *file;
	bool aborting = false;

	if( path == "" )
	{
		std::cerr << " - No path for logging specified." << std::endl;
		aborting = true;
	}

	if( protocol == "" )
	{
		std::cerr << " - No protocol for logging specified." << std::endl;
		aborting = true;
	}

	if( !aborting )
	{
		// not aborting, so lets try to open the file.
		file = fopen( path.c_str() , "w+" );

		if( file == NULL )
		{
			std::cerr << " - Can not open " << path << " file for logging. " << std::endl;
			aborting = true;
		}
	}

	if( aborting )
	{
		return;
	}

	// All OK!
	// Lets start this..
	// Initialize ZeroMQ
	try
	{
		zmq::context_t& context = ZMQContext::getSingleton().getContext();
		zmq::socket_t socket (context, ZMQ_PULL);
		socket.bind( protocol.c_str() );

		fprintf( file , "Started logging from ZeroMQ Logserver.\n----\n File:\t\t%s\n Protocol:\t%s\n----\n Happy hunting.\n----\n" , path.c_str() , protocol.c_str() );

		int requests_received = 0;

		std::cout << "Logserver running." << std::endl;

		// Init done, and waiting for connections.
		{
			std::lock_guard<std::mutex> lock(mutex);
			running = true;
			condition.notify_one();
		}

		// Fetch log messages in endless loop.
		while( true )
		{
			zmq::message_t msg;

			// Wait for next request from client
			try {
				socket.recv( &msg );
			}
			catch( ... ) {
				std::cout << "Error recv messages" << std::endl;
				continue;
			}

			((char*)msg.data())[msg.size() - 1] = '\0';

			fprintf( file , "%i\t:%s\n" , requests_received , (char*)msg.data() );
			requests_received++;
		}
	}
	catch( zmq::error_t& t )
	{
		std::cout << "LogServer failed: " << t.what() << std::endl;
	}
	catch( ... )
	{
		std::cout << "LogServer failed! Unknown reason." << std::endl;
	}
	std::cout << "Logserver quitting." << std::endl;

	fclose( file );
}

void LogServerEntity::kill()
{
	if( thread != NULL )
	{
		thread->interrupt();
		delete thread;
		thread = NULL;
	}
}

void LogServerEntity::run()
{
	// Block, until really running.
	std::unique_lock<std::mutex> lock(mutex);

	running = false;
	thread = new std::thread( std::ref(*this) );

	while( !running )
	{
		condition.wait(lock);
	}
}

LogServer::LogServer()
: server(NULL)
{
}

LogServer::~LogServer()
{
	kill();
}

void LogServer::init( std::string filename , std::string protocol )
{
	if( server == NULL )
	{
		// Create
		LogServerEntity *lse = new LogServerEntity;
		server = lse;

		lse->setConnectPoint( protocol );
		lse->setPath( filename );

		lse->run();
	}
}

void LogServer::kill()
{
	if( server != NULL )
	{
		delete ((LogServerEntity*)server);
		server = NULL;
	}
}

} /* namespace ice */
