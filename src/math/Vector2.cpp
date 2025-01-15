#include "Vector2.h"
#include <cmath>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif // !M_PI

Vector2::Vector2(float _x, float _y):x(_x), y(_y){}
Vector2::Vector2(const Vector2& rhs): x(rhs.x), y(rhs.y){}
Vector2::Vector2(): x(0), y(0){}
Vector2::Vector2(Position p):x(p.x), y(p.y){}

Vector2 Vector2::operator+(const Vector2 &rhs) const
{
	Vector2 temp(*this);
	temp += rhs;
	return temp;
}
Vector2 Vector2::operator-(const Vector2 &rhs) const
{
	Vector2 temp(*this);
	temp -= rhs;
	return temp;
}

Vector2 Vector2::operator*(const Vector2 &rhs) const{
	Vector2 temp(*this);
	temp *= rhs;
	return temp;
}

Vector2 Vector2::operator*(float scalar) const{
	Vector2 temp(*this);
	temp *= scalar;
	return temp;
}

Vector2 Vector2::operator/(const Vector2 &rhs) const
{
	Vector2 temp(*this);
	temp /= rhs;
	return temp;
}

Vector2& Vector2::operator+=(const Vector2 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2 &rhs)
{
	if(rhs.x != 0 && rhs.y != 0){
		x /= rhs.x;
		y /= rhs.y;
	}
	return *this;
}

void Vector2::normalize()
{
	if(x != 0 || y != 0){
		float lenght = sqrt(x * x + y * y);
		x /= lenght;
		y /= lenght;
	}
}

Vector2 Vector2::normalized() const
{
	if(x != 0 || y != 0){
		float lenght = sqrt(x * x + y * y);
		return Vector2(
			x / lenght,
			y / lenght);
	}
	else{
		return Vector2(0, 0);
	}
}

void Vector2::rotate(int angle)
{
	float radians = angle * M_PI / 180.0f;

    x = x * cos(radians) - y * sin(radians);
    y = x * sin(radians) + y * cos(radians);
}

float Vector2::length() const
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

bool Vector2::isZero() const
{
	return std::abs(x) < 0.0001 && std::abs(y) < 0.0001;
}

float Vector2::dot(const Vector2 &lhs, const Vector2 &rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2::distance(const Vector2 &lhs, const Vector2 &rhs)
{
    return (lhs - rhs).length();
}