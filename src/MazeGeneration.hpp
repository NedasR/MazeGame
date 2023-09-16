#pragma once
#include <vector>

enum class directions
{
	NONE = 0,
	up = 1,
	left = 2,
	down = 3,
	right = 4
};

struct directionsAvailable
{
	public:

	bool directions[4];

	directionsAvailable();

	directionsAvailable(bool set);
};

class MazeGeneration
{
	private:

	public:

	static std::vector<std::vector<char>> backtrackingGeneration(int width , int height);

};