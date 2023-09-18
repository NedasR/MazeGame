#include "MazeGeneration.hpp"
#include "Vendors/glm/glm.hpp"
#include <stack>
#include <iostream>

std::vector<std::vector<char>> MazeGeneration::backtrackingGeneration(int width, int height)
{
	std::vector<std::vector<char>> maze;
	maze.resize(height);
	for (int row = 0; row < height; row++)
	{
		maze[row].resize(width);
		for (int column = 0; column < width; column++)
		{
			//  maze[ y ][   x  ]
			maze[row][column] = '#';
		}
	}
	glm::vec2 head;
	//std::srand((unsigned int)std::time(nullptr));
	head.x = std::rand() % width;
	head.y = std::rand() % height;
	head.x = 1;
	head.y = 1;
	std::cout << head.y << " y << and >> x " << head.x << std::endl;

	std::stack<glm::ivec2> processNodes;
	processNodes.push(head);

	maze[0][1] = '0';
	maze[height -1][width - 2] = '0';

	directionsAvailable directionsAvail;
	int direction = 0;

	int up = 2;
	int left = -2;
	int down = -2;
	int right = 2;

	std::vector<int> chooseDirection;


	while (!processNodes.empty())
	{
		head = processNodes.top();

		directionsAvail.dir[0] = false;
		directionsAvail.dir[1] = false;
		directionsAvail.dir[2] = false;
		directionsAvail.dir[3] = false;
		directionsAvail.dir[4] = false;

		if (head.x + 2 >= width)
		{
		}
		else if (maze[head.y][head.x + 2] == '#')
		{
			directionsAvail.dir[4] = true;
			chooseDirection.push_back(4);
		}

		if (head.y + 2 >= height)
		{
		}
		else if (maze[head.y + 2][head.x] == '#')
		{
			directionsAvail.dir[3] = true;
			chooseDirection.push_back(3);
		}

		if (head.x - 2 < 0)
		{
		}
		else if (maze[head.y][head.x - 2] == '#')
		{
			directionsAvail.dir[2] = true;
			chooseDirection.push_back(2);
		}

		if (head.y - 2 < 0)
		{
		}
		else if (maze[head.y - 2][head.x] == '#')
		{
			directionsAvail.dir[1] = true;
			chooseDirection.push_back(1);
		}

		if (!directionsAvail.dir[1] &&
			!directionsAvail.dir[2] &&
			!directionsAvail.dir[3] &&
			!directionsAvail.dir[4])
		{
			direction = 0;
		}
		else 
		{
			if (chooseDirection.size() == 1)
			 {
				direction = chooseDirection[0];
			}
			else
			{
				direction = chooseDirection[std::rand() % chooseDirection.size()];
			}
			chooseDirection.clear();
		}
		maze[head.y][head.x] = '0';
		switch (static_cast<directions>(direction))
		{
		case directions::NONE:
		{
			processNodes.pop();
			break;
		}
		case directions::up:
		{
			maze[head.y - 1][head.x] = '0';
			maze[head.y - 2][head.x] = '0';
			processNodes.push(glm::ivec2(head.x, head.y - 2));
			break;
		}
		case directions::left:
		{
			maze[head.y][head.x - 1] = '0';
			maze[head.y][head.x - 2] = '0';
			processNodes.push(glm::ivec2(head.x - 2, head.y));
			break;
		}
		case directions::down:
		{
			maze[head.y + 1][head.x] = '0';
			maze[head.y + 2][head.x] = '0';
			processNodes.push(glm::ivec2(head.x, head.y + 2));
			break;
		}
		case directions::right:
		{
			maze[head.y][head.x + 1] = '0';
			maze[head.y][head.x + 2] = '0';
			processNodes.push(glm::ivec2(head.x + 2, head.y));

			break;
		}
		}
	}

	return maze;
}