#ifndef VEC3D_H
#define VEC3D_H

#include <cmath>     // For std::sqrt
#include <stdexcept> // For std::runtime_error

struct Vec3D {
    double x = 0.0, y = 0.0, z = 0.0;

    Vec3D();
    Vec3D(double x_val, double y_val, double z_val);

    Vec3D operator+(const Vec3D& other) const;
    Vec3D operator-(const Vec3D& other) const;
    Vec3D operator*(double scalar) const;
    Vec3D operator/(double scalar) const;
    double dot(const Vec3D& other) const;
    double magnitude_sq() const;
    double magnitude() const;
    // 必要であれば他のメソッド (例: normalize, cross_product) を追加
};

#endif // VEC3D_H
