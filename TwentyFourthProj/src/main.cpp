// GLEW
#include <GLew/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "GraphicsHandler.h"

// The drawing grid within the window (Not the window size)
#define GRID_RESX  800
#define GRID_RESY  600

void key_callback(GLFWwindow* window,
                  int key,
                  int scancode,
                  int action,
                  int mode) {
  

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  
  if (window == NULL)
  {
      std::cout << "Failed to create GLFW window\n";
      glfwTerminate();
      return -1;
  }
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
      std::cout << "Failed to initialize GLEW\n";
      return -1;
  }

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
    
  glfwSetKeyCallback(window, key_callback);
  
  GraphicsHandler graphics;
  graphics.loadShaders("./shaders/shader.vert", "./shaders/shader.frag", "basic");
  graphics.init(GRID_RESX, GRID_RESY, "basic");
  graphics.loadTexture("ship", "./Textures/image.png");
  
  float rotation = 0.0f;
  GLfloat deltaTime = 0.0f;
  GLfloat lastTime = 0.0f;
  while(!glfwWindowShouldClose(window)) {
    
    GLfloat current_time = glfwGetTime();
    deltaTime = current_time - lastTime;
    lastTime = current_time;
    
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    graphics.useShader("basic");
    
    // Updates
    rotation+=deltaTime*60;
    
    // Draw
    graphics.drawObject(glm::vec2(GRID_RESX*0.5, GRID_RESY*0.5f), glm::vec2(100.0f, 100.0f), rotation, glm::vec3(1.0f, 0.5f, 0.5f), "ship");

    glfwSwapBuffers(window);
  } 
  glfwTerminate();
   return 0;

}

