#include <iostream>
#include <array>
#include <cmath>
#include <vector>

// 2D Vector
struct Vec2 {
    double x, y;

    Vec2 operator+(const Vec2& other) 
    const { return {x + other.x, y + other.y}; }
    Vec2 operator-(const Vec2& other) 
    const { return {x - other.x, y - other.y}; }
    Vec2 operator*(double scalar) 
    const { return {x * scalar, y * scalar}; }

    double dot(const Vec2& other) 

    const { return x * other.x + y * other.y; }
    double length() 
    const { return std::sqrt(x * x + y * y); }
    Vec2 normalize() 
    const { double len = length(); return {x / len, y / len}; }
};

// 2x2 Matrix for rotation/scaling
struct Mat2 {
    std::array<std::array<double, 2>, 2> m;

    Vec2 operator*(const Vec2& v) const {
        return {
            m[0][0] * v.x + m[0][1] * v.y,
            m[1][0] * v.x + m[1][1] * v.y
        };
    }

    static Mat2 rotation(double angleRad) {
        return {{{ {std::cos(angleRad), -std::sin(angleRad)},
                   {std::sin(angleRad), std::cos(angleRad)} }}};
    }

    static Mat2 scaling(double sx, double sy) {
        return {{{ {sx, 0}, {0, sy} }}};
    }
};

Vec2 project(const Vec2& v) {
    return v;
}

int main() {
    // Define a square
    std::vector<Vec2> square = { {1,1}, {-1,1}, {-1,-1}, {1,-1} };

    // Apply transformations
    double angle = M_PI / 4;
    Mat2 rot = Mat2::rotation(angle);
    Mat2 scale = Mat2::scaling(2.0, 0.5);

    std::cout << "Transformed square vertices:\n";
    for (auto& v : square) 
    {
        Vec2 transformed = rot * (scale * v);
        Vec2 projected = project(transformed);
        std::cout << "(" << projected.x << ", " << projected.y << ")\n";
    }

    Vec2 position{0,0};
    Vec2 velocity{1,2}; 
    double dt = 0.1;  // timestep
    position = position + velocity * dt;
    std::cout << "\nPosition after dt: (" << position.x << ", " << position.y << ")\n";

    return 0;
}
