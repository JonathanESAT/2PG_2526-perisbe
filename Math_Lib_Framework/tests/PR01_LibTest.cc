/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *
 *  Math Library framework.
 *  Unitary test to check each calcule.
 *
 */


#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <utility>
#include <math.h>

#include "ML/vec_2.h"
#include "ML/vec_3.h"
#include "ML/vec_4.h"
#include "ML/mat_2.h"
#include "ML/mat_3.h"
#include "ML/mat_4.h"


#define VEC2_TEST_ENABLED 1
#define VEC3_TEST_ENABLED 1
#define VEC4_TEST_ENABLED 1

#define MAT2_TEST_ENABLED 1
#define MAT3_TEST_ENABLED 1
#define MAT4_TEST_ENABLED 1

#define TOL 0.001f

#define PrintTest(str) \
printf("\033[1;37m    %s\033[1;37m---------> \033[1;32m[OK]\033[1;37m\n", str);

#define PrintErrorTest(str) \
printf("\033[1;31m    %s\033[1;37m---------> \033[1;32m[OK]\033[1;37m\n", str);

#define PrintTestSimple(str) \
printf("\033[1;36m  %s\033[1;37m\n", str);


#if 1 == VEC2_TEST_ENABLED
void Vec2Test() {
  printf("\n\n");
  printf("\033[1;33m***********************************************\n");
  printf("\033[1;33m****************** VEC2 TEST ******************\n");
  printf("\033[1;33m***********************************************\n");

  //****************************************************
  //****** Data declaration:
  float data[2] = { 3.0f, 2.0f };
  ML::Vec2 a(data);
  ML::Vec2 b = { -1.0f, 5.0f };
  ML::Vec2 c;
  ML::Vec2 d;
  ML::Vec2 f(3.0f, 4.0f);
  ML::Vec2 e(std::move(f));
  ML::Vec2 g(33.0f);
  ML::Vec2 h(3.0f, 4.0f);
  ML::Vec2 i(h);
  ML::Vec2 zero(0.0f);
  bool output = false;


  //****************************************************
  //****** Constructors test:
  PrintTestSimple("Constructors test:");

  assert(33.0f == g.x && 33.0f == g.y); //Vec2(const float value)
  PrintTest("Vec2(float)           ");

  assert(3.0f == a.x && 2.0f == a.y); //Vec2(const float v[2]);
  PrintTest("Vec2(float[2])        ");

  assert(-1.0f == b.x && 5.0f == b.y); //Vec2(const float vx, 
                                       //     const float vy);
  PrintTest("Vec2(float, float) #1 ");

  assert(3.0f == h.x && 4.0f == h.y); //Vec2(const float vx, 
                                      //     const float vy);
  PrintTest("Vec2(float, float) #2 ");

  assert(3.0f == i.x && 4.0f == i.y); //Vec2(const Vec2& v);
  PrintTest("Vec2(Vec2)            ");

  assert(3.0f == e.x && 4.0f == e.y &&
         0.0f == f.x && 0.0f == f.y); //Vec2(const Vec2& v);
  PrintTest("Vec2(Vec2&&)          ");


  //****************************************************
  //****** Arithmetical operators test:
  PrintTestSimple("Arithmetical operators test:");

  c = a + b; //operator+
  assert(2.0f == c.x && 7.0f == c.y);
  PrintTest("Vec2 +                ");

  c = a - b; //operator-
  assert(4.0f == c.x && -3.0f == c.y);
  PrintTest("Vec2 -                ");

  c = c * 2.0f; //operator*
  assert(8.0f == c.x && -6.0f == c.y);
  PrintTest("Vec2 *                ");


  //****************************************************
  //****** Assignment operators test:
  PrintTestSimple("Assignment operators test:");

  c += a; //operator+=
  assert(11.0f == c.x && -4.0f == c.y);
  PrintTest("Vec2 +=               ");

  c -= b; //operator-=
  assert(12.0f == c.x && -9.0f == c.y);
  PrintTest("Vec2 -=               ");

  c *= 0.5f; //operator*=
  assert(6.0f == c.x && -4.5f == c.y);
  PrintTest("Vec2 *=               ");

  d = c; //operator=
  assert(6.0f == d.x && -4.5f == d.y);
  PrintTest("Vec2 = #1             ");

  h = std::move(d); //operator=
  assert(6.0f == h.x && -4.5f == h.y &&
         0.0f == d.x && 0.0f == d.y);
  PrintTest("Vec2 = #2             ");


  //****************************************************
  //****** Access operator test:
  PrintTestSimple("Access operator test:");

  g = c; //operator[]
  assert(6.0f == g[0] && -4.5f == g[1]);
  PrintTest("Vec2 [] #1            ");

  g = c; //operator[]
  assert(6.0f == g[2] && -4.5f == g[3]);
  PrintTest("Vec2 [] #2            ");

  g = c; //operator[]
  assert(6.0f == g[-2] && -4.5f == g[-1]);
  PrintTest("Vec2 [] #3            ");


  //****************************************************
  //****** Comparison operators test:
  PrintTestSimple("Comparison operators test:");

  d = c;
  output = d == c; //operator==
  assert(output);
  PrintTest("Vec2 ==               ");

  output = d != c; //operator!=
  assert(!output);
  PrintTest("Vec2 !=               ");

  output = a < b; //operator<
  assert(output);
  PrintTest("Vec2 <                ");

  output = a <= b; //operator<=
  assert(output);
  PrintTest("Vec2 <=               ");

  output = d <= c; //operator<=
  assert(output);
  PrintTest("Vec2 <=               ");

  output = a > b; //operator>
  assert(!output);
  PrintTest("Vec2 >                ");

  output = a >= b; //operator>=
  assert(!output);
  PrintTest("Vec2 >=               ");

  output = c <= d; //operator>=
  assert(output);
  PrintTest("Vec2 >=               ");


  //****************************************************
  //****** Length functions test:
  PrintTestSimple("Length functions test:");

  float length = ML::Vec2Length(b);
  assert(fabs(length - 5.099f) <= TOL);
  PrintTest("Length                ");

  float sqr_length = ML::Vec2SquaredLength(b);
  assert(26.0f == sqr_length);
  PrintTest("Sqr Length            ");

  f = ML::Vec2Normalize(zero);
  assert(0.0f == f.x && 0.0f == f.y);
  PrintErrorTest("Normalize #1          ");

  f = ML::Vec2Normalize(e);
  assert(0.6f == f.x && 0.8f == f.y);
  PrintTest("Normalize #2          ");

  output = ML::Vec2IsNormalized(e);
  assert(!output);
  PrintTest("Normalized? #1        ");

  output = ML::Vec2IsNormalized(f);
  assert(output);
  PrintTest("Normalized? #2        ");

  //****************************************************
  //****** Lerp and clamp functions test:
  PrintTestSimple("Lerp and clamp functions test:");

  f = { 1.0f, 1.0f };
  h = { 3.0f, 4.0f };
  e = ML::Vec2Lerp(f, h, 0.5f);
  assert(2.0f == e.x && 2.5f == e.y);
  PrintTest("Lerp #1               ");
  
  e = ML::Vec2Lerp(f, h, 0.0f);
  assert(1.0f == e.x && 1.0f == e.y);
  PrintTest("Lerp #2               ");

  e = ML::Vec2Lerp(f, h, 1.0f);
  assert(3.0f == e.x && 4.0f == e.y);
  PrintTest("Lerp #3               ");

  e = ML::Vec2Lerp(f, h, 2.0f);
  assert(5.0f == e.x && 7.0f == e.y);
  PrintTest("Lerp #4               ");

  e = ML::Vec2Clamp(h, 33.0f);
  assert(3.0f == e.x && 4.0f == e.y);
  PrintTest("Clamp #1              ");

  e = ML::Vec2Clamp(h, 4.0f);
  assert(fabs(e.x - 2.4f) <= TOL && fabs(e.y - 3.2f) <= TOL);
  PrintTest("Clamp #2              ");

  zero = ML::Vec2Clamp(zero, 4.0f);
  assert(0.0f == zero.x && 0.0f == zero.y);
  PrintErrorTest("Clamp #3              ");


  //****************************************************
  //****** Perpendicular and reflect functions test:
  PrintTestSimple("Perpendicular and reflect functions test:");

  e = ML::Vec2Perpendicular2D_1(h);
  assert(-4.0f == e.x && 3.0f == e.y);
  PrintTest("Perpendicular #1      ");

  e = ML::Vec2Perpendicular2D_2(h);
  assert(4.0f == e.x && -3.0f == e.y);
  PrintTest("Perpendicular #2      ");
  
  i = { 0.0f, 1.0f };
  e = ML::Vec2Reflect(e, i);
  assert(4.0f == e.x && 3.0f == e.y);
  PrintTest("Reflect #1            ");

  e = { 4.0f, -3.0f };
  i = { 1.0f, 0.0f };
  e = ML::Vec2Reflect(e, i);
  assert(-4.0f == e.x && -3.0f == e.y);
  PrintTest("Reflect #2            ");

  e = {  4.5f, 2.1f };
  i = { -1.0f, 3.3f };
  e = ML::Vec2Reflect(e, i);
  assert(fabs(4.9087f - e.x) <= TOL && fabs(0.7511f - e.y) <= TOL);
  PrintTest("Reflect #3            ");

  zero = ML::Vec2Reflect(e, zero);
  assert(0.0f == zero.x && 0.0f == zero.y);
  PrintErrorTest("Reflect #3            ");


  //****************************************************
  //****** Dot functions test:
  PrintTestSimple("Dot functions test:");

  a = { 1.0f, 0.0f };
  b = { 1.0f, 0.0f };
  float dot = ML::Vec2Dot(a, b);
  assert(1.0f == dot);
  PrintTest("Dot #1                ");

  float angle = ML::Vec2Angle(a, b);
  assert(0.0f == angle);
  PrintTest("Angle #1              ");

  a = { 1.0f, 0.0f };
  b = { -1.0f, 0.0f };
  dot = ML::Vec2Dot(a, b);
  assert(-1.0f == dot);
  PrintTest("Dot #2                ");

  angle = ML::Vec2Angle(a, b);
  assert(fabs(angle - 3.141592f) <= TOL);
  PrintTest("Angle #2              ");

  a = { 1.0f, 0.0f };
  b = { 0.0f, 1.0f };
  dot = ML::Vec2Dot(a, b);
  assert(0.0f == dot);
  PrintTest("Dot #3                ");

  angle = ML::Vec2Angle(a, b);
  assert(fabs(angle - 1.5707f) <= TOL);
  PrintTest("Angle #3              ");

  a = { 1.0f, 0.0f };
  b = { 0.0f, -1.0f };
  dot = ML::Vec2Dot(a, b);
  assert(0.0f == dot);
  PrintTest("Dot #4                ");

  angle = ML::Vec2Angle(a, b);
  assert(fabs(angle - 1.5707f) <= TOL);
  PrintTest("Angle #4              ");

  angle = ML::Vec2Angle(a);
  assert(0.0f == angle);
  PrintTest("Angle #5              ");

  angle = ML::Vec2Angle(b);
  assert(fabs(angle - 1.5707f) <= angle);
  PrintTest("Angle #6              ");


  //****************************************************
  //****** Print function test:
  PrintTestSimple("Print function test:");
  printf("    ");
  ML::Vec2Print(a);
}
#endif //VEC2_TEST_ENABLED

