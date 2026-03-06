/**
 *
 *  Ivan Sancho as Unreal Authorized Instructor (UAI), 2025.
 *  Project done by the students:
 *
 *  Math Library framework.
 *  Vec4 facilities implementation.
 *
 */

#include <cmath>
#include <cstdio>


namespace ML {
  
//****************************************************
//****** Constructors and destructor:
FInline Vec4::Vec4() {
  //TODO
    
}

FInline Vec4::Vec4(const float value) {
  //TODO
    x = value;
    y = value;
    z = value;
    w = value;
    
}

FInline Vec4::Vec4(const float v[4]) {
  //TODO
    x = v[0];
    y = v[1];
    z = v[2];
    w = v[3];
}

FInline Vec4::Vec4(const float vx, const float vy) {
  //TODO
    x = vx;
    y = vy;
    z = 0.0f;
    w = 0.0f;

}

FInline Vec4::Vec4(const float vx, const float vy, const float vz) {
  //TODO
    x = vx;
    y = vy;
    z = vz;
    w = 0.0f;
}

FInline Vec4::Vec4(const float vx, const float vy,
                   const float vz, const float vw) {
  //TODO
    x = vx;
    y = vy;
    z = vz;
    w = vw;
}

FInline Vec4::Vec4(const Vec4& v) {
  //TODO
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
}

FInline Vec4::Vec4(Vec4&& v) noexcept {
  //TODO
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;


    v.x = 0;
    v.y = 0;
    v.z = 0;
    v.w = 0;
}

FInline Vec4::~Vec4() {}


//****************************************************
//****** Arithmetical operators:

FInline Vec4 Vec4::operator+(const Vec4& v) const {
  //TODO
    Vec4 tmp;

    tmp.x = x + v.x;
    tmp.y = y + v.y;
    tmp.z = z + v.z;
    tmp.w = w + v.w;

    return tmp;

}

FInline Vec4 Vec4::operator-(const Vec4& v) const {
  //TODO

    Vec4 tmp;

    tmp.x = x - v.x;
    tmp.y = y - v.y;
    tmp.z = z - v.z;
    tmp.w = w - v.w;

    return tmp;
    
}

FInline Vec4 Vec4::operator*(const float v) const {
  //TODO
    Vec4 tmp;

    tmp.x = x * v;
    tmp.y = y * v;
    tmp.z = z * v;
    tmp.w = w * v;

    return tmp;
}


//****************************************************
//****** Assignment operators:

FInline Vec4& Vec4::operator+=(const Vec4& v) {
  //TODO
    Vec4 tmp;

    tmp.x = x += v.x;
    tmp.y = y += v.y;
    tmp.z = z += v.z;
    tmp.w = w += v.w;

    return tmp;
    
    
}

FInline Vec4& Vec4::operator-=(const Vec4& v) {
  //TODO
    return *this;
}

FInline Vec4& Vec4::operator*=(const float v) {
  //TODO
    return *this;
}

FInline Vec4& Vec4::operator=(Vec4&& v) noexcept {
  //TODO
    return *this;
}

FInline Vec4& Vec4::operator=(const Vec4& v) {
  //TODO
    return *this;
}


//****************************************************
//****** Access operator:

FInline float& Vec4::operator[](const int position) {
  //TODO
    float tmp = 0.0f;
        return tmp;
}


//****************************************************
//****** Comparison operators:

FInline bool Vec4::operator==(const Vec4& v) const {
  //TODO
    return true;
}

FInline bool Vec4::operator!=(const Vec4& v) const {
  //TODO
    return true;
}

FInline bool Vec4::operator<(const Vec4& v) const {
  //TODO
    return true;
}

FInline bool Vec4::operator<=(const Vec4& v) const {
  //TODO
    return true;
}

FInline bool Vec4::operator>(const Vec4& v) const {
  //TODO
    return true;
}

FInline bool Vec4::operator>=(const Vec4& v) const {
  //TODO
    return true;
}


//****************************************************
//****** Length functions:

float Vec4Length(const Vec4& v) {
  //TODO
    return 0.0f;
}

float Vec4SquaredLength(const Vec4& v) {
  //TODO
    return 0.0f;
}

Vec4 Vec4Normalize(const Vec4& v) {
  //TODO
    return 0.0f;
}

bool Vec4IsNormalized(const Vec4& v, const float tolerance) {
  //TODO
    return 0.0f;
}


//****************************************************
//****** Lerp, clamp and homogenize functions:

Vec4 Vec4Homogenize(const Vec4& v) {
  //TODO
    return Vec4();
}

Vec4 Vec4Lerp(const Vec4& a, const Vec4& b, const float t) {
  //TODO
    return Vec4();
}

Vec4 Vec4Clamp(const Vec4& a, const float max_length) {
  //TODO
    return Vec4();
}


//****************************************************
//****** Reflect and refract functions:

Vec4 Vec4Reflect(const Vec4& v, const Vec4& normal,
                 const bool normalize_output) {
  //TODO
    return Vec4();
}

Vec4 Vec4Refract(const Vec4& iv, const Vec4& normal, 
                 const float ref_idx, const bool normalize_output) {
  //TODO
    return Vec4();
}


//****************************************************
//****** Cross and dot functions:

Vec4 Vec4Cross(const Vec4& a, const Vec4& b) {
  //TODO
    return Vec4();
}


float Vec4Dot(const Vec4& a, const Vec4& b) {
  //TODO
    return 0.0f;
}

float Vec4Angle(const Vec4& a, const Vec4& b) {
  //TODO
    return 0.0f;
}

float Vec4Angle(const Vec4& a) {
  //TODO
    return 0.0f;
}

//****************************************************
//****** Print function:

void Vec4Print(const Vec4& v) {
  //TODO

}

} //ML