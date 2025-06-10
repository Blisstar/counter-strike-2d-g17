#ifndef CONO_H
#define CONO_H

#include "ellipse.h"
#include <math.h>

class Cone {
   private:
    Vector2 center;
    float direction;  // dirección central (en radianes)
    float radius;
    float angle;      // apertura total (en radianes)

   private:
    bool contains(const Vector2& point) const;

   public:
    Cone(Vector2 c, float dir, float r = 1.0f, float a = 0.47f * M_PI);

    unsigned int collidesWith(const Ellipse& e) const;
};

#endif