#if VEC3_TEST_ENABLED
void Vec3Test() {
  printf("\n\n");
  printf("\033[1;33m***********************************************\n");
  printf("\033[1;33m****************** VEC3 TEST ******************\n");
  printf("\033[1;33m***********************************************\n");

  //****************************************************
  //****** Data declaration:
  float data[3] = { 3.0f, 2.0f, 1.0f };
  ML::Vec3 a(data);
  ML::Vec3 b = { -1.0f, 5.0f, 3.0f };
  ML::Vec3 c;
  ML::Vec3 d;
  ML::Vec3 f(3.0f, 4.0f, -1.0f);
  ML::Vec3 e(std::move(f));
  ML::Vec3 g(33.0f);
  ML::Vec3 h(3.0f, 4.0f, 5.0f);
  ML::Vec3 i(h);
  ML::Vec3 j(14.0f, 33.0f);
  ML::Vec3 zero(0.0f);
  bool output = false;


  //****************************************************
  //****** Constructors test:
  PrintTestSimple("Constructors test:");

  assert(33.0f == g.x && 33.0f == g.y && 
         33.0f == g.z); //Vec3(const float value)
  PrintTest("Vec3(float)           ");

  assert(3.0f == a.x && 2.0f == a.y && 
         1.0f == a.z); //Vec3(const float v[3]);
  PrintTest("Vec3(float[3])        ");

  assert(14.0f == j.x && 33.0f == j.y &&
         0.0f == j.z); //Vec3(const float vx, 
                       //     const float vy);
  PrintTest("Vec3(float, float)    ");

  assert(-1.0f == b.x && 5.0f == b.y && 
         3.0f == b.z); //Vec3(const float vx, 
                       //     const float vy,
                       //     const float vz);
  PrintTest("Vec3(f, f, f) #1      ");

  assert(3.0f == h.x && 4.0f == h.y && 
         5.0f == h.z); //Vec3(const float vx, 
                       //     const float vy,
                       //     const float vz);
  PrintTest("Vec3(f, f, f) #2      ");

  assert(3.0f == i.x && 4.0f == i.y && 
         5.0f == i.z); //Vec3(const Vec3& v);
  PrintTest("Vec3(Vec3)            ");

  assert(3.0f == e.x && 4.0f == e.y && -1.0f == e.z &&
         0.0f == f.x && 0.0f == f.y && 0.0f == f.z); 
         //Vec3(const Vec3& v);
  PrintTest("Vec3(Vec3&&)          ");


  //****************************************************
  //****** Arithmetical operators test:
  PrintTestSimple("Arithmetical operators test:");

  c = a + b; //operator+
  assert(2.0f == c.x && 7.0f == c.y && 4.0f == c.z);
  PrintTest("Vec3 +                ");

  c = a - b; //operator-
  assert(4.0f == c.x && -3.0f == c.y && -2.0f == c.z);
  PrintTest("Vec3 -                ");

  c = c * 2.0f; //operator*
  assert(8.0f == c.x && -6.0f == c.y && -4.0f == c.z);
  PrintTest("Vec3 *                ");


  //****************************************************
  //****** Assignment operators test:
  PrintTestSimple("Assignment operators test:");

  c += a; //operator+=
  assert(11.0f == c.x && -4.0f == c.y && -3.0f == c.z);
  PrintTest("Vec3 +=               ");

  c -= b; //operator-=
  assert(12.0f == c.x && -9.0f == c.y && -6.0f == c.z);
  PrintTest("Vec3 -=               ");

  c *= 0.5f; //operator*=
  assert(6.0f == c.x && -4.5f == c.y && -3.0f == c.z);
  PrintTest("Vec3 *=               ");

  d = c; //operator=
  assert(6.0f == d.x && -4.5f == d.y && -3.0f == c.z);
  PrintTest("Vec3 = #1             ");

  h = std::move(d); //operator=
  assert(6.0f == h.x && -4.5f == h.y && -3.0f == h.z &&
         0.0f == d.x && 0.0f == d.y && 0.0f == d.z);
  PrintTest("Vec3 = #2             ");


  //****************************************************
  //****** Access operator test:
  PrintTestSimple("Access operator test:");

  g = c; //operator[]
  assert(6.0f == g[0] && -4.5f == g[1] && -3.0f == g[2]);
  PrintTest("Vec3 [] #1            ");

  g = c; //operator[]
  assert(6.0f == g[3] && -4.5f == g[4] && -3.0f == g[5]);
  PrintTest("Vec3 [] #2            ");

  g = c; //operator[]
  assert(6.0f == g[-3] && -4.5f == g[-2] && -3.0f == g[-1]);
  PrintTest("Vec3 [] #3            ");


  //****************************************************
  //****** Comparison operators test:
  PrintTestSimple("Comparison operators test:");

  d = c;
  output = d == c; //operator==
  assert(output);
  PrintTest("Vec3 ==               ");

  output = d != c; //operator!=
  assert(!output);
  PrintTest("Vec3 !=               ");

  output = a < b; //operator<
  assert(output);
  PrintTest("Vec3 <                ");

  output = a <= b; //operator<=
  assert(output);
  PrintTest("Vec3 <=               ");

  output = d <= c; //operator<=
  assert(output);
  PrintTest("Vec3 <=               ");

  output = a > b; //operator>
  assert(!output);
  PrintTest("Vec3 >                ");

  output = a >= b; //operator>=
  assert(!output);
  PrintTest("Vec3 >=               ");

  output = c <= d; //operator>=
  assert(output);
  PrintTest("Vec3 >=               ");


  //****************************************************
  //****** Length functions test:
  PrintTestSimple("Length functions test:");

  float length = ML::Vec3Length(b);
  assert(fabs(length - 5.916f) <= TOL);
  PrintTest("Length                ");

  float sqr_length = ML::Vec3SquaredLength(b);
  assert(35.0f == sqr_length);
  PrintTest("Sqr Length            ");

  f = ML::Vec3Normalize(zero);
  assert(0.0f == f.x && 0.0f == f.y && 0.0f == f.z);
  PrintErrorTest("Normalize #1          ");

  f = ML::Vec3Normalize(e);
  assert(fabs( 0.5883f - f.x) <= TOL && 
         fabs( 0.7844f - f.y) <= TOL && 
         fabs(-0.1961f - f.z) <= TOL);
  PrintTest("Normalize #2          ");

  output = ML::Vec3IsNormalized(e);
  assert(!output);
  PrintTest("Normalized? #1        ");

  output = ML::Vec3IsNormalized(f);
  assert(output);
  PrintTest("Normalized? #2        ");

  //****************************************************
  //****** Lerp and clamp functions test:
  PrintTestSimple("Lerp and clamp functions test:");

  f = { 1.0f, 1.0f, 5.0f };
  h = { 3.0f, 4.0f, -2.0f };
  e = ML::Vec3Lerp(f, h, 0.5f);
  assert(2.0f == e.x && 2.5f == e.y && 1.5f == e.z);
  PrintTest("Lerp #1               ");
  
  e = ML::Vec3Lerp(f, h, 0.0f);
  assert(1.0f == e.x && 1.0f == e.y && 5.0f == e.z);
  PrintTest("Lerp #2               ");

  e = ML::Vec3Lerp(f, h, 1.0f);
  assert(3.0f == e.x && 4.0f == e.y && -2.0f == e.z);
  PrintTest("Lerp #3               ");

  e = ML::Vec3Lerp(f, h, 2.0f);
  assert(5.0f == e.x && 7.0f == e.y && -9.0f == e.z);
  PrintTest("Lerp #4               ");

  e = ML::Vec3Clamp(h, 33.0f);
  assert(3.0f == e.x && 4.0f == e.y && -2.0f == e.z);
  PrintTest("Clamp #1              ");

  e = ML::Vec3Clamp(h, 4.0f);
  assert(fabs(e.x - 2.2283f) <= TOL && fabs(e.y - 2.9711f) <= TOL && 
         fabs(e.z - (-1.4855f)) <= TOL);
  PrintTest("Clamp #2              ");

  zero = ML::Vec3Clamp(zero, 4.0f);
  assert(0.0f == zero.x && 0.0f == zero.y && 0.0f == zero.z);
  PrintErrorTest("Clamp #3              ");

  h = { 3.0f, -4.0f, 2.0f };
  h = ML::Vec3Homogenize(h);
  assert(1.5f == h.x && -2.0f == h.y && 1.0f == h.z);
  PrintTest("Homogeneize #1        ");

  h = { 3.0f, -4.0f, 0.0f };
  h = ML::Vec3Homogenize(h);
  assert(3.0f == h.x && -4.0f == h.y && 0.0f == h.z);
  PrintErrorTest("Homogeneize #2        ");


  //****************************************************
  //****** Perpendicular and reflect functions test:
  PrintTestSimple("Perpendicular and reflect functions test:");

  h = { 3.0f,  4.0f, 3.3f };
  e = { 1.5f, -2.3f, 5.3f };
  g = ML::Vec3Cross(h, e);
  assert(fabs(28.79f - g.x) <= TOL && fabs(-10.95f - g.y) <= TOL &&
         fabs(-12.8999f - g.z) <= TOL);
  PrintTest("Cross #1              ");

  g = ML::Vec3Cross(e, h);
  assert(fabs(-28.79f - g.x) <= TOL && fabs(10.95f - g.y) <= TOL &&
         fabs(12.8999f - g.z) <= TOL);
  PrintTest("Cross #2              ");

  h = { 3.0f, 4.0f, 0.0f };
  e = ML::Vec3Perpendicular2D_1(h);
  assert(-4.0f == e.x && 3.0f == e.y && 0.0f == e.z);
  PrintTest("Perpendicular #1      ");

  e = ML::Vec3Perpendicular2D_2(h);
  assert(4.0f == e.x && -3.0f == e.y && 0.0f == e.z);
  PrintTest("Perpendicular #2      ");
  
  i = { 0.0f, 1.0f, 0.0f };
  e = ML::Vec3Reflect(e, i);
  assert(fabs(0.8f - e.x) <= TOL && fabs(0.6f - e.y) <= TOL && 
         0.0f == e.z);
  PrintTest("Reflect #1            ");

  e = { 4.0f, -3.0f, 0.0f };
  e = ML::Vec3Reflect(e, i, false);
  assert(4.0f == e.x && 3.0f == e.y && 0.0f == e.z);
  PrintTest("Reflect #2            ");

  e = { 4.0f, -3.0f, 5.0f };
  i = { 1.0f, 0.0f, 10.0f };
  e = ML::Vec3Reflect(e, i, false);
  assert(fabs(2.9306f - e.x) <= TOL && -3.0f == e.y &&
         fabs(-5.693f - e.z) <= TOL);
  PrintTest("Reflect #3            ");

  zero = ML::Vec3Reflect(e, zero);
  assert(0.0f == zero.x && 0.0f == zero.y && 0.0f == zero.z);
  PrintErrorTest("Reflect #4            ");

  e = { 4.0f, -3.0f, 5.0f };
  i = { 1.0f, 0.0f, 10.0f };
  g = ML::Vec3Refract(e, i, 0.85f);
  assert(fabs(0.4124f - g.x) <= TOL && fabs(-0.4226f - g.y) <= TOL &&
         fabs(-0.807f - g.z) <= TOL);
  PrintTest("Refract #1            ");

  e = { 1.0f, 0.0f, 10.0f };
  i = { 4.0f, -3.0f, 5.0f };
  g = ML::Vec3Refract(e, i, 0.33f);
  assert(fabs(-0.7592f - g.x) <= TOL && fabs(0.6412f - g.y) <= TOL &&
         fabs(-0.1116f - g.z) <= TOL);
  PrintTest("Refract #2            ");

  g = ML::Vec3Refract(e, i, 0.33f, false);
  assert(fabs(-2.6179f - g.x) <= TOL && fabs(2.2109f - g.y) <= TOL &&
         fabs(-0.3849f - g.z) <= TOL);
  PrintTest("Refract #3            ");


  //****************************************************
  //****** Dot functions test:
  PrintTestSimple("Dot functions test:");

  a = { 1.0f, 0.0f, 0.0f };
  b = { 1.0f, 0.0f, 0.0f };
  float dot = ML::Vec3Dot(a, b);
  assert(1.0f == dot);
  PrintTest("Dot #1                ");

  float angle = ML::Vec3Angle(a, b);
  assert(0.0f == angle);
  PrintTest("Angle #1              ");

  a = { 1.0f, 0.0f, 0.0f };
  b = { -1.0f, 0.0f, 0.0f };
  dot = ML::Vec3Dot(a, b);
  assert(-1.0f == dot);
  PrintTest("Dot #2                ");

  angle = ML::Vec3Angle(a, b);
  assert(fabs(angle - 3.141592f) <= TOL);
  PrintTest("Angle #2              ");

  a = { 1.0f, 0.0f, 0.0f };
  b = { 0.0f, 1.0f, 0.0f };
  dot = ML::Vec3Dot(a, b);
  assert(0.0f == dot);
  PrintTest("Dot #3                ");

  angle = ML::Vec3Angle(a, b);
  assert(fabs(angle - 1.5707f) <= TOL);
  PrintTest("Angle #3              ");

  a = { 1.0f, 0.0f, 0.0f };
  b = { 0.0f, -1.0f, 0.0f };
  dot = ML::Vec3Dot(a, b);
  assert(0.0f == dot);
  PrintTest("Dot #4                ");

  angle = ML::Vec3Angle(a, b);
  assert(fabs(angle - 1.5707f) <= TOL);
  PrintTest("Angle #4              ");

  a = { 1.0f, 0.0f, 0.0f };
  b = { 0.0f, 0.0f, -1.0f };
  dot = ML::Vec3Dot(a, b);
  assert(0.0f == dot);
  PrintTest("Dot #5                ");

  angle = ML::Vec3Angle(a, b);
  assert(fabs(angle - 1.5707f) <= TOL);
  PrintTest("Angle #5              ");

  a = { 0.0f, 1.0f, 0.0f };
  b = { 0.0f, 0.0f, -1.0f };
  dot = ML::Vec3Dot(a, b);
  assert(0.0f == dot);
  PrintTest("Dot #6                ");

  angle = ML::Vec3Angle(a, b);
  assert(fabs(angle - 1.5707f) <= TOL);
  PrintTest("Angle #6              ");

  a = { 1.0f, 0.0f, 0.0f };
  angle = ML::Vec3Angle(a);
  assert(0.0f == angle);
  PrintTest("Angle #7              ");

  a = { 0.0f, 1.0f, 0.0f };
  angle = ML::Vec3Angle(a);
  assert(fabs(1.5707f - angle) <= TOL);
  PrintTest("Angle #8              ");

  a = { 0.0f, 0.0f, 1.0 };
  angle = ML::Vec3Angle(a);
  assert(fabs(1.5707f - angle) <= TOL);
  PrintTest("Angle #9              ");

  angle = ML::Vec3Angle(b);
  assert(fabs(angle - 1.5707f) <= angle);
  PrintTest("Angle #10             ");


  //****************************************************
  //****** Print function test:
  PrintTestSimple("Print function test:");
  printf("    ");
  ML::Vec3Print(a);
}
#endif //VEC3_TEST_ENABLED

