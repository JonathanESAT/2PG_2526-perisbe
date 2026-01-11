/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Mat2 facilities implementation.
 *
 */

#include <cmath>
#include <cstdio>

namespace ML {

//****************************************************
//****** Constructors and destructor:

FInlineM2 Mat2::Mat2() {
  //TODO

}

FInlineM2 Mat2::Mat2(const float a[4]) {
  //TODO

}

FInlineM2 Mat2::Mat2(const float a) {
  //TODO

}

FInlineM2 Mat2::Mat2(const Vec2 a, const Vec2 b) {
  //TODO

}


FInlineM2 Mat2::Mat2(const float a0, const float a1,
                     const float a2, const float a3) {
  //TODO

}

FInlineM2 Mat2::Mat2(const Mat2& a) {
  //TODO

}

FInlineM2 Mat2::Mat2(Mat2&& a) noexcept {
  //TODO

}

FInlineM2 Mat2::~Mat2() {}


//****************************************************
//****** Arithmetical operators:

FInlineM2 Mat2 Mat2::operator+(const Mat2& b) const {
  //TODO

}

FInlineM2 Mat2 Mat2::operator-(const Mat2& b) const {
  //TODO

}

FInlineM2 Mat2 Mat2::operator*(const Mat2& b) const {
  //TODO

}

FInlineM2 Mat2 Mat2::operator*(float b) const {
  //TODO

}

FInlineM2 Vec2 Mat2::operator*(const Vec2& b) const {
  //TODO

}


//****************************************************
//****** Assignment operators:

FInlineM2 void Mat2::operator+=(const Mat2& b) {
  //TODO

}

FInlineM2 void Mat2::operator-=(const Mat2& b) {
  //TODO

}

FInlineM2 void Mat2::operator*=(const Mat2& b) {
  //TODO

}

FInlineM2 void Mat2::operator*=(float b) {
  //TODO

}

FInlineM2 Mat2 Mat2::operator=(Mat2&& a) noexcept {
  //TODO

}

FInlineM2 Mat2 Mat2::operator=(const Mat2& a) {
  //TODO

}


//****************************************************
//****** Access operator:

FInlineM2 float& Mat2::operator[](const int position) {
  //TODO

}


//****************************************************
//****** Comparison operators:

FInlineM2 bool Mat2::operator==(const Mat2& a) {
  //TODO

}

FInlineM2 bool Mat2::operator!=(const Mat2& a) {
  //TODO

}


//****************************************************
//****** Functions:

Mat2 Mat2Transpose(const Mat2& a) {
  //TODO

}

Mat2 Mat2InitAsIdentity() {
  //TODO

}


//****************************************************
//****** Print function:

void Mat2Print(const Mat2& m) {
  //TODO

}

} //ML