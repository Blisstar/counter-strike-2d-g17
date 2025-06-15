#include "player.h"

#include <math.h>

#define PlayerInMotionVelocity 1.0f

Player::Player(Game& _game, unsigned int _playerId, std::string _playerName, float startX,
               float startY, float vel)
    : shape(startX, startY, 1, 1, vel),
      game(_game),
      playerId(_playerId),
      playerName(_playerName),
      health(100),
      armament(PrimaryWeapon::NoPrimaryWeapon) {}

unsigned int Player::getPlayerId() {
    return playerId;
}

PlayerState Player::getState() {
    if (health == 0)
        return PlayerState::Dead;
    return (shape.velocity == 0) ? PlayerState::Idle : PlayerState::InMotion;
}

Vector2 Player::getPosition() {
    return shape.getPosition();
}

void Player::setInMotionWithDirection(Direction dir) {
    switch (dir) {
        case Direction::UP:
            shape.setDirection(M_PI + M_PI);
            break;
        case Direction::DOWN:
            shape.setDirection(M_PI + M_PI_2);
        case Direction::LEFT:
            shape.setDirection(M_PI);
            break;
        case Direction::RIGHT:
            shape.setDirection(0);
            break;
        case Direction::UP_LEFT:
            shape.setDirection(M_PI_2 + M_PI_4);
            break;
        case Direction::UP_RIGHT:
            shape.setDirection(M_PI_4);
            break;
        case Direction::DOWN_LEFT:
            shape.setDirection(M_PI + M_PI_4);
            break;
        case Direction::DOWN_RIGHT:
            shape.setDirection(M_PI + M_PI_2 + M_PI_4);
            break;
    }
    shape.velocity = PlayerInMotionVelocity;
}

void Player::setShootingWithDirection(uint16_t angle) {
    armament.fire(shape.getPosition(), angle, game);
}

void Player::move() {
    shape.move();
}

void Player::stopMotion() {
    shape.velocity = 0;
}

void Player::hurt(uint8_t damage) {
    if ((health - damage) < 0) {
        health = 0;
    } else {
        health = health - damage;
    }
}
