#include "game.h"

Game::Game(Broadcast& _broadcast, std::string _gameName, unsigned int _mapId)
    : broadcast(_broadcast),
      gameName(_gameName),
      mapId(_mapId),
      startedGame(false) {}

std::string Game::getName() {
    return gameName;
}

unsigned int Game::getMapId() {
    return mapId;
}

uint8_t Game::getPlayersCount() {
    return players.size();
}

/* void Game::processGameActions() {}

void Game::run() {
    while (should_keep_running()) {
        EventType eventType;
        while (eventsToProcess.try_pop(eventType)) {
            if (eventType == ENEMYDEAD)
                attackAEnemy();
        }
        reviveEnemies();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        for (size_t i = 0; i < nextResurrect.size(); i++) {
            nextResurrect[i]++;
        }
    }
    gameActionsToProcess.close();
}
*/

void Game::pushPlayerAction(PlayerMessage playerAction) {
    gameActionsToProcess.try_push(playerAction);
}

void Game::notifyRoomStateToPlayers() {
    size_t playersCount = players.size();
    for (size_t i = 0; i < playersCount; i++) {
        RoomSnapshot r(playersCount, i == 0);
        broadcast.pushMessageById(
            players.at(i).getPlayerId(),
            ServerMessage(ServerMessageType::RoomSnapshot, r));
    }
}

void Game::addPlayer(unsigned int playerId, std::string playerName) {
    const std::lock_guard<std::mutex> lck(mtx);
    if (startedGame)
        throw GameInProgressError();
    players.emplace_back(playerId, playerName);
    notifyRoomStateToPlayers();
}

bool Game::removePlayer(unsigned int clientId) {
    // Forma de eliminar rapido, desventaja: altera el orden de insercion
    // poniendo el ultimo elemento en la posicion del elemento eliminado
    const std::lock_guard<std::mutex> lck(mtx);
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].getPlayerId() == clientId) {
            players[i] =
                players.back();  // Mover el último sobre el que querés eliminar
            players.pop_back();  // Eliminar el último
            break;               // Salís, porque ya eliminaste uno
        }
    }
    notifyRoomStateToPlayers();
    return players.size() == 0;
}

void Game::start(unsigned int hostClientId) {
    if (hostClientId == players.front().getPlayerId())
        startedGame = true;
}
