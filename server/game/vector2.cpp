#include "vector2.h"
#include <iostream>

Vector2::Vector2(float _x , float _y) : x(_x), y(_y) {}

Vector2 Vector2::operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

void Vector2::print() const {
    std::cout << "(" << x << ", " << y << ")";
}