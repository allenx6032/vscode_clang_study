#pragma once

// #include <string>
#include "GLWindow.h"

// ImGui Widgets
#include "MenuBar.h"
#include "GLPreviewWindow.h"

// GL Widgets
#include "GridDrawer.h"

namespace Coconut
{
	class AppState
	{
	public:
		AppState(int argc, char** argv);
        bool Init();
        bool Run();

        bool GetLooping() const;
        void SetLooping(bool looping);

        Window& GetWindow();
        GLPreviewWindow& GetPreviewWindow();

    protected:
        bool CreateImGuiWidgets();
        bool CreateGLWidgets();

    private:
        bool mLooping;
        int mArgc;
        char** mArgv;
        Window mWindow;
        // ImGui Widgets
        MenuBar mMenuBar;
        GLPreviewWindow mPreviewWindow;
        // GL Widgets
        GridDrawer mGridDrawer;
	};
}
