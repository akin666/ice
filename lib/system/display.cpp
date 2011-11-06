/*
 * display.cpp
 *
 *  Created on: 22.3.2011
 *      Author: akin
 */

#include "display"
#include <iostream>
#include "global"

namespace ice
{
	DisplayProperties::DisplayProperties()
	: dpi(DEFAULT_DPI),
	  width(DEFAULT_DISPLAY_WIDTH),
	  height(DEFAULT_DISPLAY_HEIGHT),
	  red_bits(DEFAULT_DISPLAY_RED_BITS),
	  green_bits(DEFAULT_DISPLAY_GREEN_BITS),
	  blue_bits(DEFAULT_DISPLAY_BLUE_BITS),
	  alpha_bits(DEFAULT_DISPLAY_ALPHA_BITS),
	  stencil_bits(DEFAULT_DISPLAY_STENCIL_BITS),
	  depth_bits(DEFAULT_DISPLAY_DEPTH_BITS),
	  windowed(DEFAULT_DISPLAY_WINDOWED),
	  major(DEFAULT_DISPLAY_GL_MAJOR),
	  minor(DEFAULT_DISPLAY_GL_MINOR)
	{
	}

	DisplayProperties& DisplayProperties::operator = ( const DisplayProperties& dp )
	{
		dpi = dp.dpi;
		width = dp.width;
		height = dp.height;
		red_bits = dp.red_bits;
		green_bits = dp.green_bits;
		blue_bits = dp.blue_bits;
		alpha_bits = dp.alpha_bits;
		stencil_bits = dp.stencil_bits;
		depth_bits = dp.depth_bits;
		windowed = dp.windowed;
		major = dp.major;
		minor = dp.minor;

		return *this;
	}

	Display::Display()
	{
	}

	Display::~Display()
	{
	}

	int Display::getRedBits()
	{
		return current.red_bits;
	}

	int Display::getGreenBits()
	{
		return current.green_bits;
	}

	int Display::getBlueBits()
	{
		return current.blue_bits;
	}

	int Display::getAlphaBits()
	{
		return current.alpha_bits;
	}

	int Display::getStencilBits()
	{
		return current.stencil_bits;
	}

	int Display::getDepthBits()
	{
		return current.depth_bits;
	}

	int Display::getWidth()
	{
		return current.width;
	}

	int Display::getHeight()
	{
		return current.height;
	}

	float Display::getDPI()
	{
		return current.dpi;
	}

	bool Display::isWindowed()
	{
		return current.windowed;
	}

	void Display::setRedBits( const int val )
	{
		settable.red_bits = val;
	}

	void Display::setGreenBits( const int val )
	{
		settable.green_bits = val;
	}

	void Display::setBlueBits( const int val )
	{
		settable.blue_bits = val;
	}

	void Display::setAlphaBits( const int val )
	{
		settable.alpha_bits = val;
	}

	void Display::setStencilBits( const int val )
	{
		settable.stencil_bits = val;
	}

	void Display::setDepthBits( const int val )
	{
		settable.depth_bits = val;
	}

	void Display::setWidth( const int val )
	{
		settable.width = val;
	}

	void Display::setHeight( const int val )
	{
		settable.height = val;
	}

	void Display::setDPI( const float val )
	{
		settable.dpi = val;
	}

	void Display::setWindowed( const bool val )
	{
		settable.windowed = val;
	}

	bool Display::initialize()
	{
		// Dummy
		return false;
	}

	void Display::printStatistics()
	{
		// Dummy
		std::cout << "Dummy display." << std::endl;
	}

	void Display::setTitle( std::string head )
	{
		// Dummy
	}

	std::string Display::getTitle()
	{
		// Dummy
		return "";
	}

	void Display::apply()
	{
		// Dummy
	}

	bool Display::set( Display *display )
	{
		if( !Global<Display>::has("default") )
		{
			Global<Display>::set( "default" , display );
			return true;
		}
		return false;
	}

	Display *Display::get()
	{
		return Global<Display>::get( "default" );
	}

	void Display::setMajorVersion( int v )
	{
		settable.major = v;
	}

	void Display::setMinorVersion( int v )
	{
		settable.minor = v;
	}
}



