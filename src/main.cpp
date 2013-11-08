#include "Main.h"
#include <ofxVisStudioLoggerChannel.h>
#include "TApp.h"
#include <ofAppGlutWindow.h>
#include <ofxSoylent.h>


#define EXIT_CODE_BAD_PARAMS	-1
#define EXIT_CODE_SUCCESS		0


//========================================================================
int main(int argc, const char** argv)
{
	//	log to visual studio if it's attached
	if ( IsDebuggerPresent() )
		ofLog::setChannel(ofPtr<ofVisStudioLoggerChannel>(new ofVisStudioLoggerChannel));

	auto Res = ofVec2f(400,400);

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, Res.x, Res.y, OF_WINDOW);

	//	core window/global setup
	ofVec2f ScreenSize( ofGetScreenWidth(), ofGetScreenHeight() );
	ScreenSize -= Res;
	ScreenSize /= 2;
	window.setWindowPosition( ScreenSize.x, ScreenSize.y );
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	//	line antialiasing
	ofEnableSmoothing(); 
	
	//	shape antialiasing
	window.setGlutDisplayString("rgba double samples>=4");


	//	create app
	ofPtr<ofBaseApp> pApp = ofPtr<ofBaseApp>( new testApp() );

	//	not setup
	if ( !pApp )
	{
		BufferString<1000> Debug;
		Debug << "No app type specified";
		return 0;
	}

	ofRunApp( pApp );

	//	gr: these never get hit in windows... WM_CLOSE does a sudden termination
	assert(false);
	//	clear the app pointer so update/draw etc won't get automatically called after delete
	ofSetAppPtr( ofPtr<ofBaseApp>() );
	pApp.reset();

	//delete pApp;

	return EXIT_CODE_SUCCESS;
}

