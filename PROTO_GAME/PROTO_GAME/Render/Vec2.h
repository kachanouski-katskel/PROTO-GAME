#pragma once
#include <math.h>

namespace ProtoGame
{
	template<typename T>
	struct Vec2
	{
		T mPosX = 0;
		T mPosY = 0;

		Vec2()
		{
			mPosX = T();
			mPosY = T();
		}
		Vec2(T x, T y)
		{
			mPosX = x;
			mPosY = y;
		}
		
		Vec2<T> operator+(const Vec2<T>& other) const
		{
			return Vec2<T>(mPosX + other.mPosX, mPosY + other.mPosY);
		}

		Vec2<T> operator-(const Vec2<T>& other) const
		{
			return Vec2<T>(mPosX - other.mPosX, mPosY - other.mPosY);
		}

		Vec2<T> operator*(T mul) const
		{
			return Vec2<T>(mPosX * mul, mPosY * mul);
		}

		Vec2<T> operator/(T del) const
		{
			return Vec2<T>(mPosX / del, mPosY / del);
		}

		T len() const
		{
			return sqrt(mPosX * mPosX + mPosY * mPosY);
		}

		Vec2<T> getNormalVec() const
		{
			Vec2<T> vec = *this;
			return vec / len();
		}

		Vec2<T> rotate(float angle) const
		{
			//clockwise rotation, angle in radians
			return Vec2<T>(mPosX * cos(angle) + mPosY * sin(angle), -mPosX * sin(angle) + mPosY * cos(angle));
		}

		float getAngle() const
		{
			//returns angle in range -PI..PI;
			return atan2(mPosY, mPosX);
		}
	};

	typedef Vec2<float> Vec2F;
	typedef Vec2<int> Vec2I;
}