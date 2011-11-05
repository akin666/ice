// todoo
/*
 * inputlistener.cpp
 *
 *  Created on: 18.7.2011
 *      Author: akin
 */

#include "inputlistener.h"
#define _IL_DEBUG
#undef _IL_DEBUG

#ifdef _IL_DEBUG
#include <iostream>
#endif

namespace ice
{
	InputListener::InputListener()
	{
	}

	InputListener::~InputListener()
	{
	}

	void InputListener::handleMouseMove( const float x , const float y )
	{
	#ifdef _IL_DEBUG
		std::cout << "InputListener::handleMouseMove: " << x << "," << y << std::endl;
	#endif
	}

	void InputListener::handleMouseButton( const Button button , const float state )
	{
	#ifdef _IL_DEBUG
		std::cout << "InputListener::handleMouseButton: " << button << "," << state << std::endl;
	#endif
	}

	void InputListener::handleMouseButtonAction( const Button button )
	{
	#ifdef _IL_DEBUG
		std::cout << "InputListener::handleMouseButtonAction: " << button << std::endl;
	#endif
	}

	void InputListener::handleMouseWheel( const float val )
	{
	#ifdef _IL_DEBUG
		std::cout << "InputListener::handleMouseWheel: " << val << std::endl;
	#endif
	}

	void InputListener::handleJoystickMove( const int devicenum , const int joynum , const float x , const float y )
	{
	#ifdef _IL_DEBUG
		std::cout << "InputListener::handleJoystickMove: " << devicenum << "," << joynum << ":" << x << "," << y << std::endl;
	#endif
	}

	void InputListener::handleJoystickButton( const int devicenum , const Button button , const float state )
	{
	#ifdef _IL_DEBUG
		std::cout << "InputListener::handleJoystickButton: " << devicenum << "," << button << "," << state << std::endl;
	#endif
	}

	void InputListener::handleKeyboard( const unsigned int key , const float state )
	{
	#ifdef _IL_DEBUG
		std::cout << "InputListener::handleKeyboard: " << key << "," << state << std::endl;
	#endif
	}

	void InputListener::handleKeyboardCharacter( const unsigned int key , const float state )
	{
	#ifdef _IL_DEBUG
		std::cout << "InputListener::handleKeyboardCharacter: " << key << "," << state << std::endl;
	#endif
	}
}
