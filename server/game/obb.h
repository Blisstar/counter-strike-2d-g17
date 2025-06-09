#ifndef OBB_H
#define OBB_H

#include "entity.h"
#include "vector2.h"

class OBB : public Entity {
   public:
    float halfWidth, halfHeight;
    float rotation;

   public:
    OBB(float centerX = 0, float centerY = 0, float halfWidth = 1,
        float halfHeight = 1, float angle = 0, float velocity = 0.0f);

    bool collidesWith(const OBB& other) const;

    bool collidesWith(const Ellipse& ellipse) const;
};

#endif