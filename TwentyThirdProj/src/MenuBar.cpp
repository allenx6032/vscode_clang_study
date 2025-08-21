#include "MenuBar.h"
#include "AppState.h"
#include "Logger.h"
#include "GLWindow.h"
#include <nfd.h>

namespace Coconut
{
    MenuBar::MenuBar(AppState* state)
        : ImGuiWidget(state, "Menu Bar"),
          mFileSettingsClicked(false),
          mFileOpenClicked(false),
          mFileQuitClicked(false),
          mFileCloseClicked(false)
    {}

    MenuBar::~MenuBar()
    {

    }

    void MenuBar::Draw()
    {
        if (ImGui::BeginMainMenuBar())
        {
            DrawFileMenu();
            DrawLoggingMenu();
            ImGui::EndMainMenuBar();
        }

        HandleFileMenuActions();
    }

    void MenuBar::DrawFileMenu()
    {
        if (ImGui::BeginMenu("File"))
		{
			mFileOpenClicked = ImGui::MenuItem("Open File...","CTRL+O");
            ImGui::Separator();
			mFileQuitClicked = ImGui::MenuItem("Quit","CTRL+Q");
			ImGui::EndMenu();
		}
    }



    void MenuBar::DrawViewMenu()
    {
        if (ImGui::BeginMenu("View"))
        {
			for (ImGuiWidget* widget : mAppState->GetWindow().GetImGuiWidgetsVector())
			{
                if (widget != this)
                {
					ImGui::Checkbox(widget->GetName().c_str(),widget->VisiblePointer());
                }
			}
            ImGui::EndMenu();
        }
    }

    void MenuBar::DrawLoggingMenu()
    {
        if(ImGui::BeginMenu("Logging"))
		{
            auto log = spdlog::get("");
			spdlog::level::level_enum currentLogLevel =  log->level();

			if (ImGui::RadioButton("Off", currentLogLevel == spdlog::level::off))
			{
				currentLogLevel = spdlog::level::off;
				spdlog::set_level(currentLogLevel);
			}

			if (ImGui::RadioButton("Error", currentLogLevel == spdlog::level::err))
			{
				currentLogLevel = spdlog::level::err;
				spdlog::set_level(currentLogLevel);
			}
			if (ImGui::RadioButton("Warning", currentLogLevel == spdlog::level::warn))
			{
				currentLogLevel = spdlog::level::warn;
				spdlog::set_level(currentLogLevel);
			}

            if (ImGui::RadioButton("Info", currentLogLevel == spdlog::level::info))
			{
				currentLogLevel = spdlog::level::info;
				spdlog::set_level(currentLogLevel);
			}

			if (ImGui::RadioButton("Debug", currentLogLevel == spdlog::level::debug))
			{
				currentLogLevel = spdlog::level::debug;
				spdlog::set_level(currentLogLevel);
			}



			ImGui::EndMenu();
		}
    }

    void MenuBar::FileOpenAction()
    {
        debug("MenuBar: OpenFileAction");
        nfdchar_t *selected_file_path = NULL;
		nfdresult_t result = NFD_OpenDialog("nc,gcode", NULL, &selected_file_path );

		if ( result == NFD_OKAY )
        {
			info("Success! {}",selected_file_path);
			free(selected_file_path);
		}
		else if ( result == NFD_CANCEL )
        {
			debug("User pressed cancel.");
		}
		else
        {
			error("Error: %s\n", NFD_GetError() );
		}
        mFileOpenClicked = false;
    }

    void MenuBar::FileCloseAction()
    {
        debug("MenuBar: CloseFileAction");
        mFileCloseClicked = false;
    }

    void MenuBar::FileQuitAction()
    {
        mAppState->SetLooping(false);
        mFileQuitClicked = false;
    }

    void MenuBar::HandleFileMenuActions()
    {
 		// Handle File Menu Actions
		if (mFileOpenClicked)
		{
			FileOpenAction();
		}
        else if (mFileCloseClicked)
        {
			FileCloseAction();
        }
        else if (mFileQuitClicked)
		{
            FileQuitAction();
		}
    }
}
