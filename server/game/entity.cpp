#include "entity.h"

#include <cmath>

Entity::Entity(float startX, float startY, float vel) : position(startX, startY), currentDir(0, 0), velocity(vel) {}

void Entity::move() {
    if(velocity == 0) position = position + currentDir * velocity;

}

void Entity::setDirection(float angle) {
    currentDir.x = std::cos(angle);
    currentDir.y = std::sin(angle);
}

Vector2 Entity::getPosition() const {
    return position;
}
