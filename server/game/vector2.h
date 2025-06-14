#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
   public:
    float x, y;

   public:
    Vector2(float _x = 0.0f, float _y = 0.0f);

    Vector2(const Vector2& v, float angle);

    Vector2 operator+(const Vector2& other) const;

    Vector2 operator*(float scalar) const;

    Vector2 operator-(const Vector2& other) const;

    // Producto escalar
    float operator*(const Vector2& other) const;

    Vector2 rotate(float angle) const;

    void print() const;
};

#endif