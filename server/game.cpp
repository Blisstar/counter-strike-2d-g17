#include "game.h"

Game::Game(Broadcast& _broadcast, std::string _gameName)
    : broadcast(_broadcast), gameName(_gameName) {}

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
    connectedPlayers.push_back(playerId);
}

void Game::removePlayer(unsigned int clientId) {
    //Forma de eliminar rapido, desventaja: altera el orden de insercion poniendo el
    //ultimo elemento en la posicion del elemento eliminado
    auto it = std::find(connectedPlayers.begin(), connectedPlayers.end(), clientId);
    if (it != connectedPlayers.end()) {
        *it = connectedPlayers.back();  // Sobrescribís el valor con el último
        connectedPlayers.pop_back();    // Eliminás el último
    }
}

bool Game::areTherePlayers() {
    return connectedPlayers.size() > 0;
}
