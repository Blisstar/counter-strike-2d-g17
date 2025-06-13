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

void Game::processPlayerActions() {
    PlayerAction playerAction;
    while (playerActionsToProcess.try_pop(playerAction)) {
        switch (playerAction.message.type) {
            case constant expression:
                /* code */
                break;

            default:
                break;
        }
    }
}

void Game::updateGame() {}

void Game::sendSnapshots() {}

void Game::run() {
    while (should_keep_running()) {
        processPlayerActions();
        updateGame();
        sendSnapshots();
    }
    playerActionsToProcess.close();
}

void Game::pushPlayerAction(PlayerMessage playerAction) {
    playerActionsToProcess.try_push(playerAction);
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
        run();
}