#if VEC4_TEST_ENABLED
void Vec4Test() {
  printf("\n\n");
  printf("\033[1;33m***********************************************\n");
  printf("\033[1;33m****************** VEC4 TEST ******************\n");
  printf("\033[1;33m***********************************************\n");

  //****************************************************
  //****** Data declaration:
  float data[4] = { 3.0f, 2.0f, -4.0f, 1.0f };
  ML::Vec4 a(data);
  ML::Vec4 b = { -1.0f, 5.0f, 3.0f, 2.0f };
  ML::Vec4 c;
  ML::Vec4 d;
  ML::Vec4 f(3.0f, 4.0f, -1.0f, -3.0f);
  ML::Vec4 e(std::move(f));
  ML::Vec4 g(33.0f);
  ML::Vec4 h(3.0f, 4.0f, 5.0f, 1.0f);
  ML::Vec4 i(h);
  ML::Vec4 j(14.0f, 33.0f);
  ML::Vec4 k(14.0f, 33.0f, 93.0f);
  ML::Vec4 zero(0.0f);
  bool output = false;


  //****************************************************
  //****** Constructors test:
  PrintTestSimple("Constructors test:");

  assert(33.0f == g.x && 33.0f == g.y && 
         33.0f == g.z && 33.0f == g.w); //Vec4(const float value)
  PrintTest("Vec4(float)           ");

  assert(3.0f == a.x && 2.0f == a.y && 
         -4.0f == a.z && 1.0f == a.w); //Vec4(const float v[4]);
  PrintTest("Vec4(float[4])        ");

  assert(14.0f == j.x && 33.0f == j.y && 
         0.0f == j.z && 0.0f == j.w); //Vec4(const float vx, 
                                      //     const float vy);
  PrintTest("Vec4(float, float)    ");

  assert(14.0f == k.x && 33.0f == k.y && 
         93.0f == k.z && 0.0f == k.w); //Vec4(const float vx, 
                                       //     const float vy,
                                       //     const float vz);
  PrintTest("Vec4(f, f, f)         ");

  assert(-1.0f == b.x && 5.0f == b.y && 
         3.0f == b.z && 2.0f == b.w); //Vec4(const float vx, 
                                      //     const float vy,
                                      //     const float vz,
                                      //     const float vw);
  PrintTest("Vec4(f, f, f, f) #1   ");

  assert(3.0f == h.x && 4.0f == h.y && 
         5.0f == h.z && 1.0f == h.w); //Vec4(const float vx, 
                                      //     const float vy);
  PrintTest("Vec4(f, f, f, f) #2   ");

  assert(3.0f == i.x && 4.0f == i.y && 
         5.0f == i.z && 1.0f == i.w); //Vec4(const Vec4& v);
  PrintTest("Vec4(Vec4)            ");

  assert(3.0f == e.x && 4.0f == e.y && -1.0f == e.z && -3.0f == e.w &&
         0.0f == f.x && 0.0f == f.y && 0.0f == f.z && 0.0f == f.w);
         //Vec4(const Vec4& v);
  PrintTest("Vec4(Vec4&&)          ");


  //****************************************************
  //****** Arithmetical operators test:
  PrintTestSimple("Arithmetical operators test:");

  c = a + b; //operator+
  assert(2.0f == c.x && 7.0f == c.y && -1.0f == c.z && 3.0f == c.w);
  PrintTest("Vec4 +                ");

  c = a - b; //operator-
  assert(4.0f == c.x && -3.0f == c.y && -7.0f == c.z && -1.0f == c.w);
  PrintTest("Vec4 -                ");

  c = c * 2.0f; //operator*
  assert(8.0f == c.x && -6.0f == c.y && -14.0f == c.z && -2.0f == c.w);
  PrintTest("Vec4 *                ");


  //****************************************************
  //****** Assignment operators test:
  PrintTestSimple("Assignment operators test:");

  c += a; //operator+=
  assert(11.0f == c.x && -4.0f == c.y && -18.0f == c.z && -1.0f == c.w);
  PrintTest("Vec4 +=               ");

  c -= b; //operator-=
  assert(12.0f == c.x && -9.0f == c.y && -21.0f == c.z && -3.0f == c.w);
  PrintTest("Vec4 -=               ");

  c *= 0.5f; //operator*=
  assert(6.0f == c.x && -4.5f == c.y && -10.5f == c.z && -1.5f == c.w);
  PrintTest("Vec4 *=               ");

  d = c; //operator=
  assert(6.0f == d.x && -4.5f == d.y && -10.5f == c.z && -1.5f == c.w);
  PrintTest("Vec4 = #1             ");

  h = std::move(d); //operator=
  assert(6.0f == h.x && -4.5f == h.y && -10.5f == h.z && -1.5f == h.w &&
         0.0f == d.x && 0.0f == d.y && 0.0f == d.z && 0.0f == d.w);
  PrintTest("Vec4 = #2             ");


  //****************************************************
  //****** Access operator test:
  PrintTestSimple("Access operator test:");

  g = c; //operator[]
  assert(6.0f == g[0] && -4.5f == g[1] && -10.5f == g[2] && 
         -1.5f == g[3]);
  PrintTest("Vec4 [] #1            ");

  g = c; //operator[]
  assert(6.0f == g[4] && -4.5f == g[5] && -10.5f == g[6] && 
         -1.5f == g[7]);
  PrintTest("Vec4 [] #2            ");

  g = c; //operator[]
  assert(6.0f == g[-4] && -4.5f == g[-3] && -10.5f == g[-2] && 
         -1.5f == g[-1]);
  PrintTest("Vec4 [] #3            ");


  //****************************************************
  //****** Comparison operators test:
  PrintTestSimple("Comparison operators test:");

  d = c;
  output = d == c; //operator==
  assert(output);
  PrintTest("Vec4 ==               ");

  output = d != c; //operator!=
  assert(!output);
  PrintTest("Vec4 !=               ");

  output = a < b; //operator<
  assert(output);
  PrintTest("Vec4 <                ");

  output = a <= b; //operator<=
  assert(output);
  PrintTest("Vec4 <=               ");

  output = d <= c; //operator<=
  assert(output);
  PrintTest("Vec4 <=               ");

  output = a > b; //operator>
  assert(!output);
  PrintTest("Vec4 >                ");

  output = a >= b; //operator>=
  assert(!output);
  PrintTest("Vec4 >=               ");

  output = c <= d; //operator>=
  assert(output);
  PrintTest("Vec4 >=               ");


  //****************************************************
  //****** Length functions test:
  PrintTestSimple("Length functions test:");

  float length = ML::Vec4Length(b);
  assert(fabs(length - 6.2449f) <= TOL);
  PrintTest("Length                ");

  float sqr_length = ML::Vec4SquaredLength(b);
  assert(39.0f == sqr_length);
  PrintTest("Sqr Length            ");

  f = ML::Vec4Normalize(zero);
  assert(0.0f == f.x && 0.0f == f.y && 0.0f == f.z && 0.0f == f.w);
  PrintErrorTest("Normalize #1          ");

  f = ML::Vec4Normalize(e);
  assert(fabs( 0.5071f - f.x) <= TOL && 
         fabs( 0.6761f - f.y) <= TOL && 
         fabs(-0.1690f - f.z) <= TOL && 
         fabs(-0.5071f - f.w) <= TOL);
  PrintTest("Normalize #2          ");

  output = ML::Vec4IsNormalized(e);
  assert(!output);
  PrintTest("Normalized? #1        ");

  output = ML::Vec4IsNormalized(f);
  assert(output);
  PrintTest("Normalized? #2        ");

  //****************************************************
  //****** Lerp and clamp functions test:
  PrintTestSimple("Lerp and clamp functions test:");

  f = { 1.0f, 1.0f, 5.0f, -3.0f };
  h = { 3.0f, 4.0f, -2.0f, 6.0f };
  e = ML::Vec4Lerp(f, h, 0.5f);
  assert(2.0f == e.x && 2.5f == e.y && 1.5f == e.z && 1.5f == e.w);
  PrintTest("Lerp #1               ");
  
  e = ML::Vec4Lerp(f, h, 0.0f);
  assert(1.0f == e.x && 1.0f == e.y && 5.0f == e.z && -3.0f == e.w);
  PrintTest("Lerp #2               ");

  e = ML::Vec4Lerp(f, h, 1.0f);
  assert(3.0f == e.x && 4.0f == e.y && -2.0f == e.z && 6.0f == e.w);
  PrintTest("Lerp #3               ");

  e = ML::Vec4Lerp(f, h, 2.0f);
  assert(5.0f == e.x && 7.0f == e.y && -9.0f == e.z && 15.0f == e.w);
  PrintTest("Lerp #4               ");

  e = ML::Vec4Clamp(h, 33.0f);
  assert(3.0f == e.x && 4.0f == e.y && -2.0f == e.z && 6.0f == e.w);
  PrintTest("Clamp #1              ");

  e = ML::Vec4Clamp(h, 4.0f);
  assert(fabs(e.x - 1.4884f) <= TOL && fabs(e.y - 1.9845f) <= TOL && 
         fabs(e.z - (-0.9923f)) <= TOL && fabs(e.w - (2.9768f)) <= TOL);
  PrintTest("Clamp #2              ");

  zero = ML::Vec4Clamp(zero, 4.0f);
  assert(0.0f == zero.x && 0.0f == zero.y && 0.0f == zero.z && 
         0.0f == zero.w);
  PrintErrorTest("Clamp #3              ");

  h = { 3.0f, -4.0f, 2.0f, 2.0f };
  h = ML::Vec4Homogenize(h);
  assert(1.5f == h.x && -2.0f == h.y && 1.0f == h.z && 1.0f == h.w);
  PrintTest("Homogeneize #1        ");

  h = { 3.0f, -4.0f, 3.3f, 0.0f };
  h = ML::Vec4Homogenize(h);
  assert(3.0f == h.x && -4.0f == h.y && 3.3f == h.z && 0.0f == h.w);
  PrintErrorTest("Homogeneize #2        ");


  //****************************************************
  //****** Perpendicular and reflect functions test:
  PrintTestSimple("Perpendicular and reflect functions test:");

  h = { 3.0f,  4.0f, 3.3f, 0.0f };
  e = { 1.5f, -2.3f, 5.3f, 0.0f };
  g = ML::Vec4Cross(h, e);
  assert(fabs(28.79f - g.x) <= TOL && fabs(-10.95f - g.y) <= TOL &&
         fabs(-12.8999f - g.z) <= TOL);
  PrintTest("Cross #1              ");

  g = ML::Vec4Cross(e, h);
  assert(fabs(-28.79f - g.x) <= TOL && fabs(10.95f - g.y) <= TOL &&
         fabs(12.8999f - g.z) <= TOL);
  PrintTest("Cross #2              ");
  
  e = { 1.5f, -2.3f, 5.3f, 0.0f };
  i = { 0.0f, 1.0f, -2.0f, 0.0f };
  g = ML::Vec4Reflect(e, i);
  assert(fabs(0.2512f - g.x) <= TOL && fabs(0.4791f - g.y) <= TOL &&
         fabs(-0.8409f - g.z) <= TOL && 0.0f == g.w);
  PrintTest("Reflect #1            ");

  g = ML::Vec4Reflect(e, i, false);
  assert(1.5f == g.x && fabs(2.8599f - g.y) <= TOL &&
         fabs(-5.0199f - g.z) <= TOL && 0.0f == g.w);
  PrintTest("Reflect #2            ");

  e = { 4.0f, -3.0f, 5.0f, 0.0f };
  i = { 1.0f, 0.0f, 10.0f, 0.0f };
  g = ML::Vec4Reflect(e, i, false);
  assert(fabs(2.9307f - g.x) <= TOL && -3.0f == g.y &&
         fabs(-5.6931f - g.z) <= TOL && 0.0f == g.w);
  PrintTest("Reflect #3            ");

  g = ML::Vec4Reflect(e, i);
  assert(fabs(0.4144f - g.x) <= TOL && fabs(-0.4243f - g.y) <= TOL &&
         fabs(-0.8051f - g.z) <= TOL && 0.0f == g.w);
  PrintTest("Reflect #4            ");

  zero = ML::Vec4Reflect(e, zero);
  assert(0.0f == zero.x && 0.0f == zero.y && 0.0f == zero.z &&
         0.0f == zero.y);
  PrintErrorTest("Reflect #5            ");

  e = { 4.0f, -3.0f, 5.0f, 0.0f };
  i = { 1.0f, 0.0f, 10.0f, 0.0f };
  g = ML::Vec4Refract(e, i, 0.85f);
  assert(fabs(0.41238f - g.x) <= TOL && fabs(-0.4226f - g.y) <= TOL &&
         fabs(-0.807f - g.z) <= TOL && 0.0f == g.w);
  PrintTest("Refract #1            ");

  e = { 1.0f, 0.0f, 10.0f, 0.0f };
  i = { 4.0f, -3.0f, 5.0f, 0.0f };
  g = ML::Vec4Refract(e, i, 0.33f);
  assert(fabs(-0.7592f - g.x) <= TOL && fabs(0.6412f - g.y) <= TOL &&
         fabs(-0.1116f - g.z) <= TOL && 0.0f == g.w);
  PrintTest("Refract #2            ");

  g = ML::Vec4Refract(e, i, 0.33f, false);
  assert(fabs(-2.6179f - g.x) <= TOL && fabs(2.2109f - g.y) <= TOL &&
         fabs(-0.3849f - g.z) <= TOL && 0.0f == g.w);
  PrintTest("Refract #3            ");


  //****************************************************
  //****** Dot functions test:
  PrintTestSimple("Dot functions test:");

  a = { 1.0f, 0.0f, 0.0f, 0.0f };
  b = { 1.0f, 0.0f, 0.0f, 0.0f };
  float dot = ML::Vec4Dot(a, b);
  assert(1.0f == dot);
  PrintTest("Dot #1                ");

  float angle = ML::Vec4Angle(a, b);
  assert(0.0f == angle);
  PrintTest("Angle #1              ");

  a = {  1.0f, 0.0f, 0.0f, 0.0f };
  b = { -1.0f, 0.0f, 0.0f, 0.0f };
  dot = ML::Vec4Dot(a, b);
  assert(-1.0f == dot);
  PrintTest("Dot #2                ");

  angle = ML::Vec4Angle(a, b);
  assert(fabs(angle - 3.141592f) <= TOL);
  PrintTest("Angle #2              ");

  a = { 1.0f, 0.0f, 0.0f, 0.0f };
  b = { 0.0f, 1.0f, 0.0f, 0.0f };
  dot = ML::Vec4Dot(a, b);
  assert(0.0f == dot);
  PrintTest("Dot #3                ");

  angle = ML::Vec4Angle(a, b);
  assert(fabs(angle - 1.5707f) <= TOL);
  PrintTest("Angle #3              ");

  a = { 1.0f,  0.0f, 0.0f, 0.0f };
  b = { 0.0f, -1.0f, 0.0f, 0.0f };
  dot = ML::Vec4Dot(a, b);
  assert(0.0f == dot);
  PrintTest("Dot #4                ");

  angle = ML::Vec4Angle(a, b);
  assert(fabs(angle - 1.5707f) <= TOL);
  PrintTest("Angle #4              ");

  a = { 1.0f, 0.0f,  0.0f, 0.0f };
  b = { 0.0f, 0.0f, -1.0f, 0.0f };
  dot = ML::Vec4Dot(a, b);
  assert(0.0f == dot);
  PrintTest("Dot #5                ");

  angle = ML::Vec4Angle(a, b);
  assert(fabs(angle - 1.5707f) <= TOL);
  PrintTest("Angle #5              ");

  a = { 0.0f, 1.0f,  0.0f, 0.0f };
  b = { 0.0f, 0.0f, -1.0f, 0.0f };
  dot = ML::Vec4Dot(a, b);
  assert(0.0f == dot);
  PrintTest("Dot #6                ");

  angle = ML::Vec4Angle(a, b);
  assert(fabs(angle - 1.5707f) <= TOL);
  PrintTest("Angle #6              ");

  a = { 1.0f, 0.0f, 0.0f };
  angle = ML::Vec4Angle(a);
  assert(0.0f == angle);
  PrintTest("Angle #7              ");

  a = { 0.0f, 1.0f, 0.0f };
  angle = ML::Vec4Angle(a);
  assert(fabs(1.5707f - angle) <= TOL);
  PrintTest("Angle #8              ");

  a = { 0.0f, 0.0f, 1.0 };
  angle = ML::Vec4Angle(a);
  assert(fabs(1.5707f - angle) <= TOL);
  PrintTest("Angle #9              ");

  angle = ML::Vec4Angle(b);
  assert(fabs(angle - 1.5707f) <= angle);
  PrintTest("Angle #10             ");


  //****************************************************
  //****** Print function test:
  PrintTestSimple("Print function test:");
  printf("    ");
  ML::Vec4Print(a);
}
#endif //VEC4_TEST_ENABLED

