/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Mat4 facilities header.
 *
 */

#pragma once


#include "vec_3.h"
#include "vec_4.h"
#include "mat_3.h"


namespace ML {

#ifdef INLINED
#define FInlineM4 __forceinline
#define FStatic static
#else
#define FInlineM4 
#define FStatic 
#endif


struct Mat4 {
  //*** Constructors and destructor:
  FInlineM4 Mat4();
  FInlineM4 Mat4(const float a[16]);
  FInlineM4 Mat4(const float a);
  FInlineM4 Mat4(const Vec4 a, const Vec4 b, const Vec4 c, 
                 const Vec4 d);
  FInlineM4 Mat4(const float a0, const float a1, const float a2, 
                 const float a3, const float a4, const float a5, 
                 const float a6, const float a7, const float a8, 
                 const float a9, const float a10, const float a11, 
                 const float a12, const float a13, const float a14, 
                 const float a15);
  FInlineM4 Mat4(const Mat3& a);
  FInlineM4 Mat4(const Mat4& a);
  FInlineM4 Mat4(Mat4&& a) noexcept;
  FInlineM4 ~Mat4();

  //*** Arithmetical operators:
  FInlineM4 Mat4 operator+(const Mat4& b) const;
  FInlineM4 Mat4 operator-(const Mat4& b) const;
  FInlineM4 Mat4 operator*(const Mat4& b) const;
  FInlineM4 Mat4 operator*(float b) const;
  //Acts like a point. Should homogenize:
  FInlineM4 Vec3 operator*(const Vec3& b) const;
  FInlineM4 Vec4 operator*(const Vec4& b) const; //Should homogenize:

  //*** Assignment operators:
  FInlineM4 void operator+=(const Mat4& b);
  FInlineM4 void operator-=(const Mat4& b);
  FInlineM4 void operator*=(const Mat4& b);
  FInlineM4 void operator*=(float b);
  FInlineM4 Mat4 operator=(Mat4&& a) noexcept;
  FInlineM4 Mat4 operator=(const Mat4& a);

  //*** Access operator:
  FInlineM4 float& operator[](const int position);

  //*** Comparison operators:
  FInlineM4 bool operator==(const Mat4& a);
  FInlineM4 bool operator!=(const Mat4& a);

  //*** Data:
  float m[16];
};

//*** Functions:
FStatic Mat4 Mat4Transpose(const Mat4& a);
FStatic Mat4 Mat4InitAsIdentity();

//*** Basic transform functions:
FStatic Mat4 Mat4InitAsScale(float x, float y, float z);
FStatic Mat4 Mat4InitAsRotateX(const float radians);
FStatic Mat4 Mat4InitAsRotateY(const float radians);
FStatic Mat4 Mat4InitAsRotateZ(const float radians);
FStatic Mat4 Mat4InitAsTranslate(float x, float y, float z);

//*** Advanced transform functions:
FStatic Mat4 Mat4InitAsView(const Vec3& position,
                            const Vec3& target_point, 
                            const Vec3& up);
FStatic Mat4 Mat4InitAsPerspective(float fov_in_radians, float aspect,
                                   float z_near, float z_far);
FStatic Mat4 Mat4InitAsOrtho(float right, float left, float top,
                             float bottom, float z_near, float z_far);

//*** Print function:
FStatic void Mat4Print(const Mat4& m);

} //ML


#ifdef INLINED
#include "mat_4.inl"
#endif

