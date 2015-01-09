#pragma once
/*
Custom stack class
Because STD stack sucks ass, and so do templates
From: http://www.cs.utsa.edu/~wagner/CS2213/stack/stack.html
*/
#include <SFML/Graphics.hpp>

class Stack
{
private:
	int MaxStack;
	int EmptyStack;
	int top;
	sf::Vector2u* items;

public:
	Stack(int);
	~Stack();
	void push(sf::Vector2u);
	sf::Vector2u pop();
	int empty();
	int full();
};

