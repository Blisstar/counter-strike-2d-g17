#include "game.h"

#include "player.h"

Game::Game(Broadcast& _broadcast, std::string _gameName, unsigned int _mapId,
           unsigned int hostId, std::string hostName)
    : broadcast(_broadcast),
      gameName(_gameName),
      hostClientId(hostId),
      mapId(_mapId),
      rate(20),
      stopWatch(0), 
      startedGame(false) {
    addPlayer(hostId, hostName);
}

std::string Game::getName() {
    return gameName;
}

unsigned int Game::getMapId() {
    return mapId;
}

uint8_t Game::getPlayersCount() {
    return players.size();
}

unsigned int Game::getStopWatch() {
    return stopWatch * rate.count() / 10;
}

void Game::processPlayerActions() {
    const std::lock_guard<std::mutex> lck(mtx);
    bool isEmpty;
    do {
        PlayerAction playerAction = playerActionsToProcess.try_pop(isEmpty);
        unsigned int idPlayer = playerAction.idPlayer;
        uint16_t parameter = playerAction.message.parameter;
        switch (playerAction.message.type) {
            case PlayerMessageType::StartMotion:
                players.at(idPlayer).setInMotionWithDirection(
                    static_cast<Direction>(parameter));
                break;
            case PlayerMessageType::StartShooting:
                players.at(idPlayer).setShootingWithDirection(parameter);
                break;
            case PlayerMessageType::InteractWithZone:
                players.at(idPlayer).interact(interactionZones.at(parameter));
                break;
            case PlayerMessageType::BuyWeapon:
                players.at(idPlayer).buyWeapon(parameter);
                break;
            case PlayerMessageType::ChooseTerrorist:
                players.at(idPlayer).setTeam(
                    static_cast<TerroristSkin>(parameter));
                break;
            case PlayerMessageType::ChooseCounterTerrorist:
                players.at(idPlayer).setTeam(
                    static_cast<CounterTerroristSkin>(parameter));
                break;
            case PlayerMessageType::BuySecondaryAmmo:
                players.at(idPlayer).buyAmmo(false);
                break;
            case PlayerMessageType::BuyPrimaryAmmo:
                players.at(idPlayer).buyAmmo(true);
                break;
            case PlayerMessageType::EquipKnife:
                players.at(idPlayer).equip(WeaponType::Knife);
                break;
            case PlayerMessageType::EquipSecondaryWeapon:
                players.at(idPlayer).equip(WeaponType::Glock);
                break;
            case PlayerMessageType::EquipPrimaryWeapon:
                players.at(idPlayer).equip(WeaponType::PrimaryWeapon);
                break;
            case PlayerMessageType::StopMotion:
                players.at(idPlayer).stopMotion();
                break;
            case PlayerMessageType::StopShooting:
                players.at(idPlayer).stopShooting();
                break;
            default:
                break;
        }
    } while (isEmpty);
}

void Game::updateGame() {}

void Game::sendSnapshots() {}

void Game::run() {
    using clock = std::chrono::steady_clock;
    auto t1 = clock::now();

    while (should_keep_running()) {
        processPlayerActions();
        updateGame();
        sendSnapshots();

        auto t2 = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        auto rest = rate - elapsed;

        if (rest.count() < 0) {
            auto behind = -rest;
            auto lost = behind - std::chrono::milliseconds(behind.count() % rate.count());
            t1 += lost;
            stopWatch += static_cast<int>(lost.count() / rate.count());
        } else {
            std::this_thread::sleep_for(rest);
            t1 += rate;
            stopWatch++;
        }
    }
    playerActionsToProcess.close();
}

void Game::pushPlayerAction(PlayerAction playerAction) {
    const std::lock_guard<std::mutex> lck(mtx);
    playerActionsToProcess.push(playerAction);
}

void Game::notifyRoomStateToPlayers() {
    size_t playersCount = players.size();
    for (auto it = players.begin(); it != players.end();) {
        RoomSnapshot r(playersCount, it->first == hostClientId);
        broadcast.pushMessageById(
            it->first, ServerMessage(ServerMessageType::RoomSnapshot, r));
        ++it;
    }
}

void Game::addPlayer(unsigned int playerId, std::string playerName) {
    const std::lock_guard<std::mutex> lck(mtx);
    if (startedGame)
        throw GameInProgressError();
    players.emplace(std::piecewise_construct, std::forward_as_tuple(playerId),
                    std::forward_as_tuple(*this, gameName, mapId, hostClientId,
                                          playerName));
    notifyRoomStateToPlayers();
}

bool Game::removePlayer(unsigned int clientId) {
    const std::lock_guard<std::mutex> lck(mtx);
    players.erase(clientId);
    notifyRoomStateToPlayers();
    return players.size() == 0;
}

void Game::start(unsigned int hostClientId) {
    if (hostClientId == this->hostClientId)
        run();
}
