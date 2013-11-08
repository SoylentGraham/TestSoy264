#pragma once

#include "Main.h"
#include <Soy264.h>
#include <ofxSoylent.h>


class testApp;



class TDecodeThread : public ofThread
{
public:
	TDecodeThread(const char* Filename,testApp& Parent);

	virtual void	threadedFunction();

protected:
	void				OnError(Soy264::TError::Type Error);
	void				OnLog(const char* Message);

public:
	testApp&			mParent;
	bool				mDecoding;
	Soy264::TDecoder	mDecoder;
};



class testApp : public ofBaseApp
{
public:
	testApp();

	virtual void	setup();
	virtual void	update();
	virtual void	draw();
	virtual void	exit();

	void			OnLog(const char* Message);

protected:
	ofPtr<TDecodeThread>				mDecodeThread;
	ofMutexT<Array<BufferString<100>>>	mLogs;
};
