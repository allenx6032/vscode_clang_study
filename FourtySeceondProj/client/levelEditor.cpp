/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Level Editor
*/

#include "levelEditor.hpp"

MainMenu::MainMenu(gameEngine::RenderWindow& window) : window(window)
{
    _back.setSize(gameEngine::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    _back.setFillColor(gameEngine::Color::Black);
    _font.loadFromFile("r-type.ttf");
    _texLetter.loadFromFile("R-type_letter.png");
    _rectLetter[0] = gameEngine::IntRect(0, 0, 240, 300);
    _rectLetter[1] = gameEngine::IntRect(240, 0, 180, 300);
    _rectLetter[2] = gameEngine::IntRect(420, 0, 240, 300);
    _rectLetter[3] = gameEngine::IntRect(660, 0, 260, 300);
    _rectLetter[4] = gameEngine::IntRect(920, 0, 260, 300);
    _rectLetter[5] = gameEngine::IntRect(1180, 0, 240, 300);
    _state = 0;

    _text.setFont(_font);
    _text2.setFont(_font);
    _text3.setFont(_font);
    _text.setCharacterSize(30);
    _text2.setCharacterSize(30);
    _text3.setCharacterSize(30);
    _text.setFillColor(gameEngine::Color::Cyan);
    _text2.setFillColor(gameEngine::Color::Magenta);
    _text3.setFillColor(gameEngine::Color::Cyan);
    _text.setString("Blast off and strike\nthe evil Bydo Empire!");
    _text2.setString("Press Enter to continue");
    _text3.setString("2023 by funky team.");
    _text.setPosition(1000, 100);
    _text2.setPosition(1000, 200);
    _text3.setPosition(1200, 1000);

}

void MainMenu::setState(int state)
{
    _state = state;
}

int MainMenu::getState()
{
    return _state;
}

void MainMenu::cinematic()
{
    if (_state == 0) {
        sf::Time time = _clock.getElapsedTime();
        int pos = WINDOW_WIDTH - time.asMilliseconds();

        for (int i = 0; i < 6; i++) {
            _spriteLetter[i].setTexture(_texLetter);
            _spriteLetter[i].setTextureRect(_rectLetter[i]);

            if (pos > 0) {
                _spriteLetter[i].setPosition(pos, 100);
            } else {
                // sleep(1);
                _clock.restart();
                _state = 1;
            }

            window.draw(_spriteLetter[i]);
        }
    }
    else if (_state == 1) {
        sf::Time time = _clock.getElapsedTime();
        int pos = WINDOW_WIDTH - time.asMilliseconds();

        for (int i = 0; i < 6; i++) {
            _spriteLetter[i].setTexture(_texLetter);
            _spriteLetter[i].setTextureRect(_rectLetter[i]);

            if (pos <= 0) {
                _spriteLetter[i].setPosition(100 + i * 240, 100);
                _clock.restart();
                _state = 2;
            } else {
                int destinationX = 100 + i * 240;
                float progress = 1.0f - static_cast<float>(pos) / (WINDOW_WIDTH);
                int currentX = static_cast<int>(destinationX * progress);

                _spriteLetter[i].setPosition(currentX, 100);
            }
            window.draw(_spriteLetter[i]);
        }
    }
    else if (_state == 2) {
        sf::Time time = _clock.getElapsedTime();
        int pos = WINDOW_WIDTH - time.asMilliseconds();

        for (int i = 0; i < 6; i++) {
            _spriteLetter[i].setTexture(_texLetter);
            _spriteLetter[i].setTextureRect(_rectLetter[i]);

            if (pos <= 0) {
                _spriteLetter[i].setPosition(100 + i * 240, 550);
                // _clock.restart();
                _state = 3;
            } else {
                int destinationX = 100 + i * 240;
                int destinationY = 450;
                float progress = 1.0f - static_cast<float>(pos) / (WINDOW_WIDTH);
                // int currentX = static_cast<int>(destinationX * progress);
                int currentY = static_cast<int>(destinationY * progress + 100);

                _spriteLetter[i].setPosition(destinationX, currentY);
            }
            window.draw(_spriteLetter[i]);
        }
    }
}

void MainMenu::update()
{
    sf::Time elapsed = _clock.getElapsedTime();

    if (elapsed.asSeconds() >= _blinkInterval) {
        _isVisible = !_isVisible;
        _clock.restart();
    }
    if (_isVisible) {
        window.draw(_text2);
    }

    for (int i = 0; i < 6; i++) {
        _spriteLetter[i].setTexture(_texLetter);
        _spriteLetter[i].setTextureRect(_rectLetter[i]);
        _spriteLetter[i].setPosition(100 + i * 240, 550);
        window.draw(_spriteLetter[i]);
    }
    window.draw(_text);
    window.draw(_text3);
}

Menu::Menu(gameEngine::RenderWindow& window) : window(window), selectedIndex(0) {
    _texture.loadFromFile("Client/sprites/MainPanel02.png");
    _back.setTexture(_texture);
    _back.setScale(3.15, 2.7);
    // _back.setSize(gameEngine::Vector2f(950, WINDOW_HEIGHT));
    // _back.setFillColor(gameEngine::Color::White);
    _enemies.resize(4);
    _enemiesTex.resize(4);
    _enemiesTex[0].loadFromFile("Client/sprites/r-typesheet5.png");
    _enemiesTex[1].loadFromFile("Client/sprites/r-typesheet7.png");
    _enemiesTex[2].loadFromFile("Client/sprites/r-typesheet8.png");
    _enemiesTex[3].loadFromFile("Client/sprites/R-Type 2 Sprites.png");
    for (int i = 0; i < 4; i++) {
        _enemies[i].setTexture(_enemiesTex[i]);
        _enemies[i].setTextureRect(gameEngine::IntRect(0, 0, 32, 32));
        _enemies[i].setScale(4, 4);
    }
    clickCooldown = 700;
}

void Menu::update(gameEngine::View view1) {
    
    gameEngine::Vector2i mousePos = gameEngine::Mouse::getPosition(window);
    gameEngine::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);
    gameEngine::Vector2f mousePosF(static_cast<float>(worldMousePos.x), static_cast<float>(worldMousePos.y));

    _back.setPosition(view1.getCenter().x + view1.getSize().x / 2 - 950, 0);
    
    for (int i = 0; i < 4; i++) {
        _enemies[i].setPosition(view1.getCenter().x + view1.getSize().x / 2 - 900, 100 + i * 200);
        _enemiesShape[i] = gameEngine::RectangleShape(gameEngine::Vector2f(100, 100));
        _enemiesShape[i].setPosition(view1.getCenter().x + view1.getSize().x / 2 - 900, 100 + i * 200);
    }
    for (int i = 0; i < 4; i++) {
        if (_enemiesShape[i].getGlobalBounds().contains(mousePosF) && gameEngine::Mouse::isButtonPressed(gameEngine::Mouse::Left)) {
           selectedIndex = i + 1;
        }
    }
    
    _back.setPosition(view1.getCenter().x + view1.getSize().x / 2 - 950, 0);
}

