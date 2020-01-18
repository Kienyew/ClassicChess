// Javascript-like event handling.

#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <functional>
#include "Chess.h"

typedef sf::Vector2i v2i;
typedef sf::Vector2u v2u;
typedef sf::Vector2f v2f;

struct MouseEventArgs;
struct MouseDownEventArgs;
struct MouseUpEventArgs;
struct MouseMoveEventArgs;

class UserMouse
{
public:
	UserMouse(sf::Window* window);
	void update(sf::Event& evt);
	void onMouseDown(std::function<void(MouseDownEventArgs)> callback) { mouseDownCallbacks.emplace_back(callback); }
	void onMouseUp(std::function<void(MouseUpEventArgs)> callback) { mouseUpCallbacks.emplace_back(callback); }
	void onMouseMove(std::function<void(MouseMoveEventArgs)> callback) { mouseMoveCallbacks.emplace_back(callback); }
	void selected(Chess* selected) { m_selected = selected; }
	Chess* selected() const { return m_selected; }
	
	~UserMouse();

private:
	std::vector<std::function<void(MouseDownEventArgs)>> mouseDownCallbacks;
	std::vector<std::function<void(MouseUpEventArgs)>> mouseUpCallbacks;
	std::vector<std::function<void(MouseMoveEventArgs)>> mouseMoveCallbacks;
	v2i lastLeftMouseDownPosition;
	v2i lastLeftMouseUpPosition;
	v2i lastRightMouseDownPosition;
	v2i lastRightMouseUpPosition;
	v2i lastMiddleMouseDownPosition;
	v2i lastMiddleMouseUpPosition;
	sf::Window* window;
	Chess* m_selected;
};

struct MouseEventArgs {
	MouseEventArgs(v2i pos) : pos(pos) {}
	v2i pos;
};

struct MouseDownEventArgs : public MouseEventArgs {
	MouseDownEventArgs(sf::Mouse::Button btn, v2i pos) : MouseEventArgs(pos), button(btn) {}
	sf::Mouse::Button button;
};

struct MouseUpEventArgs : public MouseEventArgs {
	MouseUpEventArgs(sf::Mouse::Button btn, v2i pos) : MouseEventArgs(pos), button(btn) {}
	sf::Mouse::Button button;
};

struct MouseMoveEventArgs : public MouseEventArgs {
	using MouseEventArgs::MouseEventArgs;
};