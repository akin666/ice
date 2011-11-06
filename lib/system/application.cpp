/*
 * application.cpp
 *
 *  Created on: 26.10.2011
 *      Author: akin
 */

#include "application"

namespace ice
{

Application *Application::application = NULL;

void Application::set( Application *app )
{
	application = app;
}

Application *Application::get()
{
	return application;
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::processArgs( int argc , char *argv[] )
{
	arguments.clear();
	for( int i = argc - 1 ; i >= 0 ; --i )
	{
		arguments.push_back( std::string( argv[i] ) );
	}
}

std::string Application::getPath()
{
	return arguments[0];
}

void Application::getArg( std::vector<std::string>& args )
{
	args = arguments;
}

} /* namespace ice */


