#include "maze.h"

bool Maze::CheckBounds(sf::Vector2u pos) const
{
	// Bounds checking
	if (pos.x >= 0 && pos.x < MAZE_WIDTH && 
		pos.y >= 0 && pos.y < MAZE_HEIGHT)
		return true;
	else
		return false;
}

void Maze::MarkVisited(sf::Vector2u pos)
{
	if (CheckBounds(pos))
	{
		map[pos.x][pos.y].visited = true;
		numVisited++;
	}
}

Maze::Maze()
{
	ClearMap();
}

bool Maze::IsDone()
{
	return done;
}

void Maze::GenerateMaze()
{
	if (done) return; // Don't do any of this if we're done

	// Visit every tile
	if (numVisited < MAZE_WIDTH * MAZE_HEIGHT)
	{
		// Surrounding tile positions, not including diagonals
		sf::Vector2u n[4] = { sf::Vector2u(x + 1, y), sf::Vector2u(x - 1, y),
			sf::Vector2u(x, y + 1), sf::Vector2u(x, y - 1) };
		// Make sure no neighbors are out of bounds
		for (int i = 0; i < 4; i++)
		{
			if (!CheckBounds(n[i]))
				n[i] = sf::Vector2u(x,y); // Hopefully has been visited
		}

		// Does current cell have unvisited neighbors?
		if (!map[n[0].x][n[0].y].visited || !map[n[1].x][n[1].y].visited ||
			!map[n[2].x][n[2].y].visited || !map[n[3].x][n[3].y].visited)
		{
			// Randomly choose neighbor that hasn't been visited
			bool chosen = false;
			unsigned int rndNeighbor = 0; // random neighbor tile
			while (!chosen)
			{
				// Choose neighbor and check if its visited
				rndNeighbor = rand.Random(4);
				if (!map[n[rndNeighbor].x][n[rndNeighbor].y].visited) // Hasn't been visited
					chosen = true; // Set chosen flag
			}

			// Push current tile onto stack for backtracking
			stTiles.push(sf::Vector2u(x, y));
			// Remove wall between current tile and chosen tile
			if (n[rndNeighbor].x < x)
			{
				map[n[rndNeighbor].x][n[rndNeighbor].y].right = false;
				map[x][y].left = false;
			}
			if (n[rndNeighbor].x > x)
			{
				map[n[rndNeighbor].x][n[rndNeighbor].y].left = false;
				map[x][y].right = false;
			}
			if (n[rndNeighbor].y < y)
			{
				map[n[rndNeighbor].x][n[rndNeighbor].y].bottom = false;
				map[x][y].top = false;
			}
			if (n[rndNeighbor].y > y)
			{
				map[n[rndNeighbor].x][n[rndNeighbor].y].top = false;
				map[x][y].bottom = false;
			}

			// Make chosen tile the current one and mark it as visited
			x = n[rndNeighbor].x;
			y = n[rndNeighbor].y;
			MarkVisited(n[rndNeighbor]);
		}
		// Is the stack not empty?
		else if (!stTiles.empty())
		{
			// Make top tile on stack current tile and pop it off
			sf::Vector2u newPos = stTiles.pop();
			x = newPos.x;
			y = newPos.y;
		}
		// Pick a random unvisited tile
		else
		{
			unsigned int randX = rand.Random(MAZE_WIDTH);
			unsigned int randY = rand.Random(MAZE_HEIGHT);
			// Check if tile has already been visited
			if (!map[randX][randY].visited)
			{
				// Make it current tile
				x = randX;
				y = randY;
				// Mark it visited
				MarkVisited(sf::Vector2u(x, y));
			}
		}
	}
	// No more left to visit, set as done
	else
	{
		//exit = sf::Vector2u(x, y);
		done = true;
	}
}

