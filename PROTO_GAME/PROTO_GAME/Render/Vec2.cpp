#include "Vec2.h"

using namespace ProtoGame;

Vec2F::Vec2F()
{
	mPosX = 0.0f;
	mPosY = 0.0f;
}

Vec2F::Vec2F(float x, float y)
{
	mPosX = x;
	mPosY = y;
}

namespace ProtoGame
{
	Vec2F operator+(const Vec2F& l, const Vec2F& r)
	{
		return Vec2F(l.mPosX + r.mPosX, l.mPosY + r.mPosY);
	}
}