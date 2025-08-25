#ifndef TINYENGINE
#define TINYENGINE

/*
* TinyEngine
* by Nicholas McDonald
* https://github.com/weigert/TinyEngine
*/

#define TINYENGINE_VERSION "1.7"

#include <iostream>
#include <functional>
#include <initializer_list>
#include <string>
#include <csignal>
#include <deque>
#include <filesystem>
#include <sstream>

#include <GLew/glew.h>                                //Rendering Dependencies
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

// Include Utility Headers
#ifndef TINYENGINE_UTILITIES
#define TINYENGINE_UTILITIES

#include <TinyEngine/Buffer.hpp>
#include <TinyEngine/Instance.hpp>
#include <TinyEngine/Model.hpp>
#include <TinyEngine/Shader.hpp>
#include <TinyEngine/Target.hpp>
#include <TinyEngine/Texture.hpp>

#endif

using slist = std::initializer_list<std::string>;
using Handle = std::function<void()>;

// TinyEngine Namespace / Entrypoint
#ifndef TINYENGINE_NAMESPACE
#define TINYENGINE_NAMESPACE

#include <TinyEngine/Audio.hpp>
#include <TinyEngine/View.hpp>
#include <TinyEngine/Event.hpp>

#include <TinyEngine/timer.hpp>

namespace Tiny{

static View view;           //Window and Interface  (Requires Initialization)
static Event event;         //Event Handler
static Audio audio;         //Audio Processor       (Requires Initialization)

void sighandler(int signal){
  event.quit = true;
}

bool init(){

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
    printf( "SDL could not initialize! Error: %s\n", SDL_GetError() );
    return false;
  }

  #ifndef TINYENGINE_COMPATIBILITY
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  #endif

  if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ){
    printf( "SDL_Image could not initialize! Error: %s\n", IMG_GetError() );
    return false;
  }

  if( TTF_Init() == -1 ){ //for some reason this is -1
    printf( "SDL_ttf could not initialize! Error: %s\n", TTF_GetError() );
    return false;
  }

  signal(SIGINT, &sighandler);

  if(!view.windowed && !view.init("TinyEngine OpenGL Context", 0, 0)){ //Open a Dummy Window
    std::cout<<"Failed to launch OpenGL Context"<<std::endl;
    return false;
  }

  return true;

}

bool window(std::string windowName, int width, int height){ //Open a window

  view.windowed = true;

  if(!Tiny::init())
    return false;

  if(!view.init(windowName, width, height)){ //Start the View Class
    std::cout<<"Failed to launch visual interface."<<std::endl;
    return false;
  }

  if(!audio.init()){ //Start the Audio Interface
    std::cout<<"Failed to launch audio interface."<<std::endl;
		return false;
	}

  return true;
}

void quit(){
  if(Tiny::view.enabled)  view.quit();
  if(Tiny::audio.enabled) audio.quit();
  TTF_Quit();
  SDL_Quit();
}

bool benchmark = false;
int average = 0;

template<typename F, typename... Args>
void loop(F function, Args&&... args){

  if(!benchmark)
  while(!event.quit){

    if(Tiny::view.enabled){
      event.input();        //Get Input
      event.handle(view);   //Call the event-handling system
    }

    if(Tiny::audio.enabled) audio.process();      //Audio Processor

    function(args...);      //User-defined Game Loop

    if(Tiny::view.enabled){
      view.render();         //Render View
    }

  }

  else while(!event.quit){

    if(Tiny::view.enabled){
      std::cout<<"Event Input ";
      timer::benchmark<std::chrono::milliseconds>([&](){
        event.input();        //Get Input
      });
      std::cout<<"Event Handling ";
      timer::benchmark<std::chrono::milliseconds>([&](){
      event.handle(view);   //Call the event-handling system
      });
    }

    if(Tiny::audio.enabled){
      std::cout<<"Audio Processing ";
      timer::benchmark<std::chrono::milliseconds>([&](){
        audio.process();      //Audio Processor
      });
    }

    std::cout<<"Loop Function ";
    timer::benchmark<std::chrono::microseconds>([&](){
      function(args...);      //User-defined Game Loop
    });

    if(Tiny::view.enabled){
      std::cout<<"Render Pipeline ";
      average = 0.99*average + 0.01*timer::benchmark<std::chrono::microseconds>([&](){
        view.render();         //Render View
        glFinish();
      });
    }

  }

}

}

#endif
#endif
