/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Server system custom
*/

#include "pongServerSystem.hpp"


void ballColisionSystemServer(GameEngine &ge,
                        SparseArray<component::Ball> &ball,
                        SparseArray<component::Border> &border,
                        SparseArray<component::Player> &player,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::ColisionBox> &colisionBox,
                        int &scorePlayer1, int &scorePlayer2)
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

                // if hit on left or right border behind a player
                if (isBorder &&
                    (ballTransform._posx < 70 ||
                    ballTransform._posx > WINDOW_WIDTH - 70)) {

                    if (ballTransform._posx < 70)
                        scorePlayer2++;
                    else
                        scorePlayer1++;
                    ballTransform._posx = WINDOW_WIDTH / 2 -10;
                    ballTransform._posy = WINDOW_HEIGHT / 2 -10;
                    ballVelocity._velx = 600;
                    ballVelocity._vely = 600;
                }
                // if hit on right
                else if (angle >= 45 && angle < 135) {
                    ballTransform._posx -= ballVelocity._velx * ge.deltaTime;
                    ballVelocity._velx = -ballVelocity._velx;
                }
                // if hit on bottom
                else if (angle >= 135 && angle < 225) {
                    ballTransform._posy -= ballVelocity._vely * ge.deltaTime;
                    ballVelocity._vely = -ballVelocity._vely;
                }
                // if hit on left
                else if (angle >= 225 && angle < 315) {
                    ballTransform._posx -= ballVelocity._velx * ge.deltaTime;
                    ballVelocity._velx = -ballVelocity._velx;
                }
                // if hit on top
                else if (angle >= 315 || angle < 45) {
                    ballTransform._posy -= ballVelocity._vely * ge.deltaTime;
                    ballVelocity._vely = -ballVelocity._vely;
                }

                // send the new ball position and velocity to the client
                pong_ball_t ballMove;
                ballMove.posx = ballTransform._posx;
                ballMove.posy = ballTransform._posy;
                ballMove.velx = ballVelocity._velx;
                ballMove.vely = ballVelocity._vely;
                net::MessageUdp<udpProtocol> msgToSend;
                msgToSend.header.id = udpProtocol::PongBallMove;
                msgToSend << ballMove;
                ge.netUdpSendAll(msgToSend);
            }
        }
    }
}
