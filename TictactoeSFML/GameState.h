#pragma once
#include "State.h"
#include <map>

class GameState :
    public State
{
private:
	sf::RenderWindow* window;

	std::map<std::string, sf::Texture*> t;
	sf::Sprite* bg;
	sf::Sprite* x;
	sf::Sprite* o;
	sf::Sprite* ghost;

	int grid[3][3];
	bool turn;
	bool highlighted;
	std::string winner;

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	void init();
	void updateEvent(const sf::Event& event);
	void update();
	void render(sf::RenderTarget* window);
	bool changeState(std::stack<State*>* states);
};

