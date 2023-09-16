#include "MazeGeneration.hpp"
#include "Vendors/glm/glm.hpp"
#include <deque>
#include <ctime>
#include <iostream>

std::vector<std::vector<char>> MazeGeneration::backtrackingGeneration(int width, int height)
{
	std::vector<std::vector<char>> maze;
	maze.resize(height);
	for (int column = 0; column < height; column++)
	{
		maze[column].resize(width);
		for (int row = 0; row < width; row++)
		{
			maze[column][row] = '#';
		}
	}
	glm::vec2 head;

	head.x = std::rand() % width;
	head.y = std::rand() % height;

	std::deque<glm::vec2> processNodes;
	processNodes.push_front(head);

	directionsAvailable directionsAvail;
	std::srand(std::time(nullptr));
	int direction = 0;
	while (!processNodes.empty())
	{
		head = processNodes.front();

		if (head.x > width || head.x < 0 ||
			head.y > height || head.y < 0)
		{
			processNodes.pop_front();
			continue;
		}

		//directionsAvail = directionsAvailable(true);
		directionsAvail.directions[0] = true;
		directionsAvail.directions[1] = true;
		directionsAvail.directions[2] = true;
		directionsAvail.directions[3] = true;

		// these four if stetement checks which directions are valid
		if (!(head.y + 2 > height || head.y + 2 < 0))
		{
			if (maze[head.y + 2][head.x] == '0')
			{
				directionsAvail.directions[0] = false;
			}
		} 
		else { directionsAvail.directions[(int)directions::up - 1] = false;}

		if (head.x - 2 > height || head.x - 2 < 0)
		{
			if (maze[head.y][head.x - 2] == '0')
			{
				directionsAvail.directions[1] = false;
			}
		}
		else { directionsAvail.directions[(int)directions::left - 1] = false; }

		if (head.y - 2 > height || head.y - 2 < 0)
		{
			if (maze[head.y - 2][head.x ] == '0')
			{
				directionsAvail.directions[2] = false;
			}
		} 
		else { directionsAvail.directions[(int)directions::down - 1] = false; }

		if (head.x + 2 > height || head.x + 2 < 0)
		{
			if (maze[head.y][head.x + 2] == '0')
			{
				directionsAvail.directions[3] = false;
			}
		} 
		else { directionsAvail.directions[(int)directions::right -1] = false; }


		//this code chooses which available direction to use
		do
		{
			direction = std::rand() % 5 + 1;

			if (!directionsAvail.directions[0] &&
				!directionsAvail.directions[1] &&
				!directionsAvail.directions[2] &&
				!directionsAvail.directions[3])
			{
				direction = 0;
				break;
			}
		}
		while (!directionsAvail.directions[direction -1]);

		switch (static_cast<directions>(direction))
		{
			case directions::up:
			{
				maze[head.y + 1][head.x] = '0';
				maze[head.y + 2][head.x] = '0';
				processNodes.push_front(glm::vec2(head.y + 2, head.x));
				break;
			}
			case directions::left:
			{
				maze[head.y][head.x - 1] = '0';
				maze[head.y][head.x - 2] = '0';
				processNodes.push_front(glm::vec2(head.y, head.x - 2));
				break;
			}
			case directions::down:
			{
				maze[head.y - 1][head.x] = '0';
				maze[head.y - 2][head.x] = '0';
				processNodes.push_front(glm::vec2(head.y - 2, head.x));
				break;
			}
			case directions::right:
			{
				maze[head.y][head.x + 1] = '0';
				maze[head.y][head.x + 2] = '0';
				processNodes.push_front(glm::vec2(head.y, head.x + 2));
				break;
			}
			case directions::NONE:
			{
				processNodes.pop_front();
				break;
			} 
		}
	}
	return maze;
}

directionsAvailable::directionsAvailable()
{
	directions[0] = true;
	directions[1] = true;
	directions[2] = true;
	directions[3] = true;
}

directionsAvailable::directionsAvailable(bool set)
{
	directions[0] = set;
	directions[1] = set;
	directions[2] = set;
	directions[3] = set;
}
