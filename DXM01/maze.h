#pragma once
/*
Maze class
Generates a maze, displays and handles collisions in said maze
*/
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Stack.h"

#define TILE_WIDTH 20 // Tile width (in pixels)
#define TILE_HEIGHT 20 // Tile height (in pixels)
#define MAZE_WIDTH 30 // Total maze width
#define MAZE_HEIGHT 15 // Total maze height

class Maze
{
private:
	// Map tile
	struct Tile_t
	{
		// Determines which sides have walls
		bool top;
		bool bottom;
		bool left;
		bool right;
		// Has this tile been visited or not
		// Should default to false
		bool visited;
	};

	Tile_t map[MAZE_WIDTH][MAZE_HEIGHT]; // Array of maze tiles
	Stack stTiles = Stack((int)(MAZE_WIDTH * MAZE_HEIGHT)); // Stack of tiles, for backtracking
	unsigned int numVisited; // Number of tiles visited, halts loop when equal to size of array
	CRandom rand; // Random number generator
	unsigned int x, y; // X and Y iterators
	bool done; // Level generation complete flag
	sf::Vector2u exit; // Exit tile position

	// Make sure the X/Y positions aren't outside map array
	// Will return true if it is in array
	bool CheckBounds(sf::Vector2u pos) const;
	// Mark tile visited
	void MarkVisited(sf::Vector2u pos);

public:
	// Constructor
	// Will call GenerateMaze on construction
	Maze();
	// Is level done generating?
	bool IsDone();
	// Clear map
	// Will reset map to beginning stage
	void ClearMap();
	// Create randomized Maze
	// Runs every frame
	void GenerateMaze();
	// Try to move to a spot in Maze
	// Will return true if maze spot is valid
	// otherwise, returns false
	bool TryMove(sf::Vector2u prev, sf::Vector2u next) const;
	// Draw map onto screen
	void DrawMap(sf::RenderWindow &window) const;
};

