#pragma once


namespace ProtoGame
{
	struct Vec2F
	{
		float mPosX = 0;
		float mPosY = 0;

		Vec2F();
		Vec2F(float x, float y);
		
		friend Vec2F operator+(const Vec2F& l, const Vec2F& r);
	};
}