#if MAT2_TEST_ENABLED
void Mat2Test() {
  printf("\n\n");
  printf("\033[1;33m***********************************************\n");
  printf("\033[1;33m****************** MAT2 TEST ******************\n");
  printf("\033[1;33m***********************************************\n");

  //****************************************************
  //****** Data declaration:
  float data[4] = { 1.0f, 2.0f,
                    3.0f, 4.0f };
  ML::Mat2 a;
  ML::Mat2 b(data);
  ML::Mat2 c(2.0f);
  ML::Vec2 v;
  ML::Vec2 v1 = {  3.0f, -2.0f };
  ML::Vec2 v2 = {  1.0f, -1.0f };
  ML::Mat2 d(v1, v2);
  ML::Mat2 e(9.0f, 8.0f,
             6.0f, 5.0f);
  ML::Mat2 f(c);
  ML::Mat2 h;
  ML::Mat2 i;
  ML::Mat2 j;
  ML::Mat2 z;
  bool output = false;


  //****************************************************
  //****** Constructors test:
  PrintTestSimple("Constructors test:");

  assert(0.0f == a.m[0] && 0.0f == a.m[1] && 
         0.0f == a.m[2] && 0.0f == a.m[3]); 
         //Mat2()
  PrintTest("Mat2()                             ");

  assert(1.0f == b.m[0] && 2.0f == b.m[1] && 
         3.0f == b.m[2] && 4.0f == b.m[3]);
         //Mat2(const float a[4])
  PrintTest("Mat2(const float[4])               ");
  
  assert(2.0f == c.m[0] && 2.0f == c.m[1] && 
         2.0f == c.m[2] && 2.0f == c.m[3]); 
         //Mat2(const float a)
  PrintTest("Mat2(const float)                  ");
  
  assert(3.0f == d.m[0] && -2.0f == d.m[1] && 
         1.0f == d.m[2] && -1.0f == d.m[3]);
         //Mat2(const Vec2 a, const Vec2 b)
  PrintTest("Mat2(const Vec2, const Vec2)       ");
  
  assert(9.0f == e.m[0] && 8.0f == e.m[1] &&
         6.0f == e.m[2] && 5.0f == e.m[3]);
         //Mat2(const float a0, const float a1, 
         //     const float a2, const float a3)
  PrintTest("Mat2(const float x4)               ");
  
  assert(2.0f == f.m[0] && 2.0f == f.m[1] && 
         2.0f == f.m[2] && 2.0f == f.m[3]); 
         //Mat2(const Mat2& a)
  PrintTest("Mat2(const Mat2 a)                 ");
  
  ML::Mat2 g(std::move(f));
  assert(2.0f == g.m[0] && 2.0f == g.m[1] && 
         2.0f == g.m[2] && 2.0f == g.m[3] &&
         0.0f == f.m[0] && 0.0f == f.m[1] && 
         0.0f == f.m[2] && 0.0f == f.m[3]); 
         //Mat2(Mat2&& a)
  PrintTest("Mat2(Mat2&& a)                     ");


  //****************************************************
  //****** Arithmetical operators test:
  PrintTestSimple("Arithmetical operators test:");

  a = b + c; //operator+
  assert(3.0f == a.m[0] && 4.0f == a.m[1] &&  
         5.0f == a.m[2] && 6.0f == a.m[3]);
  PrintTest("Mat2 +                             ");

  a = b - c; //operator-
  assert(-1.0f == a.m[0] && 0.0f == a.m[1] && 
          1.0f == a.m[2] && 2.0f == a.m[3]);
  PrintTest("Mat2 -                             ");

  a = b * c; //operator*(const Mat2& b)
  assert(8.0f == a.m[0] && 12.0f == a.m[1] && 
         8.0f == a.m[2] && 12.0f == a.m[3]); 
  PrintTest("Mat2 * Mat2 #1                     ");

  a = d * b; //operator*(const Mat2& b)
  assert( 5.0f == a.m[0] &&  -4.0f == a.m[1] && 
         13.0f == a.m[2] && -10.0f == a.m[3]); 
  PrintTest("Mat2 * Mat2 #2                     ");

  a = a * 2.0f; //operator*(float b)
  assert(10.0f == a.m[0] &&  -8.0f == a.m[1] && 
         26.0f == a.m[2] && -20.0f == a.m[3]); 
  PrintTest("Mat2 * float                       ");

  v = a * v1; //operator*(const Vec2& b)
  assert(-22.0f == v.x && 16.0f == v.y);
  PrintTest("Mat3 * Vec2 #1                     ");

  v = d * v2; //operator*(const Vec2& b)
  assert(2.0f == v.x && -1.0f == v.y);
  PrintTest("Mat3 * Vec2 #2                     ");


  //****************************************************
  //****** Assignment operators test:
  PrintTestSimple("Assignment operators test:");

  h = d; //operator=
  assert(3.0f == h.m[0] && -2.0f == h.m[1] && 
         1.0f == h.m[2] && -1.0f == h.m[3]);
  PrintTest("Mat2 = #1                          ");

  i = std::move(h); //operator=
  assert(3.0f == i.m[0] && -2.0f == i.m[1] && 
         1.0f == i.m[2] && -1.0f == i.m[3] &&
         0.0f == h.m[0] &&  0.0f == h.m[1] && 
         0.0f == h.m[2] &&  0.0f == h.m[3]); 
  PrintTest("Mat2 = #2                          ");

  e += i; //operator+=
  assert(12.0f == e.m[0] && 6.0f == e.m[1] && 
          7.0f == e.m[2] && 4.0f == e.m[3]);
  PrintTest("Mat2 +=                            ");

  i -= e; //operator-=
  assert(-9.0f == i.m[0] && -8.0f == i.m[1] && 
         -6.0f == i.m[2] && -5.0f == i.m[3]);
  PrintTest("Mat2 -=                            ");

  e *= d; //operator*=
  assert(22.0f == e.m[0] && 10.0f == e.m[1] && 
          5.0f == e.m[2] &&  2.0f == e.m[3]);
  PrintTest("Mat2 *= Mat2                       ");

  e *= 0.5f; //operator*=
  assert(11.0f == e.m[0] && 5.0f == e.m[1] && 
          2.5f == e.m[2] && 1.0f == e.m[3]);
  PrintTest("Mat2 *= float                      ");


  //****************************************************
  //****** Access operator test:
  PrintTestSimple("Access operator test:");

  assert(11.0f == e[0] &&  5.0f == e[1] && 
          2.5f == e[2] &&  1.0f == e[3]);
  PrintTest("Mat2 [] #1                         ");
  
  assert(11.0f == e[4] &&  5.0f == e[5] && 
          2.5f == e[6] &&  1.0f == e[7]);
  PrintTest("Mat2 [] #2                         ");
  
  assert(11.0f == e[-4] &&  5.0f == e[-3] && 
          2.5f == e[-2] &&  1.0f == e[-1]);
  PrintTest("Mat2 [] #3                         ");


  //****************************************************
  //****** Comparison operators test:
  PrintTestSimple("Comparison operators test:");

  e = c;
  output = e == c; //operator==
  assert(output);
  PrintTest("Mat2 ==                            ");

  output = e != c; //operator!=
  assert(!output);
  PrintTest("Mat2 != #1                         ");

  output = e == g; //operator!=
  assert(output);
  PrintTest("Mat2 != #2                         ");


  //****************************************************
  //****** Functions test:
  PrintTestSimple("Functions test:");

  h = ML::Mat2InitAsIdentity();
  assert(1.0f == h[0] && 0.0f == h[1]&&
         0.0f == h[2] && 1.0f == h[3]); 
  PrintTest("Mat2InitAsIdentity                 ");

  g = ML::Mat2Transpose(i);
  assert(-9.0f == g[0] && -6.0f == g[1] && 
         -8.0f == g[2] && -5.0f == g[3]);
  PrintTest("Mat2Transpose                      ");


  //****************************************************
  //****** Print function test:
  PrintTestSimple("Print function test:");

  ML::Mat2Print(g);
}
#endif //MAT2_TEST_ENABLED

