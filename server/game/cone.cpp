#include "cone.h"

Cone::Cone(Vector2 c, float dir, float r, float a) : center(c), direction(dir), radius(r), angle(a) {}

bool Cone::contains(const Vector2& point) const {
    Vector2 toPoint = { point.x - center.x, point.y - center.y };
    float distanceSq = toPoint.x * toPoint.x + toPoint.y * toPoint.y;

    if (distanceSq > radius * radius) return false;

    float pointAngle = std::atan2(toPoint.y, toPoint.x);
    float diff = std::fmod(pointAngle - direction + M_PI * 3, M_PI * 2) - M_PI;

    return std::abs(diff) <= angle / 2.0f;
}

unsigned int Cone::collidesWith(const Ellipse& e) const {
    const int NUM_SEGMENTS = 16;
    unsigned int collisionPoints = 0;
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        float angle = (M_2_PI * i) / NUM_SEGMENTS;
        float px = e.radiusX * std::cos(angle);
        float py = e.radiusY * std::sin(angle);
        Vector2 point = { e.getPosition().x + px, e.getPosition().y + py };
        if (contains(point)) collisionPoints++;
    }
    return collisionPoints;
}
