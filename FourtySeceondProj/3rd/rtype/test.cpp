/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#include "gameEngine.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

#define SECOND_IN_MS 1000
#define FRAMERATE 60
#define ENTITY_COUNT 1000
#define MAX_SPEED 3000
#define PLAYER_SIZE 50
#define ENTITY_SIZE 5
#define MAX_RGBA_VALUE 255
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define HELLO_WORLD_INTERVAL 100
#define WALL_COLLISION_SIZE 100
#define ENTITY_SPAWN_OFFSET 10
#define MAX_ENTITY_VEL 600

#include "sfml/SFML_Graphics.hpp"

int jump(lua_State *L)
{
    int jumpTime = 0;
    LuaManager::luaGetArgument(L, jumpTime);
    std::cout << "Jumping during " << jumpTime << "ms..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(jumpTime));
    std::cout << "End of jump!" << std::endl;
    LuaManager::luaSendResult(L, jumpTime);
    return 1;
}

void luaTest(GameEngine &ge)
{
    // load lua file
    ge.luaLoadFile("testingFile/test.lua");

    // add C++ function to lua so it can be called from lua
    ge.luaAddCppFunction("testingFile/test.lua", "jump", jump);

    // call lua function
    // function myJump()
    //     print("jump() called from C++")
    //     jump()
    //     print("I Jumped!")
    // end
    ge.luaCallFunction("testingFile/test.lua", "myJump", 0);
    std::cout << std::endl;

    // call lua function with arguments but without return value
    // function myPrint(str, num)
    //     print("myPrint() called from C++")
    //     for i = 1, num do
    //         print(str)
    //     end
    // end
    ge.luaCallFunction("testingFile/test.lua", "myPrint", 0, std::string("Hello world from C++"), 4);
    std::cout << std::endl;

    // call lua function with arguments and return value
    // function myAdd(a, b)
    //     print("myAdd() called from C++")
    //     return a + b
    // end
    int result;
    ge.luaCallFunction("testingFile/test.lua", "myAdd", 1, 4, 3);
    ge.luaGetReturnValue("testingFile/test.lua", result);
    std::cout << "Result: " << result << std::endl;
    std::cout << std::endl;

    // call lua function without arguments but with return value
    // function myGetValue()
    //     print("myGetValue() called from C++")
    //     return 123
    // end
    ge.luaCallFunction("testingFile/test.lua", "myGetValue", 1);
    ge.luaGetReturnValue("testingFile/test.lua", result);
    std::cout << "Result: " << result << std::endl;
    std::cout << std::endl;

    // call lua function without arguments but with multiple return value
    // function myGetValues()
    //     print("myGetValues() called from C++")
    //     return 1, 2, 3
    // end
    int result2, result3;
    ge.luaCallFunction("testingFile/test.lua", "myGetValues", 3);
    ge.luaGetReturnValue("testingFile/test.lua", result, result2, result3);
    std::cout << "Result: " << result << ", " << result2 << ", " << result3 << std::endl;
    std::cout << std::endl;

    // test passing table (map)
    // function myPrintTable(t)
    //     print("myPrintTable()")
    //     for k, v in pairs(t) do
    //         print(k, " = ", v)
    //     end
    // end
    LUA_TABLE_MAP_TYPE myMap;
    const int randomInt = 123;
    const float randomFloat = 123.456f;
    const double randomDouble = 123.456;
    myMap["str"] = std::string("Hello world");
    myMap["int"] = randomInt;
    myMap["float"] = randomFloat;
    myMap["double"] = randomDouble;
    myMap["bool"] = true;
    ge.luaCallFunction("testingFile/test.lua", "myPrintTable", 0, myMap);
    std::cout << std::endl;

    // test passing table (array)
    // function myPrintTable(t)
    //     print("myPrintTable()")
    //     for k, v in pairs(t) do
    //         print(k, " = ", v)
    //     end
    // end
    LUA_TABLE_VECTOR_TYPE myVector;
    myVector.push_back(std::string("Hello world"));
    myVector.push_back(randomInt);
    myVector.push_back(randomFloat);
    myVector.push_back(randomDouble);
    myVector.push_back(true);
    ge.luaCallFunction("testingFile/test.lua", "myPrintTable", 0, myVector);
    std::cout << std::endl;

    // test getting table (map)
    // function myGetTable()
    //     print("myGetTable()")
    //     return 56, {str = "hello", num = 123, bool = true}, 3, 18, 72
    // end
    const int myGetTableNbOfReturnValue = 5;
    ge.luaCallFunction("testingFile/test.lua", "myGetTable", myGetTableNbOfReturnValue);
    LUA_TABLE_MAP_TYPE myMap2;
    int result4, result5;
    ge.luaGetReturnValue("testingFile/test.lua", result5, myMap2, result2, result3, result4);
    ge.luaCallFunction("testingFile/test.lua", "myPrintTable", 0, myMap2);
    std::cout << "Result: " << result2 << ", " << result3 << ", " << result4 << ", " << result5 << std::endl;
    std::cout << std::endl;

    // test getting table (array)
    // function myGetArray()
    //     print("myGetArray()")
    //     return 56, {"hello", 123, true}, 3, 18, 72
    // end
    ge.luaCallFunction("testingFile/test.lua", "myGetArray", myGetTableNbOfReturnValue);
    LUA_TABLE_VECTOR_TYPE myVector2;
    ge.luaGetReturnValue("testingFile/test.lua", result5, myVector2, result2, result3, result4);
    ge.luaCallFunction("testingFile/test.lua", "myPrintTable", 0, myVector2);
    std::cout << "Result: " << result2 << ", " << result3 << ", " << result4 << ", " << result5 << std::endl;
    std::cout << std::endl;

    return;
}

