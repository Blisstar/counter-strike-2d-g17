#ifndef VECTOR2_H
#define VECTOR2_H

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};

class Vector2 {
    public:
    float x, y;

    public:
    Vector2(float _x = 0.0f, float _y = 0.0f);

    Vector2 operator+(const Vector2& other) const;

    Vector2 operator*(float scalar) const;

    void print() const;
};

#endif