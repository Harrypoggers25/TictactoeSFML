#pragma once
#include "GameState.h"
#include <stack>

class Game
{
public:
	void run();
	virtual ~Game();

private:
	sf::RenderWindow* window;
	std::stack<State*>* states;

	void init();
	void updateEvent();
	void update();
	void render();
};

