#pragma once
/*
Player class
Handles player character; reads input, draws to screen
*/
#include <SFML/Graphics.hpp>
#include "maze.h"
extern Maze maze; // Maze defined in main.cpp

class Player
{
private:
	unsigned int x; // X position in world
	unsigned int y; // Y position in world

public:
	// Constructor
	// Spawns player into the world
	Player(unsigned int x = 0, unsigned int y = 0);
	// Move Player
	// Reads input and moves player accordingly
	void Move();
	// Set player position
	// Forces player into grid position you specify
	void SetPos(unsigned int x, unsigned int y);
	// Draw Player
	// draws player onto screen
	void Draw(sf::RenderWindow &window) const;
};

