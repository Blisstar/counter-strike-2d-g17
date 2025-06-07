#ifndef DEFS
#define DEFS

#include <variant>

// Messages that the client send

#define SEND_CLIENT_MESSAGE 0X00
#define SEND_PLAYER_MESSAGE 0X01

enum class ClientMessageType : uint8_t {
    InvalidClientMessage = 0x00,
    CreateGame = 0x01,
    ConnectGame = 0x02,
    DisconnectGame = 0x03,
    StartGame = 0x04,
    GetListGame = 0x05
};



struct CreateGame {
    std::string gameName;
    unsigned int mapId;
    std::string playerName;

    CreateGame(std::string _gameName, unsigned int _mapId, std::string _playerName): gameName(_gameName), mapId(_mapId), playerName(_playerName) {}
    
};

struct ConnectGame {
    unsigned int gameId;
    std::string playerName;

    ConnectGame(unsigned int _gameId, std::string _playerName): gameId(_gameId), playerName(_playerName) {}

};

using ClientMessageData = std::variant<std::monostate, CreateGame, ConnectGame>;

struct ClientMessage {
    ClientMessageType type;
    ClientMessageData data;

    ClientMessage(ClientMessageType _type, ClientMessageData _data)
        : type(_type), data(_data) {}
};

// Messages that the server send

enum class ServerMessageType : uint8_t {
    InvalidServerMessage = 0x00,
    Error = 0x01,
    LobbySnapshot = 0x02,
    RoomSnapshot = 0x03,
    GameSnapshot = 0x04
};

enum class ErrorType : uint8_t { 
    GameInProgress = 0x00,
    GameIsFull = 0x01
};

struct ErrorMessage {
    ErrorType type;

    ErrorMessage(ErrorType _type) : type(_type) {}
};

struct RoomData {
    unsigned int gameId;
    std::string gameName;
    unsigned int mapId;
    uint8_t playersCount;

    RoomData(unsigned int _gameId, std::string _gameName, unsigned int _mapId,
             uint8_t _playersCount)
        : gameId(_gameId),
          gameName(_gameName),
          mapId(_mapId),
          playersCount(_playersCount) {}
};

struct LobbySnapshot {
    std::vector<RoomData> roomListData;

    void addRoomData(unsigned int gameId, std::string gameName,
                     unsigned int mapId, uint8_t playersCount) {
        roomListData.push_back(RoomData(gameId, gameName, mapId, playersCount));
    }
};

struct RoomSnapshot {
    uint8_t playersCount;
    bool isHost;

    RoomSnapshot(uint8_t _playersCount, bool _isHost)
        : playersCount(_playersCount), isHost(_isHost) {}
};

struct GameSnapshot {
    std::vector<unsigned int> connectedPlayers;
    uint8_t state;

    GameSnapshot(std::vector<unsigned int> _connectedPlayers, uint8_t _state)
        : connectedPlayers(_connectedPlayers), state(_state) {}
};

using ServerMessageData =
    std::variant<std::monostate, ErrorMessage, LobbySnapshot, RoomSnapshot, GameSnapshot>;

struct ServerMessage {
    ServerMessageType type;
    ServerMessageData data;

    ServerMessage(ServerMessageType _type, ServerMessageData _data)
        : type(_type), data(std::move(_data)) {}
};



// Messages that the player send

/* struct PlayerMsg {
    PlayerMessageType t;
    uint16_t firstParameter;
}

enum class PlayerMessageType : uint8_t {
    MoveUp = 0x10,
    MoveRight = 0x11,
    MoveDown = 0x12,
    MoveLeft = 0x13,
    BuyWeapon = 0x20
};

struct MovePlayer {
    char direction;
    MovePlayer(char _direction) : direction(_direction) {}
};

struct BuyWeapon {
    uint8_t weapon;
    MovePlayer(uint8_t weapon) : weapon(_weapon) {}
};
 */
#endif
