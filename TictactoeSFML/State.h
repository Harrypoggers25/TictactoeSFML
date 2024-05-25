#pragma once
#include "SFML/Graphics.hpp"

class State
{
public:
	virtual ~State();

	virtual void init() = 0;
	virtual void updateEvent(const sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* window) = 0;
};

