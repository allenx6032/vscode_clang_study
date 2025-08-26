/*
** EPITECH PROJECT, 2023
** gameClient
** File description:
** game
*/

#include "entityCreation.hpp"
#include "componentCustom2.hpp"

Entity createBall(GameEngine &ge, bool isServer)
{
    Entity ball = ge.ecsSpawnEntity();
    component::Transform ballTransform { WINDOW_WIDTH / 2 -10, WINDOW_HEIGHT / 2 -10, 0,
                                        0, 0, 0,
                                        1, 1, 1 };
    component::Velocity ballVelocity { 600, 600, 0 };
    component::ColisionBox ballCollider { 20, 20, 20};
    component::Ball ballTag;
    ge.ecsAddComponent(ball, ballTransform);
    ge.ecsAddComponent(ball, ballVelocity);
    ge.ecsAddComponent(ball, ballCollider);
    ge.ecsAddComponent(ball, ballTag);

    if (!isServer) {
        gameEngine::IntRect ballRect(0, 0, 20, 20);
        component::Sprite ballSprite(ballRect);
        component::Texture ballTexture(255, 0, 0, 255);
        component::Drawable ballDrawable { true };
        ge.ecsAddComponent(ball, ballSprite);
        ge.ecsAddComponent(ball, ballTexture);
        ge.ecsAddComponent(ball, ballDrawable);
    }

    return ball;
}

Entity createPlayerLeft(GameEngine &ge, bool isServer)
{
    Entity player = ge.ecsSpawnEntity();
    component::Transform playerTransform { 60, WINDOW_HEIGHT / 2 - 75, 0,
                                            0, 0, 0,
                                            1, 1, 1 };
    component::Velocity playerVelocity { 0, 0, 0 };
    component::ColisionBox playerCollider { 20, 150, 20};
    component::Player playerTag;
    ge.ecsAddComponent(player, playerTransform);
    ge.ecsAddComponent(player, playerVelocity);
    ge.ecsAddComponent(player, playerCollider);
    ge.ecsAddComponent(player, playerTag);

    if (!isServer) {
        gameEngine::IntRect playerRect(0, 0, 20, 150);
        component::Sprite playerSprite(playerRect);
        component::Texture playerTexture(255, 255, 255, 255);
        component::Drawable playerDrawable { true };
        ge.ecsAddComponent(player, playerSprite);
        ge.ecsAddComponent(player, playerTexture);
        ge.ecsAddComponent(player, playerDrawable);
    }

    return player;
}

Entity createPlayerRight(GameEngine &ge, bool isServer)
{
    Entity player = ge.ecsSpawnEntity();
    component::Transform playerTransform { WINDOW_WIDTH - 80, WINDOW_HEIGHT / 2 - 75, 0,
                                            0, 0, 0,
                                            1, 1, 1 };
    component::Velocity playerVelocity { 0, 0, 0 };
    component::ColisionBox playerCollider { 20, 150, 20};
    component::Player playerTag;
    ge.ecsAddComponent(player, playerTransform);
    ge.ecsAddComponent(player, playerVelocity);
    ge.ecsAddComponent(player, playerCollider);
    ge.ecsAddComponent(player, playerTag);


    if (!isServer) {
        gameEngine::IntRect playerRect(0, 0, 20, 150);
        component::Sprite playerSprite(playerRect);
        component::Texture playerTexture(255, 255, 255, 255);
        component::Drawable playerDrawable { true };
        ge.ecsAddComponent(player, playerSprite);
        ge.ecsAddComponent(player, playerTexture);
        ge.ecsAddComponent(player, playerDrawable);
    }

    return player;
}