void jsonTest(GameEngine &ge)
{
    ge.jsonLoadFile("testingFile/test.json");

    nlohmann::json &jsonData = ge.jsonGetFile("testingFile/test.json");

    std::cout << "name: " << jsonData["name"] << std::endl;
    std::cout << "image: " << jsonData["image"] << std::endl;
    std::cout << "FrameSize: " << jsonData["frames"].size() << std::endl;
    std::cout << "Frames: " << std::endl;
    for (auto &frame : jsonData["frames"]) {
        if (!frame["x"].is_number_integer() ||
            !frame["y"].is_number_integer() ||
            !frame["width"].is_number_integer() ||
            !frame["height"].is_number_integer())
            continue;
        std::cout << "    width:  " << frame["width"] << std::endl;
        std::cout << "    height: " << frame["height"] << std::endl;
        std::cout << "    x:      " << frame["x"] << std::endl;
        std::cout << "    y:      " << frame["y"] << std::endl;
        std::cout << std::endl;
    }

    std::cout << "name: " << ge.jsonGetValue<std::string>("testingFile/test.json", "name") << std::endl;
    std::cout << "image: " << ge.jsonGetValue<std::string>("testingFile/test.json", "image") << std::endl;
    std::cout << "FrameSize: " << ge.jsonGetValue<std::vector<nlohmann::json>>("testingFile/test.json", "frames").size() << std::endl;
    std::cout << "Frames: " << std::endl;
    for (auto &frame : ge.jsonGetValue<std::vector<nlohmann::json>>("testingFile/test.json", "frames")) {
        try {
            std::cout << "    width:  " << ge.jsonGetValue<int>(frame, "width") << std::endl;
            std::cout << "    height: " << ge.jsonGetValue<int>(frame, "height") << std::endl;
            std::cout << "    x:      " << ge.jsonGetValue<int>(frame, "x") << std::endl;
            std::cout << "    y:      " << ge.jsonGetValue<int>(frame, "y") << std::endl;
            std::cout << std::endl;
        }
        catch (gameEngine::json::JsonKeyNotFound &e) {
            std::cerr << "    " << e.what() << std::endl;
        }
    }

    return;
}

