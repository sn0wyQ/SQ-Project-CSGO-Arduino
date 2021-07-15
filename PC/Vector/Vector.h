#ifndef VECTOR_H_
#define VECTOR_H_
#define _USE_MATH_DEFINES

#include <cfloat>
#include <cmath>
#include <crtdbg.h>
#include <cstdlib>
#include <iostream>

#define DEG2RAD( x )  ( (float)(x) * (float)(M_PI / 180.f) )
#define RAD2DEG( x )  ( (float)(x) * 180.0f / M_PI)

#define CHECK_VALID( _v ) _ASSERT( (_v).IsValid() )
#define Assert( _exp ) ((void)0)

#define VALVE_RAND_MAX 0x7fff

#define FastSqrt( x )			(sqrt)(x)

class QAngle;
class Vector;
struct matrix3x4_t;

typedef float vec_t;

enum
{
  PITCH = 0, // up / down
  YAW, // left / right
  ROLL // fall over
};

void inline SinCos(float radians, float* sine, float* cosine)
{
  _asm
  {
    fld DWORD PTR[radians]
    fsincos

    mov edx, DWORD PTR[cosine]
    mov eax, DWORD PTR[sine]

    fstp DWORD PTR[edx]
    fstp DWORD PTR[eax]
  }
}
struct matrix3x4_t
{
  matrix3x4_t()
  {
  }

  matrix3x4_t(
      float m00, float m01, float m02, float m03,
      float m10, float m11, float m12, float m13,
      float m20, float m21, float m22, float m23)
  {
    m_flMatVal[0][0] = m00;
    m_flMatVal[0][1] = m01;
    m_flMatVal[0][2] = m02;
    m_flMatVal[0][3] = m03;
    m_flMatVal[1][0] = m10;
    m_flMatVal[1][1] = m11;
    m_flMatVal[1][2] = m12;
    m_flMatVal[1][3] = m13;
    m_flMatVal[2][0] = m20;
    m_flMatVal[2][1] = m21;
    m_flMatVal[2][2] = m22;
    m_flMatVal[2][3] = m23;
  }

  float* operator[](int i)
  {
    _ASSERT((i >= 0) && (i < 3));
    return m_flMatVal[i];
  }

  const float* operator[](int i) const
  {
    _ASSERT((i >= 0) && (i < 3));
    return m_flMatVal[i];
  }

  float* Base() { return &m_flMatVal[0][0]; }
  const float* Base() const { return &m_flMatVal[0][0]; }

  float m_flMatVal[3][4];
};

class QAngle
{
 public:
  // Members
  vec_t x, y, z;

  // Construction/destruction
  QAngle(void) = default;

  inline QAngle(vec_t X, vec_t Y, vec_t Z) : x(0), y(0), z(0)
  {
    this->x = X;
    this->y = Y;
    this->z = Z;
  }

  QAngle operator-(const QAngle& v) const;
  QAngle operator*(float fl) const;
  vec_t operator[](int i) const;

  Vector ToVector() const;
  vec_t& operator[](int i);
  float   Length() const;
  float   LengthSqr() const;

  inline QAngle Normalize() const
  {
    QAngle vector;
    float length = this->Length();

    if (length != 0) {
      vector.x = x / length;
      vector.y = y / length;
      vector.z = z / length;
    }
    else
      vector.x = vector.y = 0.0f; vector.z = 1.0f;

    return vector;
  }

  QAngle Normalized()
  {
    if (this->x != this->x)
      this->x = 0;
    if (this->y != this->y)
      this->y = 0;
    if (this->z != this->z)
      this->z = 0;

    if (this->x > 89.f)
      this->x = 89.f;
    if (this->x < -89.f)
      this->x = -89.f;

    while (this->y > 180)
      this->y -= 360;
    while (this->y <= -180)
      this->y += 360;

    if (this->y > 180.f)
      this->y = 180.f;
    if (this->y < -180.f)
      this->y = -180.f;

    this->z = 0;

    return *this;
  }
};

inline float QAngle::Length() const
{
  return static_cast<float>(sqrt(LengthSqr()));
}


inline float QAngle::LengthSqr() const
{
  return x * x + y * y;
}

__forceinline void QAngleSubtract(const QAngle& a, const QAngle& b, QAngle& result)
{
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;
}

__forceinline void QAngleMultiply(const QAngle& a, vec_t b, QAngle& c)
{
  _ASSERT(isfinite(b));
  c.x = a.x * b;
  c.y = a.y * b;
  c.z = a.z * b;
}

