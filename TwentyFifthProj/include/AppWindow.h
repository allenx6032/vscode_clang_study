#pragma once

#include <glad/glad.h>
#include <imgui/imgui.h> //For ImGuiContext
#include <GLFW/glfw3.h> //For GLFWwindow

class AppWindow {
public:
	enum class InitializationStatus {
		INIT_OK = 0,
		//Non-fatal errors (> 0)
		ERROR_ALREADY_INIT = 1,
		//Fatal errors (< 0)
		ERROR_GLFW_INIT_FAILED = -1,
		ERROR_WINDOW_CREATION_FAILED = -2,
		ERROR_OPENGL_LOADER_INIT_FAILED = -3,
		ERROR_IMGUI_CONTEXT_CREATION_FAILED = -4,
		ERROR_IMGUI_GLFW_BACKEND_INIT_FAILED = -5,
		ERROR_IMGUI_OPENGL_BACKEND_INIT_FAILED = -6,
	};

	AppWindow() {};
	virtual ~AppWindow();

	InitializationStatus Initialize(int width_hint, int height_hint, const char* title, GLFWmonitor* monitor = nullptr);
	void UpdateAndDrawUntilClosing();
	void UpdateAndDraw();

	ImGuiContext* GetImGuiContext() const { return imgui; }
	GLFWwindow* GetGLFWWindow() const { return window; }

	float clearColor[3] = { 0.0f, 0.0f, 0.0f };
private:
	virtual void InitializationCallback();
	virtual void ImGuiDrawCallback() = 0;

	bool _Initialized = false;

	ImGuiContext* imgui = nullptr;
	GLFWwindow* window = nullptr;
};

inline bool INITIALIZATION_FAILED(AppWindow::InitializationStatus status) {
	return status < AppWindow::InitializationStatus::INIT_OK;
}