/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Vec3 facilities header.
 *
 */

#pragma once


namespace ML {

#ifdef INLINED
#define FInline __forceinline
#define FStatic static
#else
#define FInline 
#define FStatic 
#endif


union Vec3 {
  //*** Constructors and destructor:
  FInline Vec3();
  FInline Vec3(const float value);
  FInline Vec3(const float v[3]);
  FInline Vec3(const float vx, const float vy);
  FInline Vec3(const float vx, const float vy, const float vz);
  FInline Vec3(const Vec3& v);
  FInline Vec3(Vec3&& v) noexcept;
  FInline ~Vec3();

  //*** Arithmetical operators:
  FInline Vec3 operator+(const Vec3& v) const;
  FInline Vec3 operator-(const Vec3& v) const;
  FInline Vec3 operator*(const float v) const;

  //*** Assignment operators:
  FInline Vec3& operator+=(const Vec3& v);
  FInline Vec3& operator-=(const Vec3& v);
  FInline Vec3& operator*=(const float v);

  FInline Vec3& operator=(Vec3&& v) noexcept;
  FInline Vec3& operator=(const Vec3& v);

  //*** Access operator:
  FInline float& operator[](const int position);

  //*** Comparison operators:
  FInline bool operator==(const Vec3& v) const;
  FInline bool operator!=(const Vec3& v) const;
  FInline bool operator<(const Vec3& v) const;  //Works with length.
  FInline bool operator<=(const Vec3& v) const; //Works with length.
  FInline bool operator>(const Vec3& v) const;  //Works with length.
  FInline bool operator>=(const Vec3& v) const; //Works with length.

  //*** Data:
  struct { float x, y, z; };
  struct { float r, g, b; };
  struct { float f[3]; };
};


//*** Length functions:
FStatic float Vec3Length(const Vec3& v);        //With sqrt.
FStatic float Vec3SquaredLength(const Vec3& v); //Without sqrt.
FStatic Vec3 Vec3Normalize(const Vec3& v);
FStatic bool Vec3IsNormalized(const Vec3& v, 
                              const float tolerance = 0.00002f);

//*** Lerp, clamp and homogenize functions:
FStatic Vec3 Vec3Lerp(const Vec3& a, const Vec3& b, const float t);
FStatic Vec3 Vec3Clamp(const Vec3& a, const float max_length);
FStatic Vec3 Vec3Homogenize(const Vec3& v);

//*** Perpendicular functions:
FStatic Vec3 Vec3Cross(const Vec3& a, const Vec3& b);
FStatic Vec3 Vec3Perpendicular2D_1(const Vec3& v);
FStatic Vec3 Vec3Perpendicular2D_2(const Vec3& v);

//*** Reflect and refract functions:
FStatic Vec3 Vec3Reflect(const Vec3& iv, const Vec3& normal,
                         const bool normalize_output = true);
FStatic Vec3 Vec3Refract(const Vec3& iv, const Vec3& normal, 
                         const float ref_idx,
                         const bool normalize_output = true);

//*** Dot functions:
FStatic float Vec3Dot(const Vec3& a, const Vec3& b);   //-1.0f, 1.0f
FStatic float Vec3Angle(const Vec3& a, const Vec3& b); //-pi, pi
FStatic float Vec3Angle(const Vec3& a);                //-pi, pi

//*** Print function:
FStatic void Vec3Print(const Vec3& v);

} //ML


#ifdef INLINED
#include "vec_3.inl"
#endif

