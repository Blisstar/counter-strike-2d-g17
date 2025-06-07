#include "game.h"

Game::Game(Broadcast& _broadcast, std::string _gameName, unsigned int _mapId)
    : broadcast(_broadcast), gameName(_gameName), mapId(_mapId), startedGame(false) {}

std::string Game::getName(){
    return gameName;
}

unsigned int Game::getMapId(){
    return mapId;
}

uint8_t Game::getPlayersCount(){
    return connectedPlayers.size();
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

void Game::pushGameAction(GameAction gameAction) {
    gameActionsToProcess.try_push(gameAction);
} */

void Game::notifyRoomStateToPlayers() {
    size_t playersCount = connectedPlayers.size();
    for (size_t i = 0; i < playersCount; i++) {
        RoomSnapshot r(playersCount, i == 0);
        broadcast.pushMessageById(connectedPlayers.at(i).getPlayerId(), ServerMessage(ServerMessageType::RoomSnapshot, r));
    }
}

void Game::addPlayer(unsigned int playerId, std::string playerName) {
    const std::lock_guard<std::mutex> lck(mtx);
    if (startedGame) throw GameInProgressError();
    connectedPlayers.emplace_back(playerId, playerName);
    notifyRoomStateToPlayers();
}

bool Game::removePlayer(unsigned int clientId) {
    // Forma de eliminar rapido, desventaja: altera el orden de insercion
    // poniendo el ultimo elemento en la posicion del elemento eliminado
    const std::lock_guard<std::mutex> lck(mtx);
    for (size_t i = 0; i < connectedPlayers.size(); ++i) {
        if (connectedPlayers[i].getPlayerId() == clientId) {
            connectedPlayers[i] = connectedPlayers.back(); // Mover el último sobre el que querés eliminar
            connectedPlayers.pop_back();                   // Eliminar el último
            break;                                      // Salís, porque ya eliminaste uno
        }
    }
    notifyRoomStateToPlayers();
    return connectedPlayers.size() == 0;
}

void Game::start(unsigned int hostClientId) {
    if (hostClientId == connectedPlayers.front().getPlayerId())
        startedGame = true;
}
