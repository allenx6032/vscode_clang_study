#include "AppState.h"
#include "Logger.h"

#include <thread>

using std::this_thread::yield;

namespace Coconut
{
	AppState::AppState(int argc, char** argv) :
        mLooping(true),
        mArgc(argc),
    	mArgv(argv),
      	mWindow(this),
        // ImGui Widgets
        mMenuBar(this),
        mPreviewWindow(this),
		// GL Widgets
        mGridDrawer(this)
	{
		debug("AppState: Constructor");
    }

    bool AppState::Init()
    {
		debug("AppState: Init");
        if (!mWindow.Init())       return false;
        if (!CreateImGuiWidgets()) return false;
        if (!CreateGLWidgets())    return false;
        return true;
    }

    bool AppState::CreateImGuiWidgets()
    {
		debug("AppState: CreateImGuiWidgets");
        mWindow.AddImGuiWidget(&mMenuBar);
        mWindow.AddImGuiWidget(&mPreviewWindow);
        return true;
    }

    bool AppState::CreateGLWidgets()
    {
		debug("AppState: CreateGLWidgets");

        if (!mGridDrawer.Init()) return false;
        mWindow.AddGLWidget(&mGridDrawer);

        return true;
    }

    GLPreviewWindow& AppState::GetPreviewWindow()
    {
        return mPreviewWindow;
    }

    bool AppState::GetLooping() const
    {
        return mLooping;
    }

    void AppState::SetLooping(bool looping)
    {
        mLooping = looping;
    }

    bool AppState::Run()
    {
		debug("AppState: Run");
        while (mLooping)
        {
            mWindow.Update();
            yield();
        }
        return true;
    }

    Window& AppState::GetWindow()
    {
        return mWindow;
    }
}
