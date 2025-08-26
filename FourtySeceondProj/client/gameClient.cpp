/*
** EPITECH PROJECT, 2023
** gameClient
** File description:
** Game Client
*/

#include "gameClient.hpp"

GameClient::GameClient(gameEngine::RenderWindow &window) : _window(window)
{}

Entity initBox(GameEngine &ge, float posx, float posy)
{
    Entity box = ge.ecsSpawnEntity();
    component::Drawable drawable = { true };
    ge.ecsAddComponent(box, drawable);
    component::Transform pos = { posx, posy, 0, 0, 0, 0, 1, 1, 1 };
    ge.ecsAddComponent(box, pos);
    component::OutlineBox2D outlineBox(400, 100);
    ge.ecsAddComponent(box, outlineBox);
    return box;
}

void GameClient::connectionScreen()
{
    setUpComponents(ge);
    // _window.create(gameEngine::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Client");
    initLuaScripts(ge);
    initSystems();

    gameEngine::Listener::setPosition(WINDOW_WIDTH / 2, 0, WINDOW_HEIGHT / 2);

    gameEngine::Sound shootSound("assets/RType/sound/shoot.wav");
    shootSound.setVolume(100);
    shootSound.setMinDistance(5);
    shootSound.setAttenuation(0.1);
    shootSound.setPitch(1);
    ge.assetAddAsset<gameEngine::Sound>("shootSound", shootSound);

    gameEngine::Sound explosionSound("assets/RType/sound/explosion.wav");
    explosionSound.setVolume(1500);
    explosionSound.setMinDistance(5);
    explosionSound.setAttenuation(0.1);
    explosionSound.setPitch(1);
    ge.assetAddAsset<gameEngine::Sound>("explosionSound", explosionSound);

    gameEngine::Sound errorSound("assets/RType/sound/error.wav");
    errorSound.setVolume(1000);
    errorSound.setMinDistance(5);
    errorSound.setAttenuation(0.1);
    errorSound.setPitch(1);
    ge.assetAddAsset<gameEngine::Sound>("errorSound", errorSound);

    gameEngine::Sound validationSound("assets/RType/sound/validation.wav");
    validationSound.setVolume(500);
    validationSound.setMinDistance(5);
    validationSound.setAttenuation(0.1);
    validationSound.setPitch(1);
    ge.assetAddAsset<gameEngine::Sound>("validationSound", validationSound);

    _music.setLoop(true);
    _music.setVolume(15);
    if (!_music.openFromFile("assets/RType/music/menu.ogg")) {
        std::cerr << "error loading music\n";
    } else {
        _music.play();
    }

    component::Texture forwardBTN("Ui/Forward_BTN.png");
    ge.assetAddAsset<component::Texture>("forwardBTN", forwardBTN);

    component::Texture forwardBTNActive("Ui/Forward_BTN_active.png");
    ge.assetAddAsset<component::Texture>("forwardBTNActive", forwardBTNActive);

    component::Texture closeBTN("Ui/Close_BTN.png");
    ge.assetAddAsset<component::Texture>("closeBTN", closeBTN);

    component::Texture closeBTNActive("Ui/Close_BTN_active.png");
    ge.assetAddAsset<component::Texture>("closeBTNActive", closeBTNActive);

    component::Texture table("Ui/Table.png");
    ge.assetAddAsset<component::Texture>("table", table);

    component::Texture tableHover("Ui/TableHover.png");
    ge.assetAddAsset<component::Texture>("tableHover", tableHover);

    sf::Font font;
    if (!font.loadFromFile("r-type.ttf"))
        std::cout << "error loading font\n";

    TextBox adress(ge, 15, "127.0.0.1");
    adress.init(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2, font, 1, 1, 30, 25);
    TextBox port(ge, 5, "6000");
    port.init(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 + 100, font, 1, 1, 30, 25);
    TextBox name(ge, 15, "LeFunk");
    name.init(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 100, font, 1, 1, 30, 25);
    ge.ecsRunSingleSystem<component::Sprite, component::Texture>(loadSpriteTexture);
    name.changeTexture("tableHover");

    int boxFocus = 0;
    int intValue = 0;

    while (_window.isOpen()) {
        gameEngine::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == gameEngine::Event::Closed) {
                _window.close();
                exit(0);
            }
            if (event.type == gameEngine::Event::KeyReleased && event.key.code == gameEngine::Keyboard::Enter) {
                try {
                    intValue = std::stoi(port.getInputText());
                    if (ge.netConnectToServer(adress.getInputText(), intValue)) {
                        init(adress.getInputText(), intValue, name.getInputText());
                    }
                } catch (std::invalid_argument const &e) {
                    // The input string is not a valid integer
                    std::cerr << "Invalid input: " << e.what() << std::endl;
                }
            }
            if (event.type == gameEngine::Event::MouseButtonReleased && event.mouseButton.button == gameEngine::Mouse::Left) {
                if (event.mouseButton.x > name.getPos()[0] && event.mouseButton.x < name.getPos()[0] + name.getRect().width && event.mouseButton.y > name.getPos()[1] && event.mouseButton.y < name.getPos()[1] + name.getRect().height) {
                    boxFocus = 0;
                    name.changeTexture("tableHover");
                    adress.changeTexture("table");
                    port.changeTexture("table");
                } else if (event.mouseButton.x > adress.getPos()[0] && event.mouseButton.x < adress.getPos()[0] + adress.getRect().width && event.mouseButton.y > adress.getPos()[1] && event.mouseButton.y < adress.getPos()[1] + adress.getRect().height) {
                    boxFocus = 1;
                    name.changeTexture("table");
                    adress.changeTexture("tableHover");
                    port.changeTexture("table");
                } else if (event.mouseButton.x > port.getPos()[0] && event.mouseButton.x < port.getPos()[0] + port.getRect().width && event.mouseButton.y > port.getPos()[1] && event.mouseButton.y < port.getPos()[1] + port.getRect().height) {
                    boxFocus = 2;
                    name.changeTexture("table");
                    adress.changeTexture("table");
                    port.changeTexture("tableHover");
                }
            } else if (event.type == gameEngine::Event::TextEntered) {
                if (boxFocus == 0) {
                    name.update(event);
                } else if (boxFocus == 1) {
                    adress.update(event);
                } else {
                    port.update(event);
                }
            }
        }

        _window.clear();
        ge.ecsRunSystems();
        name.draw(_window);
        adress.draw(_window);
        port.draw(_window);
        _window.display();
    }
}

void GameClient::updateLobbyPlayers()
{
    int i = 0;

    for (ClientLobbyPlayer player : _currentLobby->getPlayers()) {
        if (i >= _currentLobby->getPlayers().size())
            break;
        if (i >= _players.size()) {
            _players.push_back(newLobby(ge, lobbyX, playerY, player.getId()));
            playerY += 110;
        }
        i++;
    }
}

void GameClient::sendMap(std::string mapName)
{
    std::ifstream file(mapName);
    std::string line;
    std::string map;
    while (std::getline(file, line)) {
        map += line;
        map += "\n";
    }
    Message<tcpProtocol> msg;
    msg.header.id = tcpProtocol::LobbySetMap;
    msg << map << _currentLobby->getId();
    ge.netSendTcpMessageToAll(msg);
}

