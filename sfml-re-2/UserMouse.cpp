#include "UserMouse.h"
#include <SFML\Graphics.hpp>


UserMouse::UserMouse(sf::Window* window) : window(window), m_selected(nullptr)
{
}

UserMouse::~UserMouse()
{
}

void UserMouse::update(sf::Event& evt) {
	if (evt.type == sf::Event::MouseButtonPressed)
	{
		if (evt.mouseButton.button == sf::Mouse::Left) {
			lastLeftMouseDownPosition = sf::Mouse::getPosition(*window);
		}
		else if (evt.mouseButton.button == sf::Mouse::Right) {
			lastRightMouseDownPosition = sf::Mouse::getPosition(*window);
		}
		else if (evt.mouseButton.button == sf::Mouse::Middle) {
			lastMiddleMouseDownPosition = sf::Mouse::getPosition(*window);
		}

		for (auto callback : mouseDownCallbacks) {
			callback(MouseDownEventArgs(evt.mouseButton.button, sf::Mouse::getPosition(*window)));
		}
	}

	if (evt.type == sf::Event::MouseButtonReleased)
	{
		if (evt.mouseButton.button == sf::Mouse::Left){
			lastLeftMouseUpPosition = sf::Mouse::getPosition(*window);
		}
		else if (evt.mouseButton.button == sf::Mouse::Right) {
			lastRightMouseUpPosition = sf::Mouse::getPosition(*window);
		}

		for (auto callback : mouseUpCallbacks) {
			callback(MouseUpEventArgs(evt.mouseButton.button, sf::Mouse::getPosition(*window)));
		}
	}

	if (evt.type == sf::Event::MouseMoved)
	{
		for (auto callback : mouseMoveCallbacks) {
			callback(MouseMoveEventArgs(sf::Mouse::getPosition(*window)));
		}
	}
}



