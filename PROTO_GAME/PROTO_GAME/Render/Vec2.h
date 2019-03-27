#pragma once


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
	};

	typedef Vec2<float> Vec2F;
	typedef Vec2<int> Vec2I;
}