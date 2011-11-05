// TODO
#include "ice.h"
#include <sys/log.h>
#include <graphics/loader.h>
#include <sys/opengl.h>
#include <graphics/shaderprogram.h>
#include <dio/filedio.h>
#include <dio/textfiledio.h>
#include <dio/binarydio.h>
#include <sys/utf8decoder.h>
#include <sys/display.h>
#include <sys/implementation/glfwdisplay.h>
#include <graphics/gtexture.h>
#include <graphics/simplemesh.h>
#include <text/textgenerator.h>
#include "core/vm/machine.h"
#include <SLB/SLB.hpp>
#include "corescript/commonscript.h"
#include <ui/uiframe.h>
#include <ui/uicomponent.h>
#include <ui/uiimage.h>
#include <ui/uicontainer.h>
#include <ui/uiarea.h>
#include <ui/uibutton.h>
#include <ui/uiwindow.h>
#include <ui/uitext.h>
#include <asset/assetmanager.h>

#include <glm/glm>
#include <glm/transform>

#include <logserver/logserver.h>

#include <entity/pipeline>
#include <entity/entity>

#include "test/namecomponent.h"
#include "test/movercomponent.h"

#include <entity/components/physicscomponent.h>
#include <entity/components/timecomponent.h>
#include <entity/components/testboxcomponent.h>
#include <entity/storage>

#include <sys/random.h>

#include <threadpool/threadpool>
#include "test/testwork.h"

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


int fixedFunctionPipeline()
{
	glClearColor( 0.2f , 0.4f , 0.5f , 1.0f );

	glm::mat4x4 gameProjection;

	const float aspectRatio = (float)600/(float)600;

	gameProjection = glm::frustum(
			-1.0f,
			 1.0f,
			-aspectRatio,
			 aspectRatio,
			0.5f,
			1000.0f
			);


	// open UTF8 file, & read it into string
	FileDIO utf8dio;
	utf8dio.open("utf8test.txt");
	unsigned int utf8len = utf8dio.getDataSize();
	char texti[utf8len];
	utf8dio.readBlock( (unsigned char*)texti , utf8len );
	std::string dectext( texti );

	std::vector<UNICODE> data;
	// Convert UTF8 text into UNICODE (unsigned int) vector.
	UTF8Decoder decoder;
	decoder.init( dectext );
	decoder.decodeTo( data );

	/*
	Machine *script = AssetManager<Machine>::get( "default" );
	if( !script->doFile( "ice/resources/script/ui/init_ui.lua" ) )
	{
		return -1;
	}
*/
	//if( !loader::loadTexture( "out" 	, "dragon.png" 			, "dragon.png" )) std::cout << "FAIL dragon" << std::endl;

	//SimpleMesh mesh;
	//SimpleMesh::setBox( mesh , 5 , 5 , 5 , AssetManager<Texture>::get( "dragon.png" ) );

//	UIFrame frame;
////	UIFrame::setCurrent( &frame );
//	frame.setDimensions( w , h );
//	frame.initialize();
//	frame.getMouse().initialize( AssetManager<Texture>::get("mouse2.png") );
//
//	UIWindow window;
//	window.initialize( AssetManager<Texture>::get("meta.png") , AssetManager<Texture>::get("tausta.png") );
//	window.getPosition() = Vec2<float>( 100 , 100 );
//
//	frame.getContainer().addChild( &window );
//
//	UIContainer& container = window.getContainer();
//
//	UIText label;
//	label.setText( data );
//	label.setFont("japan");
//	label.setFontSize( 32 );
//	label.setFontColor( Color<float>::blue );
//	label.apply();
//	label.getPosition() = Vec2<float>( 50 , 150 );
//	container.addChild( &label );
//
//	UIImage *imageChild;
//	imageChild = new UIImage;
//	imageChild->initialize( AssetManager<Texture>::get("firewall.png") );
//	imageChild->getPosition() = Vec2<float>( 100 , 100 );
//	container.addChild( imageChild );
//
//	imageChild = new UIImage;
//	imageChild->initialize( AssetManager<Texture>::get("prayer.png") );
//	imageChild->getPosition() = Vec2<float>( 150 , 150 );
//	container.addChild( imageChild );
//
//	imageChild = new UIImage;
//	imageChild->initialize( AssetManager<Texture>::get("shadowbolt.png") );
//	imageChild->getPosition() = Vec2<float>( 200 , 200 );
//	container.addChild( imageChild );
//
//	UIButton button;
//	button.initialize( AssetManager<Texture>::get("button_up.png") , AssetManager<Texture>::get("button_down.png") );
//	button.getPosition() = Vec2<float>( 200 , 440 );
//	container.addChild( &button );
//
//	button.setScript( "onClick" , "Hello world, I Clicked a Button1" );
//	button.setScript( "onHoverIn" , "Hovered to Button1" );
//	button.setScript( "onHoverOut" , "Hovered out of Button1" );
//
//	UIButton button2;
//	button2.initialize( AssetManager<Texture>::get("button_up.png") , AssetManager<Texture>::get("button_down.png") );
//	button2.getPosition() = Vec2<float>( 350 , 440 );
//	container.addChild( &button2 );
//
//	button2.setScript( "onClick" , "Hello world, I Clicked a Button2" );
//	button2.setScript( "onHoverIn" , "Hovered to Button2" );
//	button2.setScript( "onHoverOut" , "Hovered out of Button2" );

	glm::mat4x4 model;

	float dis = 2.5f;
	float rr = 0;

//	window.setVisible( true );

	while( true )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// escape to quit, arrow keys to rotate view
		if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
		{
		}

		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

		glLoadMatrixf( &gameProjection[0][0] );
		glMatrixMode( GL_MODELVIEW );

		rr -= 0.001f;
		dis -= 0.001f;

		model = glm::translate( glm::mat4(1.0f), glm::vec3( 0.0f , 0.0f , dis ) );

		//mesh.draw( model );


		UIFrame *current = UIFrame::getCurrent();
		if( current != NULL )
		{
			current->render();
		}

//		glEnable( GL_TEXTURE_2D );
//		glBindTexture( GL_TEXTURE_2D , font.getTextureID() );
//
//		glColor3f( 1,1,0);
//		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//		glEnableClientState(GL_VERTEX_ARRAY);
//
//		glEnable( GL_BLEND );
//		glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
//
//		textRender.bindVertexBuffer();
//		glVertexPointer(3, GL_FLOAT, 0, 0);
//
//		textRender.bindTextureBuffer();
//		glTexCoordPointer(2 , GL_FLOAT, 0 , 0);
//
//		textRender.renderBuffer();
//
//		glVertexPointer(3, GL_FLOAT, 0, 0);
//		glTexCoordPointer(2 , GL_FLOAT, 0 , 0);
//
//		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//		glDisableClientState(GL_VERTEX_ARRAY);

		glfwSwapBuffers();
	}

	glfwTerminate();

	return 0;
}

