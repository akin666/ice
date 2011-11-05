/*
 * inputlistener.h
 *
 *  Created on: 18.7.2011
 *      Author: akin
 */


#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_

namespace ice
{
	class InputListener
	{
	public:
			enum Button
			{
				LEFT,
				RIGHT,
				MIDDLE,
				ADDON_1,
				ADDON_2,
				ADDON_3,
				ADDON_4,
				ADDON_5,
				ADDON_6,
				ADDON_LAST
			};

			InputListener();
			virtual ~InputListener();

			virtual void handleMouseMove( const float x , const float y );
			virtual void handleMouseButton( const Button button , const float state );
			virtual void handleMouseButtonAction( const Button button );
			virtual void handleMouseWheel( const float val );
			virtual void handleJoystickMove( const int devicenum , const int joynum , const float x , const float y );
			virtual void handleJoystickButton( const int devicenum , const Button button , const float state );
			virtual void handleKeyboard( const unsigned int key , const float state );
			virtual void handleKeyboardCharacter( const unsigned int key , const float state );
	};

}

#endif

