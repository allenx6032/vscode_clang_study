/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Server system custom
*/

#include "systemServer.hpp"

void takeHitSystem(GameEngine &ge,
                    SparseArray<component::Transform> &transform,
                    SparseArray<component::ColisionBoxCustom> &colisionBox,
                    SparseArray<component::Bullet> &bullets,
                    SparseArray<component::Health> &health,
                    int &enemySpawnNumber)
{
    for (auto &bullet : bullets) {
        if (!colisionBox.has(bullet.first) || !transform.has(bullet.first))
            continue;
        auto const &col = colisionBox[bullet.first];
        auto &tra = transform[bullet.first];

        for (auto &other : colisionBox) {
            if (other.first == bullet.first || !health.has(other.first) ||
                !transform.has(other.first) || !colisionBox.has(other.first) ||
                bullets.has(other.first))
                continue;
            auto const &otherCol = colisionBox[other.first];
            auto &otherTra = transform[other.first];
            auto &otherHealth = health[other.first];

            float x1 = tra._posx + col._offsetx;
            float y1 = tra._posy + col._offsety;
            float x2 = otherTra._posx + otherCol._offsetx;
            float y2 = otherTra._posy + otherCol._offsety;

            float w1 = col._width;
            float h1 = col._height;
            float w2 = otherCol._width;
            float h2 = otherCol._height;

            if ((x1 < x2 + w2 && x1 + w1 > x2 &&
                y1 < y2 + h2 && y1 + h1 > y2) ||
                (x2 < x1 + w1 && x2 + w2 > x1 &&
                y2 < y1 + h1 && y2 + h2 > y1)) {

                otherHealth._health -= bullet.second._damage;

                try {
                    component::ToDelete del;
                    ge.ecsAddComponent(ge.ecsEntityFromIndex(bullet.first), del);

                    auto &bulletId = ge.ecsGetComponents<component::Id>()[bullet.first];
                    net::MessageUdp<udpProtocol> msgToSend;
                    destroy_t delToSend = { bulletId._id };
                    msgToSend.header.id = udpProtocol::Destroy;
                    msgToSend << delToSend;
                    ge.netUdpSendAll(msgToSend);
                } catch (std::exception &e) {
                    std::cerr << "element is already waiting for destruction" << std::endl;
                }

                if (otherHealth._health <= 0) {
                    try {
                        component::ToDelete otherDel;
                        ge.ecsAddComponent(ge.ecsEntityFromIndex(other.first), otherDel);

                        auto &otherId = ge.ecsGetComponents<component::Id>()[other.first];
                        net::MessageUdp<udpProtocol> msgToSend2;
                        destroy_t delToSend2 = { otherId._id };
                        msgToSend2.header.id = udpProtocol::Destroy;
                        msgToSend2 << delToSend2;
                        ge.netUdpSendAll(msgToSend2);

                        enemySpawnNumber++;
                    } catch (std::exception &e){
                        std::cerr << "element is already waiting for destruction" << std::endl;
                    }
                }
                break;
            }
        }
    }
}

void deleteOutOfMapBullets(GameEngine &ge,
                            SparseArray<component::Transform> &transform,
                            SparseArray<component::Bullet> &bullets)
{
    for (auto &bullet : bullets) {
        if (!transform.has(bullet.first))
            continue;
        auto &tra = transform[bullet.first];

        if (tra._posx < 0 || tra._posx > WINDOW_WIDTH || tra._posy < 0 || tra._posy > WINDOW_HEIGHT) {
            try {
                component::ToDelete del;
                ge.ecsAddComponent(ge.ecsEntityFromIndex(bullet.first), del);

                auto &bulletId = ge.ecsGetComponents<component::Id>()[bullet.first];
                net::MessageUdp<udpProtocol> msgToSend;
                destroy_t delToSend = { bulletId._id };
                msgToSend.header.id = udpProtocol::Destroy;
                msgToSend << delToSend;
                ge.netUdpSendAll(msgToSend);
            } catch (std::exception &e) {
                std::cerr << "element is already waiting for destruction" << std::endl;
            }
        }
    }
}

void enemyHitPlayerSystem(GameEngine &ge,
                        SparseArray<component::Transform> &transform,
                        SparseArray<component::ColisionBoxCustom> &colisionBox)
{
    for (auto &entity : colisionBox) {
        if (!colisionBox.has(entity.first) || !transform.has(entity.first))
            continue;
        auto const &col = colisionBox[entity.first];
        auto &tra = transform[entity.first];

        if (col._layer != component::ColisionBoxCustom::Layer::PLAYER)
            continue;

        for (auto &other : colisionBox) {
            if (other.first == entity.first || !transform.has(other.first) || !colisionBox.has(other.first))
                continue;
            auto const &otherCol = colisionBox[other.first];
            auto &otherTra = transform[other.first];

            if (otherCol._layer != component::ColisionBoxCustom::Layer::ENEMY &&
                otherCol._layer != component::ColisionBoxCustom::Layer::OBSTACLE)
                continue;

            float x1 = tra._posx + col._offsetx;
            float y1 = tra._posy + col._offsety;
            float x2 = otherTra._posx + otherCol._offsetx;
            float y2 = otherTra._posy + otherCol._offsety;

            float w1 = col._width;
            float h1 = col._height;
            float w2 = otherCol._width;
            float h2 = otherCol._height;

            if ((x1 < x2 + w2 && x1 + w1 > x2 &&
                y1 < y2 + h2 && y1 + h1 > y2) ||
                (x2 < x1 + w1 && x2 + w2 > x1 &&
                y2 < y1 + h1 && y2 + h2 > y1)) {

                try {
                    component::ToDelete del;
                    ge.ecsAddComponent(ge.ecsEntityFromIndex(entity.first), del);

                    auto &entityId = ge.ecsGetComponents<component::Id>()[entity.first];
                    net::MessageUdp<udpProtocol> msgToSend;
                    destroy_t delToSend = { entityId._id };
                    msgToSend.header.id = udpProtocol::Destroy;
                    msgToSend << delToSend;
                    ge.netUdpSendAll(msgToSend);
                } catch (std::exception &e) {
                    std::cerr << "element is already waiting for destruction" << std::endl;
                }
                break;
            }
        }
    }
}
