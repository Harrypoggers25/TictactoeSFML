#pragma once
#include "SFML/Graphics.hpp"
#include <stack>
class State
{
public:
	bool isChangedState;
	
	virtual ~State();

	virtual void init() = 0;
	virtual void updateEvent(const sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* window) = 0;
	virtual bool changeState(std::stack<State*>* states) = 0;
};

