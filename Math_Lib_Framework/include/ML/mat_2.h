/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Mat2 facilities header.
 *
 */

#pragma once


#include "vec_2.h"


namespace ML {

#ifdef INLINED
#define FInlineM2 __forceinline
#define FStatic static
#else
#define FInlineM2 
#define FStatic 
#endif


struct Mat2 {
  //*** Constructors and destructor:
  FInlineM2 Mat2();
  FInlineM2 Mat2(const float a[4]);
  FInlineM2 Mat2(const float a);
  FInlineM2 Mat2(const Vec2 a, const Vec2 b);
  FInlineM2 Mat2(const float a0, const float a1, 
                 const float a2, const float a3);
  FInlineM2 Mat2(const Mat2& a);
  FInlineM2 Mat2(Mat2&& a) noexcept;
  FInlineM2 ~Mat2();

  //*** Arithmetical operators:
  FInlineM2 Mat2 operator+(const Mat2& b) const;
  FInlineM2 Mat2 operator-(const Mat2& b) const;
  FInlineM2 Mat2 operator*(const Mat2& b) const;
  FInlineM2 Mat2 operator*(float b) const;
  FInlineM2 Vec2 operator*(const Vec2& b) const;

  //*** Assignment operators:
  FInlineM2 void operator+=(const Mat2& b);
  FInlineM2 void operator-=(const Mat2& b);
  FInlineM2 void operator*=(const Mat2& b);
  FInlineM2 void operator*=(float b);
  FInlineM2 Mat2 operator=(Mat2&& a) noexcept;
  FInlineM2 Mat2 operator=(const Mat2& a);

  //*** Access operator:
  FInlineM2 float& operator[](const int position);

  //*** Comparison operators:
  FInlineM2 bool operator==(const Mat2& a);
  FInlineM2 bool operator!=(const Mat2& a);

  //*** Data:
  float m[4];
};

//*** Functions:
FStatic Mat2 Mat2Transpose(const Mat2& a);
FStatic Mat2 Mat2InitAsIdentity();

//*** Print function:
FStatic void Mat2Print(const Mat2& m);

} //ML


#ifdef INLINED
#include "mat_2.inl"
#endif

