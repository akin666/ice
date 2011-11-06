
#ifndef ICE_OPENGL_H_
#define ICE_OPENGL_H_

#include <iostream>

#define NO_GLEE

#define GL_NULL_BUFFER 0

#ifndef NO_GLEE
 #include "../lib/GLee.h"
#else
 #define GLEW_STATIC
 #include <glew/glew.h>
 #define GL_INITIALIZATION ( glewInit() == GLEW_OK )
#endif

#ifndef NO_GLFW
 #include <GL/glfw.h>
#endif

#ifndef NO_GL
 #include <GL/gl.h>
#endif

#ifndef GL_INITIALIZATION
	#define GL_INITIALIZATION true
#endif

// TODO!
#if 0
#define _OPENGL_2_0_
#define _OPENGL_2_1_
#define _OPENGL_3_0_
#define _OPENGL_3_1_
#define _OPENGL_3_2_
#define _OPENGL_3_3_
#define _OPENGL_4_0_
#define _OPENGL_4_1_
#endif

#if not defined(NO_LOGGER) and defined(LOG_ERROR)
#define LOG_SYSTEM_ERROR(txt) LOG_ERROR(txt)
#endif

#if not defined(LOG_SYSTEM_ERROR)
#define LOG_SYSTEM_ERROR(txt) std::cout<<txt<<std::endl
#endif

#define GL_FLUSH_ERRORS() while( glGetError() != GL_NO_ERROR )

#ifndef _RELEASE
 #define GL_TEST_ERROR(txt) { \
  int gl_error_var; \
  while( ( gl_error_var = glGetError() ) != GL_NO_ERROR ) { \
  switch( gl_error_var ) { \
	case GL_NO_ERROR : break; \
	case GL_INVALID_VALUE : { LOG_SYSTEM_ERROR( std::string( "GL_INVALID_VALUE " ) + txt ); break; } \
	case GL_INVALID_ENUM : { LOG_SYSTEM_ERROR( std::string( "GL_INVALID_ENUM " ) + txt ); break; } \
	case GL_INVALID_OPERATION : { LOG_SYSTEM_ERROR( std::string( "GL_INVALID_OPERATION "  ) + txt ); break; } \
	case GL_STACK_OVERFLOW : { LOG_SYSTEM_ERROR( std::string( "GL_STACK_OVERFLOW "  ) + txt ); break; } \
	case GL_STACK_UNDERFLOW : { LOG_SYSTEM_ERROR( std::string( "GL_STACK_UNDERFLOW "  ) + txt ); break; } \
	case GL_OUT_OF_MEMORY : { LOG_SYSTEM_ERROR( std::string( "GL_OUT_OF_MEMORY "  ) + txt ); break; } \
 	default : { LOG_SYSTEM_ERROR( std::string( "GL WTF!"  ) + txt ); break; } \
  } } }
#else
 #define GL_TEST_ERROR(txt)
#endif

#endif /* ICE_OPENGL_H_ */