void GameClient::inLobbyScreen()
{
    ge.ecsKillAllEntities();

    std::vector<std::string> maps;
    int currMap = 0;
    if (std::filesystem::exists("levels/")) {
        for (const auto &entry : std::filesystem::directory_iterator("levels/")) {
            maps.push_back(entry.path().string());
        }
        if (maps.size() == 0)
            currMap = -1;
    } else {
        currMap = -1;
    }

    sf::Font font;
    if (!font.loadFromFile("r-type.ttf"))
        std::cout << "error loading font\n";

    paralaxCreation("./Ui/BG.png");
    initLobbyScreen(ge);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);

    Entity buttonStart =  initButton(ge, "Ui/Forward_BTN.png", 1200, 125, 0.35, 0.35);
    // Entity buttonLeave = initButton(ge, "Ui/Close_BTN.png", 625, 125, 0.35, 0.35);
    Entity buttonChangeGame = initButton(ge, "Ui/Forward_BTN.png", WINDOW_WIDTH / 6 - 37, WINDOW_HEIGHT / 2, 0.35, 0.35);
    Entity buttonChangeMap = initButton(ge, "Ui/Forward_BTN.png", WINDOW_WIDTH - 337, WINDOW_HEIGHT / 2, 0.35, 0.35);

    if (_currentLobby->getOwner().getId() != _myId) {
        ge.ecsKillEntity(buttonStart);
        ge.ecsKillEntity(buttonChangeGame);
        ge.ecsKillEntity(buttonChangeMap);
    }

    TextBox lobbyName(ge, 10, _currentLobby->getName());
    lobbyName.init(800, 125, font, 0.8, 0.8, 30, 25);

    _lobbies.clear();

    ge.ecsRunSingleSystem<component::Sprite, component::Texture>(loadSpriteTexture);

    while (_window.isOpen() && _inLobby) {
        if (!ge.netIsConnected()) {
            _window.close();
            std::cerr << "Unable to connect to server\n";
            exit(84);
        }
        auto startFrame = std::chrono::high_resolution_clock::now();
        gameEngine::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == gameEngine::Event::Closed || (event.type == gameEngine::Event::KeyPressed && event.key.code == gameEngine::Keyboard::Escape)) {
                _window.close();
                exit(0);
            }
            if (event.type == gameEngine::Event::MouseMoved) {
                if (_currentLobby->getOwner().getId() == _myId) {
                    auto &tra = ge.ecsGetComponents<component::Transform>()[buttonStart];
                    auto &spr = ge.ecsGetComponents<component::Sprite>()[buttonStart];
                    auto &text = ge.ecsGetComponents<component::Texture>()[buttonStart];
                    sf::FloatRect startBounds(tra._posx, tra._posy, spr._rect.width * tra._scalex, spr._rect.height * tra._scaley);
                    if (startBounds.contains(event.mouseMove.x, event.mouseMove.y)) {
                        auto &texture = ge.assetGetAsset<component::Texture>("forwardBTNActive");
                        spr._sprite.setTexture(texture._texture);
                        text._texture = texture._texture;
                    } else {
                        auto &texture = ge.assetGetAsset<component::Texture>("forwardBTN");
                        spr._sprite.setTexture(texture._texture);
                        text._texture = texture._texture;
                    }

                    auto &tra2 = ge.ecsGetComponents<component::Transform>()[buttonChangeGame];
                    auto &spr2 = ge.ecsGetComponents<component::Sprite>()[buttonChangeGame];
                    auto &text2 = ge.ecsGetComponents<component::Texture>()[buttonChangeGame];
                    sf::FloatRect buttonBounds2(tra2._posx, tra2._posy, spr2._rect.width * tra2._scalex, spr2._rect.height * tra2._scaley);
                    if (buttonBounds2.contains(event.mouseMove.x, event.mouseMove.y)) {
                        auto &texture = ge.assetGetAsset<component::Texture>("forwardBTNActive");
                        spr2._sprite.setTexture(texture._texture);
                        text2._texture = texture._texture;
                    } else {
                        auto &texture = ge.assetGetAsset<component::Texture>("forwardBTN");
                        spr2._sprite.setTexture(texture._texture);
                        text2._texture = texture._texture;
                    }
                    if (currMap != -1) {
                        auto &tra3 = ge.ecsGetComponents<component::Transform>()[buttonChangeMap];
                        auto &spr3 = ge.ecsGetComponents<component::Sprite>()[buttonChangeMap];
                        auto &text3 = ge.ecsGetComponents<component::Texture>()[buttonChangeMap];
                        sf::FloatRect buttonBounds3(tra3._posx, tra3._posy, spr3._rect.width * tra3._scalex, spr3._rect.height * tra3._scaley);
                        if (buttonBounds3.contains(event.mouseMove.x, event.mouseMove.y)) {
                            auto &texture = ge.assetGetAsset<component::Texture>("forwardBTNActive");
                            spr3._sprite.setTexture(texture._texture);
                            text3._texture = texture._texture;
                        } else {
                            auto &texture = ge.assetGetAsset<component::Texture>("forwardBTN");
                            spr3._sprite.setTexture(texture._texture);
                            text3._texture = texture._texture;
                        }
                    }
                }
                // auto &tra2 = ge.ecsGetComponents<component::Transform>()[buttonLeave];
                // auto &spr2 = ge.ecsGetComponents<component::Sprite>()[buttonLeave];
                // auto &text2 = ge.ecsGetComponents<component::Texture>()[buttonLeave];
                // sf::FloatRect leaveBounds(tra2._posx, tra2._posy, spr2._rect.width * tra2._scalex, spr2._rect.height * tra2._scaley);
                // if (leaveBounds.contains(event.mouseMove.x, event.mouseMove.y)) {
                //     auto &texture = ge.assetGetAsset<component::Texture>("closeBTNActive");
                //     spr2._sprite.setTexture(texture._texture);
                //     text2._texture = texture._texture;
                // } else {
                //     auto &texture = ge.assetGetAsset<component::Texture>("closeBTN");
                //     spr2._sprite.setTexture(texture._texture);
                //     text2._texture = texture._texture;
                // }
            }
            if (event.type == gameEngine::Event::MouseButtonReleased && event.mouseButton.button == gameEngine::Mouse::Left) {
                bool validationSoundPlayed = false;
                if (_currentLobby->getOwner().getId() == _myId) {
                    auto &tra = ge.ecsGetComponents<component::Transform>()[buttonStart];
                    auto &spr = ge.ecsGetComponents<component::Sprite>()[buttonStart];
                    sf::FloatRect buttonBounds(tra._posx, tra._posy, spr._rect.width * tra._scalex, spr._rect.height * tra._scaley);
                    if (buttonBounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                        //start the game
                        if (currMap != -1) {
                            sendMap(maps[currMap]);
                        }

                        Message<tcpProtocol> msg;
                        msg.header.id = tcpProtocol::LobbyStart;
                        msg << _currentLobby->getId();
                        ge.netSendTcpMessageToAll(msg);

                        gameEngine::Sound &validationSound = ge.assetGetAsset<gameEngine::Sound>("validationSound");
                        validationSound.play();
                        validationSoundPlayed = true;

                        _window.close();
                    }

                    auto &tra2 = ge.ecsGetComponents<component::Transform>()[buttonChangeGame];
                    auto &spr2 = ge.ecsGetComponents<component::Sprite>()[buttonChangeGame];
                    sf::FloatRect buttonBounds2(tra2._posx, tra2._posy, spr2._rect.width * tra2._scalex, spr2._rect.height * tra2._scaley);
                    if (buttonBounds2.contains(event.mouseButton.x, event.mouseButton.y)) {
                        //change the game
                        Message<tcpProtocol> msg;
                        msg.header.id = tcpProtocol::LobbyChangeGame;
                        msg << _currentLobby->getId();
                        ge.netSendTcpMessageToAll(msg);
                        std::cout << "sent change game\n";

                        gameEngine::Sound &validationSound = ge.assetGetAsset<gameEngine::Sound>("validationSound");
                        validationSound.play();
                        validationSoundPlayed = true;
                    }
                    if (currMap != -1) {
                        auto &tra3 = ge.ecsGetComponents<component::Transform>()[buttonChangeMap];
                        auto &spr3 = ge.ecsGetComponents<component::Sprite>()[buttonChangeMap];
                        sf::FloatRect buttonBounds3(tra3._posx, tra3._posy, spr3._rect.width * tra3._scalex, spr3._rect.height * tra3._scaley);
                        if (buttonBounds3.contains(event.mouseButton.x, event.mouseButton.y)) {
                            if (currMap + 1 >= maps.size())
                                currMap = 0;
                            else
                                currMap++;
                            gameEngine::Sound &validationSound = ge.assetGetAsset<gameEngine::Sound>("validationSound");
                            validationSound.play();
                            validationSoundPlayed = true;
                        }
                    }
                }

                if (!validationSoundPlayed) {
                    gameEngine::Sound &errorSound = ge.assetGetAsset<gameEngine::Sound>("errorSound");
                    errorSound.play();
                }
            }
        }
        _window.clear();
        updateTcp();
        updateLobbyPlayers();
        ge.ecsRunSystems();

        text.setString((_playingPong) ? "Game\nPong " : "Game\nRType");
        text.setPosition(WINDOW_WIDTH / 6 - text.getLocalBounds().width / 2, WINDOW_HEIGHT / 2 + 100);
        _window.draw(text);
        if (currMap != -1 && _currentLobby->getOwner().getId() == _myId) {
            text.setString(maps[currMap].substr(maps[currMap].find_last_of('/') + 1, maps[currMap].find_last_of('.') - maps[currMap].find_last_of('/') - 1));
            text.setPosition(((WINDOW_WIDTH / 6) * 5) - text.getLocalBounds().width / 2, WINDOW_HEIGHT / 2 + 100);
            _window.draw(text);
        }

        int i = 0;
        for (auto player : _currentLobby->getPlayers()) {
            if (i >= _players.size())
                break;
            auto &tra = ge.ecsGetComponents<component::Transform>()[_players[i]];
            auto &spr = ge.ecsGetComponents<component::Sprite>()[_players[i]];

            text.setPosition(tra._posx + 50, tra._posy + 10);
            text.setString(player.getName());
            _window.draw(text);
            i++;
        }

        _window.draw(lobbyName.getText());
        auto endFrame = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - startFrame);
        if (duration.count() < SECOND_IN_MS / FRAMERATE)
            std::this_thread::sleep_for(std::chrono::milliseconds(SECOND_IN_MS / FRAMERATE - duration.count()));

        _window.display();
    }
}


