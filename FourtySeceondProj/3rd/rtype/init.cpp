/*
** EPITECH PROJECT, 2023
** init
** File description:
** init
*/

#include "init.hpp"

void setUpComponents(GameEngine &ge)
{
    ge.ecsRegisterComponent<component::Id>();
    ge.ecsRegisterComponent<component::Sprite>();
    ge.ecsRegisterComponent<component::Texture>();
    ge.ecsRegisterComponent<component::Drawable>();
    ge.ecsRegisterComponent<component::Transform>();
    ge.ecsRegisterComponent<component::Velocity>();
    ge.ecsRegisterComponent<component::ColisionBoxCustom>();
    ge.ecsRegisterComponent<component::Unmovable>();
    ge.ecsRegisterComponent<component::Paralax>();
    ge.ecsRegisterComponent<component::OutlineBox2D>();
    ge.ecsRegisterComponent<component::Bullet>();
    ge.ecsRegisterComponent<component::Health>();
    ge.ecsRegisterComponent<component::ToDelete>();
    ge.ecsRegisterComponent<component::IsEnemy>();
    ge.ecsRegisterComponent<component::EnemyType>();
    ge.ecsRegisterComponent<component::Animation>();
    ge.ecsRegisterComponent<component::hasTouch>();
}

size_t getFromIdComponent(GameEngine &ge, size_t id)
{
    auto &ids = ge.ecsGetComponents<component::Id>();
    for (auto &entity : ids)
        if (entity.second._id == id)
            return entity.first;
    throw std::runtime_error("id not found");
}
//get Component from id : Entity tmp = ge.ecsEntityFromIndex(getFromIdComponent(ge, 1));


bool hasIdComponent(GameEngine &ge, size_t id)
{
    auto &ids = ge.ecsGetComponents<component::Id>();
    for (auto &entity : ids)
        if (entity.second._id == id)
            return true;
    return false;
}

void initLobbyScreen(GameEngine &ge)
{
//     Entity tmp = ge.ecsSpawnEntity();
//     component::Drawable drawable { true };
//     component::Sprite sprite(sf::IntRect(0, 0, 1920, 1080));
//     component::Texture texture("Ui/BG.png");
//     ge.ecsAddComponent(tmp, drawable);
//     ge.ecsAddComponent(tmp, sprite);
//     ge.ecsAddComponent(tmp, texture);

    Entity window = ge.ecsSpawnEntity();
    component::Drawable drawableWindow { true };
    component::Sprite spriteWindow(sf::IntRect(0, 0, 940, 1080));
    component::Texture textureWindow("Ui/Window.png");
    component::Transform transformWindow {575, 100, 0, 0, 0, 0, 0.8, 0.8, 1};
    ge.ecsAddComponent(window, drawableWindow);
    ge.ecsAddComponent(window, spriteWindow);
    ge.ecsAddComponent(window, textureWindow);
    ge.ecsAddComponent(window, transformWindow);
}

Entity newLobby(GameEngine &ge, float posx, float posy, size_t lobbyId)
{
    std::cout << "new lobby\n";
    std::cout << "pos x : " << posx << " pos y : " << posy << std::endl;
    Entity tmp = ge.ecsSpawnEntity();
    component::Drawable drawable { true };
    component::Sprite sprite(sf::IntRect(0, 0, 361, 101));
    component::Texture texture("Ui/Table.png");
    component::Transform transform {posx, posy, 0, 0, 0, 0, 2, 1, 1};
    ge.ecsAddComponent(tmp, drawable);
    ge.ecsAddComponent(tmp, sprite);
    ge.ecsAddComponent(tmp, texture);
    ge.ecsAddComponent(tmp, transform);
    ge.ecsRunSingleSystem<component::Sprite, component::Texture>(loadSpriteTexture);
    return tmp;
}

Entity initButton(GameEngine &ge, std::string path, float posx, float posy, float scalex, float scaley)
{
    Entity tmp = ge.ecsSpawnEntity();
    component::Drawable drawable { true };
    component::Sprite sprite(sf::IntRect(0, 0, 210, 210));
    component::Texture texture(path);
    component::Transform transform {posx, posy, 0, 0, 0, 0, scalex, scaley, 1};
    ge.ecsAddComponent(tmp, drawable);
    ge.ecsAddComponent(tmp, sprite);
    ge.ecsAddComponent(tmp, texture);
    ge.ecsAddComponent(tmp, transform);
    return tmp;
}