//int shaderPipeline( /*Font& font , SimpleRenderer& textRender ,*/ int w , int h )
//{
//	LOG("Load shaders");
//	Shader *vertexShader = loader::loadShader( Shader::VERTEX , "ice/shaders/font/font.vs" );
//	Shader *fragmentShader = loader::loadShader( Shader::FRAGMENT , "ice/shaders/font/font.fs" );
//
//	ShaderProgram program;
//	program.insert( *vertexShader );
//	program.insert( *fragmentShader );
//
//	LOG("Link shaders");
//	program.link();
//
//	if( !program.linked() )
//	{
//		std::cout << "Not linked " << program.getError() << " !!! " << std::endl;
//		return 0;
//	}
//
//	Matrixf model;
//	Matrixf lense;
//
//	lense.identity();
//	lense.frustum( // YEY this is FCKD!
//			-w/2,
//			w/2,
//			-h/2,
//			h/2,
//			0.5f,
//			50.0f
//	);
//
//	lense.identity();
//	lense.ortho(
//			-w/2,
//			w/2,
//			-h/2,
//			h/2,
//			-1.0f,
//			50.0f
//	);
//
//	model.identity();
//
//	Attribute *s_vertex = program.insertAttribute( "vertex" );
//	Attribute *s_coordinates = program.insertAttribute( "coordinates" );
//	Uniform *s_model = program.insertUniform( "model" );
//	Uniform *s_lense = program.insertUniform( "lense" );
//	Uniform *s_tex = program.insertUniform( "tex" );
//
//	program.bind();
//
//	LOG("Run loop");
//	float kk = -1;
//	while( true )
//	{
//		GL_TEST_ERROR("MainLoopErrors");
//		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//		// escape to quit, arrow keys to rotate view
//		if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
//			break;
//		if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
//		}
//		if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
//		}
//
//		if( (kk-=0.2) < -10800 ) kk = 0;
//
//		model.identity();
//		model.translate( kk , -200 , -0.5f );
//		model.scale( 5 , 5 , 1 );
//
//		s_model->setMatrix4( model.get() , 1 );
//		s_lense->setMatrix4( lense.get() , 1 );
//
////		s_tex->bindTexture( 0 , font.getTextureID() ); // lets use texture unit 0 for now..
////
////		glEnable( GL_BLEND );
////		glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
////
////		s_vertex->enable();
////		s_coordinates->enable();
////
////		textRender.bindVertexBuffer();
////		s_vertex->setPointer( 3 , GL_FLOAT , 0 );
////
////		textRender.bindTextureBuffer();
////		s_coordinates->setPointer( 2 , GL_FLOAT , 0 );
////
////		textRender.renderBuffer();
////
////		glVertexPointer(3, GL_FLOAT, 0, 0);
////		glTexCoordPointer(2 , GL_FLOAT, 0 , 0);
////
////		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
////		glDisableClientState(GL_VERTEX_ARRAY);
//
//		glfwSwapBuffers();
//	}
//
//	glfwTerminate();
//
//	return 0;
//}