void GameClient::lobbyScreen(std::string name)
{
    paralaxCreation("./Ui/BG.png");
    initLobbyScreen(ge);
    sf::Font font;
    if (!font.loadFromFile("r-type.ttf"))
        std::cout << "error loading font\n";
    Entity buttonCreateLobby = initButton(ge, "Ui/Forward_BTN.png", 1170, 125, 0.35, 0.35);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);

    TextBox lobbyName(ge, 12, "LobbyName");
    lobbyName.init(675, 125, font, 0.8, 0.8, 30, 25);

    TextBox lobbySize(ge, 1, "4");
    lobbySize.init(1025, 125, font, 0.2, 0.8, 25, 25);

    //imonde :
    if (ge.netIsConnected()) {
        Message<tcpProtocol> msg;
        msg.header.id = tcpProtocol::SetName;
        msg << name;
        ge.netSendTcpMessageToAll(msg);
    } else {
        std::cerr << "Unable to connect to server\n";
        exit(84);
    }
    //fin immonde

    int boxFocus = 0;
    size_t intValue = 0;
    std::cout << "here\n";
    ge.ecsRunSingleSystem<component::Sprite, component::Texture>(loadSpriteTexture);

    while (_window.isOpen() && !_inLobby) {
        if (!ge.netIsConnected()) {
            _window.close();
            std::cerr << "Unable to connect to server\n";
            exit(84);
        }
        auto startFrame = std::chrono::high_resolution_clock::now();
        gameEngine::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == gameEngine::Event::Closed || (event.type == gameEngine::Event::KeyPressed && event.key.code == gameEngine::Keyboard::Escape)) {
                _window.close();
                exit(0);
            } else if (event.type == gameEngine::Event::TextEntered) {
                if (boxFocus == 0) {
                    lobbyName.update(event);
                } else {
                    lobbySize.update(event);
                }
            }
            if (event.type == gameEngine::Event::KeyReleased && event.key.code == gameEngine::Keyboard::Enter) {
                if (lobbySize.getText().getString().isEmpty() || lobbySize.getText().getString()[0] < '1' || lobbySize.getText().getString()[0] > '9')
                    continue;
                try {
                    intValue = std::stoi(lobbySize.getInputText());
                    Message<tcpProtocol> msg;
                    msg.header.id = tcpProtocol::LobbyCreate;
                    msg << lobbyName.getInputText() << intValue;
                    ge.netSendTcpMessageToAll(msg);
                    //TODO add server validation

                    gameEngine::Sound &validationSound = ge.assetGetAsset<gameEngine::Sound>("validationSound");
                    validationSound.play();
                } catch (std::invalid_argument const &e) {
                    std::cerr << "Invalid input: " << e.what() << std::endl;
                }

            }
            if (event.type == gameEngine::Event::MouseButtonReleased && event.mouseButton.button == gameEngine::Mouse::Left) {
                bool validationSoundPlayed = false;
                // Check if the mouse click occurred within the bounds of a lobby
                for (int i = 0; i < _lobbies.size(); i++) {
                    auto &tra = ge.ecsGetComponents<component::Transform>()[_lobbies[i]];
                    auto &spr = ge.ecsGetComponents<component::Sprite>()[_lobbies[i]];
                    sf::FloatRect lobbyBounds(tra._posx, tra._posy, spr._rect.width * tra._scalex, spr._rect.height * tra._scaley);
                    if (lobbyBounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                        // Retrieve all the information of the clicked lobby and display it to the user
                        auto lobby = _lobbyHandler.getLobbies()[i];
                        Message<tcpProtocol> msg;
                        msg.header.id = tcpProtocol::LobbyJoin;
                        msg << (size_t) lobby.getId();
                        ge.netSendTcpMessageToAll(msg);
                        //TODO add server validation

                        gameEngine::Sound &validationSound = ge.assetGetAsset<gameEngine::Sound>("validationSound");
                        validationSound.play();
                        validationSoundPlayed = true;
                    }
                }
                auto &tra = ge.ecsGetComponents<component::Transform>()[buttonCreateLobby];
                auto &spr = ge.ecsGetComponents<component::Sprite>()[buttonCreateLobby];
                sf::FloatRect buttonBounds(tra._posx, tra._posy, spr._rect.width * tra._scalex, spr._rect.height * tra._scaley);
                if (buttonBounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (lobbySize.getText().getString().isEmpty() || lobbySize.getText().getString()[0] < '1' || lobbySize.getText().getString()[0] > '9')
                        continue;
                    try {
                        intValue = std::stoi(lobbySize.getInputText());
                        Message<tcpProtocol> msg;
                        msg.header.id = tcpProtocol::LobbyCreate;
                        msg << lobbyName.getInputText() << intValue;
                        ge.netSendTcpMessageToAll(msg);

                        gameEngine::Sound &validationSound = ge.assetGetAsset<gameEngine::Sound>("validationSound");
                        validationSound.play();
                        validationSoundPlayed = true;
                    } catch (std::invalid_argument const &e) {
                        std::cerr << "Invalid input: " << e.what() << std::endl;
                    }
                    //TODO add server validation §§ like enter
                }

                if (!validationSoundPlayed) {
                    gameEngine::Sound &errorSound = ge.assetGetAsset<gameEngine::Sound>("errorSound");
                    errorSound.play();
                }
            } else if (event.type == gameEngine::Event::MouseMoved) {
                // Check if the mouse is hovering over a lobby
                for (int i = 0; i < _lobbies.size(); i++) {
                    auto &tra = ge.ecsGetComponents<component::Transform>()[_lobbies[i]];
                    auto &spr = ge.ecsGetComponents<component::Sprite>()[_lobbies[i]];
                    auto &text = ge.ecsGetComponents<component::Texture>()[_lobbies[i]];
                    sf::FloatRect lobbyBounds(tra._posx, tra._posy, spr._rect.width * tra._scalex, spr._rect.height * tra._scaley);
                    if (lobbyBounds.contains(event.mouseMove.x, event.mouseMove.y)) {
                        // Change the color of the text or the sprite of the hovered lobby
                        auto &texture = ge.assetGetAsset<component::Texture>("tableHover");
                        spr._sprite.setTexture(texture._texture);
                        text._texture = texture._texture;
                    } else {
                        // Reset the color of the text or the sprite of the unhovered lobby
                        auto &texture = ge.assetGetAsset<component::Texture>("table");
                        spr._sprite.setTexture(texture._texture);
                        text._texture = texture._texture;
                    }
                }
                auto &tra = ge.ecsGetComponents<component::Transform>()[buttonCreateLobby];
                auto &spr = ge.ecsGetComponents<component::Sprite>()[buttonCreateLobby];
                auto &text = ge.ecsGetComponents<component::Texture>()[buttonCreateLobby];
                sf::FloatRect buttonBounds(tra._posx, tra._posy, spr._rect.width * tra._scalex, spr._rect.height * tra._scaley);
                if (buttonBounds.contains(event.mouseMove.x, event.mouseMove.y)) {
                    // Change the color of the text or the sprite of the hovered lobby
                    auto &texture = ge.assetGetAsset<component::Texture>("forwardBTNActive");
                    spr._sprite.setTexture(texture._texture);
                    text._texture = texture._texture;
                } else {
                    // Reset the color of the text or the sprite of the unhovered lobby
                    auto &texture = ge.assetGetAsset<component::Texture>("forwardBTN");
                    spr._sprite.setTexture(texture._texture);
                    text._texture = texture._texture;
                }
            }
            if (event.mouseButton.x > lobbyName.getPos()[0] && event.mouseButton.x < lobbyName.getPos()[0] + lobbyName.getRect().width && event.mouseButton.y > lobbyName.getPos()[1] && event.mouseButton.y < lobbyName.getPos()[1] + lobbyName.getRect().height) {
                boxFocus = 0;
                lobbyName.changeTexture("tableHover");
                lobbySize.changeTexture("table");
            } else if (event.mouseButton.x > lobbySize.getPos()[0] && event.mouseButton.x < lobbySize.getPos()[0] + lobbySize.getRect().width && event.mouseButton.y > lobbySize.getPos()[1] && event.mouseButton.y < lobbySize.getPos()[1] + lobbySize.getRect().height) {
                boxFocus = 1;
                lobbySize.changeTexture("tableHover");
                lobbyName.changeTexture("table");
            }
        }

        _window.clear();
        updateTcp();
        ge.ecsRunSystems();
        int i = 0;

        for (int i = 0 ; i < _lobbies.size() ; i++) {
            if (i >= _lobbyHandler.getLobbies().size()) {
                ge.ecsKillEntity(_lobbies[i]);
                _lobbies.erase(_lobbies.begin() + i);
                lobbyY -= 110;
            }
        }

        for (auto lobby : _lobbyHandler.getLobbies()) {
            if (i >= _lobbies.size())
                break;
            auto &tra = ge.ecsGetComponents<component::Transform>()[_lobbies[i]];
            auto &spr = ge.ecsGetComponents<component::Sprite>()[_lobbies[i]];
            text.setPosition(tra._posx + 50, tra._posy + 10);
            text.setString(lobby.getName());
            _window.draw(text);
            text.setPosition(tra._posx + (spr._rect.width * tra._scalex) - 100, tra._posy + 20);
            text.setString(std::to_string(lobby.getPlayers().size()) + "/" + std::to_string(lobby.getSize()));
            _window.draw(text);
            i++;
        }

        _window.draw(lobbyName.getText());
        _window.draw(lobbySize.getText());

        auto endFrame = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - startFrame);
        if (duration.count() < SECOND_IN_MS / FRAMERATE)
            std::this_thread::sleep_for(std::chrono::milliseconds(SECOND_IN_MS / FRAMERATE - duration.count()));

        _window.display();
    }
}

