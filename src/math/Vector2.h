#ifndef _VECTOR_2__H_
#define _VECTOR_2__H_

#include "components/Position.h"

class Vector2{
public:
	Vector2(float x, float y);
	Vector2(const Vector2& rhs);
	Vector2();
    Vector2(Position p);

	Vector2 operator+(const Vector2 &rhs) const;
	Vector2 operator-(const Vector2 &rhs) const;
	Vector2 operator*(const Vector2 &rhs) const;
    Vector2 operator*(float scalar) const;
	Vector2 operator/(const Vector2 &rhs) const;
	Vector2& operator+=(const Vector2 &rhs);
	Vector2& operator-=(const Vector2 &rhs);
	Vector2& operator*=(const Vector2 &rhs);
    Vector2& operator*=(float scalar);
	Vector2& operator/=(const Vector2 &rhs);

	void normalize();
	Vector2 normalized() const;
	void rotate(int angle);
	float length() const;
	bool isZero() const;
	static float dot(const Vector2 &lhs, const Vector2 &rhs);
    static float distance(const Vector2 &lhs, const Vector2 &rhs);
public:
    float x;
    float y;
};

#endif