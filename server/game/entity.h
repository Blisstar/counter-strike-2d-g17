#include "vector2.h"
#ifndef ENTITY_H
#define ENTITY_H

class Entity {
   public:
    float velocity;

   protected:
    Vector2 position;
    Vector2 currentDir;

   public:
    Entity(float startX = 0.0f, float startY = 0.0f, float vel = 0.0f);

    void move();

    void setDirection(float angle);

    Vector2 getPosition() const;
};

#endif