void GameClient::init(std::string ip, size_t port, std::string name)
{
    srand(time(NULL));

    ge.ecsKillAllEntities();

    lobbyScreen(name);
    inLobbyScreen();
    waitGameStart();

    _window.create(gameEngine::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Client");

    ge.ecsKillAllEntities();

    _music.stop();

    if (_playingPong) {
        PongClient pongClient(_window, ge);
        pongClient.run(_myId);
    } else {
        if (!_music.openFromFile("assets/RType/music/game.ogg")) {
            std::cerr << "error loading music\n";
        } else {
            _music.play();
        }
        paralaxCreation("./Client/sprites/background1.png");
        // Set the texture for each sprite
        ge.ecsRunSingleSystem<component::Sprite, component::Texture>(loadSpriteTexture);
        run();
    }
    exit(0);
}

void GameClient::updateTcp()
{
    if (ge.netGetConnections().empty())
        return;
    size_t lobbyId;
    size_t lobbySize;
    size_t playerId;
    size_t owner;
    std::string lobbyName;
    std::string playerName;
    int game;

    while (!ge.netIncomingTcp().empty()) {
        net::Message<tcpProtocol> msg = ge.netIncomingTcp().popFront().msg;
        switch (msg.header.id) {
            case tcpProtocol::Udp:
                if (!ge.netGetDataChannel()) {
                    asio::ip::udp::endpoint peer;
                    msg >> peer;
                    std::cout << "endpoint: " << peer << std::endl;
                    ge.netCreateDataChannel("0.0.0.0", 0);
                    ge.netAddClientUdp(peer);
                    net::MessageUdp<udpProtocol> data = {udpProtocol::CreatePlayer, 0, {}};
                    ge.netUdpSendAll(data);
                }
                break;
            case tcpProtocol::LobbyCreated:
                msg >> lobbyId >> playerId >> lobbySize >> lobbyName >> playerName;
                std::cout << "Lobby created: " << lobbyId << " " << playerId << " " << lobbySize << " " << lobbyName << " " << playerName << std::endl;
                if (!_inLobby) {
                    _lobbyHandler.createLobby(lobbySize, ClientLobbyPlayer { playerName, playerId}, lobbyName, lobbyId);
                    _lobbies.push_back(newLobby(ge, lobbyX, lobbyY, lobbyId));
                    ge.ecsRunSingleSystem<component::Sprite, component::Texture>(loadSpriteTexture);
                    lobbyY += 110;
                }
                break;
            case tcpProtocol::LobbyJoined:
                msg >> lobbyId >> playerId >> playerName;
                _lobbyHandler.addPlayerToLobby(lobbyId, ClientLobbyPlayer { playerName, playerId});
                break;
            case tcpProtocol::LobbyLeft:
                msg >> lobbyId >> playerId;
                _lobbyHandler.removePlayerFromLobby(lobbyId, playerId);
                break;
            case tcpProtocol::LobbyStarted:
                _window.close();
                break;
            case tcpProtocol::LobbyChangeGame:
                msg >> lobbyId >> game;
                if (lobbyId == _currentLobby->getId()) {
                    std::cout << "changing game\n";
                    if (game == 0)
                        _playingPong = false;
                    if (game == 1)
                        _playingPong = true;
                }
                break;
            case tcpProtocol::LobbyJoin:
                msg >> game >> playerId >> lobbyId;
                _currentLobby = _lobbyHandler.getLobbyById(lobbyId);
                if (_currentLobby == nullptr) {
                    std::cerr << "Lobby not found\n";
                    return;
                }
                _myId = playerId;
                _inLobby = true;
                if (game == 0)
                    _playingPong = false;
                if (game == 1)
                    _playingPong = true;
                break;
            case tcpProtocol::LobbyRemoved:
                msg >> lobbyId;
                // get lobby by id and check if i'm not in it and delete it
                if (!(_currentLobby != nullptr && _currentLobby->getId() == lobbyId)) {
                    _lobbyHandler.removeLobby(lobbyId);
                }
                break;
            default:
                break;
        }
    }
}

void GameClient::waitGameStart()
{
    while (!ge.netGetDataChannel()) {
        updateTcp();
    }
}

void GameClient::paralaxCreation(std::string path)
{
    for (int i = 0; i < 2; i++) {
        Entity entity = ge.ecsSpawnEntity();
        component::Sprite sprite(sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
        ge.ecsAddComponent(entity, sprite);
        component::Texture text(path);
        ge.ecsAddComponent(entity, text);
        component::Drawable drawable = { true };
        ge.ecsAddComponent(entity, drawable);
        component::Transform pos = { (float)(WINDOW_WIDTH * i), 0, 0, 0, 0, 0, 1, 1, 1 };
        ge.ecsAddComponent(entity, pos);
        component::Velocity vel = { -180, 0, 0 };
        ge.ecsAddComponent(entity, vel);
        component::Paralax paralax = { WINDOW_WIDTH };
        ge.ecsAddComponent(entity, paralax);
    }
}

void GameClient::playerCreation(player_t position, Entity &player, bool isSelf)
{
    component::Sprite sprite(sf::IntRect(PLAYER_WIDTH * 2, PLAYER_HEIGHT * position.player_sprite, PLAYER_WIDTH, PLAYER_HEIGHT));
    ge.ecsAddComponent(player, sprite);
    component::Texture text("./Client/sprites/ship.png");
    ge.ecsAddComponent(player, text);

    auto &spr = ge.ecsGetComponents<component::Sprite>()[player];
    auto &tex = ge.ecsGetComponents<component::Texture>()[player];
    spr._sprite.setTexture(tex._texture);

    component::Drawable drawable = { true };
    ge.ecsAddComponent(player, drawable);
    component::Transform pos = { position.posx, position.posy, 0, 0, 0, 0, (float) ((isSelf) ? 3:3), (float) ((isSelf) ? 3:3), (float) ((isSelf) ? 3:3) };
    ge.ecsAddComponent(player, pos);
    component::Velocity vel = { 0, 0, 0 };
    ge.ecsAddComponent(player, vel);
    component::ColisionBoxCustom col = { 0, 0, 0, PLAYER_WIDTH * 3, PLAYER_HEIGHT * 3, 0, false, component::ColisionBoxCustom::Layer::PLAYER,COLLISION_MATRIX };
    ge.ecsAddComponent(player, col);
    component::Unmovable unmovable = { true };
    ge.ecsAddComponent(player, unmovable);
    component::OutlineBox2D outlineBox(PLAYER_WIDTH * (float) ((isSelf) ? 3:3), PLAYER_HEIGHT * (float) ((isSelf) ? 3:3));
    ge.ecsAddComponent(player, outlineBox);
    component::Id id = { position.id };
    ge.ecsAddComponent(player, id);

    std::cout << "./Client/sprites/json/player" + std::to_string(position.player_sprite + 1) + ".json" << std::endl;
    std::string path = "./Client/sprites/json/player" + std::to_string(position.player_sprite + 1) + ".json";
    component::Animation anim(path, gameEngine::Time::Zero, false, false);
    anim._currentFrame = 2;
    ge.ecsAddComponent(player, anim);

    if (isSelf) {
        _rtypeIsAlive = true;
    }
}

void GameClient::syncPlayer(net::OwnedMessageUdp<udpProtocol> &msg)
{
    player_t pos;
    msg.msg >> pos;
    if (hasIdComponent(ge, pos.id))
        return;
    else {
        Entity playerN = ge.ecsSpawnEntity();
        playerCreation(pos, playerN);
    }
}

void GameClient::initSystems()
{
    ge.ecsAddSystem<component::Transform,
            component::Paralax>(calcParallaxSystem);
    ge.ecsAddSystem<component::Transform,
            component::Velocity,
            component::EnemyType,
            component::hasTouch,
            component::IsEnemy>(enemyPattern);
    ge.ecsAddSystem<component::Transform,
            component::Velocity>(updatePosSystem);
    ge.ecsAddSystem<component::Transform,
            component::ColisionBoxCustom,
            component::Velocity,
            component::Unmovable>(colisionSystemCustom);
    ge.ecsAddSystem<component::Transform,
            component::Sprite>(refreshSpriteSystem);
    ge.ecsAddSystem<component::Animation,
            component::Sprite>(animationSystem);
    ge.ecsAddSystem<component::Sprite,
            component::Drawable>(drawSprite, _window);
    ge.ecsAddSystem<component::Transform,
            component::OutlineBox2D,
            component::Drawable>(outlineBox2DDrawSystem, _window);
    ge.ecsAddSystem<component::ToDelete>(garbageCollectorSystem);
}

void GameClient::createBullet(pos_t bullet_pos)
{
    Entity bullet = ge.ecsSpawnEntity();
    component::Sprite sprite(sf::IntRect(0, 0, BULLET_WIDTH, BULLET_HEIGHT));
    ge.ecsAddComponent(bullet, sprite);
    component::Texture text("./Client/sprites/missile.png");
    ge.ecsAddComponent(bullet, text);
    auto &spr = ge.ecsGetComponents<component::Sprite>()[bullet];
    auto &tex = ge.ecsGetComponents<component::Texture>()[bullet];
    spr._sprite.setTexture(tex._texture);
    component::Drawable drawable = { true };
    ge.ecsAddComponent(bullet, drawable);
    component::Transform pos = { bullet_pos.posx, bullet_pos.posy, 0, 0, 0, 0, 0.5, 0.5, 0.5 };
    ge.ecsAddComponent(bullet, pos);
    component::Velocity vel = { BULLET_SPEED, 0, 0 };
    ge.ecsAddComponent(bullet, vel);
    component::ColisionBoxCustom col = { 0, 0, 0, BULLET_WIDTH * 0.5, BULLET_HEIGHT * 0.5, 0, true, component::ColisionBoxCustom::Layer::MISSILE, COLLISION_MATRIX };
    ge.ecsAddComponent(bullet, col);
    component::OutlineBox2D outlineBox(BULLET_WIDTH * 0.5, BULLET_HEIGHT * 0.5);
    ge.ecsAddComponent(bullet, outlineBox);
    component::Bullet bulletComp = { 25 };
    ge.ecsAddComponent(bullet, bulletComp);
    component::Id idComp = { bullet_pos.id };
    ge.ecsAddComponent(bullet, idComp);

    gameEngine::Sound &shootSound = ge.assetGetAsset<gameEngine::Sound>("shootSound");
    shootSound.setPosition(bullet_pos.posx, 0, bullet_pos.posy);
    shootSound.play();
}

void GameClient::handlePlayer(Entity &player, int &bulletTime)
{
    auto &velocities = ge.ecsGetComponents<component::Velocity>();
    auto &transforms = ge.ecsGetComponents<component::Transform>();
    if (!velocities.has(player) || !transforms.has(player))
        return;
    auto &curVel = velocities[player];
    auto &curPos = transforms[player];
    vel_t newVel = { curVel._velx, curVel._vely, _myId };
    if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Key::Left)) {
        newVel.velx = -PLAYER_SPEED;
    }
    else if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Key::Right)) {
        newVel.velx = PLAYER_SPEED;
    }
    else {
        newVel.velx = 0;
    }
    if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Key::Up)) {
        newVel.vely = -PLAYER_SPEED;
        auto &anim = ge.ecsGetComponents<component::Animation>()[player];
        anim._currentFrame++;
    }
    else if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Key::Down)) {
        newVel.vely = PLAYER_SPEED;
        auto &anim = ge.ecsGetComponents<component::Animation>()[player];
        if (anim._currentFrame > 0)
            anim._currentFrame--;
    }
    else {
        newVel.vely = 0;
        auto &anim = ge.ecsGetComponents<component::Animation>()[player];
        anim._currentFrame = 2;
    }

    if (newVel.velx != oldVel.velx || newVel.vely != oldVel.vely) {
        net::MessageUdp<udpProtocol> msg;
        msg.header.id = udpProtocol::PlayerMove;
        msg << newVel;
        ge.netUdpSendAll(msg);
        oldVel.velx = newVel.velx;
        oldVel.vely = newVel.vely;
        oldVel.id = newVel.id;
    }

    if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Key::Space) && bulletTime <= 0) {
        bulletTime = 2;
        net::MessageUdp<udpProtocol> msg;
        msg.header.id = udpProtocol::CreateBullet;
        msg << pos_t{ curPos._posx, curPos._posy, 0 };
        ge.netUdpSendAll(msg);
    }
}

