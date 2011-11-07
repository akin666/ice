//============================================================================
// Name        : winice.cpp
// Author      : Mikael Korpela
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "ice.h"
#include <iostream>
#include <system/os> // if you need different entry point for some OS, than main, use ifdefs from here.

int main( int argc , char *argv[] )
{
	return iceMain( argc , argv );
}
