#ifndef DEFS
#define DEFS

#include <variant>

// Actions that the player send
#define CONNECT_GAME 0x00
#define DISCONNECT_GAME 0x01
#define CREATE_GAME 0x02
#define START_GAME 0x03
#define GET_LIST_GAME 0x04

// Messages that the server send

enum class MessageType { Error, LobbySnapshot, RoomSnapshot, GameSnapshot };

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

using MessageData =
    std::variant<ErrorMessage, std::unique_ptr<LobbySnapshot>,
                 std::unique_ptr<RoomSnapshot>, std::unique_ptr<GameSnapshot>>;

struct Message {
    MessageType type;
    MessageData data;

    Message(MessageType _type, MessageData _data)
        : type(_type), data(std::move(_data)) {}
};

#endif