#if MAT3_TEST_ENABLED
void Mat3Test() {
  printf("\n\n");
  printf("\033[1;33m***********************************************\n");
  printf("\033[1;33m****************** MAT3 TEST ******************\n");
  printf("\033[1;33m***********************************************\n");

  //****************************************************
  //****** Data declaration:
  float data[9] = { 1.0f, 2.0f, 3.0f,
                    4.0f, 5.0f, 6.0f,
                    7.0f, 8.0f, 9.0f };
  ML::Mat3 a;
  ML::Mat3 b(data);
  ML::Mat3 c(2.0f);
  ML::Vec2 w;
  ML::Vec2 w1 = { -3.0f, 4.0f };
  ML::Vec3 v;
  ML::Vec3 v1 = {  3.0f, -2.0f, 1.0f };
  ML::Vec3 v2 = {  1.0f, -1.0f, 0.0f };
  ML::Vec3 v3 = { -3.0f,  2.0f, 1.0f };
  ML::Mat3 d(v1, v2, v3);
  ML::Mat3 e(9.0f, 8.0f, 7.0f,
             6.0f, 5.0f, 4.0f,
             3.0f, 2.0f, 1.0f);
  ML::Mat3 f(c);
  ML::Mat3 h;
  ML::Mat3 i;
  ML::Mat3 j;
  ML::Mat3 z;
  bool output = false;


  //****************************************************
  //****** Constructors test:
  PrintTestSimple("Constructors test:");

  assert(0.0f == a.m[0] && 0.0f == a.m[1] && 0.0f == a.m[2] &&
         0.0f == a.m[3] && 0.0f == a.m[4] && 0.0f == a.m[5] &&
         0.0f == a.m[6] && 0.0f == a.m[7] && 0.0f == a.m[8]); 
         //Mat3()
  PrintTest("Mat3()                             ");

  assert(1.0f == b.m[0] && 2.0f == b.m[1] && 3.0f == b.m[2] &&
         4.0f == b.m[3] && 5.0f == b.m[4] && 6.0f == b.m[5] &&
         7.0f == b.m[6] && 8.0f == b.m[7] && 9.0f == b.m[8]);
         //Mat3(const float a[9])
  PrintTest("Mat3(const float[9])               ");
  
  assert(2.0f == c.m[0] && 2.0f == c.m[1] && 2.0f == c.m[2] &&
         2.0f == c.m[3] && 2.0f == c.m[4] && 2.0f == c.m[5] &&
         2.0f == c.m[6] && 2.0f == c.m[7] && 2.0f == c.m[8]); 
         //Mat3(const float a)
  PrintTest("Mat3(const float)                  ");
  
  assert( 3.0f == d.m[0] && -2.0f == d.m[1] && 1.0f == d.m[2] &&
          1.0f == d.m[3] && -1.0f == d.m[4] && 0.0f == d.m[5] &&
         -3.0f == d.m[6] &&  2.0f == d.m[7] && 1.0f == d.m[8]);
         //Mat3(const Vec3 a, const Vec3 b, const Vec3 c)
  PrintTest("Mat3(Vec3, Vec3, Vec3)             ");
  
  assert(9.0f == e.m[0] && 8.0f == e.m[1] && 7.0f == e.m[2] &&
         6.0f == e.m[3] && 5.0f == e.m[4] && 4.0f == e.m[5] &&
         3.0f == e.m[6] && 2.0f == e.m[7] && 1.0f == e.m[8]);
         //Mat3(const float a0, const float a1, const float a2, 
         //     const float a3, const float a4, const float a5, 
         //     const float a6, const float a7, const float a8)
  PrintTest("Mat3(const float x9)               ");
  
  assert(2.0f == f.m[0] && 2.0f == f.m[1] && 2.0f == f.m[2] &&
         2.0f == f.m[3] && 2.0f == f.m[4] && 2.0f == f.m[5] &&
         2.0f == f.m[6] && 2.0f == f.m[7] && 2.0f == f.m[8]); 
         //Mat3(const Mat3& a)
  PrintTest("Mat3(const Mat3 a)                 ");
  
  ML::Mat3 g(std::move(f));
  assert(2.0f == g.m[0] && 2.0f == g.m[1] && 2.0f == g.m[2] &&
         2.0f == g.m[3] && 2.0f == g.m[4] && 2.0f == g.m[5] &&
         2.0f == g.m[6] && 2.0f == g.m[7] && 2.0f == g.m[8] &&
         0.0f == f.m[0] && 0.0f == f.m[1] && 0.0f == f.m[2] &&
         0.0f == f.m[3] && 0.0f == f.m[4] && 0.0f == f.m[5] &&
         0.0f == f.m[6] && 0.0f == f.m[7] && 0.0f == f.m[8]); 
         //Mat3(Mat3&& a)
  PrintTest("Mat3(Mat3&& a)                     ");


  //****************************************************
  //****** Arithmetical operators test:
  PrintTestSimple("Arithmetical operators test:");

  a = b + c; //operator+
  assert(3.0f == a.m[0] &&  4.0f == a.m[1] &&  5.0f == a.m[2] &&
         6.0f == a.m[3] &&  7.0f == a.m[4] &&  8.0f == a.m[5] &&
         9.0f == a.m[6] && 10.0f == a.m[7] && 11.0f == a.m[8]);
  PrintTest("Mat3 +                             ");

  a = b - c; //operator-
  assert(-1.0f == a.m[0] && 0.0f == a.m[1] && 1.0f == a.m[2] &&
          2.0f == a.m[3] && 3.0f == a.m[4] && 4.0f == a.m[5] &&
          5.0f == a.m[6] && 6.0f == a.m[7] && 7.0f == a.m[8]);
  PrintTest("Mat3 -                             ");

  a = b * c; //operator*(const Mat3& b)
  assert(24.0f == a.m[0] && 30.0f == a.m[1] && 36.0f == a.m[2] &&
         24.0f == a.m[3] && 30.0f == a.m[4] && 36.0f == a.m[5] &&
         24.0f == a.m[6] && 30.0f == a.m[7] && 36.0f == a.m[8]); 
  PrintTest("Mat3 * Mat3 #1                     ");

  a = d * b; //operator*(const Mat3& b)
  assert(-4.0f == a.m[0] &&  2.0f == a.m[1] &&  4.0f == a.m[2] &&
         -1.0f == a.m[3] && -1.0f == a.m[4] && 10.0f == a.m[5] &&
          2.0f == a.m[6] && -4.0f == a.m[7] && 16.0f == a.m[8]); 
  PrintTest("Mat3 * Mat3 #2                     ");

  j = a * 2.0f; //operator*(float b)
  assert(-8.0f == j.m[0] &&  4.0f == j.m[1] &&  8.0f == j.m[2] &&
         -2.0f == j.m[3] && -2.0f == j.m[4] && 20.0f == j.m[5] &&
          4.0f == j.m[6] && -8.0f == j.m[7] && 32.0f == j.m[8]); 
  PrintTest("Mat3 * float                       ");

  w = d * w1; //operator*(const Vec2& b)
  assert(4.0f == w.x && -2.0f == w.y); 
  PrintTest("Mat3 * Vec2                        ");

  v = d * v2; //operator*(const Vec3& b)
  assert(2.0f == v.x && -1.0f == v.y && 1.0f == v.z);
  PrintTest("Mat3 * Vec3 #1                     ");

  v = d * v3; //operator*(const Vec3& b)
  assert(5.0f == v.x && -3.0f == v.y && 1.0f == v.z);
  PrintTest("Mat3 * Vec3 #2                     ");


  //****************************************************
  //****** Assignment operators test:
  PrintTestSimple("Assignment operators test:");

  h = d; //operator=
  assert( 3.0f == h.m[0] && -2.0f == h.m[1] && 1.0f == h.m[2] &&
          1.0f == h.m[3] && -1.0f == h.m[4] && 0.0f == h.m[5] &&
         -3.0f == h.m[6] &&  2.0f == h.m[7] && 1.0f == h.m[8]);
  PrintTest("Mat3 = #1                          ");

  i = std::move(h); //operator=
  assert( 3.0f == i.m[0] && -2.0f == i.m[1] && 1.0f == i.m[2] &&
          1.0f == i.m[3] && -1.0f == i.m[4] && 0.0f == i.m[5] &&
         -3.0f == i.m[6] &&  2.0f == i.m[7] && 1.0f == i.m[8] &&
          0.0f == h.m[0] &&  0.0f == h.m[1] && 0.0f == h.m[2] &&
          0.0f == h.m[3] &&  0.0f == h.m[4] && 0.0f == h.m[5] &&
          0.0f == h.m[6] &&  0.0f == h.m[7] && 0.0f == h.m[8]); 
  PrintTest("Mat3 = #2                          ");

  e += i; //operator+=
  assert(12.0f == e.m[0] && 6.0f == e.m[1] && 8.0f == e.m[2] &&
          7.0f == e.m[3] && 4.0f == e.m[4] && 4.0f == e.m[5] &&
          0.0f == e.m[6] && 4.0f == e.m[7] && 2.0f == e.m[8]);
  PrintTest("Mat3 +=                            ");

  i -= e; //operator-=
  assert(-9.0f == i.m[0] && -8.0f == i.m[1] && -7.0f == i.m[2] &&
         -6.0f == i.m[3] && -5.0f == i.m[4] && -4.0f == i.m[5] &&
         -3.0f == i.m[6] && -2.0f == i.m[7] && -1.0f == i.m[8]);
  PrintTest("Mat3 -=                            ");

  e *= d; //operator*=
  assert( 22.0f == e.m[0] && 14.0f == e.m[1] && 18.0f == e.m[2] &&
           5.0f == e.m[3] &&  2.0f == e.m[4] &&  4.0f == e.m[5] &&
         -22.0f == e.m[6] && -6.0f == e.m[7] && 18.0f == e.m[8]);
  PrintTest("Mat3 *= Mat3                       ");

  e *= 0.5f; //operator*=
  assert( 11.0f == e.m[0] &&  7.0f == e.m[1] && 9.0f == e.m[2] &&
           2.5f == e.m[3] &&  1.0f == e.m[4] && 2.0f == e.m[5] &&
         -11.0f == e.m[6] && -3.0f == e.m[7] && 9.0f == e.m[8]);
  PrintTest("Mat3 *= float                      ");


  //****************************************************
  //****** Access operator test:
  PrintTestSimple("Access operator test:");

  assert( 11.0f == e[0] &&  7.0f == e[1] && 9.0f == e[2] &&
           2.5f == e[3] &&  1.0f == e[4] && 2.0f == e[5] &&
         -11.0f == e[6] && -3.0f == e[7] && 9.0f == e[8]);
  PrintTest("Mat3 [] #1                         ");
  
  assert( 11.0f == e[ 9] &&  7.0f == e[10] && 9.0f == e[11] &&
           2.5f == e[12] &&  1.0f == e[13] && 2.0f == e[14] &&
         -11.0f == e[15] && -3.0f == e[16] && 9.0f == e[17]);
  PrintTest("Mat3 [] #2                         ");

  assert( 11.0f == e[-9] &&  7.0f == e[-8] && 9.0f == e[-7] &&
           2.5f == e[-6] &&  1.0f == e[-5] && 2.0f == e[-4] &&
         -11.0f == e[-3] && -3.0f == e[-2] && 9.0f == e[-1]);
  PrintTest("Mat3 [] #3                         ");


  //****************************************************
  //****** Comparison operators test:
  PrintTestSimple("Comparison operators test:");

  e = c;
  output = e == c; //operator==
  assert(output);
  PrintTest("Mat3 ==                            ");

  output = e != c; //operator!=
  assert(!output);
  PrintTest("Mat3 != #1                         ");

  output = e == g; //operator!=
  assert(output);
  PrintTest("Mat3 != #2                         ");


  //****************************************************
  //****** Functions test:
  PrintTestSimple("Functions test:");

  h = ML::Mat3InitAsIdentity();
  assert(1.0f == h[0] && 0.0f == h[1] && 0.0f == h[2] &&
         0.0f == h[3] && 1.0f == h[4] && 0.0f == h[5] &&
         0.0f == h[6] && 0.0f == h[7] && 1.0f == h[8]); 
  PrintTest("Mat3InitAsIdentity                 ");

  g = ML::Mat3Transpose(i);
  assert(-9.0f == g[0] && -6.0f == g[1] && -3.0f == g[2] &&
         -8.0f == g[3] && -5.0f == g[4] && -2.0f == g[5] &&
         -7.0f == g[6] && -4.0f == g[7] && -1.0f == g[8]);
  PrintTest("Mat3Transpose                      ");


  //****************************************************
  //****** Basic transform functions test:
  PrintTestSimple("Basic transform functions test:");

  j = ML::Mat3InitAsScale(20.0f, 10.0f);
  assert(20.0f == j[0] &&  0.0f == j[1] && 0.0f == j[2] &&
          0.0f == j[3] && 10.0f == j[4] && 0.0f == j[5] &&
          0.0f == j[6] &&  0.0f == j[7] && 1.0f == j[8]); 
  PrintTest("Mat3InitAsScale                    ");

  h = j * h; //operator*=
  assert(20.0f == h[0] &&  0.0f == h[1] && 0.0f == h[2] &&
          0.0f == h[3] && 10.0f == h[4] && 0.0f == h[5] &&
          0.0f == h[6] &&  0.0f == h[7] && 1.0f == h[8]);
  PrintTest("Mat3 *= Mat3 #1                    ");

  j = ML::Mat3InitAsRotate(0.78f);
  assert(fabs( 0.7109f - j[0]) <= TOL && 
         fabs( 0.7032f - j[1]) <= TOL &&
         0.0f == j[2] &&

         fabs(-0.7032f - j[3]) <= TOL &&
         fabs( 0.7109f - j[4]) <= TOL &&
         0.0f == j[5] &&

         0.0f == j[6] &&
         0.0f == j[7] &&
         1.0f == j[8]);
  PrintTest("Mat3InitAsRotate                   ");

  h = j * h; //operator*=
  assert(fabs(14.2183f - h[0]) <= TOL && 
         fabs(14.0656f - h[1]) <= TOL &&
         0.0f == h[2] &&

         fabs(-7.0328f - h[3]) <= TOL &&
         fabs( 7.1091f - h[4]) <= TOL &&
         0.0f == h[5] &&

         0.0f == h[6] &&
         0.0f == h[7] &&
         1.0f == h[8]);
  PrintTest("Mat3 *= Mat3 #2                    ");
  
  j = ML::Mat3InitAsTranslate(400.0f, 300.0f);
  assert(  1.0f == j[0] &&   0.0f == j[1] && 0.0f == j[2] &&
           0.0f == j[3] &&   1.0f == j[4] && 0.0f == j[5] &&
         400.0f == j[6] && 300.0f == j[7] && 1.0f == j[8]); 
  PrintTest("Mat3InitAsTranslate                ");

  h = j * h; //operator*=
  assert(fabs(14.2183f - h[0]) <= TOL &&
         fabs(14.0656f - h[1]) <= TOL &&
         0.0f == h[2] &&

         fabs(-7.0328f - h[3]) <= TOL &&
         fabs( 7.1091f - h[4]) <= TOL &&
         0.0f == h[5] &&

         400.0f == h[6] &&
         300.0f == h[7] &&
         1.0f == h[8]);
  PrintTest("Mat3 *= Mat3 #3                    ");

  v = { 2.5f, -3.0f, 1.0f }; 
  v = h * v; //operator*(const Vec3& b)
  assert(fabs(456.6440f - v.x) <= TOL &&
         fabs(313.8365f - v.y) <= TOL &&
         1.0f ==  v.z);
  PrintTest("Mat3 * Vec3 #1                     ");

  v = { 2.5f, -3.0f, 0.0f };
  v = h * v; //operator*(const Vec3& b)
  assert(fabs(56.6440f - v.x) <= TOL &&
         fabs(13.8365f - v.y) <= TOL &&
         0.0f ==  v.z);
  PrintTest("Mat3 * Vec3 #2                     ");


  //****************************************************
  //****** Print function test:
  PrintTestSimple("Print function test:");

  ML::Mat3Print(j);
}
#endif //MAT3_TEST_ENABLED

