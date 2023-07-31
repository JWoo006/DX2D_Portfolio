#pragma once
#include <math.h>
#include <cmath>
#define PI 3.141592

struct Vector2
{
	static Vector2 Up;
	static Vector2 Right;

	static Vector2 One;
	static Vector2 Zero;

	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}

	Vector2(float x, float y)
		: x(x)
		, y(y)
	{

	}

	Vector2(int x, int y)
		: x(x)
		, y(y)
	{

	}
	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2 operator-()
	{
		return Vector2(-x, -y);
	}

	Vector2 operator+(const Vector2& other)
	{
		Vector2 temp;

		temp.x = x + other.x;
		temp.y = y + other.y;

		return temp;
	}

	Vector2 operator-(const Vector2& other)
	{
		Vector2 temp;

		temp.x = x - other.x;
		temp.y = y - other.y;

		return temp;
	}

	Vector2 operator*(const Vector2& other)
	{
		Vector2 temp;

		temp.x = x * other.x;
		temp.y = y * other.y;

		return temp;
	}

	Vector2 operator*(const float radio)
	{
		Vector2 temp;

		temp.x = x * radio;
		temp.y = y * radio;

		return temp;
	}

	Vector2 operator/(const float radio)
	{
		Vector2 temp;

		temp.x = x / radio;
		temp.y = y / radio;

		return temp;
	}

	// 누적연산자 반환값이 필요없음 void로 막음
	void operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}



	void operator*=(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;
	}

	void operator*=(const float& value)
	{
		x *= value;
		y *= value;
	}

	bool operator==(const Vector2& other)
	{
		return (x == other.x && y == other.y);
	}

	void operator-=(const float& value1)
	{
		x -= value1;
		y -= value1;
	}

	void Clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float Length()
	{
		//  sqrtf() - 루트를 구해주는 함수
		return sqrtf(x * x + y * y);
	}

	Vector2& Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;

		return *this;
	}

};

namespace jw::math
{
	inline static Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.0f) * PI;
		//float radian = (degree) * (PI / 180.0f);
		vector.Normalize();

		float x = vector.x * cosf(radian) - vector.y * sinf(radian);
		float y = vector.x * sinf(radian) + vector.y * cos(radian);

		return Vector2(x, y);
	}

	inline static float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline static float Cross(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	inline static float CalculateAngle(Vector2& v1, Vector2& v2)
	{
		float Angle = 0.0f;

		// 각도 계산 라디안 추출
		float x = v2.x - v1.x;
		float y = v2.y - v1.y;
		Angle = atan2(y, x);

		// Convert radians to degrees
		Angle = Angle * (180.0 / PI);

		return Angle;
	}

}

