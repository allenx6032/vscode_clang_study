#pragma once

#include "ImGuiWidget.h"

namespace Coconut
{
    class MenuBar : public ImGuiWidget
    {
    public:
        MenuBar(AppState*);
        ~MenuBar() override;
        void Draw() override;

    protected:
        void DrawFileMenu();
        void DrawViewMenu();
        void DrawLoggingMenu();


        void HandleFileMenuActions();

        void FileOpenAction();
        void FileCloseAction();
        void FileQuitAction();


    private:
        bool mFileSettingsClicked;
        bool mFileOpenClicked;
        bool mFileQuitClicked;
        bool mFileCloseClicked;
            };
}