void GameClient::run()
{
    Entity player = ge.ecsSpawnEntity();

    int bulletTime = 0;
    ge.timeSetInterval([&bulletTime]() {
        bulletTime--;
    }, 100);
    ge.timeStartTick();
    while (_window.isOpen()) {
        auto startFrame = std::chrono::high_resolution_clock::now();
        gameEngine::Event event;

        while (_window.pollEvent(event)) {
            if (event.type == gameEngine::Event::Closed) {
                ge.netDisconnect();
                _window.close();
            }
            if (event.type == gameEngine::Event::LostFocus)
                _isFocused = false;
            if (event.type == gameEngine::Event::GainedFocus)
                _isFocused = true;
            if (event.type == gameEngine::Event::MouseButtonReleased && event.mouseButton.button == gameEngine::Mouse::Left) {
                std::cout << "X = " << event.mouseButton.x << " Y = " << event.mouseButton.y << std::endl;
            }
        }

        if (_isFocused && _rtypeIsAlive) {
            handlePlayer(player, bulletTime);
        }

        _window.clear();
        if (ge.netIsConnected() == false) {
            _window.close();
            break;
        }
        updateGame(player);
        ge.ecsRunSystems();

        auto endFrame = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - startFrame);
        if (duration.count() < SECOND_IN_MS / FRAMERATE)
            std::this_thread::sleep_for(std::chrono::milliseconds(SECOND_IN_MS / FRAMERATE - duration.count()));

        _window.display();
    }
}

