/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Vec4 facilities header.
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


union Vec4 {
  //*** Constructors and destructor:
  FInline Vec4();
  FInline Vec4(const float value);
  FInline Vec4(const float v[4]);
  FInline Vec4(const float vx, const float vy);
  FInline Vec4(const float vx, const float vy, const float vz);
  FInline Vec4(const float vx, const float vy, const float vz, 
               const float vw);
  FInline Vec4(const Vec4& v);
  FInline Vec4(Vec4&& v) noexcept;
  FInline ~Vec4();

  //*** Arithmetical operators:
  FInline Vec4 operator+(const Vec4& v) const;
  FInline Vec4 operator-(const Vec4& v) const;
  FInline Vec4 operator*(const float v) const;

  //*** Assignment operators:
  FInline Vec4& operator+=(const Vec4& v);
  FInline Vec4& operator-=(const Vec4& v);
  FInline Vec4& operator*=(const float v);

  FInline Vec4& operator=(Vec4&& v) noexcept;
  FInline Vec4& operator=(const Vec4& v);

  //*** Access operator:
  FInline float& operator[](const int position);

  //*** Comparison operators:
  FInline bool operator==(const Vec4& v) const;
  FInline bool operator!=(const Vec4& v) const;
  FInline bool operator<(const Vec4& v) const;
  FInline bool operator<=(const Vec4& v) const;
  FInline bool operator>(const Vec4& v) const;
  FInline bool operator>=(const Vec4& v) const;

  //*** Data:
  struct { float x, y, z, w; };
  struct { float r, g, b, a; };
  struct { float f[4]; };
};


//*** Length functions:
FStatic float Vec4Length(const Vec4& v);        //With sqrt.
FStatic float Vec4SquaredLength(const Vec4& v); //Without sqrt.
FStatic Vec4 Vec4Normalize(const Vec4& v);
FStatic bool Vec4IsNormalized(const Vec4& v, 
                              const float tolerance = 0.00002f);

//*** Lerp, clamp and homogenize functions:
FStatic Vec4 Vec4Lerp(const Vec4& a, const Vec4& b, const float t);
FStatic Vec4 Vec4Clamp(const Vec4& a, const float max_length);
FStatic Vec4 Vec4Homogenize(const Vec4& v);

//*** Reflect and refract functions:
FStatic Vec4 Vec4Reflect(const Vec4& v, const Vec4& normal,
                         const bool normalize_output = true);
FStatic Vec4 Vec4Refract(const Vec4& iv, const Vec4& normal, 
                         const float ref_idx,
                         const bool normalize_output = true);

//*** Cross and dot functions:
FStatic Vec4 Vec4Cross(const Vec4& a, const Vec4& b);
FStatic float Vec4Dot(const Vec4& a, const Vec4& b);   //-1.0f, 1.0f
FStatic float Vec4Angle(const Vec4& a, const Vec4& b); //-pi, pi
FStatic float Vec4Angle(const Vec4& a);                //-pi, pi

//*** Print function:
FStatic void Vec4Print(const Vec4& v);

} //ML


#if INLINED
#include "vec_4.inl"
#endif

