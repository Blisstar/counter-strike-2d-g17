#include "vector2.h"

#include <cmath>
#include <iostream>

Vector2::Vector2(float _x, float _y) : x(_x), y(_y) {}

Vector2::Vector2(const Vector2& v, float angle)
    : x(v.x * std::cos(angle) - y * std::sin(angle)),
      y(x * std::sin(angle) + y * std::cos(angle)) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return {x - other.x, y - other.y};
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

float Vector2::operator*(const Vector2& other) const {
    return x * other.x + y * other.y;
}

Vector2 Vector2::rotate(float angle) const {
    return {x * std::cos(angle) - y * std::sin(angle),
            x * std::sin(angle) + y * std::cos(angle)};
}

void Vector2::print() const {
    std::cout << "(" << x << ", " << y << ")";
}