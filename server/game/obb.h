#ifndef OBB_H
#define OBB_H

#include "vector2.h"

class OBB {
public:
    Vector2 center;
    float halfWidth, halfHeight;
    float rotation;

public:
    OBB(float centerX = 0, float centerY = 0, float halfWidth = 1, float halfHeight = 1, float angle = 0);

    bool collidesWith(const OBB& other) const;

    bool collidesWith(const Ellipse& ellipse) const;
};

#endif