int iceMain( int argc , char *argv[] )
{
	std::cout << "Ice Starting LogServer." << std::endl;
	std::string logPoint("inproc://log");
	LogServer logServer;
	logServer.init( "test.log" , logPoint );

	IceApplication application( argc , argv );

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

	application.initialize( logPoint , hwThreadCount );
	Application::set( &application );

	// Common begin.
	ThreadPool& pool = Application::get()->getThreadPool();

	TestWork work[32];
	for( int i = 0 ; i < 32 ; ++i )
	{
		pool.schedule( &work[i] );
	}

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

//	NameComponent namer;
//	MoverComponent mover;
	TimeComponent times;
	PhysicsComponent physics;
	TestBoxComponent testBox;

	Pipeline& pipeline = Application::get()->getPipeline();

	Random& random = Random::get();

	PositionProperty *positionProperty = Storage::createProperty<PositionProperty>( PROPERTY_POSITION_NAME );
	WeightProperty *weightProperty = Storage::createProperty<WeightProperty>( PROPERTY_WEIGHT_NAME );

	for( int i = entityCount - 1 ; i >= 0 ; --i )
	{
		times.attach( entity[i] );
		physics.attach( entity[i] );
		testBox.attach( entity[i] );

		PositionProperty::Data& positionData = positionProperty->get( entity[i].id );
		float& weight = weightProperty->get( entity[i].id );

		/**/
		positionData.position.y = random.getFloat() * 100.0f; // the thing is up to 2 meters.

		positionData.position.x = random.getFloat() * 100.0f - 50.0f;
		positionData.position.z = -random.getFloat() * 50.0f;

		weight = 50.0f + random.getFloat() * 950.0f; // fatass weights a [50g,1kg]
		/**/
		/*
		positionData.position.y =  random.getFloat() * 125.0f; // the thing is up to 2 meters.

		positionData.position.x = -50.0f + (i*0.01);
		positionData.position.z =  -25;

		weight = 100 + i * 0.03;
		/**/
		/*
		positionData.position.y =  125;//random.getFloat() * 125.0f; // the thing is up to 2 meters.

		positionData.position.x = -50.0f + (i*0.01);
		positionData.position.z =  -25;

		weight = 100;//100 + i * 0.03;
		/**/
	}

	pipeline.attach( &times );
	pipeline.attach( &physics );
	pipeline.attach( &testBox );

	do {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		Application::get()->getPipeline().run();
		glfwSwapBuffers();

		if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
		{
			Application::get()->kill();
		}
	} while( !Application::get()->shouldExit() );

	glfwTerminate();



//	Machine *script = new Machine;
//	AssetManager<Machine>::set( "default" , script );

//	script->initialize();

	// commonScript load all things.
//	ice::corescript::loadAll();


/*
	if( !script->doFile( "ice/resources/script/system/system_init.lua" ) )
	{
		return -1;
	}
*/

	//////////////////////////
	// Font loading test
	////////////
//	LOG("Load font");
//	Font font;
//	FileDIO dio;
//	//dio.open("ice/resources/fonts/bitstream-vera/Vera.ttf");
//	//dio.open("ice/resources/fonts/AGOptimaCyr_Roman.ttf");
//	dio.open("ice/resources/fonts/GT2000K2.TTF");
//	font.initialize( dio );
//
//	LOG("Load utf8 text");
//	FileDIO utf8dio;
//	utf8dio.open("utf8test.txt");
//	unsigned int utf8len = utf8dio.getDataSize();
//	char texti[utf8len];
//	utf8dio.readBlock( (unsigned char*)texti , utf8len );
//	std::string dectext( texti );
//	font.loadGlyph( dectext );
//
//	SimpleRenderer textRender( font );
//
//	textRender.setText( dectext );

//	Dictionary dictionary;
//
//	bool writeKirja = false;
//	std::string kirjaFile = "kirja.dp";
//	if( writeKirja )
//	{
//		FileDIO outDio;
//		outDio.open(kirjaFile);
//
//		TextEntry myHuge;
//		myHuge.name = "MyHugeIsSooHuge";
//		myHuge.text = "HugeIsVeryVeryHumongouslyHugeandSoftLongLike A Long long peacock. I wanna see your peacockPeacockPEACOCK.";
//		TextEntry myHuge2;
//		myHuge2.name = "JOOIHANHEMMETIN";
//		myHuge2.text = "ISOonISO ja hemmetin iso on isompi kuin julmetun kokoinen PEACKOCK.";
//
//		dictionary.add( &myHuge );
//		dictionary.add( &myHuge2 );
//
//		EntryManager::save( dictionary , outDio );
//	}
//	else
//	{
//		// Read kirja data
//		FileDIO inDio;
//		inDio.open(kirjaFile);
//
//		EntryManager::load( dictionary , inDio );
//
//		std::vector<std::string> keys;
//		dictionary.getKeys( keys );
//
//		for( unsigned int i = 0 ; i < keys.size() ; ++i )
//		{
//			std::cout << "Found key: " << keys[i] << std::endl;
//
//			TextEntry *entry = (TextEntry *)dictionary.get( keys[i] );
//
//			std::cout << "text: " << entry->text << std::endl;
//		}
//	}

	//return fixedFunctionPipeline();
	return 0;
}



