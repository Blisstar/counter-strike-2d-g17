#include "game.h"

Game::Game(Broadcast& _broadcast, std::string _gameName, unsigned int _mapId)
    : broadcast(_broadcast), gameName(_gameName), mapId(_mapId), startedGame(false) {}

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

void Game::addPlayer(unsigned int playerId) {
    const std::lock_guard<std::mutex> lck(mtx);
    if (startedGame) throw GameInProgressError();
    connectedPlayers.push_back(playerId);
}

bool Game::removePlayer(unsigned int clientId) {
    // Forma de eliminar rapido, desventaja: altera el orden de insercion
    // poniendo el ultimo elemento en la posicion del elemento eliminado
    const std::lock_guard<std::mutex> lck(mtx);
    auto it =
        std::find(connectedPlayers.begin(), connectedPlayers.end(), clientId);
    if (it != connectedPlayers.end()) {
        *it = connectedPlayers.back();  // Sobrescribís el valor con el último
        connectedPlayers.pop_back();    // Eliminás el último
    }
    return connectedPlayers.size() > 0;
}

void Game::start(unsigned int hostClientId) {
    if (hostClientId == connectedPlayers.front())
        startedGame = true;
}
