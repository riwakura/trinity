#include "Vec3D.h"

Vec3D::Vec3D() : x(0.0), y(0.0), z(0.0) {}
Vec3D::Vec3D(double x_val, double y_val, double z_val) : x(x_val), y(y_val), z(z_val) {}

Vec3D Vec3D::operator+(const Vec3D& other) const {
    return Vec3D(x + other.x, y + other.y, z + other.z);
}
Vec3D Vec3D::operator-(const Vec3D& other) const {
    return Vec3D(x - other.x, y - other.y, z - other.z);
}
Vec3D Vec3D::operator*(double scalar) const {
    return Vec3D(x * scalar, y * scalar, z * scalar);
}
Vec3D Vec3D::operator/(double scalar) const {
    if (scalar == 0.0 || std::abs(scalar) < 1e-18) { // ゼロ除算チェック
        // エラー処理または適切な値を返す (例: Vec3D() or throw)
        // ここでは簡単のため例外を投げる
        throw std::runtime_error("Vec3D: Division by zero or very small number.");
    }
    return Vec3D(x / scalar, y / scalar, z / scalar);
}
double Vec3D::dot(const Vec3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}
double Vec3D::magnitude_sq() const {
    return x * x + y * y + z * z;
}
double Vec3D::magnitude() const {
    return std::sqrt(magnitude_sq());
}