inline QAngle QAngle::operator*(float fl) const
{
  QAngle res;
  QAngleMultiply(*this, fl, res);
  return res;
}

inline QAngle QAngle::operator-(const QAngle& v) const
{
  QAngle res;
  QAngleSubtract(*this, v, res);
  return res;
}

inline vec_t& QAngle::operator[](int i)
{
  return ((vec_t*)this)[i];
}

inline vec_t QAngle::operator[](int i) const
{
  return ((vec_t*)this)[i];
}

class Vector
{
 public:
  vec_t x, y, z;
  Vector(void) = default;

  inline Vector(vec_t X, vec_t Y, vec_t Z) : x(0), y(0), z(0)
  {
    this->x = X;
    this->y = Y;
    this->z = Z;
  }

  bool IsValid() const;
  bool IsZero() const;
  Vector Angle();
  Vector Cross(Vector& vOther) const;
  Vector Normalized() const;
  vec_t Length() const;
  vec_t Length2D() const;
  vec_t NormalizeVector();
  Vector operator+(const Vector& v) const;
  Vector& operator/=(float fl);
  Vector operator-(const Vector& v) const;
  Vector operator*(float fl) const;
  Vector operator*(const Vector & v) const;
  QAngle ToQAngle() const;
  vec_t operator[](int i) const;
  vec_t Dot(Vector& vOther) const;
  inline float DistTo(const Vector& vOther) const;
  float DistToSqr(const Vector& vOther) const;
  float Dot(const Vector& vOther) const;
  void Invalidate();
  void NormalizeInPlace();
  vec_t& operator[](int i);
  float LengthSqr() const;

};

inline void AngleVectors(const QAngle &angles, Vector *forward, Vector *right, Vector *up)
{
  float sr, sp, sy, cr, cp, cy;

  SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
  SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);
  SinCos(DEG2RAD(angles[ROLL]), &sr, &cr);

  if (forward)
  {
    forward->x = cp * cy;
    forward->y = cp * sy;
    forward->z = -sp;
  }

  if (right)
  {
    right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
    right->y = (-1 * sr*sp*sy + -1 * cr*cy);
    right->z = -1 * sr*cp;
  }

  if (up)
  {
    up->x = (cr*sp*cy + -sr * -sy);
    up->y = (cr*sp*sy + -sr * cy);
    up->z = cr * cp;
  }
}

inline void VectorAnglesX(Vector* forward, Vector* angles)
{
  float tmp, yaw, pitch;

  if (forward->y == 0 && forward->x == 0)
  {
    yaw = 0;
    if (forward->z > 0)
      pitch = 90.0;
    else
      pitch = 270.0;
  }
  else
  {
    yaw = static_cast<float>(atan2(forward->y, forward->x) * 180.0 / M_PI);

    if (yaw < 0) yaw += 360.0;

    tmp = static_cast<float>(sqrt(forward->x * forward->x + forward->y * forward->y));

    pitch = static_cast<float>(atan2(forward->z, tmp) * 180 / M_PI);
  }

  angles->x = -pitch;
  angles->y = yaw;
  angles->z = 0;
}


inline void AngleToVectors(const Vector& vAngles, Vector* vForward, Vector* vRight, Vector* vUp)
{
  float Angle;
  float sr, sp, sy, cr, cp, cy;

  Angle = static_cast<vec_t>(vAngles.y * (M_PI * 2 / 360));
  sy = sin(Angle);
  cy = cos(Angle);

  Angle = static_cast<vec_t>(vAngles.x * (M_PI * 2 / 360));
  sp = sin(Angle);
  cp = cos(Angle);

  Angle = static_cast<vec_t>(vAngles.z * (M_PI * 2 / 360));
  sr = sin(Angle);
  cr = cos(Angle);

  if (vForward)
  {
    vForward->x = cp * cy;
    vForward->y = cp * sy;
    vForward->z = -sp;
  }
  if (vRight)
  {
    vRight->x = (-1 * sr * sp * cy + -1 * cr * -sy);
    vRight->y = (-1 * sr * sp * sy + -1 * cr * cy);
    vRight->z = -1 * sr * cp;
  }
  if (vUp)
  {
    vUp->x = (cr * sp * cy + -sr * -sy);
    vUp->y = (cr * sp * sy + -sr * cy);
    vUp->z = cr * cp;
  }
}


