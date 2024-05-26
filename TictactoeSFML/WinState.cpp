#include "WinState.h"

WinState::WinState(State* gameState, const std::string& winner) : gameState(gameState)
{
	this->bg = new sf::RectangleShape(sf::Vector2f(900.f, 900.f));
	this->bg->setFillColor(sf::Color(0, 0, 0, 200));
	this->font = new sf::Font();
	this->font->loadFromFile("Fonts/Roboto-Bold.ttf");
	this->winningText = new sf::Text(winner == "draw" ? "Draw" : winner == "x" ? "X wins" : "O wins", *this->font, 120);
	this->winningText->setPosition(sf::Vector2f(450.f, 420.f) - winningText->getGlobalBounds().getSize() / 2.f);
	init();
}

WinState::~WinState()
{
	delete this->bg;
	delete this->font;
	delete this->winningText;
}

void WinState::init()
{
}

void WinState::updateEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) this->isChangedState = true;
	if (event.type == sf::Event::MouseButtonPressed) this->isChangedState = true;
}

void WinState::update()
{
}

void WinState::render(sf::RenderTarget* window)
{
	this->gameState->render(window);
	window->draw(*this->bg);
	window->draw(*this->winningText);
}

bool WinState::changeState(std::stack<State*>* states)
{
	this->gameState->init();

	return true;
}
