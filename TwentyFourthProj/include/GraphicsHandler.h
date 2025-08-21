#ifndef GRAPHICSHANDLER
#define GRAPHICSHANDLER

// GLEW
#include <glew/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <map>

#include "./LoadTexture.h"

class GraphicsHandler {
  public:
    GraphicsHandler();
    void init(int width, int height, std::string name);
    
    // Call once per loop (At start), or anytime you switch shaders
    void useShader(std::string name);
    GLuint getShader(std::string name);

    // Loads texture ready to use, with reference name
    void loadTexture(std::string name, const char * filename);
    
    // Draws object at position x/y, with specified size, rotated 0 degrees, full colour
    void drawObject(glm::vec2 position, glm::vec2 size, std::string name);
    // Draws object at position x/y, with specified size, rotated specified degrees, full colour
    void drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, std::string name);
    // Draws object at position x/y, with specified size, rotated specified degrees, With only colours specified drawn
    void drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 colour, std::string name);
    

    void loadShaders(const char * vertex_file_path,const char * fragment_file_path, std::string name);
  protected:
    void draw();
    
    void transformModel(glm::vec3 position, glm::vec2 size, GLfloat rotation, glm::vec3 colour);

    std::string crntShader;
    GLuint quadVAO;
    
    glm::vec2 grid;
    
    std::map<std::string, GLuint> textures;
    std::map<std::string, GLuint> shaders;
    // Interesting way to give names to array
    // std::map<std::string, Texture2D> textures
    // std::string name = "Weapon3"
    // return textures[name]
};

#endif
