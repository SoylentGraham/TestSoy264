#include "TApp.h"



TDecodeThread::TDecodeThread(const char* Filename,testApp& Parent) :
	mParent		( Parent ),
	mDecoding	( true )
{
	auto Error = mDecoder.Load("D:\\bike.h264");
	OnError( Error );
	mDecoding = (Error==Soy264::TError::Success);
}

void TDecodeThread::threadedFunction()
{
	while ( isThreadRunning() && mDecoding )
	{
		TPixels Pixels;
		auto Error = mDecoder.DecodeNextFrame( Pixels );
		OnError( Error );

		if ( Error != Soy264::TError::Success )
			mDecoding = false;
	}
}

void TDecodeThread::OnError(Soy264::TError::Type Error)
{
	mParent.OnLog( Soy264::TError::ToString(Error) );
}

void TDecodeThread::OnLog(const char* Message)
{
	mParent.OnLog( Message );
}





testApp::testApp()
{
}


void testApp::setup() 
{
	mDecodeThread = ofPtr<TDecodeThread>( new TDecodeThread( "D:\\bike.h264", *this ) );
	mDecodeThread->startThread(true,true);

	ofBackground( 185, 140, 90 );

}

void testApp::exit()
{
}

void testApp::update() 
{
	
	float t = (ofGetElapsedTimef()) * 0.9f;
	float div = 250.0;
}


void testApp::draw() 
{
	
	ofSetColor(255);
	string info = ofToString(ofGetFrameRate(), 2);
	
	{
		ofMutex::ScopedLock lock( mLogs );
		auto& Logs = mLogs.Get();
		for ( int e=0;	e<Logs.GetSize();	e++ )
		{
			info += "\n";
			info += Logs[e];
		}
	}

	ofDrawBitmapStringHighlight(info, 30, 30);
}


void testApp::OnLog(const char* Message)
{
	ofMutex::ScopedLock lock( mLogs );
	auto& Logs = mLogs.Get();
	Logs.PushBack( Message );
}

