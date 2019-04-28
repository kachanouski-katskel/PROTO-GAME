#pragma once
#include <random>

namespace ProtoGame
{
	static std::random_device randD;
	static std::mt19937 randMT(randD());

	int uniformRand(int from, int to)
	{
		std::uniform_int_distribution <int> range(from, to);
		return range(randMT);
	}
}