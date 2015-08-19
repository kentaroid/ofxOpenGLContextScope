#include "ofxOpenGLContextScope.h"

#ifdef TARGET_OSX

#include <OpenGL/OpenGL.h>

struct ofxOpenGLContextScopeImpl
{
	ofxOpenGLContextScopeImpl()
	{
		CGLCreateContext(pixStuff, ctx, &newCtx);
		CGLLockContext(newCtx);
		CGLSetCurrentContext(newCtx);
		CGLEnable(newCtx, kCGLCEMPEngine);
	}
	
	~ofxOpenGLContextScopeImpl()
	{
		CGLDisable(newCtx, kCGLCEMPEngine);
		CGLUnlockContext(newCtx);
		CGLDestroyContext(newCtx);
	}
	
	static void setup(bool useSharedContext)
	{
		//TODO: check useSharedContext
		ctx = useSharedContext?CGLGetCurrentContext():NULL;
		pixStuff = CGLGetPixelFormat(ctx);
	}


	CGLContextObj newCtx;
	static CGLContextObj ctx;
	static CGLPixelFormatObj pixStuff;
};

CGLContextObj ofxOpenGLContextScopeImpl::ctx = NULL;
CGLPixelFormatObj ofxOpenGLContextScopeImpl::pixStuff = NULL;

#elif defined TARGET_WIN32 

struct ofxOpenGLContextScopeImpl 
{
	ofxOpenGLContextScopeImpl()
	{
		glfwMakeContextCurrent(g_SubWindow);
	}

	~ofxOpenGLContextScopeImpl()
	{
		glfwMakeContextCurrent(nullptr);
	}

	static void setup(bool useSharedContext) {
	
		GLFWwindow *window = glfwGetCurrentContext();
		g_SubWindow = glfwCreateWindow(1, 1, "Thread", nullptr, useSharedContext ? window : nullptr);
		if (g_SubWindow) {
			glfwHideWindow(g_SubWindow);
		}else {
			glfwTerminate();
		}
	}

	static GLFWwindow *g_SubWindow;
};

GLFWwindow * ofxOpenGLContextScopeImpl::g_SubWindow = NULL;

#else
#error not implemented
#endif

#pragma mark -

ofxOpenGLContextScope::ofxOpenGLContextScope() : impl(new ofxOpenGLContextScopeImpl) {}

ofxOpenGLContextScope::~ofxOpenGLContextScope()
{
	delete impl;
	impl = NULL;
}

void ofxOpenGLContextScope::setup(bool useSharedContext)
{
	ofxOpenGLContextScopeImpl::setup(useSharedContext);
}
