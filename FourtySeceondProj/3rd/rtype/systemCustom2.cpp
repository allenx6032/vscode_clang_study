/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** System custom
*/

#include "systemCustom2.hpp"

void playerColisionSystem(GameEngine &ge,
                        SparseArray<component::Player> &player,
                        SparseArray<component::Border> &border,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::ColisionBox> &colisionBox)
{
    for (auto &playerEntity : player) {
        if (!player.has(playerEntity.first) || !transform.has(playerEntity.first) || !colisionBox.has(playerEntity.first))
            continue;
        auto &playerColisionBox = colisionBox[playerEntity.first];
        auto &playerTransform = transform[playerEntity.first];

        for (auto &borderEntity : border) {
            if (!border.has(borderEntity.first) || !transform.has(borderEntity.first) || !colisionBox.has(borderEntity.first))
                continue;
            auto &borderColisionBox = colisionBox[borderEntity.first];
            auto &borderTransform = transform[borderEntity.first];


            if (playerTransform._posx + playerColisionBox._width > borderTransform._posx &&
                playerTransform._posx < borderTransform._posx + borderColisionBox._width &&
                playerTransform._posy + playerColisionBox._height > borderTransform._posy &&
                playerTransform._posy < borderTransform._posy + borderColisionBox._height) {
                // calculate by how much the player is inside the border and move it back by that amount
                if (playerTransform._posy < borderTransform._posy) {
                    playerTransform._posy = borderTransform._posy - playerColisionBox._height;
                } else if (playerTransform._posy > borderTransform._posy) {
                    playerTransform._posy = borderTransform._posy + borderColisionBox._height;
                }
            }
        }
    }
}

void ballColisionSystem(GameEngine &ge,
                        SparseArray<component::Ball> &ball,
                        SparseArray<component::Border> &border,
                        SparseArray<component::Player> &player,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::ColisionBox> &colisionBox,
                        gameEngine::Sound &sound)
{
    for (auto &ballEntity : ball) {
        if (!ball.has(ballEntity.first) || !transform.has(ballEntity.first) || !colisionBox.has(ballEntity.first))
            continue;
        auto &ballColisionBox = colisionBox[ballEntity.first];
        auto &ballTransform = transform[ballEntity.first];
        auto &ballVelocity = ge.ecsGetComponents<component::Velocity>()[ballEntity.first];

        for (auto &otherEntity : transform) {
            if (!transform.has(otherEntity.first) || !colisionBox.has(otherEntity.first) || (!border.has(otherEntity.first) && !player.has(otherEntity.first)))
                continue;
            auto &otherColisionBox = colisionBox[otherEntity.first];
            auto &otherTransform = transform[otherEntity.first];
            bool isBorder = border.has(otherEntity.first);

            if (ballTransform._posx + ballColisionBox._width > otherTransform._posx &&
                ballTransform._posx < otherTransform._posx + otherColisionBox._width &&
                ballTransform._posy + ballColisionBox._height > otherTransform._posy &&
                ballTransform._posy < otherTransform._posy + otherColisionBox._height) {
                // std::cout << "colision" << std::endl;

                float ballCenterX = ballTransform._posx + ballColisionBox._width / 2;
                float ballCenterY = ballTransform._posy + ballColisionBox._height / 2;

                float borderCenterX = otherTransform._posx + otherColisionBox._width / 2;
                float borderCenterY = otherTransform._posy + otherColisionBox._height / 2;

                // calculat the angle between the ball and the border
                float angle = atan2(ballCenterY - borderCenterY, ballCenterX - borderCenterX);

                if (angle < 0)
                    angle += 2 * M_PI;

                // convert the angle to degrees
                angle = angle * RAD_TO_DEG;

                // std::cout << "angle: " << angle << std::endl;

                // if hit on left or right border behind a player
                if (isBorder &&
                    (ballTransform._posx < 70 ||
                    ballTransform._posx > WINDOW_WIDTH - 70)) {

                    ballTransform._posx = WINDOW_WIDTH / 2 -10;
                    ballTransform._posy = WINDOW_HEIGHT / 2 -10;
                    ballVelocity._velx = 600;
                    ballVelocity._vely = 600;
                }
                // if hit on right
                else if (angle >= 45 && angle < 135) {
                    ballTransform._posx -= ballVelocity._velx * ge.deltaTime;
                    ballVelocity._velx = -ballVelocity._velx;
                    // std::cout << "right" << std::endl;
                }
                // if hit on bottom
                else if (angle >= 135 && angle < 225) {
                    ballTransform._posy -= ballVelocity._vely * ge.deltaTime;
                    ballVelocity._vely = -ballVelocity._vely;
                    // std::cout << "bottom" << std::endl;
                }
                // if hit on left
                else if (angle >= 225 && angle < 315) {
                    // resolve on left
                    ballTransform._posx -= ballVelocity._velx * ge.deltaTime;
                    ballVelocity._velx = -ballVelocity._velx;
                }
                // if hit on top
                else if (angle >= 315 || angle < 45) {
                    // resolve on top
                    ballTransform._posy -= ballVelocity._vely * ge.deltaTime;
                    ballVelocity._vely = -ballVelocity._vely;
                    // std::cout << "top" << std::endl;
                }

                // play sound
                sound.setPosition(ballCenterX, 0, ballCenterY);
                sound.play();
            }
        }
    }
}

void refreshScoreSystem(GameEngine &ge,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::Score> &score,
                        SparseArray<component::Text> &text,
                        int &scorePlayer1, int &scorePlayer2)
{
    for (auto &scoreEntity : score) {
        if (!score.has(scoreEntity.first) || !transform.has(scoreEntity.first) || !text.has(scoreEntity.first))
            continue;
        auto &scoreTransform = transform[scoreEntity.first];
        auto &scoreText = text[scoreEntity.first];
        auto &scoreScore = score[scoreEntity.first];

        if (scoreScore._nb == 1) {
            scoreText._text.setString(std::to_string(scorePlayer1));
        } else if (scoreScore._nb == 2) {
            scoreText._text.setString(std::to_string(scorePlayer2));
        } else {
            std::cerr << "Error: score entity has no score" << std::endl;
        }
        scoreText._text.setPosition(scoreTransform._posx, scoreTransform._posy);
    }
}

void drawScoreSystem(GameEngine &ge,
                    SparseArray<component::Text> &text,
                    SparseArray<component::Score> &score,
                    SparseArray<component::Drawable> &drawable,
                    gameEngine::RenderWindow &window)
{
    for (auto &scoreEntity : score) {
        if (!score.has(scoreEntity.first) || !text.has(scoreEntity.first) || !drawable.has(scoreEntity.first))
            continue;
        auto &scoreText = text[scoreEntity.first];
        auto &scoreDrawable = drawable[scoreEntity.first];

        if (scoreDrawable._isDrawable)
            window.draw(scoreText._text);
    }
}
