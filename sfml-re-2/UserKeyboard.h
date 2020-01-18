#pragma once

#include <SFML\Graphics.hpp>
#include <deque>
#include <vector>
#include <utility>
#include <functional>

struct KeyDownEventArgs;

class UserKeyboard
{
public:
	UserKeyboard(size_t key_buffer=200);
	~UserKeyboard();
	void update(sf::Event& evt);
	void onKeyDown(std::function<void(KeyDownEventArgs)> f);
	std::string lastNChars(size_t n);

	static char sfkey2char(sf::Keyboard::Key key_code);
	


private:
	size_t m_key_buffers;
	std::deque<char> m_prev_keys;
	std::vector<std::function<void(KeyDownEventArgs)>> keyDownCallbacks;
	
};


struct KeyDownEventArgs {
public:
	KeyDownEventArgs(sf::Keyboard::Key key_code) : keyCode(key_code)
	{}

	sf::Keyboard::Key keyCode;
	char toChar() { return UserKeyboard::sfkey2char(keyCode); }
};
