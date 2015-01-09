#include "Stack.h"


Stack::Stack(int size)
{
	MaxStack = size;
	EmptyStack = -1;
	top = EmptyStack;
	items = new sf::Vector2u[MaxStack];
}


Stack::~Stack()
{
	delete[] items;
}

void Stack::push(sf::Vector2u c)
{
	items[++top] = c;
}

sf::Vector2u Stack::pop()
{
	return items[top--];
}

int Stack::full()
{
	return top + 1 == MaxStack;
}

int Stack::empty()
{
	return top == EmptyStack;
}