std::vector<Entity> createBorder(GameEngine &ge, bool isServer)
{

    // Border top
    Entity borderTop = ge.ecsSpawnEntity();
    component::Transform borderTopTransform { 20, 20, 0,
                                            0, 0, 0,
                                            1, 1, 1 };
    component::Velocity borderTopVelocity { 0, 0, 0 };
    component::ColisionBox borderTopCollider { WINDOW_WIDTH - 40, 20, 20};
    component::Border borderTopTag;
    ge.ecsAddComponent(borderTop, borderTopTransform);
    ge.ecsAddComponent(borderTop, borderTopVelocity);
    ge.ecsAddComponent(borderTop, borderTopCollider);
    ge.ecsAddComponent(borderTop, borderTopTag);

    if (!isServer) {
        gameEngine::IntRect borderTopRect(0, 0, WINDOW_WIDTH - 40, 20);
        component::Sprite borderTopSprite(borderTopRect);
        component::Texture borderTopTexture(255, 255, 255, 255);
        component::Drawable borderTopDrawable { true };
        ge.ecsAddComponent(borderTop, borderTopSprite);
        ge.ecsAddComponent(borderTop, borderTopTexture);
        ge.ecsAddComponent(borderTop, borderTopDrawable);
    }

    // Border bottom
    Entity borderBottom = ge.ecsSpawnEntity();
    component::Transform borderBottomTransform { 20, WINDOW_HEIGHT - 40, 0,
                                            0, 0, 0,
                                            1, 1, 1 };
    component::Velocity borderBottomVelocity { 0, 0, 0 };
    component::ColisionBox borderBottomCollider { WINDOW_WIDTH - 40, 20, 20};
    component::Border borderBottomTag;
    ge.ecsAddComponent(borderBottom, borderBottomTransform);
    ge.ecsAddComponent(borderBottom, borderBottomVelocity);
    ge.ecsAddComponent(borderBottom, borderBottomCollider);
    ge.ecsAddComponent(borderBottom, borderBottomTag);

    if (!isServer) {
        gameEngine::IntRect borderBottomRect(0, 0, WINDOW_WIDTH - 40, 20);
        component::Sprite borderBottomSprite(borderBottomRect);
        component::Texture borderBottomTexture(255, 255, 255, 255);
        component::Drawable borderBottomDrawable { true };
        ge.ecsAddComponent(borderBottom, borderBottomSprite);
        ge.ecsAddComponent(borderBottom, borderBottomTexture);
        ge.ecsAddComponent(borderBottom, borderBottomDrawable);
    }

    // Border left
    Entity borderLeft = ge.ecsSpawnEntity();
    component::Transform borderLeftTransform { 20, 20, 0,
                                            0, 0, 0,
                                            1, 1, 1 };
    component::Velocity borderLeftVelocity { 0, 0, 0 };
    component::ColisionBox borderLeftCollider { 20, WINDOW_HEIGHT - 40, 20};
    component::Border borderLeftTag;
    ge.ecsAddComponent(borderLeft, borderLeftTransform);
    ge.ecsAddComponent(borderLeft, borderLeftVelocity);
    ge.ecsAddComponent(borderLeft, borderLeftCollider);
    ge.ecsAddComponent(borderLeft, borderLeftTag);

    if (!isServer) {
        gameEngine::IntRect borderLeftRect(0, 0, 20, WINDOW_HEIGHT - 40);
        component::Sprite borderLeftSprite(borderLeftRect);
        component::Texture borderLeftTexture(255, 255, 255, 255);
        component::Drawable borderLeftDrawable { true };
        ge.ecsAddComponent(borderLeft, borderLeftSprite);
        ge.ecsAddComponent(borderLeft, borderLeftTexture);
        ge.ecsAddComponent(borderLeft, borderLeftDrawable);
    }

    // Border right
    Entity borderRight = ge.ecsSpawnEntity();
    component::Transform borderRightTransform { WINDOW_WIDTH - 40, 20, 0,
                                            0, 0, 0,
                                            1, 1, 1 };
    component::Velocity borderRightVelocity { 0, 0, 0 };
    component::ColisionBox borderRightCollider { 20, WINDOW_HEIGHT - 40, 20};
    component::Border borderRightTag;
    ge.ecsAddComponent(borderRight, borderRightTransform);
    ge.ecsAddComponent(borderRight, borderRightVelocity);
    ge.ecsAddComponent(borderRight, borderRightCollider);
    ge.ecsAddComponent(borderRight, borderRightTag);

    if (!isServer) {
        gameEngine::IntRect borderRightRect(0, 0, 20, WINDOW_HEIGHT - 40);
        component::Sprite borderRightSprite(borderRightRect);
        component::Texture borderRightTexture(255, 255, 255, 255);
        component::Drawable borderRightDrawable { true };
        ge.ecsAddComponent(borderRight, borderRightSprite);
        ge.ecsAddComponent(borderRight, borderRightTexture);
        ge.ecsAddComponent(borderRight, borderRightDrawable);
    }

    std::vector<Entity> borders = { borderTop, borderBottom, borderLeft, borderRight };
    return borders;
}

