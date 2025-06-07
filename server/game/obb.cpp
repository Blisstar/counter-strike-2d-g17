#include "obb.h"

#include <cmath>
#include "ellipse.h"

OBB::OBB(float centerX, float centerY, float halfWidth, float halfHeight,
         float angle)
    : center(centerX, centerY),
      halfWidth(halfWidth),
      halfHeight(halfHeight),
      rotation(angle) {}


bool OBB::collidesWith(const OBB& other) const {
    Vector2 axes[4] = {
        Vector2({1, 0}, rotation),
        Vector2({0, 1}, rotation),
        Vector2({1, 0}, other.rotation),
        Vector2({0, 1}, other.rotation)
    };

    for (int i = 0; i < 4; ++i) {
        Vector2 axis = axes[i];

        // Proyección OBB A
        float projA = center * axis;
        float extentA =
            std::abs(axis * Vector2({halfWidth, 0}, rotation)) +
            std::abs(axis * Vector2({0, halfHeight}, rotation));

        // Proyección OBB B
        float projB = other.center * axis;
        float extentB =
            std::abs(axis * Vector2({other.halfWidth, 0}, other.rotation)) +
            std::abs(axis * Vector2({0, other.halfHeight}, other.rotation));

        if (std::abs(projA - projB) > (extentA + extentB))
            return false; // Separación detectada
    }

    return true; // No hay separación, hay colisión
}

bool OBB::collidesWith(const Ellipse& ellipse) const {
    return ellipse.collidesWith(*this);
}