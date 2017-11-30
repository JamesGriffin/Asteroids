#include <cmath>

struct Vector2 {
    float x, y;

    Vector2(float x_=0, float y_=0): x(x_), y(y_) {};
    Vector2 operator+(const Vector2 &b) { return Vector2(x+b.x, y+b.y); };
    Vector2 operator-(const Vector2 &b) { return Vector2(x-b.x, y-b.y); };
    Vector2 operator*(const float &b) { return Vector2(x*b, y*b); };
    Vector2 operator/(const float &b) { return Vector2(x/b, y/b); };

    Vector2 rotate(float rot) {
        float x_ = x * std::cos(rot) - y * std::sin(rot);
        float y_ = x * std::sin(rot) + y * std::cos(rot);
        return Vector2(x_, y_);
    }

    float mag() {
        return std::sqrt(x*x + y*y);
    }
};
