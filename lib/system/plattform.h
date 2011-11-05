/*
 * plattform.h
 *
 *  Created on: May 15, 2010
 *      Author: akin
 */

#ifndef PLATTFORM_H_
#define PLATTFORM_H_

#include <datatypes/common.h>
#include <iostream>

namespace ice
{
class Plattform {
private:
	Plattform();
	virtual ~Plattform();
public:
	static void exitSuccess();
	static void exitError( std::string errorMsg = "" );
	static Time getTime();
	static void error( std::string errorMsg );
	static void sleep( unsigned int ms );
};
}

#endif /* PLATTFORM_H_ */
