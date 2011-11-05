/*
 * plattform.cpp
 *
 *  Created on: May 15, 2010
 *      Author: akin
 */

#include "plattform.h"
#include <iostream>
#include "opengl.h"
#include "log.h"

namespace ice
{
Plattform::Plattform() {
}

Plattform::~Plattform() {
}

void Plattform::exitSuccess() {
#ifdef _STDLIB_H
#ifndef EXIT_SUCCESS
	exit(0);
#else
	exit( EXIT_SUCCESS );
#endif
#else
	LOG_ERROR( "Quit dammit, but no STDLIB declared WTF!" );
#endif
}

void Plattform::exitError( std::string errorMsg ) {
	LOG_ERROR( errorMsg );
#ifdef _STDLIB_H
#ifndef EXIT_FAILURE
	exit(-1);
#else
	exit( EXIT_FAILURE );
#endif
#else
	LOG_ERROR( "Quit dammit, but no STDLIB declared WTF!" );
#endif
}

Time Plattform::getTime() {
#ifndef NO_GLFW
	Time now;
	now = (Time)(glfwGetTime() * 1000.0);
	return now;
#else
	return 0;
#endif
}

void Plattform::error( std::string errorMsg )
{
	LOG_ERROR( errorMsg );
}

void Plattform::sleep( unsigned int ms )
{
	double sleepTimeInSeconds = (double)ms / 1000.0;
	glfwSleep( sleepTimeInSeconds );
}
}
