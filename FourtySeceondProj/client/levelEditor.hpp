#pragma once

#include <sfml/SFML_Graphics.hpp>
#include <sfml/SFML_Window.hpp>
#include <sfml/SFML_System.hpp>
#include <sfml/SFML_Audio.hpp>
#include <sfml/SFML_Network.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "rtype/gameEngine.hpp"


#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define CELL_WIDTG 82
#define CELL_HEIGHT 82
#define INITIAL_WIDTH WINDOW_WIDTH / CELL_WIDTG
#define INITIAL_HEIGHT WINDOW_HEIGHT / CELL_HEIGHT
#define EMPTY 0
#define WALL 1
#include <vector>

class MainMenu {
public:
    MainMenu() = delete;
    MainMenu(gameEngine::RenderWindow& window);

    void update();
    void cinematic();
    int getState();
    void setState(int state);
    void draw();

private:
    gameEngine::RenderWindow& window;
    gameEngine::RectangleShape _back;
    gameEngine::Font _font;
    gameEngine::Text _text;
    gameEngine::Text _text2;
    gameEngine::Text _text3;
    gameEngine::Texture _texLetter;
    gameEngine::Sprite _spriteLetter[6];
    gameEngine::IntRect _rectLetter[6];
    sf::Clock _clock;
    int _state;
    float _blinkInterval = 0.50f;
    bool _isVisible = true;
};

class Menu {
public:
    Menu() = delete;
    Menu(gameEngine::RenderWindow& window);
    int getSelectedIndex();
    void update(gameEngine::View view1);
    void draw();
    int selectedIndex;

private:
    gameEngine::RenderWindow& window;
    gameEngine::Texture _texture;
    gameEngine::Sprite _back;
    gameEngine::Font font;
    gameEngine::RectangleShape _enemiesShape[4];
    std::vector<gameEngine::Sprite> _enemies;
    std::vector<gameEngine::Texture> _enemiesTex;
    std::vector<gameEngine::Text> menuItems;
    gameEngine::Text selectedItem;
    int clickCooldown;
    sf::Clock clickTimer;
    bool isClicked;
};

class Button {
public:
    Button() = default;
    Button(gameEngine::Vector2f position, gameEngine::Vector2f size);
    void update(gameEngine::RenderWindow& window, gameEngine::View view1);
    void draw(gameEngine::RenderWindow& window);
    bool isOpen();
    gameEngine::Sprite getShape();

    bool isClicked;

private:
    // gameEngine::RectangleShape buttonShape;
    gameEngine::Texture buttonTexture;
    gameEngine::Texture buttonTextureActive;
    gameEngine::Sprite buttonShape;

    bool wasButtonPressed;
    sf::Clock clickTimer;
    int clickCooldown;
    bool open;
};

class LevelEditor {
public:
    LevelEditor() = delete;

    LevelEditor(gameEngine::RenderWindow& window);

    ~LevelEditor() = default;

    void createParalax();
    void saveLevel();
    void loadLevel();
    void eventHandle();
    void printGrid();
    void run();

private:
    Button _button;
    Menu _menu = Menu(_window);
    MainMenu _mainMenu = MainMenu(_window);
    bool _isFocused = true;
    gameEngine::RenderWindow &_window;
    std::vector<gameEngine::Sprite> _paralax;
    gameEngine::Texture _background;
    std::vector<std::vector<int>> _levelGrid;
    gameEngine::View view1;
    gameEngine::Event event;
    // int _save[2] = {0, 0};
    // int _load[2] = {0, 0};
    bool _isSaving = false;
    bool _isloading = false;
    std::string _fileName;
    std::string _fileToLoad;
    gameEngine::Font font;
    int _state = 0;

    std::vector<gameEngine::Sprite> _enemiesLevel;
    std::vector<gameEngine::Texture> _enemiesTexLevel;
    gameEngine::RectangleShape _enemiesShape[3];
};

