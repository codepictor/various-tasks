#pragma once
#include <math.h>

namespace my
{

class Vector2f
{
public:
	Vector2f()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2f(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float scalMul(Vector2f v1, Vector2f v2)
	{
		return (v1.x * v2.x + v1.y * v2.y);
	}

	Vector2f getNorma()
	{
		float length = getLength();
		if (length <= 0.0f)
		{
			return Vector2f(0.0f, 0.0f);
		}
		else
		{
			return Vector2f(x / this->getLength(), y / this->getLength());
		}
	}
	float getLength()
	{
		return sqrt(x * x + y * y);
	}

	~Vector2f()
	{
		//std::cout << "destructor\n";
	}

	float x;
	float y;
};	

Vector2f operator+ (Vector2f v1, Vector2f v2)
{
	return Vector2f(v1.x + v2.x, v1.y + v2.y);
}

Vector2f operator* (Vector2f vec, float value)
{
	return Vector2f(vec.x * value, vec.y * value);
}

Vector2f operator- (Vector2f v1, Vector2f v2)
{
	return Vector2f(v1.x - v2.x, v1.y - v2.y);
}

float operator^ (Vector2f v1, Vector2f v2)
{
	return v1.x * v2.y - v2.x * v1.y;
}

} // namespace my