std::vector<Entity> createScore(GameEngine &ge, gameEngine::Font &font)
{
    Entity scorePlayer1 = ge.ecsSpawnEntity();
    component::Transform scorePlayer1Transform { (WINDOW_WIDTH / 4) * 1, 50, 0,
                                                0, 0, 0,
                                                1, 1, 1 };
    component::Drawable scorePlayer1Drawable { true };
    gameEngine::Text scorePlayer1Text(font, "0", 50);
    component::Text scorePlayer1TextComponent { scorePlayer1Text };
    component::Score scorePlayer1Tag = { 1 };
    ge.ecsAddComponent(scorePlayer1, scorePlayer1Transform);
    ge.ecsAddComponent(scorePlayer1, scorePlayer1Drawable);
    ge.ecsAddComponent(scorePlayer1, scorePlayer1TextComponent);
    ge.ecsAddComponent(scorePlayer1, scorePlayer1Tag);

    Entity scorePlayer2 = ge.ecsSpawnEntity();
    component::Transform scorePlayer2Transform { (WINDOW_WIDTH / 4) * 3, 50, 0,
                                                0, 0, 0,
                                                1, 1, 1 };
    component::Drawable scorePlayer2Drawable { true };
    gameEngine::Text scorePlayer2Text(font, "0", 50);
    component::Text scorePlayer2TextComponent { scorePlayer2Text };
    component::Score scorePlayer2Tag = { 2 };
    ge.ecsAddComponent(scorePlayer2, scorePlayer2Transform);
    ge.ecsAddComponent(scorePlayer2, scorePlayer2Drawable);
    ge.ecsAddComponent(scorePlayer2, scorePlayer2TextComponent);
    ge.ecsAddComponent(scorePlayer2, scorePlayer2Tag);

    std::vector<Entity> scores = { scorePlayer1, scorePlayer2 };

    return scores;
}

void createDottedLine(GameEngine &ge)
{
    // create multiple entity as the border (without the tag and colision) to create a dotted line in the middle of the screen
    for (int i = 30; i < WINDOW_HEIGHT - 40; i += 80) {
        Entity dottedLine = ge.ecsSpawnEntity();
        component::Transform dottedLineTransform { WINDOW_WIDTH / 2 - 5, (float)i, 0,
                                                0, 0, 0,
                                                1, 1, 1 };
        component::Drawable dottedLineDrawable { true };
        gameEngine::IntRect dottedLineRect(0, 0, 10, 60);
        component::Sprite dottedLineSprite(dottedLineRect);
        component::Texture dottedLineTexture(255, 255, 255, 255);
        ge.ecsAddComponent(dottedLine, dottedLineTransform);
        ge.ecsAddComponent(dottedLine, dottedLineDrawable);
        ge.ecsAddComponent(dottedLine, dottedLineSprite);
        ge.ecsAddComponent(dottedLine, dottedLineTexture);
    }
}
