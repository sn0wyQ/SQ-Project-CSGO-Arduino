#ifndef PC_VECTOR_VECTOR_H_
#define PC_VECTOR_VECTOR_H_

#include <cmath>
#include <cfloat>
#include <crtdbg.h>
#include <cstdlib>
#include <iostream>

constexpr float kPi = 3.14159265359f;
constexpr float kDegToRad = kPi / 180.f;
constexpr float kRadToDeg = 180.f / kPi;

inline float DegToRad(float x) {
  return x * kDegToRad;
}

inline float RadToDeg(float x) {
  return x * kRadToDeg;
}

class QAngle;
class Vector;

enum {
  kPitch = 0,  // up / down
  kYaw,  // left / right
  kRoll  // fall over
};

class QAngle {
 public:
  float x, y, z;

  QAngle() = default;
  QAngle(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

  QAngle operator-(const QAngle& v) const;
  QAngle operator*(float fl) const;
  float operator[](int i) const;

  Vector ToVector() const;
  float& operator[](int i);
  float Length() const;
  float LengthSqr() const;
};

inline float QAngle::Length() const {
  return sqrt(LengthSqr());
}


inline float QAngle::LengthSqr() const {
  return x * x + y * y;
}

inline void QAngleSubtract(const QAngle& a, const QAngle& b, QAngle* result) {
  result->x = a.x - b.x;
  result->y = a.y - b.y;
  result->z = a.z - b.z;
}

inline void QAngleMultiply(const QAngle& a, float b, QAngle* c) {
  c->x = a.x * b;
  c->y = a.y * b;
  c->z = a.z * b;
}

inline QAngle QAngle::operator*(float fl) const {
  QAngle res{};
  QAngleMultiply(*this, fl, &res);
  return res;
}

inline QAngle QAngle::operator-(const QAngle& v) const {
  QAngle res{};
  QAngleSubtract(*this, v, &res);
  return res;
}

inline float& QAngle::operator[](int i) {
  return reinterpret_cast<float*>(this)[i];
}

inline float QAngle::operator[](int i) const {
  return reinterpret_cast<const float*>(this)[i];
}

class Vector {
 public:
  float x, y, z;

