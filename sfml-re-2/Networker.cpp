#include "Networker.h"

#include <stdexcept>
#include <string>
#include <iostream>
#include <exception>
#include <SFML/Network.hpp>

Networker::Networker(NetworkRole role) :
	network_role(role),
	thread(&Networker::receiveLoop, this)

{
	thread.launch();
}


Networker::~Networker()
{
}

void Networker::acceptOne(unsigned short port)
{
	if (this->network_role != Server) throw std::runtime_error("Only server can accept.");
	listener.listen(port);
	listener.accept(this->socket);
	for (auto& f : onClientConnectCallbacks) {
		f(OnClientConnectEventArgs(this->socket.getRemoteAddress()));
	}
}

void Networker::connect(const sf::IpAddress& remote_ip, unsigned short port)
{
	this->socket.connect(remote_ip, port);
}

bool Networker::send(const std::string & data)
{
	return (socket.send(data.c_str(), data.length() + 1) == sf::Socket::Status::Done);
}

void Networker::sendImportant(const std::string & data, float delayInSeconds)
{
	bool success;
	do {
		success = this->send(data);
		if (!success) sf::sleep(sf::seconds(0.1f));
	} while (!success);
}

void Networker::OnClientConnect(std::function<void(OnClientConnectEventArgs)> f)
{
	onClientConnectCallbacks.push_back(f);
}

void Networker::OnReceive(std::function<void(OnReceiveEventArgs)> f)
{
	onReceiveCallbacks.push_back(f);
}

void Networker::receiveLoop()
{
	while (true) {
		size_t received;
		char buffer[2048];
		socket.receive(buffer, sizeof(buffer), received);
		if (received != 0) {
			for (auto& f : onReceiveCallbacks) {
				f(OnReceiveEventArgs(std::string(buffer, received), received, socket.getRemoteAddress()));
			}
		}
		sf::sleep(sf::seconds(0.025f));
	}
}

void Networker::setColor(ChessColor team)
{
	m_team = team; 
	if (team == White) 
		m_onTurn = true;
	else
		m_onTurn = false;
}
