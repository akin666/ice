/*
 * glfwdisplay.h
 *
 *  Created on: 23.3.2011
 *      Author: akin
 */

#ifndef GLFWDISPLAY_H_
#define GLFWDISPLAY_H_

#include "../display.h"

namespace ice
{
	class GLFWDisplay : public Display
	{
	protected:
		std::string title;
	public:
		GLFWDisplay();
		virtual ~GLFWDisplay();

		virtual bool initialize();

		virtual void printStatistics();

		virtual void setTitle( std::string head );
		virtual std::string getTitle();

		virtual void apply();
	};
}

#endif /* GLFWDISPLAY_H_ */
