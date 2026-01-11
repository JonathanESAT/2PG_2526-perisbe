/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Mat4 facilities implementation.
 *
 */

#include <cmath>
#include <cstdio>

namespace ML {

//****************************************************
//****** Constructors and destructor:

FInlineM4 Mat4::Mat4() {
  //TODO

}

FInlineM4 Mat4::Mat4(const float a[16]) {
  //TODO

}

FInlineM4 Mat4::Mat4(const float a) {
  //TODO

}

FInlineM4 Mat4::Mat4(const Vec4 a, const Vec4 b, const Vec4 c, 
                     const Vec4 d) {
  //TODO

}

FInlineM4 Mat4::Mat4(const float a0, const float a1, const float a2, 
                     const float a3, const float a4, const float a5, 
                     const float a6, const float a7, const float a8, 
                     const float a9, const float a10, const float a11,
                     const float a12, const float a13, const float a14, 
                     const float a15) {
  //TODO

}

FInlineM4 Mat4::Mat4(const Mat3& a) {
  //TODO

}

FInlineM4 Mat4::Mat4(const Mat4& a) {
  //TODO

}

FInlineM4 Mat4::Mat4(Mat4&& a) noexcept {
  //TODO

}

FInlineM4 Mat4::~Mat4() {}


//****************************************************
//****** Arithmetical operators:

FInlineM4 Mat4 Mat4::operator+(const Mat4& b) const {
  //TODO

}

FInlineM4 Mat4 Mat4::operator-(const Mat4& b) const {
  //TODO

}

FInlineM4 Mat4 Mat4::operator*(const Mat4& b) const {
  //TODO

}

FInlineM4 Mat4 Mat4::operator*(float b) const {
  //TODO

}

FInlineM4 Vec3 Mat4::operator*(const Vec3& b) const {
  //TODO

}

FInlineM4 Vec4 Mat4::operator*(const Vec4& b) const {
  //TODO

}


//****************************************************
//****** Assignment operators:

FInlineM4 void Mat4::operator+=(const Mat4& b) {
  //TODO

}

FInlineM4 void Mat4::operator-=(const Mat4& b) {
  //TODO

}

FInlineM4 void Mat4::operator*=(const Mat4& b) {
  //TODO

}

FInlineM4 void Mat4::operator*=(float b) {
  //TODO

}

FInlineM4 Mat4 Mat4::operator=(Mat4&& a) noexcept {
  //TODO

}

FInlineM4 Mat4 Mat4::operator=(const Mat4& a) {
  //TODO

}


//****************************************************
//****** Access operator:

FInlineM4 float& Mat4::operator[](const int position) {
  //TODO

}


//****************************************************
//****** Comparison operators:

FInlineM4 bool Mat4::operator==(const Mat4& a) {
  //TODO

}

FInlineM4 bool Mat4::operator!=(const Mat4& a) {
  //TODO

}


//****************************************************
//****** Functions:

Mat4 Mat4Transpose(const Mat4& a) {
  //TODO

}

Mat4 Mat4InitAsIdentity() {
  //TODO

}


//****************************************************
//****** Basic transform functions:

Mat4 Mat4InitAsScale(float x, float y, float z) {
  //TODO

}

Mat4 Mat4InitAsRotateX(const float radians) {
  //TODO

}

Mat4 Mat4InitAsRotateY(const float radians) {
  //TODO

}

Mat4 Mat4InitAsRotateZ(const float radians) {
  //TODO

}

Mat4 Mat4InitAsTranslate(float x, float y, float z) {
  //TODO

}


//****************************************************
//****** Advanced transform functions:

Mat4 Mat4InitAsView(const Vec3& position, const Vec3& target_point, 
                    const Vec3& up) {
  //TODO

}

Mat4 Mat4InitAsPerspective(float fov, float aspect, float z_near, 
                           float z_far) {
  //TODO

}

Mat4 Mat4InitAsOrtho(float left, float right, float bottom, 
                     float top, float z_near, float z_far) {
  //TODO

}


//****************************************************
//****** Print function:

void Mat4Print(const Mat4& m) {
  //TODO

}

} //ML