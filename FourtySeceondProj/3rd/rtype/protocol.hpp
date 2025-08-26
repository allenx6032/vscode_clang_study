// Protocol for the network library
#pragma once

#include "common.hpp"

enum class tcpProtocol : uint8_t
{
    Udp,
    StartRoom,
    SetName,
    LobbyCreate,
    LobbyJoin,
    LobbyLeave,
    LobbyStart,
    LobbySetName,
    LobbyChangeGame,
    LobbyRemoved,

    LobbyCreated,
    LobbyJoined,
    LobbyLeft,
    LobbyStarted,
    LobbyNameSet,
    LobbySetMap,
};

enum class udpProtocol : uint8_t
{
    ConnectedPlayer,
    CreatePlayer,
    CreateEnnemy,
    CreateBullet,
    Destroy,
    PlayerMove,
    Resync,

    PongPlayerAskMove,
    PongPlayerMove,
    PongBallMove,
    PongScore,
    PongResync,
};

// Pong udp protocol
typedef struct {
    int move;
    size_t id;
} pong_player_move_ask_t;

typedef struct {
    float posy;
    size_t id;
} pong_player_resync_t;

typedef struct {
    float vely;
    size_t id;
} pong_player_move_t;

typedef struct {
    float posx;
    float posy;
    float velx;
    float vely;
} pong_ball_t;

typedef struct {
    int scorePlayer1;
    int scorePlayer2;
} pong_score_t;

// R-Type udp protocol
typedef struct {
    float posx;
    float posy;
    size_t id;
    int player_sprite;
} player_t;

typedef struct {
    float posx;
    float posy;
    size_t id;
} pos_t;

typedef struct {
    float velx;
    float vely;
    size_t id;
} vel_t;

typedef struct {
    size_t id;
} destroy_t;

typedef struct {
    size_t size;
    char *name;
} lobby_create_t;