#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <string>
#include "maze.h"
#include "player.h"

// Generating and gameplay framerates
#define FPS_GEN 60
#define FPS_MOV 15
// Game name for title bar
const std::string GAME_NAME = "DXM01";

// Init window
sf::RenderWindow window(sf::VideoMode(MAZE_WIDTH * TILE_WIDTH, MAZE_HEIGHT * TILE_HEIGHT), GAME_NAME);

// Maze
Maze maze;
// Player
Player player;

// Initialize
void Init()
{
	player.SetPos(0, 0);
	window.setFramerateLimit(FPS_GEN);
}

// Run game logic loop
void GameLoop()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::Resized)
		{
			// Increase view instead of sretching display
			window.setView(sf::View(sf::Vector2f(event.size.width / 2, event.size.height / 2),
				sf::Vector2f(event.size.width, event.size.height)));
		}
	}
	// Close window in Alt+F4
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt))
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F4))
	{
		window.close();
	}

	// Generate maze
	maze.GenerateMaze();

	// When level is done generating
	if (maze.IsDone())
	{
		window.setTitle(GAME_NAME + " - Get to the red square!");
		window.setFramerateLimit(FPS_MOV);
		player.Move();
	}
	// When level is in process of generating
	else
	{
		window.setTitle(GAME_NAME + " - Generating...");
		window.setFramerateLimit(FPS_GEN);
	}
}

// Draw objects onto screen
void Draw()
{
	// Clear previous frame
	// Will create background color
	window.clear(sf::Color::Black);
	// Draw player
	player.Draw(window);
	// Draw maze
	maze.DrawMap(window);
	// Show window
	window.display();
}

// MAIN FUNCTION //
int main()
{
	Init();

	// Do main loop
	while (window.isOpen())
	{
		GameLoop();
		Draw();
	}
	// Quit
	return 0;
}