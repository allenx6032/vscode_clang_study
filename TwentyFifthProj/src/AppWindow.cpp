
#include <cstdio>
#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "AppWindow.h"

using InitStatus = AppWindow::InitializationStatus;

AppWindow::InitializationStatus AppWindow::Initialize(int width_hint, int height_hint, const char* title, GLFWmonitor* monitor) {
	if (_Initialized) {
		return InitStatus::ERROR_ALREADY_INIT;
	}

	auto status = InitStatus::INIT_OK;

	const auto GlfwErrorCallback = [](int error, const char* description) {
		fprintf(stderr, "Glfw Error #%d: %s\n", error, description);
	};

	glfwSetErrorCallback(GlfwErrorCallback);

	if (!glfwInit()) {
		status = InitStatus::ERROR_GLFW_INIT_FAILED;
		glfwTerminate();
		return status;
	}

	// Decide GL+GLSL versions
#ifdef __APPLE__
	// GL 3.2 + GLSL 150
	const char* _GLSLVersion = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* GLSLVersion = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
	
	GLFWwindow* window = glfwCreateWindow(width_hint, height_hint, title, monitor, nullptr);
	if (!window) {
		status = InitStatus::ERROR_WINDOW_CREATION_FAILED;
		glfwTerminate();
		return status;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Initialize OpenGL loader (after creating a context)
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
	bool err = gladLoadGL(glfwGetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
	bool err = false;
	glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
	bool err = false;
	glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
	if (err) {
		status = InitStatus::ERROR_OPENGL_LOADER_INIT_FAILED;
		glfwDestroyWindow(window);
		glfwTerminate();
		return status;
	}

	IMGUI_CHECKVERSION();
	ImGuiContext* context = ImGui::CreateContext();
	if (!context) {
		status = InitStatus::ERROR_IMGUI_CONTEXT_CREATION_FAILED;
		glfwDestroyWindow(window);
		glfwTerminate();
		return status;
	}

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr; //Disable configuraiton saving
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //Enable keyboard controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
		status = InitStatus::ERROR_IMGUI_GLFW_BACKEND_INIT_FAILED;
		glfwDestroyWindow(window);
		glfwTerminate();
		return status;
	}
	if (!ImGui_ImplOpenGL3_Init(GLSLVersion)) {
		status = InitStatus::ERROR_IMGUI_OPENGL_BACKEND_INIT_FAILED;
		ImGui_ImplGlfw_Shutdown();
		glfwTerminate();
		return status;
	}

	this->imgui = context;
	this->window = window;
	this->_Initialized = true;

	this->InitializationCallback();

	return InitStatus::INIT_OK;

shutdown_backend:
	ImGui_ImplGlfw_Shutdown();

destroy_window:
	glfwDestroyWindow(window);

terminate_glfw:
	glfwTerminate();
	return status;
}

AppWindow::~AppWindow() {
	assert((!_Initialized && !window && !imgui) || (_Initialized && window && imgui)); 
	if (_Initialized) {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext(imgui);

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

void AppWindow::UpdateAndDraw() {
	assert(_Initialized);

	glfwPollEvents(); //Update state

	/*
	{ //Clear main (Glfw) window
		int display_w, display_h;
		glfwGetFramebufferSize(this->window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}*/

	//Start ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//Call user ImGui callback
	this->ImGuiDrawCallback();

	//Finish ImGui frame and create draw data
	ImGui::Render();

	//Draw ImGui on top of whatever user drew with OpenGL
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	
	// if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
	// 	GLFWwindow* backup_current_context = glfwGetCurrentContext();
	// 	ImGui::UpdatePlatformWindows();
	// 	ImGui::RenderPlatformWindowsDefault();
	// 	glfwMakeContextCurrent(backup_current_context);
	// }

	glfwSwapBuffers(this->window);
}

void AppWindow::UpdateAndDrawUntilClosing() {
	assert(_Initialized);

	while (!glfwWindowShouldClose(this->window))
		UpdateAndDraw();
}

void AppWindow::InitializationCallback() { /* default callback : do nothing */ }