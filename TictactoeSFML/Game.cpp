#include "Game.h"

void Game::run()
{
	this->init();
	while (this->window->isOpen()) {
		this->updateEvent();
		this->update();
		this->render();
	}
}

Game::~Game()
{
	delete this->window;
	while (!this->states->empty()) {
		delete this->states->top();
		this->states->pop();
	}
	delete this->states;
}

void Game::init()
{
	this->window = new sf::RenderWindow(sf::VideoMode(900, 900), "Tic Tac Toe SFML", sf::Style::Titlebar | sf::Style::Close);
	this->states = new std::stack<State*>;

	this->states->push(new GameState(this->window));
}

void Game::updateEvent()
{
	sf::Event event;
	while (this->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) this->window->close();
		if (!this->states->empty()) this->states->top()->updateEvent(event);
	}
}

void Game::update()
{
	if (!this->states->empty()) {
		this->states->top()->update();
		if (this->states->top()->isChangedState) {
			if (this->states->top()->changeState(this->states)) {
				delete this->states->top();
				this->states->pop();
				this->states->top()->isChangedState = false;
			}
		}
	}
	
}

void Game::render()
{
	this->window->clear();

	if (!this->states->empty()) this->states->top()->render(this->window);

	this->window->display();
}
