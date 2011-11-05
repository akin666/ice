/*
 * glfwdisplay.cpp
 *
 *  Created on: 23.3.2011
 *      Author: akin
 */

#include "glfwdisplay.h"
#include <sys/opengl.h>
#include <ui/uiframe.h>

namespace ice
{
	namespace GLFWInputHandling
	{
//	typedef void (GLFWCALL * GLFWwindowsizefun)(int,int);
//	typedef int  (GLFWCALL * GLFWwindowclosefun)(void);
//	typedef void (GLFWCALL * GLFWwindowrefreshfun)(void);

		int mouseX = 0;
		int mouseY = 0;
		int mouseWheel = 0;

		void setup()
		{
			 glfwGetMousePos( &mouseX , &mouseY );
			 mouseWheel = glfwGetMouseWheel();
		}

		void keyboardCharCallback(int key, int action)
		{
			InputListener *listener = UIFrame::getCurrent();
			if( listener != NULL )
			{
				listener->handleKeyboardCharacter( (unsigned int)key , (action == GLFW_PRESS ? 1.0f : 0.0f ) );
			}
		}

		void keyboardCallback(int key, int action)
		{
			InputListener *listener = UIFrame::getCurrent();
			if( listener != NULL )
			{
				listener->handleKeyboard( (unsigned int)key , (action == GLFW_PRESS ? 1.0f : 0.0f ) );
			}
		}

		void mouseWheelCallback(int wheel)
		{
			InputListener *listener = UIFrame::getCurrent();
			if( listener != NULL )
			{
				listener->handleMouseWheel( wheel - mouseWheel );
				mouseWheel = wheel;
			}
		}

		void mouseButtonCallback(int button, int action)
		{
			InputListener *listener = UIFrame::getCurrent();
			if( listener != NULL )
			{
				InputListener::Button resolver;
				switch( button )
				{
					case GLFW_MOUSE_BUTTON_LEFT :
						resolver = InputListener::LEFT;
						break;
					case GLFW_MOUSE_BUTTON_RIGHT :
						resolver = InputListener::RIGHT;
						break;
					case GLFW_MOUSE_BUTTON_MIDDLE :
						resolver = InputListener::MIDDLE;
						break;
					case GLFW_MOUSE_BUTTON_4 :
						resolver = InputListener::ADDON_1;
						break;
					case GLFW_MOUSE_BUTTON_5 :
						resolver = InputListener::ADDON_2;
						break;
					case GLFW_MOUSE_BUTTON_6 :
						resolver = InputListener::ADDON_3;
						break;
					case GLFW_MOUSE_BUTTON_7 :
						resolver = InputListener::ADDON_4;
						break;
					case GLFW_MOUSE_BUTTON_8 :
						resolver = InputListener::ADDON_5;
						break;
					default:
						resolver = InputListener::ADDON_6;
						break;
				}

				listener->handleMouseButton( resolver , (action == GLFW_PRESS ? 1.0f : 0.0f ) );
				listener->handleMouseButtonAction( resolver );
			}
		}

		void mouseMoveCallback(int x, int y)
		{
			InputListener *listener = UIFrame::getCurrent();
			if( listener != NULL )
			{
				listener->handleMouseMove( x - mouseX , y - mouseY );

				mouseX = x;
				mouseY = y;
			}
		}
	}

	GLFWDisplay::GLFWDisplay()
	: Display()
	{
	}

	GLFWDisplay::~GLFWDisplay()
	{
		glfwTerminate();
	}

	bool GLFWDisplay::initialize()
	{
		if (glfwInit() != GL_TRUE)
		{
			return false;
		}

		glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR , settable.major );
		glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR , settable.minor );

		// set same mode as on desktop
		if (glfwOpenWindow(
				settable.width,
				settable.height,
				settable.red_bits,
				settable.green_bits,
				settable.blue_bits,
				settable.alpha_bits,
				settable.depth_bits,
				settable.stencil_bits,
				( settable.windowed ? GLFW_WINDOW : GLFW_FULLSCREEN ) ) != GL_TRUE )
		{
			std::cout << "Failed to open window." << std::endl;
			return false;
		}

		if( !GL_INITIALIZATION )
		{
			std::cout << "Failed to initialize GL." << std::endl;
			return false;
		}

		current = settable;

		// Disable mouse cursor
		glfwDisable( GLFW_MOUSE_CURSOR );

		GLFWInputHandling::setup();

		glfwSetKeyCallback( GLFWInputHandling::keyboardCallback );
		glfwSetCharCallback( GLFWInputHandling::keyboardCharCallback );
		glfwSetMousePosCallback( GLFWInputHandling::mouseMoveCallback );
		glfwSetMouseButtonCallback( GLFWInputHandling::mouseButtonCallback );
		glfwSetMouseWheelCallback( GLFWInputHandling::mouseWheelCallback );

		return true;
	}

	void GLFWDisplay::setTitle( std::string head )
	{
		glfwSetWindowTitle( head.c_str() );
		title = head;
	}

	std::string GLFWDisplay::getTitle()
	{
		return title;
	}

	void GLFWDisplay::apply()
	{
		// TODO!

		// current = settable;
	}

	void GLFWDisplay::printStatistics()
	{
		std::cout << "Renderer Data: " << std::endl;
		std::cout << " Vendor:" << glGetString(GL_VENDOR) << std::endl;
		std::cout << " Renderer:" << glGetString(GL_RENDERER) << std::endl;
		std::cout << " Version:" << glGetString(GL_VERSION) << std::endl;
		std::cout << " Shading language:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	}
}

