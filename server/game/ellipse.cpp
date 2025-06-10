#include "ellipse.h"

#include <cmath>
#include "obb.h"

Ellipse::Ellipse(float centerX, float centerY, float radiusX, float radiusY, float velocity)
    : Entity(centerX, centerY, velocity), radiusX(radiusX), radiusY(radiusY) {}

bool Ellipse::collidesWith(const Ellipse& other) const {
    float dx = other.position.x - position.x;
    float dy = other.position.y - position.y;
    float sumRx = radiusX + other.radiusX;
    float sumRy = radiusY + other.radiusY;

    float norm = (dx * dx) / (sumRx * sumRx) + (dy * dy) / (sumRy * sumRy);
    return norm <= 1.0f;
}

bool Ellipse::collidesWith(const OBB& obb) const {
    float cosA = std::cos(-obb.rotation);
    float sinA = std::sin(-obb.rotation);

    float dx = position.x - obb.getPosition().x;
    float dy = position.y - obb.getPosition().y;

    float localX = dx * cosA - dy * sinA;
    float localY = dx * sinA + dy * cosA;

    float clampedX = std::max(-obb.halfWidth, std::min(localX, obb.halfWidth));
    float clampedY = std::max(-obb.halfHeight, std::min(localY, obb.halfHeight));

    float distX = localX - clampedX;
    float distY = localY - clampedY;

    float norm = (distX * distX) / (radiusX * radiusX) + (distY * distY) / (radiusY * radiusY);

    return norm <= 1.0f;
}