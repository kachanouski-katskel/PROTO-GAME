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
		
		Vec2<T> operator+(const Vec2<T>& other)
		{
			return Vec2<T>(mPosX + other.mPosX, mPosY + other.mPosY);
		}

		Vec2<T> operator-(const Vec2<T>& other)
		{
			return Vec2<T>(mPosX - other.mPosX, mPosY - other.mPosY);
		}

		Vec2<T> operator*(T mul)
		{
			return Vec2<T>(mPosX * mul, mPosY * mul);
		}

		Vec2<T> operator/(T del)
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
	};

	typedef Vec2<float> Vec2F;
	typedef Vec2<int> Vec2I;
}