#if MAT4_TEST_ENABLED
void Mat4Test() {
  printf("\n\n");
  printf("\033[1;33m***********************************************\n");
  printf("\033[1;33m****************** MAT4 TEST ******************\n");
  printf("\033[1;33m***********************************************\n");

  //****************************************************
  //****** Data declaration:
  float data[16] = {  1.0f,  2.0f,  3.0f,  4.0f, 
                      5.0f,  6.0f,  7.0f,  8.0f, 
                      9.0f, 10.0f, 11.0f, 12.0f,
                     13.0f, 14.0f, 15.0f, 16.0f };
  ML::Mat4 a;
  ML::Mat4 b(data);
  ML::Mat4 c(2.0f);
  ML::Vec3 w;
  ML::Vec3 w1 = { -3.0f, 4.0f, -5.0f };
  ML::Vec4 v;
  ML::Vec4 v1 = {  3.0f, -2.0f, -3.0f, 1.0f };
  ML::Vec4 v2 = {  1.0f, -1.0f,  0.0f, 1.0f };
  ML::Vec4 v3 = { -3.0f,  2.0f,  2.0f, 0.0f };
  ML::Vec4 v4 = { -3.0f,  2.0f, -2.0f, 0.0f };
  ML::Mat4 d(v1, v2, v3, v4);
  ML::Mat4 e(16.0f, 15.0f, 14.0f, 13.0f,
             12.0f, 11.0f, 10.0f,  9.0f, 
              8.0f,  7.0f,  6.0f,  5.0f, 
              4.0f,  3.0f,  2.0f,  1.0f);
  ML::Mat4 f(c);
  ML::Mat4 h;
  ML::Mat4 i;
  ML::Mat4 j;
  ML::Mat3 k(9.0f, 8.0f, 7.0f,
             6.0f, 5.0f, 4.0f, 
             3.0f, 2.0f, 1.0f);
  ML::Mat4 l(k);
  ML::Mat4 m;
  ML::Mat4 n;
  ML::Mat4 o;
  ML::Mat4 p;
  ML::Mat4 z;
  bool output = false;


  //****************************************************
  //****** Constructors test:
  PrintTestSimple("Constructors test:");

  assert(0.0f == a.m[ 0] && 0.0f == a.m[ 1] && 0.0f == a.m[ 2] &&
         0.0f == a.m[ 3] && 0.0f == a.m[ 4] && 0.0f == a.m[ 5] &&
         0.0f == a.m[ 6] && 0.0f == a.m[ 7] && 0.0f == a.m[ 8] &&
         0.0f == a.m[ 9] && 0.0f == a.m[10] && 0.0f == a.m[11] &&
         0.0f == a.m[12] && 0.0f == a.m[13] && 0.0f == a.m[14] &&
         0.0f == a.m[15]); 
         //Mat4()
  PrintTest("Mat4()                             ");

  assert( 1.0f == b.m[ 0] &&  2.0f == b.m[ 1] &&  3.0f == b.m[ 2] &&
          4.0f == b.m[ 3] &&  5.0f == b.m[ 4] &&  6.0f == b.m[ 5] &&
          7.0f == b.m[ 6] &&  8.0f == b.m[ 7] &&  9.0f == b.m[ 8] &&
         10.0f == b.m[ 9] && 11.0f == b.m[10] && 12.0f == b.m[11] &&
         13.0f == b.m[12] && 14.0f == b.m[13] && 15.0f == b.m[14] &&
         16.0f == b.m[15]);
         //Mat4(const float a[16])
  PrintTest("Mat4(const float[16])              ");
  
  assert(2.0f == c.m[ 0] && 2.0f == c.m[ 1] && 2.0f == c.m[ 2] &&
         2.0f == c.m[ 3] && 2.0f == c.m[ 4] && 2.0f == c.m[ 5] &&
         2.0f == c.m[ 6] && 2.0f == c.m[ 7] && 2.0f == c.m[ 8] &&
         2.0f == c.m[ 9] && 2.0f == c.m[10] && 2.0f == c.m[11] &&
         2.0f == c.m[12] && 2.0f == c.m[13] && 2.0f == c.m[14] &&
         2.0f == c.m[15]); 
         //Mat4(const float a)
  PrintTest("Mat4(const float)                  ");
  
  assert( 3.0f == d.m[ 0] && -2.0f == d.m[ 1] && -3.0f == d.m[ 2] &&
          1.0f == d.m[ 3] &&  1.0f == d.m[ 4] && -1.0f == d.m[ 5] &&
          0.0f == d.m[ 6] &&  1.0f == d.m[ 7] && -3.0f == d.m[8] &&
          2.0f == d.m[ 9] &&  2.0f == d.m[10] &&  0.0f == d.m[11] &&
         -3.0f == d.m[12] &&  2.0f == d.m[13] && -2.0f == d.m[14] &&
          0.0f == d.m[15]);
         //Mat4(const Vec4 a, const Vec4 b, const Vec4 c, const Vec4 d)
  PrintTest("Mat4(Vec4, Vec4, Vec4, Vec4)       ");
  
  assert(16.0f == e.m[ 0] && 15.0f == e.m[ 1] && 14.0f == e.m[ 2] &&
         13.0f == e.m[ 3] && 12.0f == e.m[ 4] && 11.0f == e.m[ 5] &&
         10.0f == e.m[ 6] &&  9.0f == e.m[ 7] &&  8.0f == e.m[ 8] &&
          7.0f == e.m[ 9] &&  6.0f == e.m[10] &&  5.0f == e.m[11] &&
          4.0f == e.m[12] &&  3.0f == e.m[13] &&  2.0f == e.m[14] &&
          1.0f == e.m[15]);
         //Mat4(const float, const float, const float, const float, 
         //     const float, const float, const float, const float, 
         //     const float, const float, const float, const float, 
         //     const float, const float, const float, const float)
  PrintTest("Mat4(const float x16)              ");
  
  assert(9.0f == l.m[ 0] && 8.0f == l.m[ 1] && 7.0f == l.m[ 2] &&
         0.0f == l.m[ 3] && 6.0f == l.m[ 4] && 5.0f == l.m[ 5] &&
         4.0f == l.m[ 6] && 0.0f == l.m[ 7] && 3.0f == l.m[ 8] &&
         2.0f == l.m[ 9] && 1.0f == l.m[10] && 0.0f == l.m[11] &&
         0.0f == l.m[12] && 0.0f == l.m[13] && 0.0f == l.m[14] &&
         1.0f == l.m[15]);
         //Mat4(const float a0, const float a1, const float a2, 
         //     const float a3, const float a4, const float a5, 
         //     const float a6, const float a7, const float a8)
  PrintTest("Mat4(const Mat3)                   ");

  assert(2.0f == f.m[ 0] && 2.0f == f.m[ 1] && 2.0f == f.m[ 2] &&
         2.0f == f.m[ 3] && 2.0f == f.m[ 4] && 2.0f == f.m[ 5] &&
         2.0f == f.m[ 6] && 2.0f == f.m[ 7] && 2.0f == f.m[ 8] &&
         2.0f == f.m[ 9] && 2.0f == f.m[10] && 2.0f == f.m[11] &&
         2.0f == f.m[12] && 2.0f == f.m[13] && 2.0f == f.m[14] &&
         2.0f == f.m[15]); 
         //Mat4(const Mat4& a)
  PrintTest("Mat4(const Mat4)                   ");
  
  ML::Mat4 g(std::move(f));
  assert(2.0f == g.m[ 0] && 2.0f == g.m[ 1] && 2.0f == g.m[ 2] &&
         2.0f == g.m[ 3] && 2.0f == g.m[ 4] && 2.0f == g.m[ 5] &&
         2.0f == g.m[ 6] && 2.0f == g.m[ 7] && 2.0f == g.m[ 8] &&
         2.0f == g.m[ 9] && 2.0f == g.m[10] && 2.0f == g.m[11] &&
         2.0f == g.m[12] && 2.0f == g.m[13] && 2.0f == g.m[14] &&
         2.0f == g.m[15] && 
         0.0f == f.m[ 0] && 0.0f == f.m[ 1] && 0.0f == f.m[ 2] &&
         0.0f == f.m[ 3] && 0.0f == f.m[ 4] && 0.0f == f.m[ 5] &&
         0.0f == f.m[ 6] && 0.0f == f.m[ 7] && 0.0f == f.m[ 8] &&
         0.0f == f.m[ 9] && 0.0f == f.m[10] && 0.0f == f.m[11] &&
         0.0f == f.m[12] && 0.0f == f.m[13] && 0.0f == f.m[14] &&
         0.0f == f.m[15]); 
         //Mat4(Mat4&& a)
  PrintTest("Mat4(Mat4&& a)                     ");


  //****************************************************
  //****** Arithmetical operators test:
  PrintTestSimple("Arithmetical operators test:");

  a = b + c; //operator+
  assert( 3.0f == a.m[ 0] &&  4.0f == a.m[ 1] &&  5.0f == a.m[ 2] &&
          6.0f == a.m[ 3] &&  7.0f == a.m[ 4] &&  8.0f == a.m[ 5] &&
          9.0f == a.m[ 6] && 10.0f == a.m[ 7] && 11.0f == a.m[ 8] &&
         12.0f == a.m[ 9] && 13.0f == a.m[10] && 14.0f == a.m[11] &&
         15.0f == a.m[12] && 16.0f == a.m[13] && 17.0f == a.m[14] &&
         18.0f == a.m[15]);
  PrintTest("Mat4 +                             ");

  a = b - c; //operator-
  assert(-1.0f == a.m[ 0] &&  0.0f == a.m[ 1] &&  1.0f == a.m[ 2] &&
          2.0f == a.m[ 3] &&  3.0f == a.m[ 4] &&  4.0f == a.m[ 5] &&
          5.0f == a.m[ 6] &&  6.0f == a.m[ 7] &&  7.0f == a.m[ 8] &&
          8.0f == a.m[ 9] &&  9.0f == a.m[10] && 10.0f == a.m[11] &&
         11.0f == a.m[12] && 12.0f == a.m[13] && 13.0f == a.m[14] &&
         14.0f == a.m[15]);
  PrintTest("Mat4 -                             ");

  a = e * l; //operator*(const Mat4& b)
  assert(296.0f == a.m[ 0] && 272.0f == a.m[ 1] && 248.0f == a.m[ 2] &&
         224.0f == a.m[ 3] && 188.0f == a.m[ 4] && 173.0f == a.m[ 5] &&
         158.0f == a.m[ 6] && 143.0f == a.m[ 7] &&  80.0f == a.m[ 8] &&
          74.0f == a.m[ 9] &&  68.0f == a.m[10] &&  62.0f == a.m[11] &&
           4.0f == a.m[12] &&   3.0f == a.m[13] &&   2.0f == a.m[14] &&
           1.0f == a.m[15]); 
  PrintTest("Mat4 * Mat4 #1                     ");

  a = d * b; //operator*(const Mat4& b)
  assert(-16.0f == a.m[ 0] &&  10.0f == a.m[ 1] &&  -5.0f == a.m[ 2] &&
           3.0f == a.m[ 3] && -24.0f == a.m[ 4] &&  14.0f == a.m[ 5] &&
         -17.0f == a.m[ 6] &&  11.0f == a.m[ 7] && -32.0f == a.m[ 8] &&
          18.0f == a.m[ 9] && -29.0f == a.m[10] &&  19.0f == a.m[11] &&
         -40.0f == a.m[12] &&  22.0f == a.m[13] && -41.0f == a.m[14] &&
          27.0f == a.m[15]); 
  PrintTest("Mat4 * Mat4 #2                     ");

  j = a * 2.0f; //operator*(float b)
  assert(-32.0f == j.m[ 0] &&  20.0f == j.m[ 1] && -10.0f == j.m[ 2] &&
           6.0f == j.m[ 3] && -48.0f == j.m[ 4] &&  28.0f == j.m[ 5] &&
         -34.0f == j.m[ 6] &&  22.0f == j.m[ 7] && -64.0f == j.m[ 8] &&
          36.0f == j.m[ 9] && -58.0f == j.m[10] &&  38.0f == j.m[11] &&
         -80.0f == j.m[12] &&  44.0f == j.m[13] && -82.0f == j.m[14] &&
          54.0f == j.m[15]); 
  PrintTest("Mat4 * float                       ");

  w = d * w1; //operator*(const Vec3& b)
  assert(7.0f == w.x && -6.0f == w.y && -3.0f, == w.z); 
  PrintTest("Mat4 * Vec3                        ");

  v = d * v2; //operator*(const Vec4& b)
  assert(-1.0f == v.x && 1.0f == v.y && -5.0f == v.z && 0.0f == v.w);
  PrintTest("Mat4 * Vec4 #1                     ");

  v = d * v3; //operator*(const Vec4& b)
  assert(13.0f == v.x && -8.0f == v.y && -13.0f == v.z && 1.0f == v.w);
  PrintTest("Mat4 * Vec4 #2                     ");


  //****************************************************
  //****** Assignment operators test:
  PrintTestSimple("Assignment operators test:");

  h = d; //operator=
  assert( 3.0f == h.m[ 0] && -2.0f == h.m[ 1] && -3.0f == h.m[ 2] &&
          1.0f == h.m[ 3] &&  1.0f == h.m[ 4] && -1.0f == h.m[ 5] &&
          0.0f == h.m[ 6] &&  1.0f == h.m[ 7] && -3.0f == h.m[8] &&
          2.0f == h.m[ 9] &&  2.0f == h.m[10] &&  0.0f == h.m[11] &&
         -3.0f == h.m[12] &&  2.0f == h.m[13] && -2.0f == h.m[14] &&
          0.0f == h.m[15]);
  PrintTest("Mat4 = #1                          ");

  i = std::move(h); //operator=
  assert( 3.0f == i.m[ 0] && -2.0f == i.m[ 1] && -3.0f == i.m[ 2] &&
          1.0f == i.m[ 3] &&  1.0f == i.m[ 4] && -1.0f == i.m[ 5] &&
          0.0f == i.m[ 6] &&  1.0f == i.m[ 7] && -3.0f == i.m[8] &&
          2.0f == i.m[ 9] &&  2.0f == i.m[10] &&  0.0f == i.m[11] &&
         -3.0f == i.m[12] &&  2.0f == i.m[13] && -2.0f == i.m[14] &&
          0.0f == i.m[15] &&
          0.0f == h.m[ 0] &&  0.0f == h.m[ 1] &&  0.0f == h.m[ 2] &&
          0.0f == h.m[ 3] &&  0.0f == h.m[ 4] &&  0.0f == h.m[ 5] &&
          0.0f == h.m[ 6] &&  0.0f == h.m[ 7] &&  0.0f == h.m[8] &&
          0.0f == h.m[ 9] &&  0.0f == h.m[10] &&  0.0f == h.m[11] &&
          0.0f == h.m[12] &&  0.0f == h.m[13] &&  0.0f == h.m[14] &&
          0.0f == h.m[15]); 
  PrintTest("Mat4 = #2                          ");

  e += i; //operator+=
  assert(19.0f == e.m[ 0] && 13.0f == e.m[ 1] && 11.0f == e.m[ 2] &&
         14.0f == e.m[ 3] && 13.0f == e.m[ 4] && 10.0f == e.m[ 5] &&
         10.0f == e.m[ 6] && 10.0f == e.m[ 7] &&  5.0f == e.m[ 8] &&
          9.0f == e.m[ 9] &&  8.0f == e.m[10] &&  5.0f == e.m[11] &&
          1.0f == e.m[12] &&  5.0f == e.m[13] &&  0.0f == e.m[14] &&
          1.0f == e.m[15]);
  PrintTest("Mat4 +=                            ");

  i -= e; //operator-=
  assert(-16.0f == i.m[ 0] && -15.0f == i.m[ 1] && -14.0f == i.m[ 2] &&
         -13.0f == i.m[ 3] && -12.0f == i.m[ 4] && -11.0f == i.m[ 5] &&
         -10.0f == i.m[ 6] &&  -9.0f == i.m[ 7] &&  -8.0f == i.m[ 8] &&
          -7.0f == i.m[ 9] &&  -6.0f == i.m[10] &&  -5.0f == i.m[11] &&
          -4.0f == i.m[12] &&  -3.0f == i.m[13] &&  -2.0f == i.m[14] &&
          -1.0f == i.m[15]);
  PrintTest("Mat4 -=                            ");

  e *= d; //operator*=
  assert( 17.0f == e.m[ 0] &&  -3.0f == e.m[ 1] && -11.0f == e.m[ 2] &&
           8.0f == e.m[ 3] &&   7.0f == e.m[ 4] &&   8.0f == e.m[ 5] &&
           1.0f == e.m[ 6] &&   5.0f == e.m[ 7] && -21.0f == e.m[ 8] &&
          -1.0f == e.m[ 9] &&   3.0f == e.m[10] && -12.0f == e.m[11] &&
         -41.0f == e.m[12] && -37.0f == e.m[13] && -29.0f == e.m[14] &&
         -32.0f == e.m[15]);
  PrintTest("Mat4 *= Mat4                       ");

  e *= 0.5f; //operator*=
  assert(  8.5f == e.m[ 0] &&  -1.5f == e.m[ 1] &&  -5.5f == e.m[ 2] &&
           4.0f == e.m[ 3] &&   3.5f == e.m[ 4] &&   4.0f == e.m[ 5] &&
           0.5f == e.m[ 6] &&   2.5f == e.m[ 7] && -10.5f == e.m[ 8] &&
          -0.5f == e.m[ 9] &&   1.5f == e.m[10] &&  -6.0f == e.m[11] &&
         -20.5f == e.m[12] && -18.5f == e.m[13] && -14.5f == e.m[14] &&
         -16.0f == e.m[15]);
  PrintTest("Mat4 *= float                      ");


  //****************************************************
  //****** Access operator test:
  PrintTestSimple("Access operator test:");

  assert(  8.5f == e[ 0] &&  -1.5f == e[ 1] &&  -5.5f == e[ 2] &&
           4.0f == e[ 3] &&   3.5f == e[ 4] &&   4.0f == e[ 5] &&
           0.5f == e[ 6] &&   2.5f == e[ 7] && -10.5f == e[ 8] &&
          -0.5f == e[ 9] &&   1.5f == e[10] &&  -6.0f == e[11] &&
         -20.5f == e[12] && -18.5f == e[13] && -14.5f == e[14] &&
         -16.0f == e[15]);
  PrintTest("Mat4 [] #1                         ");
  
  assert(  8.5f == e[16] &&  -1.5f == e[17] &&  -5.5f == e[18] &&
           4.0f == e[19] &&   3.5f == e[20] &&   4.0f == e[21] &&
           0.5f == e[22] &&   2.5f == e[23] && -10.5f == e[24] &&
          -0.5f == e[25] &&   1.5f == e[26] &&  -6.0f == e[27] &&
         -20.5f == e[28] && -18.5f == e[29] && -14.5f == e[30] &&
         -16.0f == e[31]);
  PrintTest("Mat4 [] #2                         ");

  assert(  8.5f == e[-16] &&  -1.5f == e[-15] &&  -5.5f == e[-14] &&
           4.0f == e[-13] &&   3.5f == e[-12] &&   4.0f == e[-11] &&
           0.5f == e[-10] &&   2.5f == e[ -9] && -10.5f == e[ -8] &&
          -0.5f == e[ -7] &&   1.5f == e[ -6] &&  -6.0f == e[ -5] &&
         -20.5f == e[ -4] && -18.5f == e[ -3] && -14.5f == e[ -2] &&
         -16.0f == e[ -1]);
  PrintTest("Mat4 [] #3                         ");


  //****************************************************
  //****** Comparison operators test:
  PrintTestSimple("Comparison operators test:");

  e = c;
  output = e == c; //operator==
  assert(output);
  PrintTest("Mat4 ==                            ");

  output = e != c; //operator!=
  assert(!output);
  PrintTest("Mat4 != #1                         ");

  output = e == g; //operator!=
  assert(output);
  PrintTest("Mat4 != #2                         ");


  //****************************************************
  //****** Functions test:
  PrintTestSimple("Functions test:");

  h = ML::Mat4InitAsIdentity();
  assert(1.0f == h[ 0] && 0.0f == h[ 1] && 0.0f == h[ 2] &&
         0.0f == h[ 3] && 0.0f == h[ 4] && 1.0f == h[ 5] && 
         0.0f == h[ 6] && 0.0f == h[ 7] && 0.0f == h[ 8] && 
         0.0f == h[ 9] && 1.0f == h[10] && 0.0f == h[11] && 
         0.0f == h[12] && 0.0f == h[13] && 0.0f == h[14] && 
         1.0f == h[15]); 
  PrintTest("Mat4InitAsIdentity                 ");

  g = ML::Mat4Transpose(i);
  assert(-16.0f == g[ 0] && -12.0f == g[ 1] &&  -8.0f == g[ 2] &&
          -4.0f == g[ 3] && -15.0f == g[ 4] && -11.0f == g[ 5] &&
          -7.0f == g[ 6] &&  -3.0f == g[ 7] && -14.0f == g[ 8] &&
         -10.0f == g[ 9] &&  -6.0f == g[10] &&  -2.0f == g[11] &&
         -13.0f == g[12] &&  -9.0f == g[13] &&  -5.0f == g[14] &&
          -1.0f == g[15]);
  PrintTest("Mat4Transpose                      ");


  //****************************************************
  //****** Basic transform functions test:
  PrintTestSimple("Basic transform functions test:");

  j = ML::Mat4InitAsScale(20.0f, 10.0f, 5.0f);
  assert(20.0f == j[ 0] &&  0.0f == j[ 1] &&  0.0f == j[ 2] &&
          0.0f == j[ 3] &&  0.0f == j[ 4] && 10.0f == j[ 5] &&
          0.0f == j[ 6] &&  0.0f == j[ 7] &&  0.0f == j[ 8] &&
          0.0f == j[ 9] &&  5.0f == j[10] &&  0.0f == j[11] &&
          0.0f == j[12] &&  0.0f == j[13] &&  0.0f == j[14] &&
          1.0f == j[15]); 
  PrintTest("Mat4InitAsScale                    ");

  h = j * h; //operator*=
  assert(20.0f == h[ 0] &&  0.0f == h[ 1] &&  0.0f == h[ 2] &&
          0.0f == h[ 3] &&  0.0f == h[ 4] && 10.0f == h[ 5] &&
          0.0f == h[ 6] &&  0.0f == h[ 7] &&  0.0f == h[ 8] &&
          0.0f == h[ 9] &&  5.0f == h[10] &&  0.0f == h[11] &&
          0.0f == h[12] &&  0.0f == h[13] &&  0.0f == h[14] &&
          1.0f == h[15]);
  PrintTest("Mat4 *= Mat4 #1                    ");

  j = ML::Mat4InitAsRotateX(0.78f);
  assert(1.0f == j[0] &&
         0.0f == j[1] &&
         0.0f == j[2] &&
         0.0f == j[3] &&

         0.0f == j[4] &&
         fabs( 0.7109f - j[5]) <= TOL && 
         fabs( 0.7032f - j[6]) <= TOL &&
         0.0f == j[7] &&
         
         0.0f == j[8] &&
         fabs(-0.7032f - j[9]) <= TOL &&
         fabs( 0.7109f - j[10]) <= TOL &&
         0.0f == j[11] &&

         0.0f == j[12] &&
         0.0f == j[13] &&
         0.0f == j[14] &&
         1.0f == j[15]);
  PrintTest("Mat4InitAsRotateX                  ");

  m = ML::Mat4InitAsRotateY(0.78f);
  assert(fabs( 0.7109f - m[0]) <= TOL && 
         0.0f == m[1] &&
         fabs(-0.7032f - m[2]) <= TOL &&
         0.0f == m[3] &&

         0.0f == m[4] &&
         1.0f == m[5] &&
         0.0f == m[6] &&
         0.0f == m[7] &&
    
         fabs( 0.7032f - m[8]) <= TOL &&
         0.0f == m[9] &&
         fabs( 0.7109f - m[10]) <= TOL &&
         0.0f == m[11] &&

         0.0f == m[12] &&
         0.0f == m[13] &&
         0.0f == m[14] &&
         1.0f == m[15]);
  PrintTest("Mat4InitAsRotateY                  ");

  n = ML::Mat4InitAsRotateZ(0.78f);
  assert(fabs( 0.7109f - n[0]) <= TOL && 
         fabs( 0.7032f - n[1]) <= TOL &&
         0.0f == n[2] &&
         0.0f == n[3] &&

         fabs(-0.7032f - n[4]) <= TOL &&
         fabs( 0.7109f - n[5]) <= TOL &&
         0.0f == n[6] &&
         0.0f == n[7] &&

         0.0f == n[8] &&
         0.0f == n[9] &&
         1.0f == n[10] &&
         0.0f == n[11] &&

         0.0f == n[12] &&
         0.0f == n[13] &&
         0.0f == n[14] &&
         1.0f == n[15]);
  PrintTest("Mat4InitAsRotateZ                  ");

  h = j * h; //operator*=
  h = m * h; //operator*=
  h = n * h; //operator*=
  assert(fabs( 10.1079f - h[0]) <= TOL &&
         fabs(  9.9994f - h[1]) <= TOL &&
         fabs(-14.0655f - h[2]) <= TOL &&
         0.0f == h[3] &&

         fabs( -1.4835f - h[4]) <= TOL &&
         fabs(  8.5324f - h[5]) <= TOL &&
         fabs(  4.9997f - h[6]) <= TOL &&
         0.0f == h[7] &&

         fabs(  4.2501f - h[8]) <= TOL &&
         fabs( -0.7417f - h[9]) <= TOL &&
         fabs(  2.5269f - h[10]) <= TOL &&
         0.0f == h[11] &&

         0.0f == h[12] &&
         0.0f == h[13] &&
         0.0f == h[14] &&
         1.0f == h[15]);
  PrintTest("Mat4 *= Mat4 #2                    ");
  
  o = ML::Mat4InitAsTranslate(400.0f, 300.0f, 200.0f);
  assert(  1.0f == o[ 0] &&   0.0f == o[ 1] &&   0.0f == o[ 2] &&
           0.0f == o[ 3] &&   0.0f == o[ 4] &&   1.0f == o[ 5] &&
           0.0f == o[ 6] &&   0.0f == o[ 7] &&   0.0f == o[ 8] &&
           0.0f == o[ 9] &&   1.0f == o[10] &&   0.0f == o[11] &&
         400.0f == o[12] && 300.0f == o[13] && 200.0f == o[14] &&
           1.0f == o[15]);
  PrintTest("Mat4InitAsTranslate                ");

  h = o * h; //operator*=
  assert(fabs( 10.1079f - h[0]) <= TOL &&
         fabs(  9.9994f - h[1]) <= TOL &&
         fabs(-14.0655f - h[2]) <= TOL &&
         0.0f == h[3] &&

         fabs( -1.4835f - h[4]) <= TOL &&
         fabs(  8.5324f - h[5]) <= TOL &&
         fabs(  4.9997f - h[6]) <= TOL &&
         0.0f == h[7] &&

         fabs(  4.2501f - h[8]) <= TOL &&
         fabs( -0.7417f - h[9]) <= TOL &&
         fabs(  2.5269f - h[10]) <= TOL &&
         0.0f == h[11] &&

         400.0f == h[12] &&
         300.0f == h[13] &&
         200.0f == h[14] &&
         1.0f == h[15]);
  PrintTest("Mat4 *= Mat4 #3                    ");

  w = { 2.5f, -3.0f, 1.0f }; 
  w = h * w; //operator*(const Vec3& b)
  assert(fabs(433.9706f - w.x) <= TOL &&
         fabs(298.6595f - w.y) <= TOL &&
         fabs(152.3638f - w.z) <= TOL);
  PrintTest("Mat4 * Vec3                        ");

  v = { 2.5f, -3.0f, 1.0f, 1.0f };
  v = h * v; //operator*(const Vec4& b)
  assert(fabs(433.9706f - v.x) <= TOL &&
         fabs(298.6595f - v.y) <= TOL &&
         fabs(152.3638f - v.z) <= TOL &&
         1.0f == v.w);
  PrintTest("Mat4 * Vec4 #1                     ");

  v = { 2.5f, -3.0f, 1.0f, 0.0f };
  v = h * v; //operator*(const Vec4& b)
  assert(fabs( 33.9706f - v.x) <= TOL &&
         fabs( -1.3404f - v.y) <= TOL &&
         fabs(-47.6361f - v.z) <= TOL &&
         0.0f == v.w);
  PrintTest("Mat4 * Vec4 #2                     ");


  //****************************************************
  //****** Advanced transform functions test:
  ML::Vec3 pos = { 4.0f, 2.0f, -3.0f };
  ML::Vec3 target_point = { 20.0f, 15.0f, -15.0f };
  ML::Vec3 up = { 0.0f, 1.0f, 0.0f };
  b = ML::Mat4InitAsView(pos, target_point, up);
  assert(fabs( 0.6000f - b[0]) <= TOL &&
         fabs(-0.4359f - b[1]) <= TOL &&
         fabs(-0.6707f - b[2]) <= TOL &&
         0.0f == b[3] &&

         0.0f == b[4] &&
         fabs( 0.8384f - b[5]) <= TOL &&
         fabs(-0.5449f - b[6]) <= TOL &&
         0.0f == b[7] &&

         fabs( 0.8000f - b[8]) <= TOL &&
         fabs( 0.3269f - b[9]) <= TOL &&
         fabs( 0.5030f - b[10]) <= TOL &&
         0.0f == b[11] &&
    
         0.0f == b[12] &&
         fabs( 1.0480f - b[13]) <= TOL &&
         fabs( 5.2821f - b[14]) <= TOL &&
         1.0f == b[15]);
  PrintTest("Mat4InitAsView                     ");

  c = ML::Mat4InitAsPerspective(1.57f, 16.0f / 9.0f, 0.01f, 100.0f);
  assert(fabs( 0.5629f - c[0]) <= TOL &&
         0.0f == c[1] &&
         0.0f == c[2] &&
         0.0f == c[3] &&

         0.0f == c[4] &&
         fabs( 1.0007f - c[5]) <= TOL &&
         0.0f == c[6] &&
         0.0f == c[7] &&

         0.0f == c[8] &&
         0.0f == c[9] &&
         fabs(-1.0002f - c[10]) <= TOL &&
         fabs(-1.0000f - c[11]) <= TOL &&
    
         0.0f == c[12] &&
         0.0f == c[13] &&
         fabs(-0.0200f - c[14]) <= TOL &&
         0.0f == c[15]);
  PrintTest("Mat4InitAsPerspective              ");

  d = ML::Mat4InitAsOrtho(10.0f, -10.0f, 10.0f, -10.0f, 0.01f, 100.0f);
  assert(fabs(-0.1000f - d[0]) <= TOL &&
         0.0f == d[1] &&
         0.0f == d[2] &&
         0.0f == d[3] &&

         0.0f == d[4] &&
         fabs(-0.1000f - d[5]) <= TOL &&
         0.0f == d[6] &&
         0.0f == d[7] &&

         0.0f == d[8] &&
         0.0f == d[9] &&
         fabs(-0.0200f - d[10]) <= TOL &&
         0.0f == d[11] &&
    
         0.0f == d[12] &&
         0.0f == d[13] &&
         fabs(-1.0002f - d[14]) <= TOL &&
         1.0f == d[15]);
  PrintTest("Mat4InitAsOrtho                    ");


  //****************************************************
  //****** Print function test:
  PrintTestSimple("Print function test:");

  ML::Mat4Print(j);
}
#endif //MAT4_TEST_ENABLED

