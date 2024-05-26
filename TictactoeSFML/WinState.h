#pragma once
#include "State.h"
class WinState :
    public State
{
private:
	State* gameState;
	sf::RectangleShape* bg;
	sf::Font* font;
	sf::Text* winningText;

public:
	WinState(State* gameState, const std::string& winner);
	virtual ~WinState();

	void init();
	void updateEvent(const sf::Event& event);
	void update();
	void render(sf::RenderTarget* window);
	bool changeState(std::stack<State*>* states);
};

