#include "ellipse.h"

#include <cmath>
#include "obb.h"

Ellipse::Ellipse(float centerX, float centerY, float radiusX, float radiusY)
    : center(centerX, centerY), radiusX(radiusX), radiusY(radiusY) {}


bool Ellipse::collidesWith(const Ellipse& other) const {
    float dx = other.center.x - center.x;
    float dy = other.center.y - center.y;
    float sumRx = radiusX + other.radiusX;
    float sumRy = radiusY + other.radiusY;

    float norm = (dx * dx) / (sumRx * sumRx) + (dy * dy) / (sumRy * sumRy);
    return norm <= 1.0f;
}

bool Ellipse::collidesWith(const OBB& obb) const {
    float cosA = std::cos(-obb.rotation);
    float sinA = std::sin(-obb.rotation);

    float dx = center.x - obb.center.x;
    float dy = center.y - obb.center.y;

    float localX = dx * cosA - dy * sinA;
    float localY = dx * sinA + dy * cosA;

    float clampedX = std::max(-obb.halfWidth, std::min(localX, obb.halfWidth));
    float clampedY = std::max(-obb.halfHeight, std::min(localY, obb.halfHeight));

    float distX = localX - clampedX;
    float distY = localY - clampedY;

    float norm = (distX * distX) / (radiusX * radiusX) + (distY * distY) / (radiusY * radiusY);

    return norm <= 1.0f;
}