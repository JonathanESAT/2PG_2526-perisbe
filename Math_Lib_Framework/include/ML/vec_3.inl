/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Vec3 facilities implementation.
 *
 */

#include <cmath>
#include <cstdio>


namespace ML {
  
//****************************************************
//****** Constructors and destructor:

FInline Vec3::Vec3() {
  //TODO

}

FInline Vec3::Vec3(const float value) {
  //TODO

}

FInline Vec3::Vec3(const float v[3]) {
  //TODO

}

FInline Vec3::Vec3(const float vx, const float vy) {
  //TODO

}

FInline Vec3::Vec3(const float vx, const float vy, const float vz) {
  //TODO

}

FInline Vec3::Vec3(const Vec3& v) {
  //TODO

}

FInline Vec3::Vec3(Vec3&& v) noexcept : x(v.x), y(v.y), z(v.z) {
  //TODO

}

FInline Vec3::~Vec3() {}


//****************************************************
//****** Arithmetical operators:

FInline Vec3 Vec3::operator+(const Vec3& v) const {
  //TODO

}

FInline Vec3 Vec3::operator-(const Vec3& v) const {
  //TODO

}

FInline Vec3 Vec3::operator*(const float v) const {
  //TODO

}


//****************************************************
//****** Assignment operators:

FInline Vec3& Vec3::operator+=(const Vec3& v) {
  //TODO

}

FInline Vec3& Vec3::operator-=(const Vec3& v) {
  //TODO

}

FInline Vec3& Vec3::operator*=(const float v) {
  //TODO

}

FInline Vec3& Vec3::operator=(Vec3&& v) noexcept {
  //TODO

}

FInline Vec3& Vec3::operator=(const Vec3& v) {
  //TODO

}


//****************************************************
//****** Access operator:

FInline float& Vec3::operator[](const int position) {
  //TODO

}


//****************************************************
//****** Comparison operators:

FInline bool Vec3::operator==(const Vec3& v) const {
  //TODO

}

FInline bool Vec3::operator!=(const Vec3& v) const {
  //TODO

}

FInline bool Vec3::operator<(const Vec3& v) const {
  //TODO

}

FInline bool Vec3::operator<=(const Vec3& v) const {
  //TODO

}

FInline bool Vec3::operator>(const Vec3& v) const {
  //TODO

}

FInline bool Vec3::operator>=(const Vec3& v) const {
  //TODO

}


//****************************************************
//****** Length functions:

float Vec3Length(const Vec3& v) {
  //TODO

}

float Vec3SquaredLength(const Vec3& v) {
  //TODO

}

Vec3 Vec3Normalize(const Vec3& v) {
  //TODO

}

bool Vec3IsNormalized(const Vec3& v, const float tolerance) {
  //TODO

}


//****************************************************
//****** Lerp, clamp and homogenize functions:

Vec3 Vec3Homogenize(const Vec3& v) {
  //TODO

}

Vec3 Vec3Lerp(const Vec3& a, const Vec3& b, const float t) {
  //TODO

}

Vec3 Vec3Clamp(const Vec3& a, const float max_length) {
  //TODO

}


//****************************************************
//****** Perpendicular functions:

Vec3 Vec3Cross(const Vec3& a, const Vec3& b) {
  //TODO

}

Vec3 Vec3Perpendicular2D_1(const Vec3& v) {
  //TODO

}

Vec3 Vec3Perpendicular2D_2(const Vec3& v) {
  //TODO

}


//****************************************************
//****** Reflect and refract functions:

Vec3 Vec3Reflect(const Vec3& iv, const Vec3& normal,
                 const bool normalize_output) {
  //TODO

}

Vec3 Vec3Refract(const Vec3& iv, const Vec3& normal, 
                 const float ref_idx, const bool normalize_output) {
  //TODO

}


//****************************************************
//****** Dot functions:

float Vec3Dot(const Vec3& a, const Vec3& b) {
  //TODO

}

float Vec3Angle(const Vec3& a, const Vec3& b) {
  //TODO

}

float Vec3Angle(const Vec3& a) {
  //TODO

}

//****************************************************
//****** Print function:

void Vec3Print(const Vec3& v) {
  //TODO

}

} //ML