void test()
{
    component::Texture text2("Client/sprites/r-typesheet43.png");
    sf::IntRect rect(0, 0, ENTITY_SIZE, ENTITY_SIZE);
    sf::IntRect myRect(0, 0, PLAYER_SIZE, PLAYER_SIZE);
    component::Sprite sprite(myRect);
    component::Drawable drawable = { true };
    component::Transform spritePos = { 0, 0, 0, 0, 0, 0, 1, 1, 1 };
    component::Velocity vel = { 0, 0, 0 };
    component::ColisionBox col = { PLAYER_SIZE, PLAYER_SIZE, 0 };
    component::Unmovable unmovable = { true };

    gameEngine::Listener::setPosition(WINDOW_WIDTH / 2, 0, WINDOW_HEIGHT / 2);

    // create game engine
    GameEngine ge;

    jsonTest(ge);
    luaTest(ge);

    ge.ecsRegisterComponent<component::Sprite>();
    ge.ecsRegisterComponent<component::Texture>();
    ge.ecsRegisterComponent<component::Drawable>();
    ge.ecsRegisterComponent<component::Transform>();
    ge.ecsRegisterComponent<component::Velocity>();
    ge.ecsRegisterComponent<component::ColisionBox>();
    ge.ecsRegisterComponent<component::Unmovable>();
    // ge.ecsRegisterComponent<component::mass>();
    ge.ecsRegisterComponent<component::ToDelete>();
    ge.ecsRegisterComponent<component::Animation>();

    Entity entity1 = ge.ecsSpawnEntity();

    ge.ecsAddComponent(entity1, sprite);
    ge.ecsAddComponent(entity1, text2);
    ge.ecsAddComponent(entity1, drawable);
    ge.ecsAddComponent(entity1, spritePos);
    ge.ecsAddComponent(entity1, vel);
    ge.ecsAddComponent(entity1, col);
    ge.ecsAddComponent(entity1, unmovable);
    // component::mass mass = { 5000 };
    // ge.ecsAddComponent(entity1, mass);

    component::Animation anim("testingFile/test.json", sf::Time(sf::seconds(0.05)), true);
    ge.ecsAddComponent(entity1, anim);

    // generate 1000 entities
    srand(time(NULL));
    for (int i = 0; i < ENTITY_COUNT; i++) {
        // std::cout << "Creating entity " << i << std::endl;
        Entity entity = ge.ecsSpawnEntity();
        component::Sprite spriteTMP(rect);
        ge.ecsAddComponent(entity, spriteTMP);
        component::Texture text(rand() % MAX_RGBA_VALUE, rand() % MAX_RGBA_VALUE, rand() % MAX_RGBA_VALUE);
        ge.ecsAddComponent(entity, text);
        ge.ecsAddComponent(entity, drawable);
        component::Transform pos = { (float)((rand() % (WINDOW_WIDTH - (ENTITY_SPAWN_OFFSET * 2))) + ENTITY_SPAWN_OFFSET), (float)((rand() % (WINDOW_HEIGHT - (ENTITY_SPAWN_OFFSET * 2))) + ENTITY_SPAWN_OFFSET), 0, 0, 0, 0, 1, 1, 1 };
        ge.ecsAddComponent(entity, pos);
        component::Velocity velTMP = { (float)((rand() % MAX_ENTITY_VEL) + 1), (float)((rand() % MAX_ENTITY_VEL) + 1), 0 };
        // component::velocity velTMP = { 0, 0, 0 };
        ge.ecsAddComponent(entity, velTMP);
        component::ColisionBox colTMP = { ENTITY_SIZE, ENTITY_SIZE, 0 };
        ge.ecsAddComponent(entity, colTMP);
        // component::mass massTMP = { 0.5 };
        // ge.ecsAddComponent(entity, massTMP);
    }

    //border entities
    Entity entityWallLeft = ge.ecsSpawnEntity();
    component::Transform posWallLeft = { -WALL_COLLISION_SIZE, 0, 0, 0, 0, 0, 1, 1, 1 };
    component::ColisionBox colWallLeft = { WALL_COLLISION_SIZE, WINDOW_HEIGHT, 0 };
    ge.ecsAddComponent(entityWallLeft, posWallLeft);
    ge.ecsAddComponent(entityWallLeft, colWallLeft);
    ge.ecsAddComponent(entityWallLeft, unmovable);

    Entity entityWallRight = ge.ecsSpawnEntity();
    component::Transform posWallRight = { WINDOW_WIDTH, 0, 0, 0, 0, 0, 1, 1, 1 };
    component::ColisionBox colWallRight = { WALL_COLLISION_SIZE, WINDOW_HEIGHT, 0 };
    ge.ecsAddComponent(entityWallRight, posWallRight);
    ge.ecsAddComponent(entityWallRight, colWallRight);
    ge.ecsAddComponent(entityWallRight, unmovable);

    Entity entityWallTop = ge.ecsSpawnEntity();
    component::Transform posWallTop = { 0, -WALL_COLLISION_SIZE, 0, 0, 0, 0, 1, 1, 1 };
    component::ColisionBox colWallTop = { WINDOW_WIDTH, WALL_COLLISION_SIZE, 0 };
    ge.ecsAddComponent(entityWallTop, posWallTop);
    ge.ecsAddComponent(entityWallTop, colWallTop);
    ge.ecsAddComponent(entityWallTop, unmovable);

    Entity entityWallBottom = ge.ecsSpawnEntity();
    component::Transform posWallBottom = { 0, WINDOW_HEIGHT, 0, 0, 0, 0, 1, 1, 1 };
    component::ColisionBox colWallBottom = { WINDOW_WIDTH, WALL_COLLISION_SIZE, 0 };
    ge.ecsAddComponent(entityWallBottom, posWallBottom);
    ge.ecsAddComponent(entityWallBottom, colWallBottom);
    ge.ecsAddComponent(entityWallBottom, unmovable);

    float maxSPEEEEEEEEEEEEED = MAX_SPEED;
    float minSPEEEEEEEEEEEEED = -MAX_SPEED;
    ge.ecsRunSingleSystem<component::Sprite, component::Texture>(loadSpriteTexture);

    // ge.ecsAddSystem<component::Transform,
    //                 component::Velocity,
    //                 component::Mass,
    //                 component::Unmovable>(gravitySystem);
    ge.ecsAddSystem<component::Transform,
                    component::Velocity>(updatePosSystem);
    // ge.ecsAddSystem<component::Transform,
    //                 component::ColisionBox,
    //                 component::Velocity,
    //                 component::Unmovable>(colisionSystem);
    ge.ecsAddSystem<component::Transform,
                    component::Sprite>(refreshSpriteSystem);
    ge.ecsAddSystem<component::Animation,
                    component::Sprite>(animationSystem);

    // sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");
    // ge.createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SFML window");
    gameEngine::RenderWindow window(gameEngine::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");
    ge.ecsAddSystem<component::Sprite,
                    component::Drawable>(drawSprite, window);
    std::function<void()> removeSystem = nullptr;

    // int count = 0;
    // auto removeTick = ge.timeSetInterval([&count](){
    //     std::cout << "Hello world every 0.1 second: " << count++ << std::endl;
    // }, HELLO_WORLD_INTERVAL);
    // ge.timeStartTick();

    gameEngine::Sound sound("testingFile/shoot.wav");
    sound.setVolume(100);
    sound.setMinDistance(1);
    sound.setAttenuation(0.1);
    sound.setPitch(1);
    while (window.isOpen())
    {
        std::cout << "Delta time: " << (int)(ge.deltaTime * SECOND_IN_MS) << "ms" << std::endl;
        std::cout << "FPS: " << (1 / ge.deltaTime) << std::endl;
        auto &curVel = ge.ecsGetComponents<component::Velocity>()[entity1];
        auto &curPos = ge.ecsGetComponents<component::Transform>()[entity1];
        auto timeStartTick = std::chrono::high_resolution_clock::now();
        gameEngine::Event event;
        while (window.pollEvent(event)) // event loop
        {
            if (event.type == gameEngine::Event::Closed)
                window.close();
            if (event.type == gameEngine::Event::KeyPressed && event.key.code == gameEngine::Keyboard::Space) {
                if (removeSystem) {
                    removeSystem();
                    removeSystem = nullptr;
                }
                else
                    removeSystem = ge.ecsAddSystem<component::Transform,
                                                component::ColisionBox,
                                                component::Velocity,
                                                component::Unmovable>(colisionSystem);
            }
            // if (event.type == gameEngine::Event::KeyPressed && event.key.code == gameEngine::Keyboard::A) {
            //     if (removeTick) {
            //         removeTick();
            //         removeTick = nullptr;
            //     }
            //     else {
            //         ge.timeStopTick();
            //         removeTick = ge.timeSetInterval([&count](){
            //             std::cout << "Hello world every 0.1 second: " << count++ << std::endl;
            //         }, HELLO_WORLD_INTERVAL);
            //         ge.timeStartTick();
            //     }
            // }
            if (event.type == gameEngine::Event::KeyPressed && event.key.code == gameEngine::Keyboard::M) {
                sound.setPosition(curPos._posx, 0, curPos._posy);
                sound.play();
            }
        }
        if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Right))
            curVel._velx = std::min(curVel._velx + 60, maxSPEEEEEEEEEEEEED);
        else if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Left))
            curVel._velx = std::max(curVel._velx - 60, minSPEEEEEEEEEEEEED);
        else if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Up))
            curVel._vely = std::max(curVel._vely - 60, minSPEEEEEEEEEEEEED);
        else if (gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Down))
            curVel._vely = std::min(curVel._vely + 60, maxSPEEEEEEEEEEEEED);
        else {
            curVel._velx = (curVel._velx > 0 ? curVel._velx - 60 : (curVel._velx < 0 ? curVel._velx + 60 : 0));
            curVel._vely = (curVel._vely > 0 ? curVel._vely - 60 : (curVel._vely < 0 ? curVel._vely + 60 : 0));
        }

        window.clear();
        ge.ecsRunSystems();
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - timeStartTick);
        if (duration.count() < SECOND_IN_MS / FRAMERATE)
            std::this_thread::sleep_for(std::chrono::milliseconds(SECOND_IN_MS / FRAMERATE - duration.count()));
        window.display();
    }

    std::cout << "Hello Lenny ! Gars !" << std::endl;
}
