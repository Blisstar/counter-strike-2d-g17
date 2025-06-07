#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "vector2.h"
class OBB;

class Ellipse {
public:
    Vector2 center;
    float radiusX, radiusY;

public:
    Ellipse(float centerX = 0, float centerY = 0, float radiusX = 1, float radiusY = 1);

    bool collidesWith(const Ellipse& other) const;

    bool collidesWith(const OBB& obb) const;
};

#endif