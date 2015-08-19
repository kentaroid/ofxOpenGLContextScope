#pragma once

#include "ofMain.h"

struct ofxOpenGLContextScopeImpl;

class ofxOpenGLContextScope
{
public:

	static void setup();
	static void setup(bool useSharedContext = true);

	ofxOpenGLContextScope();
	~ofxOpenGLContextScope();
	
private:
	
	ofxOpenGLContextScopeImpl *impl;
	ofxOpenGLContextScope(const ofxOpenGLContextScope&) {}
	ofxOpenGLContextScope& operator=(const ofxOpenGLContextScope&) {}
	
};