  Vector() = default;
  inline Vector(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

  float Length() const;
  float Length2D() const;
  float NormalizeVector();
  Vector operator+(const Vector& v) const;
  Vector& operator/=(float fl);
  Vector operator-(const Vector& v) const;
  Vector operator*(float fl) const;
  Vector operator*(const Vector & v) const;
  QAngle ToQAngle() const;
  float operator[](int i) const;
  inline float DistTo(const Vector& vOther) const;
  float& operator[](int i);
};

float Vector::DistTo(const Vector& vOther) const {
  Vector delta;

  delta.x = x - vOther.x;
  delta.y = y - vOther.y;
  delta.z = z - vOther.z;

  return delta.Length();
}

inline float& Vector::operator[](int i) {
  return reinterpret_cast<float*>(this)[i];
}

inline float Vector::operator[](int i) const {
  return reinterpret_cast<const float*>(this)[i];
}

inline float Vector::Length() const {
  return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

inline float Vector::Length2D() const {
  return sqrt(this->x * this->x + this->y * this->y);
}

inline float Vector::NormalizeVector() {
  float l = this->Length();
  if (l != 0.0f) {
    *this /= l;
  } else {
    x = 0;
    y = 0;
    z = 0;
  }
  return l;
}

__forceinline void VectorAdd(const Vector& a, const Vector& b, Vector* result) {
  result->x = a.x + b.x;
  result->y = a.y + b.y;
  result->z = a.z + b.z;
}

__forceinline void VectorSubtract(
    const Vector& a, const Vector& b, Vector* result) {
  result->x = a.x - b.x;
  result->y = a.y - b.y;
  result->z = a.z - b.z;
}

__forceinline void VectorMultiply(const Vector& a, float b, Vector* c) {
  c->x = a.x * b;
  c->y = a.y * b;
  c->z = a.z * b;
}

__forceinline void VectorMultiply(const Vector& a, const Vector& b, Vector* c) {
  c->x = a.x * b.x;
  c->y = a.y * b.y;
  c->z = a.z * b.z;
}

__forceinline Vector& Vector::operator/=(float fl) {
  float oofl = 1.0f / fl;
  x *= oofl;
  y *= oofl;
  z *= oofl;
  return *this;
}

inline Vector Vector::operator-(const Vector& v) const {
  Vector res{};
  VectorSubtract(*this, v, &res);
  return res;
}

inline Vector Vector::operator+(const Vector& v) const {
  Vector res{};
  VectorAdd(*this, v, &res);
  return res;
}

inline Vector Vector::operator*(float fl) const {
  Vector res{};
  VectorMultiply(*this, fl, &res);
  return res;
}

inline Vector Vector::operator*(const Vector& v) const {
  Vector res{};
  VectorMultiply(*this, v, &res);
  return res;
}

inline Vector QAngle::ToVector() const {
  return Vector(x, y, z);
}

inline QAngle Vector::ToQAngle() const {
  return QAngle(x, y, z);
}

class Vector2D {
 public:
  float x, y;

  Vector2D() = default;
  Vector2D(float X, float Y);
  explicit Vector2D(const float *pFloat);

  // array access...
  float operator[](int i) const;
  float& operator[](int i);

  // equality
  bool operator==(const Vector2D& v) const;
  bool operator!=(const Vector2D& v) const;

  // arithmetic operations
  Vector2D& operator+=(const Vector2D &v);
  Vector2D& operator-=(const Vector2D &v);
  Vector2D& operator*=(const Vector2D &v);
  Vector2D& operator*=(float s);
  Vector2D& operator/=(const Vector2D &v);
  Vector2D& operator/=(float s);

  // assignment
  Vector2D& operator=(const Vector2D &vOther) = default;

#ifndef VECTOR_NO_SLOW_OPERATIONS
  // copy constructors
  Vector2D(const Vector2D &vOther);

  // arithmetic operations
  Vector2D operator-() const;

  Vector2D operator+(const Vector2D& v) const;
  Vector2D operator-(const Vector2D& v) const;
  Vector2D operator*(const Vector2D& v) const;
  Vector2D operator/(const Vector2D& v) const;
  Vector2D operator*(float fl) const;
  Vector2D operator/(float fl) const;

#else

 private:
  // No copy constructors allowed if we're in optimal mode
  Vector2D(const Vector2D& vOther);
#endif  // VECTOR_NO_SLOW_OPERATIONS
};

inline Vector2D::Vector2D(float X, float Y) : x(X), y(Y) {}

inline Vector2D::Vector2D(const float *pFloat) {
  x = pFloat[0];
  y = pFloat[1];
}

inline Vector2D::Vector2D(const Vector2D &vOther) {
  x = vOther.x;
  y = vOther.y;
}

inline float& Vector2D::operator[](int i) {
  return reinterpret_cast<float*>(this)[i];
}

inline float Vector2D::operator[](int i) const {
  return reinterpret_cast<const float*>(this)[i];
}

inline bool Vector2D::operator==(const Vector2D& src) const {
  return (src.x == x) && (src.y == y);
}

inline bool Vector2D::operator!=(const Vector2D& src) const {
  return (src.x != x) || (src.y != y);
}

inline Vector2D& Vector2D::operator+=(const Vector2D& v) {
  x += v.x;
  y += v.y;
  return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& v) {
  x -= v.x;
  y -= v.y;
  return *this;
}

inline Vector2D& Vector2D::operator*=(float fl) {
  x *= fl;
  y *= fl;
  return *this;
}

inline Vector2D& Vector2D::operator*=(const Vector2D& v) {
  x *= v.x;
  y *= v.y;
  return *this;
}

inline Vector2D& Vector2D::operator/=(float fl) {
  float oofl = 1.0f / fl;
  x *= oofl;
  y *= oofl;
  return *this;
}

inline Vector2D& Vector2D::operator/=(const Vector2D& v) {
  x /= v.x;
  y /= v.y;
  return *this;
}

inline void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D* c) {
  c->x = a.x + b.x;
  c->y = a.y + b.y;
}

inline void Vector2DSubtract(
    const Vector2D& a, const Vector2D& b, Vector2D* c) {
  c->x = a.x - b.x;
  c->y = a.y - b.y;
}

inline void Vector2DMultiply(const Vector2D& a, float b, Vector2D* c) {
  c->x = a.x * b;
  c->y = a.y * b;
}

inline void Vector2DMultiply(
    const Vector2D& a, const Vector2D& b, Vector2D* c) {
  c->x = a.x * b.x;
  c->y = a.y * b.y;
}

inline void Vector2DDivide(const Vector2D& a, float b, Vector2D* c) {
  float oob = 1.0f / b;
  c->x = a.x * oob;
  c->y = a.y * oob;
}

inline void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D* c) {
  c->x = a.x / b.x;
  c->y = a.y / b.y;
}

inline Vector2D Vector2D::operator-() const {
  return Vector2D(-x, -y);
}

inline Vector2D Vector2D::operator+(const Vector2D& v) const {
  Vector2D res{};
  Vector2DAdd(*this, v, &res);
  return res;
}

inline Vector2D Vector2D::operator-(const Vector2D& v) const {
  Vector2D res{};
  Vector2DSubtract(*this, v, &res);
  return res;
}

inline Vector2D Vector2D::operator*(float fl) const {
  Vector2D res{};
  Vector2DMultiply(*this, fl, &res);
  return res;
}

inline Vector2D Vector2D::operator*(const Vector2D& v) const {
  Vector2D res{};
  Vector2DMultiply(*this, v, &res);
  return res;
}

inline Vector2D Vector2D::operator/(float fl) const {
  Vector2D res{};
  Vector2DDivide(*this, fl, &res);
  return res;
}

inline Vector2D Vector2D::operator/(const Vector2D& v) const {
  Vector2D res{};
  Vector2DDivide(*this, v, &res);
  return res;
}

inline Vector2D operator*(float fl, const Vector2D& v) {
  return v * fl;
}

inline void NormalizeAngles(Vector* angle) {
  while (angle->x > 89.0f) {
    angle->x -= 180.f;
  }

  while (angle->x < -89.0f) {
    angle->x += 180.f;
  }

  while (angle->y > 180.f) {
    angle->y -= 360.f;
  }

  while (angle->y < -180.f) {
    angle->y += 360.f;
  }
}

inline float GetFov(const QAngle& viewAngle, const QAngle& aimAngle) {
  Vector delta = aimAngle.ToVector() - viewAngle.ToVector();
  NormalizeAngles(&delta);
  return sqrtf(delta.x * delta.x + delta.y * delta.y);
}

inline void VectorAngles(const Vector& forward, QAngle& angles) {
  if (forward[1] == 0.0f && forward[0] == 0.0f) {
    angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
    angles[1] = 0.0f;  //yaw left/right
  } else {
    angles[0] = atan2(-forward[2], forward.Length2D()) * kRadToDeg;
    angles[1] = atan2(forward[1], forward[0]) * kRadToDeg;

    if (angles[1] > 90.f) {
      angles[1] -= 180.f;
    } else if (angles[1] < 90.f) {
      angles[1] += 180.f;
    } else if (angles[1] == 90.f) {
      angles[1] = 0;
    }
  }

  angles[2] = 0.0f;
}

inline QAngle CalcAngle(Vector src, Vector dst) {
  QAngle angles;
  Vector delta = src - dst;
  VectorAngles(delta, angles);
  delta.NormalizeVector();
  return angles;
}

#endif  // PC_VECTOR_VECTOR_H_