void GameClient::movePlayer(size_t id, vel_t vel)
{
    Entity tmp = ge.ecsEntityFromIndex(getFromIdComponent(ge, id));
    auto &tra = ge.ecsGetComponents<component::Velocity>()[tmp];
    tra._velx = vel.velx;
    tra._vely = vel.vely;
    if (tra._vely > 0) {
        auto &anim = ge.ecsGetComponents<component::Animation>()[tmp];
        anim._currentFrame = 0;
    } else if (tra._vely < 0) {
        auto &anim = ge.ecsGetComponents<component::Animation>()[tmp];
        anim._currentFrame = 4;
    } else {
        auto &anim = ge.ecsGetComponents<component::Animation>()[tmp];
        anim._currentFrame = 2;
    }
}

void GameClient::resyncEntityWithId(net::OwnedMessageUdp<udpProtocol> &msg)
{
    pos_t pos;
    msg.msg >> pos;
    for (auto &entity : ge.ecsGetComponents<component::Id>()) {
        if (entity.second._id == pos.id) {
            auto &tra = ge.ecsGetComponents<component::Transform>()[entity.first];
            tra._posx = pos.posx;
            tra._posy = pos.posy;
        }
    }
}

void GameClient::generateEnemy(GameEngine &ge, pos_t networkPos, int typeEnemy)
{
    Entity enemy = ge.ecsSpawnEntity();

    std::cout << typeEnemy << std::endl;
    if (typeEnemy == 1) {
        component::Sprite sprite(sf::IntRect(0, 0, ENEMY_WIDTH, ENEMY_HEIGHT));
        ge.ecsAddComponent(enemy, sprite);
        component::Texture text("./Client/sprites/r-typesheetRedEnemy.png");
        ge.ecsAddComponent(enemy, text);
        component::Velocity vel = { -120, 0, 0 };
        ge.ecsAddComponent(enemy, vel);
        component::EnemyType type = { component::EnemyType::SIMPLE };
        ge.ecsAddComponent(enemy, type);
        component::Animation anim("Client/sprites/json/enemySimple.json", sf::Time(sf::seconds(0.1)), true);
        ge.ecsAddComponent(enemy, anim);
        component::Health health = { 100 };
        ge.ecsAddComponent(enemy, health);
        component::ColisionBoxCustom col = { ENEMY_WIDTH * -3, 0, 0, ENEMY_WIDTH * 3, ENEMY_HEIGHT * 3, 0, false, component::ColisionBoxCustom::Layer::ENEMY, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::OutlineBox2D outlineBox(ENEMY_WIDTH * -3, ENEMY_HEIGHT * 3);
        ge.ecsAddComponent(enemy, outlineBox);
    } else if (typeEnemy == 2) {
        component::Sprite sprite(sf::IntRect(0, 0, ENEMY_WIDTH, ENEMY_HEIGHT));
        ge.ecsAddComponent(enemy, sprite);
        component::Texture text("./Client/sprites/r-typesheet7.png");
        ge.ecsAddComponent(enemy, text);
        component::Velocity vel = {-120, 0, 0};
        ge.ecsAddComponent(enemy, vel);
        component::Animation anim("Client/sprites/json/enemyMecha.json", sf::Time(sf::seconds(0.1)), true);
        ge.ecsAddComponent(enemy, anim);
        component::EnemyType type = {component::EnemyType::MECHA };
        ge.ecsAddComponent(enemy, type);
        component::Health health = { 100 };
        ge.ecsAddComponent(enemy, health);
        component::ColisionBoxCustom col = { ENEMY_WIDTH * -3, 0, 0, ENEMY_WIDTH * 3, ENEMY_HEIGHT * 3, 0, false, component::ColisionBoxCustom::Layer::ENEMY, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::OutlineBox2D outlineBox(ENEMY_WIDTH * -3, ENEMY_HEIGHT * 3);
        ge.ecsAddComponent(enemy, outlineBox);
    } else if (typeEnemy == 3) {
        component::Sprite sprite(sf::IntRect(0, 0, ENEMY_WIDTH, ENEMY_HEIGHT));
        ge.ecsAddComponent(enemy, sprite);
        component::Texture text("./Client/sprites/r-typesheet8.png");
        ge.ecsAddComponent(enemy, text);
        component::Velocity vel = { -120, 240, 0 };
        ge.ecsAddComponent(enemy, vel);
        component::EnemyType type = { component::EnemyType::OTHER };
        ge.ecsAddComponent(enemy, type);
        component::Health health = { 100 };
        ge.ecsAddComponent(enemy, health);
        component::ColisionBoxCustom col = { ENEMY_WIDTH * -3, 0, 0, ENEMY_WIDTH * 3, ENEMY_HEIGHT * 3, 0, false, component::ColisionBoxCustom::Layer::ENEMY, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::OutlineBox2D outlineBox(ENEMY_WIDTH * -3, ENEMY_HEIGHT * 3);
        ge.ecsAddComponent(enemy, outlineBox);
    } else if (typeEnemy == 4) {
        component::Sprite sprite(sf::IntRect(0, 0, ENEMY_WIDTH, ENEMY_HEIGHT));
        ge.ecsAddComponent(enemy, sprite);
        component::Texture text("./Client/sprites/R-Type 2 Sprites.png");
        ge.ecsAddComponent(enemy, text);
        component::Velocity vel = { -120, 0, 0 };
        ge.ecsAddComponent(enemy, vel);
        component::ColisionBoxCustom col = { ENEMY_WIDTH * -3, 0, 0, ENEMY_WIDTH * 3, ENEMY_HEIGHT * 3, 0, false, component::ColisionBoxCustom::Layer::OBSTACLE, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::OutlineBox2D outlineBox(ENEMY_WIDTH * -3, ENEMY_HEIGHT * 3);
        ge.ecsAddComponent(enemy, outlineBox);
    } else if (typeEnemy == 5) {
        component::Sprite sprite(sf::IntRect(0, 0, 260, 142));
        ge.ecsAddComponent(enemy, sprite);
        component::Texture texture("./Client/sprites/r-typesheet32.png");
        ge.ecsAddComponent(enemy, texture);
        component::Velocity vel = {-120, 0, 0};
        ge.ecsAddComponent(enemy, vel);
        component::EnemyType type = {component::EnemyType::BOSS };
        ge.ecsAddComponent(enemy, type);
        component::Health health = { 2500 };
        ge.ecsAddComponent(enemy, health);
        component::ColisionBoxCustom col = { 260 * -3, 0, 0, 260 * 3, 142 * 3, 0, false, component::ColisionBoxCustom::Layer::ENEMY, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::OutlineBox2D outlineBox(260 * -3, 142 * 3);
        ge.ecsAddComponent(enemy, outlineBox);
        component::Animation anim("Client/sprites/json/boss.json", sf::Time(sf::seconds(0.3)), true);
        ge.ecsAddComponent(enemy, anim);
    } else if (typeEnemy == -1) {
        component::Sprite sprite(sf::IntRect(0, 0, 34, 34));
        ge.ecsAddComponent(enemy, sprite);
        component::Texture text("./Client/sprites/r-typesheet30a.png");
        ge.ecsAddComponent(enemy, text);
        component::Velocity vel = { -300, 300, 0 };
        ge.ecsAddComponent(enemy, vel);
        component::EnemyType type = { component::EnemyType::MISSILE };
        ge.ecsAddComponent(enemy, type);
        component::Health health = { 25 };
        ge.ecsAddComponent(enemy, health);
        component::ColisionBoxCustom col = { 0, 0, 0, 34 * 3, 34 * 3, 0, false, component::ColisionBoxCustom::Layer::ENEMY, COLLISION_MATRIX };
        ge.ecsAddComponent(enemy, col);
        component::OutlineBox2D outlineBox(34 * -3, 34 * 3);
        ge.ecsAddComponent(enemy, outlineBox);
        component::Animation anim("Client/sprites/json/enemyBullet.json", sf::Time(sf::seconds(0.1)), true);
        ge.ecsAddComponent(enemy, anim);
    } else if (typeEnemy == 4) {
        component::Texture text("./Client/sprites/R-Type 2 Sprites.png");
        ge.ecsAddComponent(enemy, text);
        component::Velocity vel = { -120, 0, 0 };
        ge.ecsAddComponent(enemy, vel);
    }

    auto &spr = ge.ecsGetComponents<component::Sprite>()[enemy];
    auto &tex = ge.ecsGetComponents<component::Texture>()[enemy];
    spr._sprite.setTexture(tex._texture);

    component::Drawable drawable = { true };
    ge.ecsAddComponent(enemy, drawable);

    component::Transform pos = { networkPos.posx, networkPos.posy, 0, 0, 0, 0, -3, 3, 3 };
    ge.ecsAddComponent(enemy, pos);

    component::Unmovable unmovable = { true };
    ge.ecsAddComponent(enemy, unmovable);

    if (typeEnemy != 4) {
        component::IsEnemy isEnemy;
        ge.ecsAddComponent(enemy, isEnemy);
    }

    component::Id id = { networkPos.id };
    ge.ecsAddComponent(enemy, id);

    component::hasTouch hasTouch;
    ge.ecsAddComponent(enemy, hasTouch);
}

Entity GameClient::createExplosion(component::Transform &pos)
{
    Entity explosion = ge.ecsSpawnEntity();
    component::Sprite sprite(sf::IntRect(96, 53, 35, 31));
    ge.ecsAddComponent(explosion, sprite);
    component::Texture text("./Client/sprites/r-typesheet43.png");
    ge.ecsAddComponent(explosion, text);
    component::Animation anim ("Client/sprites/json/explosion.json", sf::Time(sf::seconds(0.1)), false);
    ge.ecsAddComponent(explosion, anim);
    auto &spr = ge.ecsGetComponents<component::Sprite>()[explosion];
    auto &tex = ge.ecsGetComponents<component::Texture>()[explosion];
    spr._sprite.setTexture(tex._texture);
    component::Drawable drawable = { true };
    ge.ecsAddComponent(explosion, drawable);
    component::Transform posExplosion = { pos._posx, pos._posy, 0, 0, 0, 0, -3, 3, -3 };
    ge.ecsAddComponent(explosion, posExplosion);
    component::Velocity vel = { 0, 0, 0 };
    ge.ecsAddComponent(explosion, vel);

    gameEngine::Sound &explosionSound = ge.assetGetAsset<gameEngine::Sound>("explosionSound");
    explosionSound.setPosition(pos._posx, 0, pos._posy);
    explosionSound.play();
    return explosion;
}

void GameClient::destroyEntity(destroy_t &destroy, Entity &player)
{
    if (hasIdComponent(ge, destroy.id)) {
        Entity toDelete = ge.ecsEntityFromIndex(getFromIdComponent(ge, destroy.id));
        if (ge.ecsGetComponents<component::IsEnemy>().has(toDelete)) {
            // auto &vel = ge.ecsGetComponents<component::Velocity>()[toDelete];
            // vel._velx = 0;
            // vel._vely = 0;
            ge.ecsRemoveComponent<component::Velocity>(toDelete);
            ge.ecsRemoveComponent<component::Drawable>(toDelete);
            auto &pos = ge.ecsGetComponents<component::Transform>()[toDelete];
            auto &type = ge.ecsGetComponents<component::EnemyType>()[toDelete];
            component::ToDelete del;
            Entity explosion = createExplosion(pos);
            ge.timeSetTimeout([this, explosion, toDelete]() {
                component::ToDelete del;
                try {
                    ge.ecsAddComponent(explosion, del);
                    ge.ecsAddComponent(toDelete, del);
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                }
            }, 600);
//            if (type._type != component::EnemyType::Type::BOSS) {
//                component::ToDelete del;
//                Entity explosion = createExplosion(pos);
//                ge.timeSetTimeout([this, explosion, toDelete]() {
//                    component::ToDelete del;
//                    try {
//                        ge.ecsAddComponent(explosion, del);
//                        ge.ecsAddComponent(toDelete, del);
//                    } catch (std::exception &e) {
//                        std::cout << e.what() << std::endl;
//                    }
//                }, 600);
//            }
//            } else {
//                for (int i = 0; i < 50; i++) {
//                    component::ToDelete del;
//                    // random pos in rectangle of boss
//                    float x = (float) (rand() % (int) (260 * 3) + (pos._posx - 260 * 3));
//                    float y = (float) (rand() % (int) (142 * 3) + (pos._posy - 142 * 3));
//                    component::Transform posExplosion = { x, y, 0, 0, 0, 0, -3, 3, -3 };
//                    Entity explosion = createExplosion(posExplosion);
//                    ge.timeSetTimeout([this, explosion]() {
//                        component::ToDelete del;
//                        try {
//                            ge.ecsAddComponent(explosion, del);
//                        } catch (std::exception &e) {
//                            std::cout << e.what() << std::endl;
//                        }
//                    }, 600);
//                }
//                ge.timeSetTimeout([this, toDelete]() {
//                    component::ToDelete del;
//                    try {
//                        ge.ecsAddComponent(toDelete, del);
//                    } catch (std::exception &e) {
//                        std::cout << e.what() << std::endl;
//                    }
//                }, 600);
//            }
        } else {
            component::ToDelete del;
            if (toDelete == player)
                _rtypeIsAlive = false;
            try {
                ge.ecsAddComponent(toDelete, del);
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
}

void GameClient::updateGame(Entity &player)
{
    //update game
    net::MessageUdp<udpProtocol> msg;
    float posx = 0;
    float posy = 0;
    player_t playerCreateInfo;
    pos_t position;
    int typeEnemy;
    vel_t velocity;
    destroy_t destroy;
    while (!ge.netIncomingUdp().empty()) {
        net::OwnedMessageUdp<udpProtocol> msg = ge.netIncomingUdp().popFront();
        switch (msg.msg.header.id) {
            case udpProtocol::CreateBullet:
                msg.msg >> position;
                createBullet(position);
                break;
            case udpProtocol::PlayerMove:
                msg.msg >> velocity;
                movePlayer(velocity.id, velocity);
                break;
            case udpProtocol::CreateEnnemy:
                msg.msg >> typeEnemy;
                msg.msg >> position;
                generateEnemy(ge, position, typeEnemy);
                break;
            case udpProtocol::ConnectedPlayer:
                syncPlayer(msg);
                break;
            case udpProtocol::CreatePlayer:
                msg.msg >> playerCreateInfo;
                _myId = playerCreateInfo.id;
                playerCreation(playerCreateInfo, player, true);
                break;
            case udpProtocol::Destroy:
                msg.msg >> destroy;
                destroyEntity(destroy, player);
                break;
            case udpProtocol::Resync:
                resyncEntityWithId(msg);
                break;
            default:
                break;
        }
    }
}
