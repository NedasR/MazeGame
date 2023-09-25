#include "Mob.hpp"
#include <queue>
extern std::vector<std::vector<char>> maze;

void Mob::goToPoint()
{

}

void Mob::findPath()
{
	glm::vec2 head = m_PostionInMaze;

	int up = 1;
	int left = - 1;
	int down = - 1;
	int right = 1;

	std::vector<std::vector<bool>> vistedmap;

	vistedmap.resize(maze.size());
	for (int y = 0; y < maze.size(); y++)
	{
		vistedmap[y].resize(maze.size());
		for (int x = 0; x < maze.size(); x++)
		{
			vistedmap[y][x] = false;
		}
	}

	
	std::queue<glm::vec2> processNodes;
	processNodes.push(head);


	while (!processNodes.empty())
	{

		vistedmap[head.y][head.x] = true;

		if (head.x + right >= maze.size())
		{

		}
		else if (maze[head.y][head.x + 1] != '#')
		{
			processNodes.push(glm::ivec2(head.x + right, head.y));
			vistedmap[head.y][head.x + right] = true;
		}

		if (head.y + up >= maze.size())
		{
		}
		else if (maze[head.y + 1][head.x] != '#')
		{
			processNodes.push(glm::ivec2(head.x, head.y + up));
			vistedmap[head.y + up][head.x] = true;
		}

		if (head.x - left < 0)
		{
		}
		else if (maze[head.y][head.x - 1] != '#')
		{
			processNodes.push(glm::ivec2(head.x - left, head.y));
			vistedmap[head.y][head.x - left] = true;
		}

		if (head.y - down < 0)
		{
		}
		else if (maze[head.y - 1][head.x] != '#')
		{
			processNodes.push(glm::ivec2(head.x, head.y - down));
			vistedmap[head.y - down][head.x] = true;

		}





	}
	


}
