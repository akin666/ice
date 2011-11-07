// TODO
#include "ice.h"
#include <log/log>
#include <graphics/loader.h>
#include <system/opengl>
#include <graphics/shaderprogram.h>
#include <dio/filedio.h>
#include <dio/textfiledio.h>
#include <dio/binarydio.h>
#include <system/utf8decoder>
#include <system/display>
#include <system/implementation/glfwdisplay.h>
#include <graphics/gtexture.h>
#include <graphics/simplemesh.h>
#include <text/textgenerator.h>
#include <SLB/SLB.hpp>
#include <system/global>

#include <glm/glm>
#include <glm/transform>

#include <log/logserver>

#include <entity/pipeline>
#include <entity/entity>

#include <entity/components/physicscomponent.h>
#include <entity/components/timecomponent.h>
#include <entity/components/testboxcomponent.h>
#include <entity/storage>

#include <system/random.h>

#include <threadpool/threadpool>
//#include "test/testwork.h"

#include "iceapplication.h"

using namespace ice;

/*
 * TextureCoordinate array (matching those vertexes defined above)
 */
GLfloat texCoords[]={
        0.0, 0.0, // mapping coordinates for vertex v8
        0.0, 1.0, // mapping coordinates for vertex v9
        1.0, 1.0, // mapping coordinates for vertex v10
        1.0, 0.0, // mapping coordinates for vertex v11
        };

/*
 * Indices array that forms the quads i will be using..
 */
GLubyte indices[] = {
    	0, 1, 2, 3     // quad 1 bottom
        };


int iceMain( int argc , char *argv[] )
{
	IceApplication *application;

	std::string logPoint("inproc://log");
	LogServer logServer;

	// Figure out optimal thread count.
	unsigned int hwThreadCount = ThreadPool::getHardwareThreadCount();
	switch( hwThreadCount )
	{
		case 0 :
			hwThreadCount = 16;
			break; // Probably an errorcondition.. put at least 16 threads.
		case 1 :
			hwThreadCount = 1;
			break;	// OH GOD! Single core no hw threads. well, go into singlethreaded mode.
		case 2 :
			hwThreadCount = 2;
			break;  // OH GOD! Probably single core, but 2 hw threads. Well.. use em..
		default:
			hwThreadCount = (unsigned int)(hwThreadCount * 1.5);
			break; // well, if the machine has 8 HW threads, 12 should drown it.
	}

	// Init
	try
	{
		logServer.init( "test.log" , logPoint );

		application = new IceApplication( argc , argv );

		application->initialize( logPoint , hwThreadCount );

		Application::set( application );
	}
	catch( Exception& e )
	{
		std::cout << "Failed to initialize Application: " << e.getMessage() << std::endl;
		return -1;
	}
	catch( ... )
	{
		std::cout << "Failed to initialize Application, unknown cause!" << std::endl;
		return -1;
	}

	// Common begin.
	int entityCount = 10000;
	Entity entity[entityCount];

	GLFWDisplay display;
	Display::set( &display );

	display.setMajorVersion( 2 );
	display.setMinorVersion( 1 );

	if( !display.initialize() ) {
		std::cout << "Failed to init display" << std::endl;
		return 0;
	}

	int w = display.getWidth();
	int h = display.getHeight();
	glViewport( 0 , 0 , w , h );

	glMatrixMode( GL_PROJECTION );

	double aspect = (double)w/(double)h;
	double cube = 0.5;

	glFrustum( // YEY this is FCKD!
				-cube/2.0 ,
				cube/2.0 ,
				-cube*aspect/2.0 ,
				cube*aspect/2.0  ,
				0.1f,
				50
		);

	glMatrixMode( GL_MODELVIEW );
	glTranslatef( 0 , -50 , 0 );

	TimeComponent times;
	PhysicsComponent physics;
	TestBoxComponent testBox;

	Pipeline& pipeline = Application::get()->getPipeline();

	Random& random = Random::get();

	PositionProperty *positionProperty = Storage::createProperty<PositionProperty>( PROPERTY_POSITION_NAME );
	WeightProperty *weightProperty = Storage::createProperty<WeightProperty>( PROPERTY_WEIGHT_NAME );

	for( int i = entityCount - 1 ; i >= 0 ; --i )
	{
		try {
			times.attach( entity[i] );
			physics.attach( entity[i] );
			testBox.attach( entity[i] );
		}
		catch( ComponentException& e ) {
		}
		catch( ... ) {
		}

		PositionProperty::Data& positionData = positionProperty->get( entity[i].id );
		float& weight = weightProperty->get( entity[i].id );

		positionData.position.y = random.getFloat() * 100.0f; // the thing is up to 2 meters.

		positionData.position.x = random.getFloat() * 100.0f - 50.0f;
		positionData.position.z = -random.getFloat() * 50.0f;

		weight = 50.0f + random.getFloat() * 950.0f; // fatass weights a [50g,1kg]
	}

	try {
		pipeline.attach( &times );
		pipeline.attach( &physics );
		pipeline.attach( &testBox );
	}
	catch( PipelineException& e ) {
	}
	catch( ... ) {
	}

	// Main Loop:
	Application *runtime;
	do
	{
		runtime = Application::get();

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		try {
			runtime->getPipeline().run();
		}
		catch( Exception& e ) {
			runtime->handle( e );
		}
		catch( ... ) {
			runtime->kill();
		}

		glfwSwapBuffers();

		if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
		{
			runtime->kill();
		}
	}
	while( !runtime->shouldExit() );

	glfwTerminate();

	delete application;

	return 0;
}



