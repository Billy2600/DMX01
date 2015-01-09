#include "player.h"


Player::Player(unsigned int x, unsigned int y)
{
	SetPos(x, y);
}

void Player::Move()
{
	// Check for win
	if (x == (MAZE_WIDTH - 1) && y == (MAZE_HEIGHT - 1))
	{
		maze.ClearMap();
		// Reset player position
		x = 0; y = 0;
	}

	// Next Move
	int nextX = x;
	int nextY = y;

	// Read input and set next move accordingly
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) // Left
		nextX--;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) // Right
		nextX++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) // Up
		nextY--;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) // Down
		nextY++;

	// Check for valid move, and if so, move there
	sf::Vector2u pos(x, y);
	if (maze.TryMove(pos, sf::Vector2u(nextX, nextY)))
	{
		SetPos(nextX, nextY);
		return; // Stop here
	}
	// Check other combinations if we didn't stop there
	// Use previous X
	else if (maze.TryMove(pos, sf::Vector2u(x, nextY)))
	{
		SetPos(x, nextY);
		return;
	}
	// Use previous Y
	else if (maze.TryMove(pos, sf::Vector2u(nextX, y)))
	{
		SetPos(nextX, y);
		return;
	}
}

void Player::SetPos(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
}

void Player::Draw(sf::RenderWindow &window) const
{
	// Box representing the player
	sf::RectangleShape player;
	// Player width/height is the same as tile width/height from tile class
	player.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
	// Other settings
	player.setFillColor(sf::Color::Blue);
	player.setPosition(sf::Vector2f(x * TILE_WIDTH, y * TILE_HEIGHT));
	// Draw it
	window.draw(player);
}