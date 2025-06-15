#include "client_protocol.h"

#include "../common/defs.h"
#include "servererror.h"
#include "serversentincorrectmessage.h"

ClientProtocol::ClientProtocol(const char* servname, const char* port)
    : skt(Socket(servname, port)) {
    wasClosed = false;
}

LobbySnapshot ClientProtocol::recvLobbySnapshot() {
    ServerMessageType t;
    recvall(skt, &t, 1);

    std::cout << "Tipo de mensaje recibido: " << static_cast<int>(t)
              << std::endl;
    if (t == ServerMessageType::Error)
        throw new ServerError("An error ocurred in the server");
    if (t != ServerMessageType::LobbySnapshot)
        throw new ServerSentIncorrectMessage();

    uint32_t s = recvLong(skt);
    std::cout << "La cantidad de rooms que hay es: " << s << std::endl;
    LobbySnapshot l;
    for (int i = 0; i < s; i++) {
        uint32_t gameId = recvLong(skt);
        std::string gameName = recvString(skt);
        uint32_t mapId = recvLong(skt);
        uint8_t playersCount = 0;
        recvall(skt, &playersCount, 1);
        l.addRoomData(gameId, gameName, mapId, playersCount);
    }
    return l;
}

RoomSnapshot ClientProtocol::recvRoomSnapshot() {
    ServerMessageType t;
    recvall(skt, &t, 1);
    if (t == ServerMessageType::Error)
        throw new ServerError("An error ocurred in the server");
    if (t != ServerMessageType::RoomSnapshot)
        throw new ServerSentIncorrectMessage();

    bool isHost = false;
    uint8_t connectedPlayers = 0;
    recvall(skt, &isHost, 1);
    recvall(skt, &connectedPlayers, 1);
    return RoomSnapshot(isHost, connectedPlayers);
}



PlayerSnapshot ClientProtocol::recvPlayerSnapshot() {
    ServerMessageType t;
    recvall(skt, &t, 1);
    if (t == ServerMessageType::Error)
        throw new ServerError("An error ocurred in the server");
    if (t != ServerMessageType::PlayerSnapshot)
        throw new ServerSentIncorrectMessage();
    unsigned int id = recvLong(skt);
    float x = recvFloat(skt);
    float y = recvFloat(skt);
    int health = recvLong(skt);
    int team = recvLong(skt);

    uint8_t intWeapon = 0;
    recvall(skt, &intWeapon, 1);
    PrimaryWeapon primaryWeapon = <static_cast>(intWeapon);

    uint16_t loaded_primary_ammo = recvShort(skt);
    uint16_t extra_primary_ammo = recvShort(skt);
    uint16_t loaded_secondary_ammo = recvShort(skt);
    uint16_t extra_secondary_ammo = recvShort(skt);
    bool has_bomb = false;
    recvall(skt, &has_bomb, 1);
    uint16_t money = recvShort(skt);
    bool is_hit = false;
    recvall(skt, &is_hit, 1);
    return PlayerSnapshot(id, x, y, health, team, primaryWeapon,
                          loaded_primary_ammo, extra_primary_ammo,
                          loaded_secondary_ammo, extra_secondary_ammo, has_bomb,
                          money, is_hit);
    
}
/* 
    uint8_t state;
    uint16_t round;
    std::vector<PlayerSnapshot> players;
    std::vector<DroppedItem> dropped_items;
    BombInfo bomb;
    uint16_t time_left;
    uint16_t count_tt_alive;
    uint16_t count_ct_alive;
    uint16_t score_tt;
    uint16_t score_ct;
 */
GameSnapshot ClientProtocol::recvGameSnapshot() {
    ServerMessageType t;
    recvall(skt, &t, 1);
    if (t == ServerMessageType::Error)
        throw new ServerError("An error ocurred in the server");
    if (t != ServerMessageType::GameSnapshot)
        throw new ServerSentIncorrectMessage();

    uint8_t state = 0;
    recvall(skt, &state, 1);
    uint16_t round = recvShort(skt);
    
    uint16_t playersCount = recvShort(skt); // recibo primero la cantidad de jugadores
    std::vector<PlayerSnapshot> players;
    for (int i = 0; i < playersCount; i++) {
        players.push_back(recvPlayerSnapshot());
    }

    uint16_t droppedItemsCount = recvShort(skt); // recibo primero la cantidad de items droppeados
    std::vector<DroppedItem> dropped_items;
    for (int i = 0; i < droppedItemsCount; i++) {
        float x = recvFloat(skt);
        float y = recvFloat(skt);
        int type = recvLong(skt);
        dropped_items.emplace_back(x, y, type);
    }

    bool is_planted = false;
    recvall(skt, &is_planted, 1);
    float bomb_x = recvFloat(skt);
    float bomb_y = recvFloat(skt);
    uint16_t timer = recvShort(skt);
    
    BombInfo bomb(is_planted, bomb_x, bomb_y, timer);

    uint16_t time_left = recvShort(skt);
    uint16_t count_tt_alive = recvShort(skt);
    uint16_t count_ct_alive = recvShort(skt);
    uint16_t score_tt = recvShort(skt);
    uint16_t score_ct = recvShort(skt);

    return GameSnapshot(state, round, players, dropped_items, bomb,
                        time_left, count_tt_alive, count_ct_alive,
                        score_tt, score_ct);
}

void ClientProtocol::send_message(ClientMessage msg) {
    sendall(skt, &msg.type, 1);
    std::cout << "envio un " << static_cast<int>(msg.type) << std::endl;
    switch (msg.type) {
        case ClientMessageType::CreateGame: {
            CreateGame c = std::get<CreateGame>(msg.data);
            sendString(skt, c.gameName);
            sendLong(skt, c.mapId);
            sendString(skt, c.playerName);
        } break;

        case ClientMessageType::ConnectGame: {
            ConnectGame c = std::get<ConnectGame>(msg.data);
            sendLong(skt, c.gameId);
            sendString(skt, c.playerName);
        } break;

        case ClientMessageType::PlayerMessage: {
            PlayerMessage c = std::get<PlayerMessage>(msg.data);
            sendall(skt, &c.type, 1);
            sendShort(skt, c.parameter);
        } break;

        default:
            break;
    }
}

void ClientProtocol::close() {
    if (!wasClosed) {
        wasClosed = true;
        skt.shutdown(SHUT_RDWR);
        skt.close();
    }
}
