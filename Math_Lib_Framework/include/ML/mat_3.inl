/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Mat3 facilities implementation.
 *
 */

#include <cmath>
#include <cstdio>

namespace ML {

//****************************************************
//****** Constructors and destructor:

FInlineM3 Mat3::Mat3() {
  //TODO

}

FInlineM3 Mat3::Mat3(const float a[9]) {
  //TODO

}

FInlineM3 Mat3::Mat3(const float a) {
  //TODO

}

FInlineM3 Mat3::Mat3(const Vec3 a, const Vec3 b, const Vec3 c) {
  //TODO

}


FInlineM3 Mat3::Mat3(const float a0, const float a1, const float a2,
                     const float a3, const float a4, const float a5,
                     const float a6, const float a7, const float a8) {
  //TODO

}

FInlineM3 Mat3::Mat3(const Mat3& a) {
  //TODO

}

FInlineM3 Mat3::Mat3(Mat3&& a) noexcept {
  //TODO

}

FInlineM3 Mat3::~Mat3() {}


//****************************************************
//****** Arithmetical operators:

FInlineM3 Mat3 Mat3::operator+(const Mat3& b) const {
  //TODO

}

FInlineM3 Mat3 Mat3::operator-(const Mat3& b) const {
  //TODO

}

FInlineM3 Mat3 Mat3::operator*(const Mat3& b) const {
  //TODO

}

FInlineM3 Mat3 Mat3::operator*(float b) const {
  //TODO

}

FInlineM3 Vec2 Mat3::operator*(const Vec2& b) const {
  //TODO

}

FInlineM3 Vec3 Mat3::operator*(const Vec3& b) const {
  //TODO

}


//****************************************************
//****** Assignment operators:

FInlineM3 void Mat3::operator+=(const Mat3& b) {
  //TODO

}

FInlineM3 void Mat3::operator-=(const Mat3& b) {
  //TODO

}

FInlineM3 void Mat3::operator*=(const Mat3& b) {
  //TODO

}

FInlineM3 void Mat3::operator*=(float b) {
  //TODO

}

FInlineM3 Mat3 Mat3::operator=(Mat3&& a) noexcept {
  //TODO

}

FInlineM3 Mat3 Mat3::operator=(const Mat3& a) {
  //TODO

}


//****************************************************
//****** Access operator:

FInlineM3 float& Mat3::operator[](const int position) {
  //TODO

}


//****************************************************
//****** Comparison operators:

FInlineM3 bool Mat3::operator==(const Mat3& a) {
  //TODO

}

FInlineM3 bool Mat3::operator!=(const Mat3& a) {
  //TODO

}


//****************************************************
//****** Functions:

Mat3 Mat3Transpose(const Mat3& a) {
  //TODO

}

Mat3 Mat3InitAsIdentity() {
  //TODO

}


//****************************************************
//****** Basic transform functions:

Mat3 Mat3InitAsScale(float x, float y) {
  //TODO

}

Mat3 Mat3InitAsRotate(float radians) {
  //TODO

}

Mat3 Mat3InitAsTranslate(float x, float y) {
  //TODO

}


//****************************************************
//****** Print function:

void Mat3Print(const Mat3& m) {
  //TODO

}

} //ML