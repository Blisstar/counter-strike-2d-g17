#include "vector2.h"
#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
    Vector2 position;
    Direction currentDir;
    float velocity;

public:
    Entity(float startX = 0.0f, float startY = 0.0f, float vel = 1.0f);

    void move();

    void setDirection(Direction dir);

    void setVelocity(float vel);

    Vector2 getPosition() const;

};

#endif