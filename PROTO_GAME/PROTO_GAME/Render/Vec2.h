#pragma once
#include <math.h>
#include <utility>

namespace ProtoGame
{
	static const float M_PI = acos(-1);

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

		float len() const
		{
			return sqrt(mPosX * mPosX + mPosY * mPosY);
		}

		Vec2<T> getNormalVec() const
		{
			Vec2<T> vec = *this;
			if (len() == 0)
			{
				return { 0, 0 };
			}
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


	struct PairHash {;
		static const int PRIME_1 = 80021;

		template<typename T1, typename T2>
		std::size_t operator() (const std::pair<T1, T2>& pair) const
		{
			return PairHash::PRIME_1 * pair.first + pair.second;
		}
	};
}