inline vec_t DotProduct(const Vector& a, const Vector& b)
{
  return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline float DotProduct(const float* v1, const float* v2)
{
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

inline void VectorITransform(const float* in1, const matrix3x4_t& in2, float* out)
{
  float in1t[3];

  in1t[0] = in1[0] - in2[0][3];
  in1t[1] = in1[1] - in2[1][3];
  in1t[2] = in1[2] - in2[2][3];

  out[0] = in1t[0] * in2[0][0] + in1t[1] * in2[1][0] + in1t[2] * in2[2][0];
  out[1] = in1t[0] * in2[0][1] + in1t[1] * in2[1][1] + in1t[2] * in2[2][1];
  out[2] = in1t[0] * in2[0][2] + in1t[1] * in2[1][2] + in1t[2] * in2[2][2];
}


inline void VectorITransform(const Vector& in1, const matrix3x4_t& in2, Vector& out)
{
  VectorITransform(&in1.x, in2, &out.x);
}

// assume in2 is a rotation and rotate the input vector
inline void VectorRotate(const float* in1, const matrix3x4_t& in2, float* out)
{
  out[0] = DotProduct(in1, in2[0]);
  out[1] = DotProduct(in1, in2[1]);
  out[2] = DotProduct(in1, in2[2]);
}

inline void VectorRotate(const Vector& in1, const matrix3x4_t& in2, Vector& out)
{
  VectorRotate(&in1.x, in2, &out.x);
}

float Vector::DistTo(const Vector& vOther) const
{
  Vector delta;

  delta.x = x - vOther.x;
  delta.y = y - vOther.y;
  delta.z = z - vOther.z;

  return delta.Length();
}

inline float Vector::DistToSqr(const Vector& vOther) const
{
  Vector delta;

  delta.x = x - vOther.x;
  delta.y = y - vOther.y;
  delta.z = z - vOther.z;

  return delta.LengthSqr();
}

inline float Vector::Dot(const Vector& vOther) const
{
  const Vector& a = *this;

  return (a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
}
inline void Vector::Invalidate()
{
  Vector& src = *this;
  src.x = src.y = src.z = std::numeric_limits<float>::infinity();
}
inline void Vector::NormalizeInPlace()
{
  Vector& v = *this;

  float iradius = 1.f / (this->Length() + FLT_EPSILON);

  v.x *= iradius;
  v.y *= iradius;
  v.z *= iradius;
}

inline vec_t& Vector::operator[](int i)
{
  return reinterpret_cast<vec_t*>(this)[i];
}

inline vec_t Vector::operator[](int i) const
{
  return ((vec_t*)this)[i];
}

inline vec_t Vector::Dot(Vector& vOther) const
{
  CHECK_VALID(vOther);
  return (this->x * vOther.x + this->y * vOther.y + this->z * vOther.z);
}

__forceinline float Vector::LengthSqr() const
{
  return this->x * this->x + this->y * this->y + this->z * this->z;
}

__forceinline bool Vector::IsValid() const
{
  return isfinite(x) && isfinite(y) && isfinite(z);
}

inline Vector Vector::Normalized() const
{
  Vector res = *this;
  float l = res.Length();
  if (l != 0.0f) {
    res /= l;
  }
  else {
    res.x = res.y = res.z = 0.0f;
  }
  return res;
}


inline void VectorCrossProduct(const Vector& a, const Vector& b, Vector& result)
{
  result.x = a.y*b.z - a.z*b.y;
  result.y = a.z*b.x - a.x*b.z;
  result.z = a.x*b.y - a.y*b.x;
}

inline Vector Vector::Cross(Vector& vOther) const
{
  Vector res;
  VectorCrossProduct(*this, vOther, res);
  return res;
}

inline Vector Vector::Angle()
{
  Vector* up = this;
  if (!x && !y)
    return Vector(0, 0, 0);

  float roll = 0;

  if (up)
  {
    Vector left = (*up).Cross(*this);
    roll = static_cast<vec_t>(atan2f(left.z, (left.y * x) - (left.x * y)) * 180.0f / M_PI);
  }
  return Vector(static_cast<vec_t>(atan2f(-z, sqrt(x * x + y * y)) * 180.0f / M_PI), static_cast<vec_t>(atan2f(y, x) * 180.0f / M_PI), static_cast<vec_t>(roll));
}
__forceinline bool Vector::IsZero() const
{
  return  x == 0 && y == 0 && z == 0;
}

inline vec_t Vector::Length(void) const
{
  return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

inline vec_t Vector::Length2D(void) const
{
  return sqrt(this->x * this->x + this->y * this->y);
}

inline vec_t Vector::NormalizeVector()
{
  vec_t l = this->Length();
  if (l != 0.0f)
  {
    *this /= l;
  }
  else
  {
    x = 0;
    y = 0;
    z = 0;
  }
  return l;
}

__forceinline void VectorAdd(const Vector& a, const Vector& b, Vector& result)
{
  CHECK_VALID(a);
  CHECK_VALID(b);
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  result.z = a.z + b.z;
}

__forceinline void VectorSubtract(const Vector& a, const Vector& b, Vector& result)
{
  CHECK_VALID(a);
  CHECK_VALID(b);
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;
}

__forceinline void VectorMultiply(const Vector& a, vec_t b, Vector& c)
{
  CHECK_VALID(a);
  _ASSERT(isfinite(b));
  c.x = a.x * b;
  c.y = a.y * b;
  c.z = a.z * b;
}
__forceinline void VectorMultiply(const Vector& a, const Vector& b, Vector& c)
{
  CHECK_VALID(a);
  CHECK_VALID(b);
  c.x = a.x * b.x;
  c.y = a.y * b.y;
  c.z = a.z * b.z;
}

__forceinline Vector& Vector::operator/=(float fl)
{
  float oofl = 1.0f / fl;
  x *= oofl;
  y *= oofl;
  z *= oofl;
  CHECK_VALID(*this);
  return *this;
}

inline Vector Vector::operator-(const Vector& v) const
{
  Vector res;
  VectorSubtract(*this, v, res);
  return res;
}

inline Vector Vector::operator+(const Vector& v) const
{
  Vector res;
  VectorAdd(*this, v, res);
  return res;
}

inline Vector Vector::operator*(float fl) const
{
  Vector res;
  VectorMultiply(*this, fl, res);
  return res;
}
inline Vector Vector::operator*(const Vector& v) const
{
  Vector res;
  VectorMultiply(*this, v, res);
  return res;
}


inline void AngleVectors(const QAngle& angles, Vector* forward)
{
  float sp, sy, cp, cy;

  SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
  SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

  forward->x = cp * cy;
  forward->y = cp * sy;
  forward->z = -sp;
}

inline Vector QAngle::ToVector() const
{
  return Vector(x, y, z);
}

inline QAngle Vector::ToQAngle() const
{
  return QAngle(x, y, z);
}

#endif

class Vector2D
{
 public:
  // Members
  float x, y;

  // Construction/destruction
  Vector2D(void);
  Vector2D(float X, float Y);
  Vector2D(const float *pFloat);

  // Initialization
  void Init(float ix = 0.0f, float iy = 0.0f);

  // Got any nasty NAN's?
  bool IsValid() const;

  // array access...
  float operator[](int i) const;
  float& operator[](int i);

  // Base address...
  float* Base();
  float const* Base() const;

  // Initialization methods
  void Random(float minVal, float maxVal);

  // equality
  bool operator==(const Vector2D& v) const;
  bool operator!=(const Vector2D& v) const;

  // arithmetic operations
  Vector2D&	operator+=(const Vector2D &v);
  Vector2D&	operator-=(const Vector2D &v);
  Vector2D&	operator*=(const Vector2D &v);
  Vector2D&	operator*=(float s);
  Vector2D&	operator/=(const Vector2D &v);
  Vector2D&	operator/=(float s);

  // negate the Vector2D components
  void	Negate();

  // Get the Vector2D's magnitude.
  float	Length() const;

  // Get the Vector2D's magnitude squared.
  float	LengthSqr(void) const;

  // return true if this vector is (0,0) within tolerance
  bool IsZero(float tolerance = 0.01f) const
  {
    return (x > -tolerance && x < tolerance &&
        y > -tolerance && y < tolerance);
  }

  float	Normalize();

  // Normalize in place and return the old length.
  float	NormalizeInPlace();

  // Compare length.
  bool	IsLengthGreaterThan(float val) const;
  bool	IsLengthLessThan(float val) const;

  // Get the distance from this Vector2D to the other one.
  float	DistTo(const Vector2D &vOther) const;

  // Get the distance from this Vector2D to the other one squared.
  float	DistToSqr(const Vector2D &vOther) const;

  // Copy
  void	CopyToArray(float* rgfl) const;

  // Multiply, add, and assign to this (ie: *this = a + b * scalar). This
  // is about 12% faster than the actual Vector2D equation (because it's done per-component
  // rather than per-Vector2D).
  void	MulAdd(const Vector2D& a, const Vector2D& b, float scalar);

  // Dot product.
  float	Dot(const Vector2D& vOther) const;

  // assignment
  Vector2D& operator=(const Vector2D &vOther);

#ifndef VECTOR_NO_SLOW_OPERATIONS
  // copy constructors
  Vector2D(const Vector2D &vOther);

  // arithmetic operations
  Vector2D	operator-(void) const;

  Vector2D	operator+(const Vector2D& v) const;
  Vector2D	operator-(const Vector2D& v) const;
  Vector2D	operator*(const Vector2D& v) const;
  Vector2D	operator/(const Vector2D& v) const;
  Vector2D	operator*(float fl) const;
  Vector2D	operator/(float fl) const;

  // Cross product between two vectors.
  Vector2D	Cross(const Vector2D &vOther) const;

  // Returns a Vector2D with the min or max in X, Y, and Z.
  Vector2D	Min(const Vector2D &vOther) const;
  Vector2D	Max(const Vector2D &vOther) const;

#else

  private:
	// No copy constructors allowed if we're in optimal mode
	Vector2D(const Vector2D& vOther);
#endif  // VECTOR_NO_SLOW_OPERATIONS
};

// Vector2D clear
void Vector2DClear(Vector2D& a);

// Copy
void Vector2DCopy(const Vector2D& src, Vector2D& dst);

// Vector2D arithmetic
void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMultiply(const Vector2D& a, float b, Vector2D& result);
void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DDivide(const Vector2D& a, float b, Vector2D& result);
void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result);

// Store the min or max of each of x, y, and z into the result.
void Vector2DMin(const Vector2D &a, const Vector2D &b, Vector2D &result);
void Vector2DMax(const Vector2D &a, const Vector2D &b, Vector2D &result);

#define Vector2DExpand( v ) (v).x, (v).y

// Normalization
float Vector2DNormalize(Vector2D& v);

// Length
float Vector2DLength(const Vector2D& v);

// Dot Product
float DotProduct2D(const Vector2D& a, const Vector2D& b);

// Linearly interpolate between two vectors
void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, float t, Vector2D& dest);


//-----------------------------------------------------------------------------
//
// Inlined Vector2D methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------

inline Vector2D::Vector2D(void)
{
#ifdef _DEBUG
  // Initialize to NAN to catch errors
	//x = y = float_NAN;
#endif  // _DEBUG
}

inline Vector2D::Vector2D(float X, float Y)
{
  x = X; y = Y;
  Assert(IsValid());
}

inline Vector2D::Vector2D(const float *pFloat)
{
  Assert(pFloat);
  x = pFloat[0]; y = pFloat[1];
  Assert(IsValid());
}


//-----------------------------------------------------------------------------
// copy constructor
//-----------------------------------------------------------------------------

inline Vector2D::Vector2D(const Vector2D &vOther)
{
  Assert(vOther.IsValid());
  x = vOther.x; y = vOther.y;
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

inline void Vector2D::Init(float ix, float iy)
{
  x = ix; y = iy;
  Assert(IsValid());
}

inline void Vector2D::Random(float minVal, float maxVal)
{
  x = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
  y = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
}

inline void Vector2DClear(Vector2D& a)
{
  a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline Vector2D& Vector2D::operator=(const Vector2D &vOther)
{
  Assert(vOther.IsValid());
  x = vOther.x; y = vOther.y;
  return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline float& Vector2D::operator[](int i)
{
  Assert((i >= 0) && (i < 2));
  return ((float*)this)[i];
}

inline float Vector2D::operator[](int i) const
{
  Assert((i >= 0) && (i < 2));
  return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

inline float* Vector2D::Base()
{
  return (float*)this;
}

inline float const* Vector2D::Base() const
{
  return (float const*)this;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool Vector2D::operator==(const Vector2D& src) const
{
  Assert(src.IsValid() && IsValid());
  return (src.x == x) && (src.y == y);
}

inline bool Vector2D::operator!=(const Vector2D& src) const
{
  Assert(src.IsValid() && IsValid());
  return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void Vector2DCopy(const Vector2D& src, Vector2D& dst)
{
  Assert(src.IsValid());
  dst.x = src.x;
  dst.y = src.y;
}

inline void	Vector2D::CopyToArray(float* rgfl) const
{
  Assert(IsValid());
  Assert(rgfl);
  rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

inline void Vector2D::Negate()
{
  Assert(IsValid());
  x = -x; y = -y;
}

inline Vector2D& Vector2D::operator+=(const Vector2D& v)
{
  Assert(IsValid() && v.IsValid());
  x += v.x; y += v.y;
  return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& v)
{
  Assert(IsValid() && v.IsValid());
  x -= v.x; y -= v.y;
  return *this;
}

inline Vector2D& Vector2D::operator*=(float fl)
{
  x *= fl;
  y *= fl;
  Assert(IsValid());
  return *this;
}

inline Vector2D& Vector2D::operator*=(const Vector2D& v)
{
  x *= v.x;
  y *= v.y;
  Assert(IsValid());
  return *this;
}

inline Vector2D& Vector2D::operator/=(float fl)
{
  Assert(fl != 0.0f);
  float oofl = 1.0f / fl;
  x *= oofl;
  y *= oofl;
  Assert(IsValid());
  return *this;
}

inline Vector2D& Vector2D::operator/=(const Vector2D& v)
{
  Assert(v.x != 0.0f && v.y != 0.0f);
  x /= v.x;
  y /= v.y;
  Assert(IsValid());
  return *this;
}

inline void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
  Assert(a.IsValid() && b.IsValid());
  c.x = a.x + b.x;
  c.y = a.y + b.y;
}

inline void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
  Assert(a.IsValid() && b.IsValid());
  c.x = a.x - b.x;
  c.y = a.y - b.y;
}

inline void Vector2DMultiply(const Vector2D& a, float b, Vector2D& c)
{
  Assert(a.IsValid() && IsFinite(b));
  c.x = a.x * b;
  c.y = a.y * b;
}

inline void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
  Assert(a.IsValid() && b.IsValid());
  c.x = a.x * b.x;
  c.y = a.y * b.y;
}


inline void Vector2DDivide(const Vector2D& a, float b, Vector2D& c)
{
  Assert(a.IsValid());
  Assert(b != 0.0f);
  float oob = 1.0f / b;
  c.x = a.x * oob;
  c.y = a.y * oob;
}

inline void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
  Assert(a.IsValid());
  Assert((b.x != 0.0f) && (b.y != 0.0f));
  c.x = a.x / b.x;
  c.y = a.y / b.y;
}

inline void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result)
{
  Assert(start.IsValid() && IsFinite(s) && dir.IsValid());
  result.x = start.x + s * dir.x;
  result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
inline void	Vector2D::MulAdd(const Vector2D& a, const Vector2D& b, float scalar)
{
  x = a.x + b.x * scalar;
  y = a.y + b.y * scalar;
}

inline void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, float t, Vector2D& dest)
{
  dest[0] = src1[0] + (src2[0] - src1[0]) * t;
  dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
inline float DotProduct2D(const Vector2D& a, const Vector2D& b)
{
  Assert(a.IsValid() && b.IsValid());
  return(a.x*b.x + a.y*b.y);
}

// for backwards compatability
inline float Vector2D::Dot(const Vector2D& vOther) const
{
  return DotProduct2D(*this, vOther);
}


//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float Vector2DLength(const Vector2D& v)
{
  Assert(v.IsValid());
  return (float)FastSqrt(v.x*v.x + v.y*v.y);
}

inline float Vector2D::LengthSqr(void) const
{
  Assert(IsValid());
  return (x*x + y * y);
}

inline float Vector2D::NormalizeInPlace()
{
  return Vector2DNormalize(*this);
}

inline bool Vector2D::IsLengthGreaterThan(float val) const
{
  return LengthSqr() > val*val;
}

inline bool Vector2D::IsLengthLessThan(float val) const
{
  return LengthSqr() < val*val;
}

inline float Vector2D::Length(void) const
{
  return Vector2DLength(*this);
}


inline void Vector2DMin(const Vector2D &a, const Vector2D &b, Vector2D &result)
{
  result.x = (a.x < b.x) ? a.x : b.x;
  result.y = (a.y < b.y) ? a.y : b.y;
}


inline void Vector2DMax(const Vector2D &a, const Vector2D &b, Vector2D &result)
{
  result.x = (a.x > b.x) ? a.x : b.x;
  result.y = (a.y > b.y) ? a.y : b.y;
}


//-----------------------------------------------------------------------------
// Normalization
//-----------------------------------------------------------------------------
inline float Vector2DNormalize(Vector2D& v)
{
  Assert(v.IsValid());
  float l = v.Length();
  if (l != 0.0f)
  {
    v /= l;
  }
  else
  {
    v.x = v.y = 0.0f;
  }
  return l;
}


//-----------------------------------------------------------------------------
// Get the distance from this Vector2D to the other one
//-----------------------------------------------------------------------------
inline float Vector2D::DistTo(const Vector2D &vOther) const
{
  Vector2D delta;
  Vector2DSubtract(*this, vOther, delta);
  return delta.Length();
}

inline float Vector2D::DistToSqr(const Vector2D &vOther) const
{
  Vector2D delta;
  Vector2DSubtract(*this, vOther, delta);
  return delta.LengthSqr();
}


//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
inline void ComputeClosestPoint2D(const Vector2D& vecStart, float flMaxDist, const Vector2D& vecTarget, Vector2D *pResult)
{
  Vector2D vecDelta;
  Vector2DSubtract(vecTarget, vecStart, vecDelta);
  float flDistSqr = vecDelta.LengthSqr();
  if (flDistSqr <= flMaxDist * flMaxDist)
  {
    *pResult = vecTarget;
  }
  else
  {
    vecDelta /= FastSqrt(flDistSqr);
    Vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
  }
}

//-----------------------------------------------------------------------------
// Returns a Vector2D with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------
inline Vector2D Vector2D::Min(const Vector2D &vOther) const
{
  return Vector2D(x < vOther.x ? x : vOther.x,
                  y < vOther.y ? y : vOther.y);
}
inline Vector2D Vector2D::Max(const Vector2D &vOther) const
{
  return Vector2D(x > vOther.x ? x : vOther.x,
                  y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

inline Vector2D Vector2D::operator-(void) const
{
  return Vector2D(-x, -y);
}

inline Vector2D Vector2D::operator+(const Vector2D& v) const
{
  Vector2D res;
  Vector2DAdd(*this, v, res);
  return res;
}

inline Vector2D Vector2D::operator-(const Vector2D& v) const
{
  Vector2D res;
  Vector2DSubtract(*this, v, res);
  return res;
}

inline Vector2D Vector2D::operator*(float fl) const
{
  Vector2D res;
  Vector2DMultiply(*this, fl, res);
  return res;
}

inline Vector2D Vector2D::operator*(const Vector2D& v) const
{
  Vector2D res;
  Vector2DMultiply(*this, v, res);
  return res;
}

inline Vector2D Vector2D::operator/(float fl) const
{
  Vector2D res;
  Vector2DDivide(*this, fl, res);
  return res;
}

inline Vector2D Vector2D::operator/(const Vector2D& v) const
{
  Vector2D res;
  Vector2DDivide(*this, v, res);
  return res;
}

inline Vector2D operator*(float fl, const Vector2D& v)
{
  return v * fl;
}

inline  void AngleVectors(const QAngle &angles, Vector& forward)
{
  Assert(s_bMathlibInitialized);
  Assert(forward);

  float sp, sy, cp, cy;

  SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
  SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

  forward.x = cp * cy;
  forward.y = cp * sy;
  forward.z = -sp;
}

inline void ClampAngles(Vector& qaAngs)
{
  if (qaAngs.x > 89.0f)
    qaAngs.x = 89.0f;

  if (qaAngs.x < -89.0f)
    qaAngs.x = -89.0f;

  while (qaAngs.y > 180)
    qaAngs.y -= 360;

  while (qaAngs.y < -180)
    qaAngs.y += 360;

  qaAngs.z = 0;
}

inline float RandFloat(float a, float b)
{
  return ((b - a)*(static_cast<float>(rand()) / RAND_MAX)) + a;
}

inline void NormalizeAngles(Vector& angle)
{
  while (angle.x > 89.0f)
    angle.x -= 180.f;

  while (angle.x < -89.0f)
    angle.x += 180.f;

  while (angle.y > 180.f)
    angle.y -= 360.f;

  while (angle.y < -180.f)
    angle.y += 360.f;
}

inline float ClampYaw(float qYaw)
{
  while (qYaw > 180)
    qYaw -= 360;

  while (qYaw < -180)
    qYaw += 360;

  return qYaw;
}

inline float GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
{
  Vector delta = aimAngle.ToVector() - viewAngle.ToVector();
  NormalizeAngles(delta);
  return sqrtf(delta.x * delta.x + delta.y * delta.y);
}

inline float CrosshairDistance(const QAngle& viewAngle, const QAngle& aimAngle, float distance)
{
  auto fPitchDifference = sin(abs(DEG2RAD(aimAngle.x - viewAngle.x))) * distance;
  auto fYawDifference = sin(abs(DEG2RAD(aimAngle.y - viewAngle.y))) * distance;

  return sqrt(fPitchDifference * fPitchDifference + fYawDifference * fYawDifference);
}

inline void VectorAngles(const Vector &forward, const Vector &up, Vector &angles)
{
  auto left = up * forward;
  left.NormalizeInPlace();

  auto xyDist = forward.Length2D();

  if (xyDist > 0.001f)
  {
    angles.x = static_cast<vec_t>(RAD2DEG(atan2f(-forward.z, xyDist)));
    angles.y = static_cast<vec_t>(RAD2DEG(atan2f(forward.y, forward.x)));

    auto up_z = (left.y * forward.x) - (left.x * forward.y);

    angles.z = static_cast<vec_t>(RAD2DEG(atan2f(left.z, up_z)));
  }
  else
  {
    angles.x = static_cast<vec_t>(RAD2DEG(atan2f(-forward.z, xyDist)));
    angles.y = static_cast<vec_t>(RAD2DEG(atan2f(-left.x, left.y)));
    angles.z = 0;
  }
}

inline void VectorAngles(const Vector& forward, QAngle &angles)
{
  if (forward[1] == 0.0f && forward[0] == 0.0f)
  {
    angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
    angles[1] = 0.0f;  //yaw left/right
  }
  else
  {
    angles[0] = static_cast<vec_t>(atan2(-forward[2], forward.Length2D()) * -180 / M_PI);
    angles[1] = static_cast<vec_t>(atan2(forward[1], forward[0]) * 180 / M_PI);

    if (angles[1] > 90)
      angles[1] -= 180;
    else if (angles[1] < 90)
      angles[1] += 180;
    else if (angles[1] == 90)
      angles[1] = 0;
  }

  angles[2] = 0.0f;
}

inline QAngle CalcAngle(Vector src, Vector dst)
{
  QAngle angles;
  Vector delta = src - dst;

  VectorAngles(delta, angles);

  delta.NormalizeVector();

  return angles;
}

inline float Distance3D(float X, float Y, float Z, float eX, float eY, float eZ)
{
  return(sqrtf((eX - X) * (eX - X) + (eY - Y) * (eY - Y) + (eZ - Z) * (eZ - Z)));
}

inline float Distance3D(Vector from, Vector to) {
  return Distance3D(from[0], from[1], from[2], to[0], to[1], to[2]);
}

inline void AngleVectors2(const Vector& qAngles, Vector& vecForward)
{
  float sp, sy, cp, cy;
  SinCos(static_cast<float>(qAngles[1] * (M_PI / 180.f)), &sy, &cy);
  SinCos(static_cast<float>(qAngles[0] * (M_PI / 180.f)), &sp, &cp);

  vecForward[0] = cp * cy;
  vecForward[1] = cp * sy;
  vecForward[2] = -sp;
}

inline void VectorAngles2(const Vector &vecForward, Vector &vecAngles)
{
  Vector vecView;
  if (vecForward[1] == 0.f && vecForward[0] == 0.f)
  {
    vecView[0] = 0.f;
    vecView[1] = 0.f;
  }
  else
  {
    vecView[1] = static_cast<vec_t>(atan2(vecForward[1], vecForward[0]) * 180.f / M_PI);

    if (vecView[1] < 0.f)
      vecView[1] += 360.f;

    vecView[2] = static_cast<vec_t>(sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]));

    vecView[0] = static_cast<vec_t>(atan2(vecForward[2], vecView[2]) * 180.f / M_PI);
  }

  vecAngles[0] = -vecView[0];
  vecAngles[1] = vecView[1];
  vecAngles[2] = 0.f;
}

inline Vector Lerp(Vector start, Vector end, float percent)
{
  ClampAngles(start);
  ClampAngles(end);
  NormalizeAngles(start);
  NormalizeAngles(end);
  auto v = (start + ((end - start) * percent));
  NormalizeAngles(v);
  return v;
}

#endif  // VECTOR_H_