void ColorFix() {
  HANDLE output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD color_mode;
  GetConsoleMode(output_handle, &color_mode);
  color_mode |= ENABLE_PROCESSED_OUTPUT | 
                ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(output_handle, color_mode);

  printf("\033[22;34m============================================================\n"); //Blue.
  printf("\033[1;37m        Math Library Framework | Unit Tests\n"); //Resets to white.
  printf("  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025\n"); //White.
  printf("\033[22;34m============================================================\n"); //Blue.
  printf("\033[0;37m"); //Resets to default.
}

int main(int argc, char** argv) {
  ColorFix();

#if 1 == VEC2_TEST_ENABLED
  Vec2Test();
#endif //VEC2_TEST_ENABLED

#if 1 == VEC3_TEST_ENABLED
  Vec3Test();
#endif //VEC3_TEST_ENABLED

#if 1 == VEC4_TEST_ENABLED
  Vec4Test();
#endif //VEC4_TEST_ENABLED

#if 1 == MAT2_TEST_ENABLED
  Mat2Test();
#endif //MAT2_TEST_ENABLED

#if 1 == MAT3_TEST_ENABLED
  Mat3Test();
#endif //MAT3_TEST_ENABLED

#if 1 == MAT4_TEST_ENABLED
  Mat4Test();
#endif //MAT4_TEST_ENABLED


  return 0;
}