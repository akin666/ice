/*
 * display.h
 *
 *  Created on: 22.3.2011
 *      Author: akin
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define DEFAULT_DPI 96
#define DEFAULT_DISPLAY_WIDTH 800
#define DEFAULT_DISPLAY_HEIGHT 600
#define DEFAULT_DISPLAY_RED_BITS 8
#define DEFAULT_DISPLAY_GREEN_BITS 8
#define DEFAULT_DISPLAY_BLUE_BITS 8
#define DEFAULT_DISPLAY_ALPHA_BITS 8
#define DEFAULT_DISPLAY_STENCIL_BITS 8
#define DEFAULT_DISPLAY_DEPTH_BITS 24
#define DEFAULT_DISPLAY_WINDOWED true
#define DEFAULT_DISPLAY_GL_MAJOR 1
#define DEFAULT_DISPLAY_GL_MINOR 3

#include <string>
#include "../input/inputlistener.h"

namespace ice
{
	class DisplayProperties
	{
	public:
		DisplayProperties();

		float dpi;
		int width;
		int height;
		int red_bits;
		int green_bits;
		int blue_bits;
		int alpha_bits;
		int stencil_bits;
		int depth_bits;
		bool windowed;
		int major;
		int minor;

		DisplayProperties& operator = ( const DisplayProperties& dp );
	};

	class Display
	{
	protected:
		DisplayProperties current;
		DisplayProperties settable;
	public:
		Display();
		virtual ~Display();

		int getRedBits();
		int getGreenBits();
		int getBlueBits();
		int getAlphaBits();
		int getStencilBits();
		int getDepthBits();
		int getWidth();
		int getHeight();
		float getDPI();
		bool isWindowed();

		void setRedBits( const int val );
		void setGreenBits( const int val );
		void setBlueBits( const int val );
		void setAlphaBits( const int val );
		void setStencilBits( const int val );
		void setDepthBits( const int val );
		void setWidth( const int val );
		void setHeight( const int val );
		void setDPI( const float val );
		void setWindowed( const bool val );

		void setMajorVersion( int v );
		void setMinorVersion( int v );

		virtual bool initialize();
		virtual void printStatistics();

		virtual void setTitle( std::string head );
		virtual std::string getTitle();

		virtual void apply();

		static bool set( Display *display );
		static Display *get();
	};
}

#endif /* DISPLAY_H_ */
