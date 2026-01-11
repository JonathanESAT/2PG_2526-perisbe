/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Vec2 facilities implementation.
 *
 */

#include <cmath>
#include <cstdio>


namespace ML {

//****************************************************
//****** Constructors and destructor:

FInline Vec2::Vec2() {
  //TODO
	
}

FInline Vec2::Vec2(const float value) {
  //TODO
	x = value;
	y = value;
}

FInline Vec2::Vec2(const float v[2]) {
  //TODO
	x = v[0];
	y = v[1];
}

FInline Vec2::Vec2(const float vx, const float vy) {
  //TODO
	x = vx;
	y = vy;
}

FInline Vec2::Vec2(const Vec2& v) {
  //TODO
	
}

FInline Vec2::Vec2(Vec2&& v) noexcept {
  //TODO
	x = v.x;
	y = v.y;

	v.x = 0.0f;
	v.y = 0.0f;
}

FInline Vec2::~Vec2() {}


//****************************************************
//****** Arithmetical operators:

FInline Vec2 Vec2::operator+(const Vec2& v) const {
  //TODO
	Vec2 tmp = { x + v.x, y + v.y };
	return tmp;
}

FInline Vec2 Vec2::operator-(const Vec2& v) const {
  //TODO
	return Vec2();
}

FInline Vec2 Vec2::operator*(const float v) const {
  //TODO
	return Vec2();
}


//****************************************************
//****** Assignment operators:

FInline Vec2& Vec2::operator+=(const Vec2& v) {
  //TODO
	return *this;
}

FInline Vec2& Vec2::operator-=(const Vec2& v) {
  //TODO
	return *this;
}

FInline Vec2& Vec2::operator*=(const float v) {
  //TODO
	return *this;
}

FInline Vec2& Vec2::operator=(Vec2&& v) noexcept {
  //TODO
	return *this;
}

FInline Vec2& Vec2::operator=(const Vec2& v) {
  //TODO
	return *this;
}


//****************************************************
//****** Access operator:

FInline float& Vec2::operator[](const int position) {
  //TODO
	float tmp = 0.0f;
	return tmp;
}


//****************************************************
//****** Comparison operators:

FInline bool Vec2::operator==(const Vec2& v) const {
  //TODO
	return true;
}

FInline bool Vec2::operator!=(const Vec2& v) const {
  //TODO
	return true;
}

FInline bool Vec2::operator<(const Vec2& v) const {
  //TODO
	return true;
}

FInline bool Vec2::operator<=(const Vec2& v) const {
  //TODO
	return true;
}

FInline bool Vec2::operator>(const Vec2& v) const {
  //TODO
	return true;
}

FInline bool Vec2::operator>=(const Vec2& v) const {
  //TODO
	return true;
}


//****************************************************
//****** Length functions:

float Vec2Length(const Vec2& v) {
  //TODO
	return 0.0f;
}

float Vec2SquaredLength(const Vec2& v) {
  //TODO
	return 0.0f;
}

Vec2 Vec2Normalize(const Vec2& v) {
  //TODO
	return 0.0f;
}

bool Vec2IsNormalized(const Vec2& v, const float tolerance) {
  //TODO
	return 0.0f;
}


//****************************************************
//****** Lerp and clamp functions:

Vec2 Vec2Lerp(const Vec2& a, const Vec2& b, const float t) {
  //TODO
	return Vec2();
}

Vec2 Vec2Clamp(const Vec2& a, const float max_length) {
  //TODO
	return Vec2();
}


//****************************************************
//****** Perpendicular and reflect functions:

Vec2 Vec2Perpendicular2D_1(const Vec2& v) {
  //TODO
	return Vec2();
}

Vec2 Vec2Perpendicular2D_2(const Vec2& v) {
  //TODO
	return Vec2();
}

Vec2 Vec2Reflect(const Vec2& v, const Vec2& normal) {
  //TODO
	return Vec2();
}


//****************************************************
//****** Dot functions:

float Vec2Dot(const Vec2& a, const Vec2& b) {
  //TODO
	return 0.0f;
}

float Vec2Angle(const Vec2& a, const Vec2& b) {
  //TODO
	return 0.0f;
}

float Vec2Angle(const Vec2& a) {
  //TODO
	return 0.0f;
}


//****************************************************
//****** Print function:

void Vec2Print(const Vec2& v) {
  //TODO
	
}

} //ML