int Menu::getSelectedIndex() {
    return selectedIndex;
}

void Menu::draw() {
    window.draw(_back);
    for (int i = 0; i < 4; i++) {
        window.draw(_enemies[i]);
    }
}

Button::Button(gameEngine::Vector2f position, gameEngine::Vector2f size) {
    buttonShape.setPosition(position);
    buttonTexture.loadFromFile("Client/sprites/Backward_BTN.png");
    buttonTextureActive.loadFromFile("Client/sprites/Backward_BTN_Active.png");
    buttonShape.setTexture(buttonTexture);
    buttonShape.setScale(0.25, 0.5);

    open = false;
    isClicked = false;
    wasButtonPressed = false;
    clickCooldown = 500;
}

void Button::update(gameEngine::RenderWindow& window, gameEngine::View view1) {
    gameEngine::Vector2i mousePos = gameEngine::Mouse::getPosition(window);
    gameEngine::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);
    gameEngine::Vector2f mousePosF(static_cast<float>(worldMousePos.x), static_cast<float>(worldMousePos.y));

    bool isButtonPressed = gameEngine::Mouse::isButtonPressed(gameEngine::Mouse::Left);

    if (!isClicked) {
        if (isButtonPressed && buttonShape.getGlobalBounds().contains(mousePosF) && !wasButtonPressed) {
            if (clickTimer.getElapsedTime().asMilliseconds() >= clickCooldown) {
                isClicked = true;
                clickTimer.restart();
            }
        }
    } else {
        std::cout << "Button clicked" << std::endl;
        open = !open;
        isClicked = false;
    }

    if (!isButtonPressed) {
        wasButtonPressed = false;
    }

    if (buttonShape.getGlobalBounds().contains(mousePosF)) {
        buttonShape.setTexture(buttonTextureActive);
    } else {
        buttonShape.setTexture(buttonTexture);
    }
    if (open) {
        buttonShape.setPosition(view1.getCenter().x + view1.getSize().x / 2 - 1000, view1.getCenter().y - view1.getSize().y / 2 + 100);
    }
    else
        buttonShape.setPosition(view1.getCenter().x + view1.getSize().x / 2 - 50, view1.getCenter().y - view1.getSize().y / 2 + 100);
}

