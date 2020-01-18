#include "UserKeyboard.h"
#include <iostream>


UserKeyboard::UserKeyboard(size_t key_buffer) : m_key_buffers(key_buffer)
{

}


UserKeyboard::~UserKeyboard()
{
}

void UserKeyboard::update(sf::Event& evt)
{
	if (evt.type == evt.KeyPressed) {
		this->m_prev_keys.push_back(UserKeyboard::sfkey2char(evt.key.code));
		if (this->m_prev_keys.size() > this->m_key_buffers) {
			this->m_prev_keys.pop_front();
		}

		for (auto& callback : this->keyDownCallbacks) {
			callback(KeyDownEventArgs(evt.key.code));
		}
	}
}

void UserKeyboard::onKeyDown(std::function<void(KeyDownEventArgs)> f)
{
	this->keyDownCallbacks.push_back(f);
}

std::string UserKeyboard::lastNChars(size_t n)
{
	if (n > this->m_prev_keys.size()) {
		return std::string(this->m_prev_keys.cbegin(), this->m_prev_keys.cend());
	}
	return std::string(this->m_prev_keys.cend() - n, this->m_prev_keys.cend());
}


char UserKeyboard::sfkey2char(sf::Keyboard::Key key_code) {
	switch (key_code)
	{
	case sf::Keyboard::A:
		return 'a';
		break;

	case sf::Keyboard::B:
		return 'b';
		break;

	case sf::Keyboard::C:
		return 'c';
		break;

	case sf::Keyboard::D:
		return 'd';
		break;

	case sf::Keyboard::E:
		return 'e';
		break;

	case sf::Keyboard::F:
		return 'f';
		break;

	case sf::Keyboard::G:
		return 'g';
		break;

	case sf::Keyboard::H:
		return 'h';
		break;

	case sf::Keyboard::I:
		return 'i';
		break;

	case sf::Keyboard::J:
		return 'j';
		break;

	case sf::Keyboard::K:
		return 'k';
		break;

	case sf::Keyboard::L:
		return 'l';
		break;

	case sf::Keyboard::M:
		return 'm';
		break;

	case sf::Keyboard::N:
		return 'n';
		break;

	case sf::Keyboard::O:
		return 'o';
		break;

	case sf::Keyboard::P:
		return 'p';
		break;

	case sf::Keyboard::Q:
		return 'q';
		break;

	case sf::Keyboard::R:
		return 'r';
		break;

	case sf::Keyboard::S:
		return 's';
		break;

	case sf::Keyboard::T:
		return 't';
		break;

	case sf::Keyboard::U:
		return 'u';
		break;

	case sf::Keyboard::V:
		return 'v';
		break;

	case sf::Keyboard::W:
		return 'w';
		break;

	case sf::Keyboard::X:
		return 'x';
		break;

	case sf::Keyboard::Y:
		return 'y';
		break;

	case sf::Keyboard::Z:
		return 'z';
		break;

	default:
		return '\0';
	}
}