bool Maze::TryMove(sf::Vector2u prev, sf::Vector2u next) const
{
	// Don't allow player to move outside maze
	if (next.x < 0 || next.x > MAZE_WIDTH || next.y < 0 || next.y > MAZE_HEIGHT)
		return false;

	// Move from left to right
	if (prev.x < next.x)
		if (map[prev.x][prev.y].right || map[next.x][next.y].left)
			return false;
	// Move from right to left
	if (prev.x > next.x)
		if (map[prev.x][prev.y].left || map[next.x][next.y].right)
			return false;
	// Move from top to bottom
	if (prev.y < next.y)
		if (map[prev.x][prev.y].bottom || map[next.x][next.y].top)
			return false;
	// Move from bottom to top
	if (prev.y > next.y)
		if (map[prev.x][prev.y].top || map[next.x][next.y].bottom)
			return false;

	// Everything checks out
	return true;
}

void Maze::ClearMap()
{
	// X/Y iterators
	unsigned int x;
	unsigned int y;

	for (y = 0; y < MAZE_HEIGHT; y++)
	{
		for (x = 0; x < MAZE_WIDTH; x++)
		{
			const bool val = true; // All initialize to this
			map[x][y].top =		val;
			map[x][y].bottom =	val;
			map[x][y].left =	val;
			map[x][y].right =	val;
			// Set visited to false
			map[x][y].visited = false;
		}
	}
	// Reset number of tiles visited
	numVisited = 0;
	done = false;
	// Reset RNG
	rand.Randomize();
	// Start with random tile
	this->x = rand.Random(MAZE_WIDTH);
	this->y = rand.Random(MAZE_HEIGHT);
	// Mark it visited
	MarkVisited(sf::Vector2u(this->x, this->y));
	exit = sf::Vector2u(MAZE_WIDTH-1, MAZE_HEIGHT-1);
}

void Maze::DrawMap(sf::RenderWindow &window) const
{
	// x/y iterators
	unsigned int x;
	unsigned int y;

	// Draw tiles
	for (y = 0; y < MAZE_HEIGHT; y++)
	{
		for (x = 0; x < MAZE_WIDTH; x++)
		{
			// Vertex array for maze tile
			sf::Vertex lines[8];
			
			// Create lines based on which sides are filled
			if (map[x][y].top)
			{
				lines[0] = sf::Vertex(sf::Vector2f(x * TILE_WIDTH, y * TILE_HEIGHT));
				lines[1] = sf::Vertex(sf::Vector2f(x * TILE_WIDTH + TILE_WIDTH, y * TILE_HEIGHT));
			}
			if (map[x][y].bottom)
			{
				lines[2] = sf::Vertex(sf::Vector2f(x * TILE_WIDTH, y * TILE_HEIGHT + TILE_HEIGHT));
				lines[3] = sf::Vertex(sf::Vector2f(x * TILE_WIDTH + TILE_WIDTH, y * TILE_HEIGHT + TILE_HEIGHT));
			}
			if (map[x][y].left)
			{
				lines[4] = sf::Vertex(sf::Vector2f(x * TILE_WIDTH, y * TILE_HEIGHT));
				lines[5] = sf::Vertex(sf::Vector2f(x * TILE_WIDTH, y * TILE_HEIGHT + TILE_HEIGHT));
			}
			if (map[x][y].right)
			{
				lines[6] = sf::Vertex(sf::Vector2f(x * TILE_WIDTH + TILE_WIDTH, y * TILE_HEIGHT));
				lines[7] = sf::Vertex(sf::Vector2f(x * TILE_WIDTH + TILE_WIDTH, y * TILE_HEIGHT + TILE_HEIGHT));
			}
			// Draw exit
			if ((exit.x == x) && (exit.y == y))
			{
				// Exit is slightly smaller than tile size
				sf::RectangleShape rExit(sf::Vector2f(TILE_WIDTH-4, TILE_HEIGHT-4));
				rExit.setPosition(sf::Vector2f((x * TILE_WIDTH)+2, (y * TILE_HEIGHT)+2));
				rExit.setFillColor(sf::Color::Red);
				window.draw(rExit);
			}

			// Draw vertices on screen
			window.draw(lines,8,sf::Lines);
		}
	}
}