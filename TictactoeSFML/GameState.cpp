#include "GameState.h"
#include "WinState.h"
#include <iostream>

GameState::GameState(sf::RenderWindow* window) :
	window(window)
{
	this->t = {
		{"bg", new sf::Texture},
		{"x", new sf::Texture},
		{"o", new sf::Texture}
	};
	this->t["bg"]->loadFromFile("Images/bg.png");
	this->t["x"]->loadFromFile("Images/x.png");
	this->t["o"]->loadFromFile("Images/o.png");

	this->bg = new sf::Sprite(*t["bg"]);
	this->x = new sf::Sprite(*t["x"]);
	this->o = new sf::Sprite(*t["o"]);

	init();
}

GameState::~GameState()
{
	for (auto iter = this->t.begin(); iter != this->t.end(); ++iter) {
		delete t[iter->first];
	}
	this->t.clear();

	delete this->bg;
	delete this->x;
	delete this->o;
	delete this->ghost;
}

void GameState::init()
{
	this->ghost = new sf::Sprite(*t["x"]);

	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			this->grid[i][j] = 0;
		}
	}
	this->turn = false; // False = X, True = O
	this->highlighted = false;
	this->winner = "none";
}

void GameState::updateEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseMoved) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
		int col = (int)(mousePos.x / 300);
		int row = (int)(mousePos.y / 300);
		float cellx = (float)(col * 300);
		float celly = (float)(row * 300);
		this->highlighted = true;

		if (this->grid[row][col] == 0) this->ghost->setPosition(cellx, celly);
		else this->highlighted = false;
	}
	if (event.type == sf::Event::MouseLeft) this->highlighted = false;
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
		int col = (int)(mousePos.x / 300);
		int row = (int)(mousePos.y / 300);

		if (this->grid[row][col] == 0) {
			this->grid[row][col] = this->turn == false ? 1 : 2;
			this->turn = !this->turn;
			this->ghost->setTexture(this->turn == false ? *t["x"] : *t["o"]);
			this->highlighted = false;

			auto checkWin = [](const int grid[3][3]) {
				auto checkLine = [](const std::string& str) {
					if (str == "111") return "x";
					else if (str == "222") return "o";
					else return "none";
				};

				// Check vertical
				for (size_t j = 0; j < 3; j++) {
					std::string str = 
						std::to_string(grid[0][j]) + 
						std::to_string(grid[1][j]) + 
						std::to_string(grid[2][j]);
					std::string result = checkLine(str);
					if (result != "none") return result;
				}

				// Check horizontal
				for (size_t i = 0; i < 3; i++) {
					std::string str =
						std::to_string(grid[i][0]) +
						std::to_string(grid[i][1]) +
						std::to_string(grid[i][2]);
					std::string result = checkLine(str);
					if (result != "none") return result;
				}

				// check diagonal
				std::string str =
					std::to_string(grid[0][0]) +
					std::to_string(grid[1][1]) +
					std::to_string(grid[2][2]); // Down-right diagonal
				std::string result = checkLine(str);
				if (result != "none") return result;

				str =
					std::to_string(grid[2][0]) +
					std::to_string(grid[1][1]) +
					std::to_string(grid[0][2]); // Up-right diagonal
				result = checkLine(str);
				if (result != "none") return result;

				// check draw
				for (size_t i = 0; i < 3; i++) {
					for (size_t j = 0; j < 3; j++) {
						if (grid[i][j] == 0) return (std::string) "none";
					}
				}

				return (std::string) "draw";
			};
			this->winner = checkWin(this->grid);
			if (this->winner != "none") {
				this->isChangedState = true;
			}
		}
	}
}

void GameState::update()
{
}

void GameState::render(sf::RenderTarget* window)
{
	window->draw(*this->bg);
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (this->grid[i][j] == 1) {
				this->x->setPosition(j * 300.f, i * 300.f);
				window->draw(*this->x);
			}
			else if (this->grid[i][j] == 2) {
				this->o->setPosition(j * 300.f, i * 300.f);
				window->draw(*this->o);
			}
		}
	}
	if (this->highlighted) window->draw(*this->ghost);
}

bool GameState::changeState(std::stack<State*>* states)
{
	states->push(new WinState(this, this->winner));

	return false; // keep previous state
}
