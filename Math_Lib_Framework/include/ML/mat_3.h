/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Mat3 facilities header.
 *
 */

#pragma once


#include "vec_2.h"
#include "vec_3.h"
#include "mat_2.h"


namespace ML {

#ifdef INLINED
#define FInlineM3 __forceinline
#define FStatic static
#else
#define FInlineM3 
#define FStatic 
#endif


struct Mat3 {
  //*** Constructors and destructor:
  FInlineM3 Mat3();
  FInlineM3 Mat3(const float a[9]);
  FInlineM3 Mat3(const float a);
  FInlineM3 Mat3(const Vec3 a, const Vec3 b, const Vec3 c);
  FInlineM3 Mat3(const float a0, const float a1, const float a2, 
                 const float a3, const float a4, const float a5, 
                 const float a6, const float a7, const float a8);
  FInlineM3 Mat3(const Mat3& a);
  FInlineM3 Mat3(Mat3&& a) noexcept;
  FInlineM3 ~Mat3();

  //*** Arithmetical operators:
  FInlineM3 Mat3 operator+(const Mat3& b) const;
  FInlineM3 Mat3 operator-(const Mat3& b) const;
  FInlineM3 Mat3 operator*(const Mat3& b) const;
  FInlineM3 Mat3 operator*(float b) const;
  //Acts like a point. Should homogenize:
  FInlineM3 Vec2 operator*(const Vec2& b) const;
  FInlineM3 Vec3 operator*(const Vec3& b) const; //Should homogeneize.

  //*** Assignment operators:
  FInlineM3 void operator+=(const Mat3& b);
  FInlineM3 void operator-=(const Mat3& b);
  FInlineM3 void operator*=(const Mat3& b);
  FInlineM3 void operator*=(float b);
  FInlineM3 Mat3 operator=(Mat3&& a) noexcept;
  FInlineM3 Mat3 operator=(const Mat3& a);

  //*** Access operator:
  FInlineM3 float& operator[](const int position);

  //*** Comparison operators:
  FInlineM3 bool operator==(const Mat3& a);
  FInlineM3 bool operator!=(const Mat3& a);

  //*** Data:
  float m[9];
};

//*** Functions:
FStatic Mat3 Mat3InitAsIdentity();
FStatic Mat3 Mat3Transpose(const Mat3& a);

//*** Basic transform functions:
FStatic Mat3 Mat3InitAsScale(float x, float y);
FStatic Mat3 Mat3InitAsRotate(float radians);
FStatic Mat3 Mat3InitAsTranslate(float x, float y);

//*** Print function:
FStatic void Mat3Print(const Mat3& m);

} //ML


#ifdef INLINED
#include "mat_3.inl"
#endif