void Button::draw(gameEngine::RenderWindow& window) {
    window.draw(buttonShape);
}

bool Button::isOpen()
{
    return open;
}

 gameEngine::Sprite Button::getShape() {
    return buttonShape;
}

LevelEditor::LevelEditor(gameEngine::RenderWindow& window) : _window(window), _menu(window), _mainMenu(window)  {
    _window.create(gameEngine::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Level Editor");
    _background.loadFromFile("Client/sprites/background1.png");

    _levelGrid.resize(INITIAL_WIDTH, std::vector<int>(INITIAL_HEIGHT, 0));
    std::cout << "_levelGrid size : " << _levelGrid.size() << std::endl;

    view1.setCenter(gameEngine::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
    view1.setSize(gameEngine::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    _window.setView(view1);

    gameEngine::Sprite background(_background);
    _paralax.push_back(background);

    _button = Button(gameEngine::Vector2f(1820, 100), gameEngine::Vector2f(50, 100));

    font.loadFromFile("arial.ttf");
    _fileName = "";

    _enemiesLevel.resize(4);
    _enemiesTexLevel.resize(4);
    _enemiesTexLevel[0].loadFromFile("Client/sprites/r-typesheet5.png");
    _enemiesTexLevel[1].loadFromFile("Client/sprites/r-typesheet7.png");
    _enemiesTexLevel[2].loadFromFile("Client/sprites/r-typesheet8.png");
    _enemiesTexLevel[3].loadFromFile("Client/sprites/R-Type 2 Sprites.png");
    for (int i = 0; i < 4; i++) {
        _enemiesLevel[i].setTexture(_enemiesTexLevel[1]);
        _enemiesLevel[i].setTextureRect(gameEngine::IntRect(0, 0, 32, 32));
    }


};

void LevelEditor::createParalax() {
    if (_paralax.back().getPosition().x + _paralax.back().getGlobalBounds().width < _window.getView().getCenter().x + _window.getView().getSize().x / 2) {
        std::cout << "creating new paralax" << std::endl;
        gameEngine::Sprite background(_background);
        background.setPosition(_paralax.back().getPosition().x + _paralax.back().getGlobalBounds().width, 0);
        _paralax.push_back(background);
        for (int i = 0; i <= 23 ; i++) {
            _levelGrid.push_back(std::vector<int>(_levelGrid[0].size(), 0));
        }
        std::cout << "_levelGrid size : " << _levelGrid.size() << std::endl;
    }
}

void LevelEditor::saveLevel() {
    gameEngine::Text fileNameText;
    fileNameText.setFont(font);
    fileNameText.setString("Enter file name: " + _fileName);
    fileNameText.setCharacterSize(20);
    fileNameText.setPosition(_window.getView().getCenter().x - _window.getView().getSize().x / 2 + 10, _window.getView().getCenter().y - _window.getView().getSize().y / 2 + 10);
    fileNameText.setCharacterSize(50);
    _window.draw(fileNameText);
}

void LevelEditor::loadLevel() {
    std::string folder_path = "levels";
    gameEngine::Vector2i mousePos = gameEngine::Mouse::getPosition(_window);
    gameEngine::Vector2f worldMousePos = _window.mapPixelToCoords(mousePos);
    gameEngine::Vector2f mousePosF(static_cast<float>(worldMousePos.x), static_cast<float>(worldMousePos.y));

    try {
        int i = 0;
        for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
                gameEngine::Text fileNameText;
                fileNameText.setFont(font);
                fileNameText.setString(entry.path().filename().string());
                fileNameText.setCharacterSize(20);
                fileNameText.setPosition(_window.getView().getCenter().x - _window.getView().getSize().x / 2 + 10, _window.getView().getCenter().y - _window.getView().getSize().y / 2 + 10 + i * 50);
                fileNameText.setCharacterSize(50);
                if (fileNameText.getGlobalBounds().contains(mousePosF))
                    fileNameText.setFillColor(gameEngine::Color::Red);
                _window.draw(fileNameText);
                if (gameEngine::Mouse::isButtonPressed(gameEngine::Mouse::Left) && fileNameText.getGlobalBounds().contains(mousePosF)) {
                    _fileToLoad = entry.path().filename().string();
                    _isloading = false;
                    _levelGrid.clear();
                    std::ifstream file(folder_path + "/" + _fileToLoad);
                    std::string line;
                    while (std::getline(file, line)) {
                        std::vector<int> row;
                        for (int i = 0; i < line.size(); i++) {
                            row.push_back(line[i] - '0');
                        }
                        _levelGrid.push_back(row);
                    }
                    file.close();
                }
            i++;
        }
    } catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Error accessing the directory: " << ex.what() << std::endl;
    }
}

void LevelEditor::eventHandle() {
    while (_window.pollEvent(event)) {
        if (event.type == gameEngine::Event::Closed)
            _window.close();
        if (event.type == gameEngine::Event::MouseButtonPressed) {
            if (event.mouseButton.button == gameEngine::Mouse::Left && !_button.getShape().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !_isSaving && !_isloading) {
                if (!_button.isOpen()) {
                    gameEngine::Vector2i windowMousePos = gameEngine::Mouse::getPosition(_window);
                    gameEngine::Vector2f worldMousePos = _window.mapPixelToCoords(windowMousePos);
                    int x = worldMousePos.x / CELL_WIDTG;
                    int y = worldMousePos.y / CELL_HEIGHT;
                    if (_levelGrid[x][y] == EMPTY) {
                        _levelGrid[x][y] = _menu.getSelectedIndex();
                    }
                    else if (_levelGrid[x][y] != EMPTY)
                        _levelGrid[x][y] = EMPTY;
                }
            }
        }
        if (event.type == gameEngine::Event::KeyPressed) {
            if (event.key.code == gameEngine::Keyboard::Enter && _state == 0) {
                _state = 1;
            }
            if (event.key.code == gameEngine::Keyboard::Left) {
                if (view1.getCenter().x - view1.getSize().x / 2 > 0) {
                    std::cout << "left" << std::endl;
                    view1.move(-50, 0);
                    _window.setView(view1);
                }
            }
            if (event.key.code == gameEngine::Keyboard::Escape) {
                _state = 10;
            }
            if (event.key.code == gameEngine::Keyboard::Right) {
                std::cout << "right" << std::endl;
                view1.move(50, 0);
                _window.setView(view1);
            }
            if (event.key.code == gameEngine::Keyboard::R) {
                view1.setCenter(gameEngine::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
                _window.setView(view1);
            }
            if (event.key.code == gameEngine::Keyboard::S && !_isSaving && !_isloading) {
                _isSaving = true;
                _fileName = "";
            }
            if (event.key.code == gameEngine::Keyboard::L && !_isSaving && !_isloading) {
                _isloading = true;
                _fileToLoad = "";
            }
            if (event.key.code == gameEngine::Keyboard::Enter && _isSaving) {
                std::ofstream file("levels/" + _fileName + ".txt");
                for (int x = 0; x < _levelGrid.size(); x++) {
                    for (int y = 0; y < _levelGrid[0].size(); y++) {
                        if (x == _levelGrid.size() - 1 && y == _levelGrid[0].size() - 5)
                            file << 5;
                        else
                            file << _levelGrid[x][y];
                    }
                    file << std::endl;
                }
                file.close();
                _fileName = "";
                _isSaving = false;
            }
            if (event.key.code == gameEngine::Keyboard::Escape && (_isSaving || _isloading)) {
                _fileName = "";
                _fileToLoad = "";
                _isloading = false;
                _isSaving = false;
            }
        }

        if (event.type == gameEngine::Event::TextEntered) {
            if (event.text.unicode == 8 && _fileName.size() > 0) {
                _fileName.pop_back();
            } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                _fileName += static_cast<char>(event.text.unicode);
            }
        }

        if (event.type == gameEngine::Event::MouseWheelScrolled && !_isSaving) {
            if (view1.getCenter().x - view1.getSize().x / 2 > 0) {
                if (event.mouseWheelScroll.delta > 0) {
                    view1.move(-50, 0);
                    _window.setView(view1);
                }
            }
            if (event.mouseWheelScroll.delta < 0) {
                view1.move(50, 0);
                _window.setView(view1);
            }
        }
    }
}

void LevelEditor::printGrid() {
    for (int x = 0; x < _levelGrid.size(); x++) {
        for (int y = 0; y < _levelGrid[0].size(); y++) {
            gameEngine::Sprite cellSprite;
            cellSprite.setTextureRect(gameEngine::IntRect(0, 0, CELL_WIDTG - 2, CELL_HEIGHT - 2));
            // gameEngine::RectangleShape cell(gameEngine::Vector2f(CELL_WIDTG - 2, CELL_HEIGHT - 2));
            cellSprite.setPosition(x * CELL_WIDTG, y * CELL_HEIGHT);
            // cell.setPosition(x * CELL_WIDTG, y * CELL_HEIGHT);
            if (_levelGrid[x][y] == EMPTY) {
                continue;
            } else if (_levelGrid[x][y] == 1) {
                cellSprite.setTextureRect(gameEngine::IntRect(0, 0, 32, 32));
                cellSprite.setScale(4, 4);
                cellSprite.setTexture(_enemiesTexLevel[0]);
            } else if (_levelGrid[x][y] == 2) {
                cellSprite.setTextureRect(gameEngine::IntRect(0, 0, 32, 32));
                cellSprite.setScale(3, 3);
                cellSprite.setTexture(_enemiesTexLevel[1]);
            } else if (_levelGrid[x][y] == 3) {
                cellSprite.setTextureRect(gameEngine::IntRect(0, 0, 32, 32));
                cellSprite.setScale(3, 3);
                cellSprite.setTexture(_enemiesTexLevel[2]);
            }
            else if (_levelGrid[x][y] == 4) {
                cellSprite.setTextureRect(gameEngine::IntRect(0, 0, 32, 32));
                cellSprite.setScale(2.7, 2.7);
                cellSprite.setTexture(_enemiesTexLevel[3]);
            }
            _window.draw(cellSprite);
        }
    }
}

void LevelEditor::run() {

    gameEngine::Texture spriteSheetTexture;
    spriteSheetTexture.loadFromFile("Client/sprites/r-typewall.png");

    gameEngine::Sprite wall[8];
    gameEngine::IntRect spriteRectangles[8];

    spriteRectangles[0] = gameEngine::IntRect(7, 0, 143, 80);
    spriteRectangles[1] = gameEngine::IntRect(1300, 0, 50, 80);
    spriteRectangles[2] = gameEngine::IntRect(887, 0, 272, 80);

    wall[0].setTexture(spriteSheetTexture);
    wall[0].setTextureRect(spriteRectangles[0]);
    wall[0].setScale(4, 4);

    wall[1].setTexture(spriteSheetTexture);
    wall[1].setTextureRect(spriteRectangles[1]);
    wall[1].setScale(4, 4);
    wall[1].setPosition(1000, 0);

    wall[2].setTexture(spriteSheetTexture);
    wall[2].setTextureRect(spriteRectangles[2]);
    wall[2].setScale(4, 4);
    wall[2].setPosition(0, 500);

    while (_window.isOpen() && _state != 10) {
        _window.clear();

        // if (_state == 0) {
        //     if (_mainMenu.getState() != 3)
        //         _mainMenu.cinematic();
        //     else {
        //         _mainMenu.update();
        //     }
        //     eventHandle();
        //     _window.display();
        //     continue;
        // }

        for (auto &paralax : _paralax) {
            _window.draw(paralax);
        }

        _button.update(_window, view1);
        _menu.update(view1);

        eventHandle();
        printGrid();
        createParalax();

        _button.draw(_window);
        if (_button.isOpen())
            _menu.draw();
        // if (_save[0] == 1 && _save[1] == 1) {
        //     _isSaving = true;
        //     _fileName = "";
        // }
        // if (_load[0] == 1 && _load[1] == 1) {
        //     _isloading = true;
        //     _fileToLoad = "";
        // }
        if (_isSaving)
            saveLevel();
        if (_isloading)
            loadLevel();

        _window.display();
    }
}
