#pragma once

#include "levelEditor.hpp"
#include "gameClient.hpp"
#include "rtype/gameEngine.hpp"
#include <sfml/SFML_Graphics.hpp>
#include <sfml/SFML_Window.hpp>
#include <sfml/SFML_System.hpp>
#include <sfml/SFML_Audio.hpp>
#include <sfml/SFML_Network.hpp>
#include "gameClient.hpp"
#include <iostream>

class MenuM {
public:
    public:
    MenuM() = delete;
    MenuM(gameEngine::RenderWindow &window);
    ~MenuM();
    void run_menu();
    int pos;
    bool pressed, theselect;

    gameEngine::RenderWindow &window;
    gameEngine::RectangleShape * winclose;
    gameEngine::Font * font;
    gameEngine::Texture * image;
    gameEngine::Sprite * bg;

    gameEngine::Vector2i pos_mouse;
    gameEngine::Vector2f mouse_coord;

    std::vector<const char *> options;
    std::vector<gameEngine::Vector2f> coords;
    std::vector<gameEngine::Text> texts;
    std::vector<std::size_t> sizes;

protected:
      void set_values();
      void loop_events();
      void draw_all();

};


void startGame();