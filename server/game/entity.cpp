#include "entity.h"
#include <cmath>

Entity::Entity(float startX, float startY, float vel) : position(startX, startY), currentDir(Direction::DOWN), velocity(vel) {}

void Entity::move() {
    if(velocity == 0) return;

    Vector2 delta;

    switch (currentDir) {
        case Direction::UP:          delta = Vector2(0, -1); break;
        case Direction::DOWN:        delta = Vector2(0, 1); break;
        case Direction::LEFT:        delta = Vector2(-1, 0); break;
        case Direction::RIGHT:       delta = Vector2(1, 0); break;
        case Direction::UP_LEFT:     delta = Vector2(-1, -1); break;
        case Direction::UP_RIGHT:    delta = Vector2(1, -1); break;
        case Direction::DOWN_LEFT:   delta = Vector2(-1, 1); break;
        case Direction::DOWN_RIGHT:  delta = Vector2(1, 1); break;
    }

    // Normalizamos para mantener velocidad constante en diagonales
    if (delta.x != 0 && delta.y != 0) {
        delta = delta * (1.0f / std::sqrt(2.0f));
    }

    position = position + delta * velocity;
}

void Entity::setDirection(Direction dir) {
    currentDir = dir;
}

void Entity::setVelocity(float vel) {
    velocity = vel;
}

Vector2 Entity::getPosition() const {
    return position;
}
