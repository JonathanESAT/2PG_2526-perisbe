/** 
 *  
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Vec2 facilities header.
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


union Vec2 {
  //*** Constructors and destructor:
  FInline Vec2();
  FInline Vec2(const float value);
  FInline Vec2(const float v[2]);
  FInline Vec2(const float vx, const float vy);
  FInline Vec2(const Vec2& v);
  FInline Vec2(Vec2&& v) noexcept;
  FInline ~Vec2();

  //*** Arithmetical operators:
  FInline Vec2 operator+(const Vec2& v) const;
  FInline Vec2 operator-(const Vec2& v) const;
  FInline Vec2 operator*(const float v) const;

  //*** Assignment operators:
  FInline Vec2& operator+=(const Vec2& v);
  FInline Vec2& operator-=(const Vec2& v);
  FInline Vec2& operator*=(const float v);

  FInline Vec2& operator=(Vec2&& v) noexcept;
  FInline Vec2& operator=(const Vec2& v);

  //*** Access operator:
  FInline float& operator[](const int position);

  //*** Comparison operators:
  FInline bool operator==(const Vec2& v) const;
  FInline bool operator!=(const Vec2& v) const;
  FInline bool operator<(const Vec2& v) const;  //Works with length.
  FInline bool operator<=(const Vec2& v) const; //Works with length.
  FInline bool operator>(const Vec2& v) const;  //Works with length.
  FInline bool operator>=(const Vec2& v) const; //Works with length.

  //*** Data:
  struct { float x, y; };
  struct { float r, g; };
  struct { float f[2]; };
};


//*** Length functions:
FStatic float Vec2Length(const Vec2& v);        //With sqrt.
FStatic float Vec2SquaredLength(const Vec2& v); //Without sqrt.
FStatic Vec2 Vec2Normalize(const Vec2& v);
FStatic bool Vec2IsNormalized(const Vec2& v,
                              const float tolerance = 0.00002f);

//*** Lerp and clamp functions:
FStatic Vec2 Vec2Lerp(const Vec2& a, const Vec2& b, const float t);
FStatic Vec2 Vec2Clamp(const Vec2& a, const float max_length);

//*** Perpendicular and reflect functions:
FStatic Vec2 Vec2Perpendicular2D_1(const Vec2& v);
FStatic Vec2 Vec2Perpendicular2D_2(const Vec2& v);
FStatic Vec2 Vec2Reflect(const Vec2& v, const Vec2& normal);

//*** Dot functions:
FStatic float Vec2Dot(const Vec2& a, const Vec2& b);
FStatic float Vec2Angle(const Vec2& a, const Vec2& b); //Uses dot.
FStatic float Vec2Angle(const Vec2& a);                //Uses dot.

//*** Print function:
FStatic void Vec2Print(const Vec2& v);

} //ML


#ifdef INLINED
#include "vec_2.inl"
#endif

