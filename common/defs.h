#ifndef DEFS
#define DEFS

#include <variant>

// Messages that the player send

enum class ClientMessageType {
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

    CreateGame(std::string _gameName, unsigned int _mapId): gameName(_gameName), mapId(_mapId) {}
    
};

struct ConnectGame {
    unsigned int gameId;

    ConnectGame(unsigned int _gameId): gameId(_gameId) {}

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
    LobbySnapshot = 0x02, gameCount<uint16_t> id<uint16_t> size<uint8_t> name
    RoomSnapshot = 0x03,
    GameSnapshot = 0x04
};

enum class ErrorType { GameInProgress, GameIsFull };

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
    std::vector<unsigned int> connectedPlayers;
    unsigned int mapId;
    bool isHost;

    RoomSnapshot(std::vector<unsigned int> _connectedPlayers,
                 unsigned int _mapId, bool _isHost)
        : connectedPlayers(_connectedPlayers), mapId(_mapId), isHost(_isHost) {}
};

struct GameSnapshot {
    std::vector<unsigned int> connectedPlayers;
    uint8_t state;

    GameSnapshot(std::vector<unsigned int> _connectedPlayers, uint8_t _state)
        : connectedPlayers(_connectedPlayers), state(_state) {}
};

using ServerMessageData =
    std::variant<ErrorMessage, std::unique_ptr<LobbySnapshot>,
                 std::unique_ptr<RoomSnapshot>, std::unique_ptr<GameSnapshot>>;

struct ServerMessage {
    ServerMessageType type;
    ServerMessageData data;

    ServerMessage(ServerMessageType _type, ServerMessageData _data)
        : type(_type), data(std::move(_data)) {}
};

#endif
