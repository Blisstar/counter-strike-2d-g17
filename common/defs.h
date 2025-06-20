#ifndef DEFS
#define DEFS

#include <cstdint>
#include <variant>

// Messages that the client send

#define SEND_CLIENT_MESSAGE 0X00
#define SEND_PLAYER_MESSAGE 0X01

enum class PrimaryWeapon : uint8_t {
    NoPrimaryWeapon = 0x00,
    AK47 = 0x01,
    M3 = 0x02,
    AWP = 0x03
};

enum class WeaponType : uint8_t {
    Knife = 0x00,
    Glock = 0x01,  // secondary weapon
    PrimaryWeapon = 0x02
};

enum class ClientMessageType : uint8_t {
    InvalidClientMessage = 0x00,
    CreateGame = 0x01,
    ConnectGame = 0x02,
    DisconnectGame = 0x03,
    StartGame = 0x04,
    GetListGame = 0x05,
    PlayerMessage = 0x06
};

struct CreateGame {
    std::string gameName;
    unsigned int mapId;
    std::string playerName;

    CreateGame(std::string _gameName, unsigned int _mapId,
               std::string _playerName)
        : gameName(_gameName), mapId(_mapId), playerName(_playerName) {}
};

struct ConnectGame {
    unsigned int gameId;
    std::string playerName;

    ConnectGame(unsigned int _gameId, std::string _playerName)
        : gameId(_gameId), playerName(_playerName) {}
};

// #############################################

enum class PlayerMessageType : uint8_t {
    StartMotion = 0x10,    // el parametro seria la direccion
    StartShooting = 0x11,  // su parametro seria el angulo del disparo
    InteractWithZone =
        0x12,                // su parametro es el id de la zona que interactuar
    BuyWeapon = 0x13,        // su parametro es la arma que desea comprar
    ChooseTerrorist = 0x1A,  // su parametro es la skin
    ChooseCounterTerrorist = 0x1B,  // sin parametro
    BuySecondaryAmmo = 0x14,  // sin parametro, compra un cargador de la pistola
    BuyPrimaryAmmo =
        0x15,           // sin parametro, compra un cargador del arma principal
    EquipKnife = 0x16,  // sin parametro
    EquipSecondaryWeapon = 0x17,  // sin parametro
    EquipPrimaryWeapon = 0x18,    // sin parametro
    StopMotion = 0x1C,            // sin parametro
    StopShooting = 0x1D,          // sin parametro
};

struct PlayerMessage {
    PlayerMessageType type;
    uint16_t parameter;

    PlayerMessage(enum PlayerMessageType _type, uint16_t _parameter)
        : type(_type), parameter(_parameter) {}
};

// #############################################

using ClientMessageData =
    std::variant<std::monostate, CreateGame, ConnectGame, PlayerMessage>;

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

enum class ErrorType : uint8_t { GameInProgress = 0x00, GameIsFull = 0x01 };

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

// ###########################################

struct PlayerSnapshot {
    unsigned int id;
    float x, y;
    int health;
    int team;
    PrimaryWeapon primaryWeapon;
    uint16_t loaded_primary_ammo;
    uint16_t extra_primary_ammo;
    uint16_t loaded_secondary_ammo;
    uint16_t extra_secondary_ammo;
    bool has_bomb;
    uint16_t money;
    bool is_hit;
    /*enum skin*/
};

struct DroppedItem {
    float x, y;
    int type;

    DroppedItem(uint16_t _x, uint16_t _y, int _type)
        : x(_x), y(_y), type(_type) {}
};

struct BombInfo {
    bool is_planted;
    float x, y;
    uint16_t timer;

    BombInfo(bool _is_planted, uint16_t _x, uint16_t _y, uint16_t _timer)
        : is_planted(_is_planted), x(_x), y(_y), timer(_timer) {}
};

struct GameSnapshot {
    // unsigned int mapId;
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
    /*map snapshot*/
    /*tienda*/

    GameSnapshot(uint8_t _state, uint16_t _round,
                 std::vector<PlayerSnapshot> _players,
                 std::vector<DroppedItem> _dropped_items, BombInfo _bomb,
                 uint16_t _time_left, uint16_t _count_tt_alive,
                 uint16_t _count_ct_alive, uint16_t _score_tt,
                 uint16_t _score_ct)
        : state(_state),
          round(_round),
          players(std::move(_players)),
          dropped_items(std::move(_dropped_items)),
          bomb(_bomb),
          time_left(_time_left),
          count_tt_alive(_count_tt_alive),
          count_ct_alive(_count_ct_alive),
          score_tt(_score_tt),
          score_ct(_score_ct) {}
};

// ###########################################

using ServerMessageData =
    std::variant<std::monostate, ErrorMessage, LobbySnapshot, RoomSnapshot,
                 GameSnapshot>;

struct ServerMessage {
    ServerMessageType type;
    ServerMessageData data;

    ServerMessage(ServerMessageType _type, ServerMessageData _data)
        : type(_type), data(std::move(_data)) {}
};

// DEFINITIONS THAT WORKING

enum class Direction : uint8_t {
    UP = 0x00,
    DOWN = 0x01,
    LEFT = 0x02,
    RIGHT = 0x03,
    UP_LEFT = 0x04,
    UP_RIGHT = 0x05,
    DOWN_LEFT = 0x06,
    DOWN_RIGHT = 0x07
};

enum class TerroristSkin : uint8_t {
    NoTerrorist = 0x00,
    Pheonix = 0x01,
    L337Krew = 0x02,
    ArticAvenger = 0x03,
    Guerrilla = 0x04
};

enum class CounterTerroristSkin : uint8_t {
    NoCounterTerrorist = 0x00,
    SealForce = 0x01,
    GermanGSG9 = 0x02,
    UKSA = 0x03,
    FrenchGIGN = 0x04
};

#endif
