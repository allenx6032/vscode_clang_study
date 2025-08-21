#include "AppWindow.h"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <cstdio>
#include <cstdlib>
#include <memory>

GLuint vertexArrayID;
GLuint vertexbuffer;

#define WEIGHT 0.75f

static const GLfloat s_vertexBufferData[] = {
	0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-WEIGHT, WEIGHT, 0.0f,
	
	0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	-WEIGHT, WEIGHT, 0.0f,

	0.0f, 0.0f, 0.0f,
	WEIGHT, WEIGHT, 0.0f,
	0.0f, 1.0f, 0.0f,

	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	WEIGHT, WEIGHT, 0.0f,


	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	WEIGHT, -WEIGHT, 0.0f,

	0.0f, 0.0f, 0.0f,
	WEIGHT, -WEIGHT, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, 0.0f, 0.0f,
	-WEIGHT, -WEIGHT, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-WEIGHT, -WEIGHT, 0.0f,
};

class SkeletonAppWindow : public AppWindow {

private:
	virtual void InitializationCallback() override {
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s_vertexBufferData), s_vertexBufferData, GL_STATIC_DRAW);
	}

	virtual void ImGuiDrawCallback() override {
		int posX, posY;
		int width, height;
		glfwGetFramebufferSize(this->GetGLFWWindow(), &width, &height);
		glfwGetWindowPos(this->GetGLFWWindow(), &posX, &posY);

		glDeleteTextures(1, &gl_draw_texture);

		glGenTextures(1, &gl_draw_texture);
		glBindTexture(GL_TEXTURE_2D, gl_draw_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		static GLuint zbuffer_texture;
		glGenTextures(1, &zbuffer_texture);
		glBindTexture(GL_TEXTURE_2D, zbuffer_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		GLuint fb_id;
		glGenFramebuffers(1, &fb_id);
		glBindFramebuffer(GL_FRAMEBUFFER, fb_id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gl_draw_texture, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, zbuffer_texture, 0);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		
		glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
		

		/* Custom OpenGL draws start here! */
			// 1st attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 24); // Starting from vertex 0; 24 verticies
			glDisableVertexAttribArray(0);
		/* End of custom OpenGL draws*/

		glDeleteFramebuffers(1, &fb_id);
		glDeleteTextures(1, &zbuffer_texture);

		ImGui::SetNextWindowPos(ImVec2(posX, posY));
		ImGui::SetNextWindowSize(ImVec2(width, height));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::Image((void*)(uintptr_t)gl_draw_texture, ImGui::GetWindowContentRegionMax());
		ImGui::End();
		ImGui::PopStyleVar(2);

		ImGui::Begin("Window 1", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Window size: (%d,%d)", width, height);
		ImGui::End();

		ImGui::Begin("window 2");
		ImGui::Checkbox("Show Demo Window", &demoWindow);
		ImGui::Text("world!");
		ImGui::End();

		if (demoWindow)
			ImGui::ShowDemoWindow(&demoWindow);
	}

	virtual void OGLDrawCallback() {

	}

	bool demoWindow = false;
	GLuint vertexArrayID = 0;
	GLuint vertexbuffer = 0;

	GLuint gl_draw_texture;
};


int main(int argc, char** argv) {
	fprintf(stderr, "ImGui version: %s\n", ImGui::GetVersion());
	SkeletonAppWindow window;
	if (INITIALIZATION_FAILED(window.Initialize(800, 600, "ImGui Skeleton"))) {
		fprintf(stderr, "Failed to initialize application window.\n");
		return EXIT_FAILURE;
	}

	window.UpdateAndDrawUntilClosing();

	return EXIT_SUCCESS;	
}