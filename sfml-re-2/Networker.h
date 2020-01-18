// Networking and Player Informations

#pragma once
#include <string>
#include <vector>
#include <functional>
#include <SFML\Network.hpp>
#include "Chess.h"

enum NetworkRole { Server, Client };

struct OnClientConnectEventArgs;
struct OnReceiveEventArgs;

class Networker
{
public:
	Networker(NetworkRole role);
	~Networker();
	
	void acceptOne(unsigned short port);
	void connect(const sf::IpAddress& remote_ip, unsigned short port);
	void OnClientConnect(std::function<void(OnClientConnectEventArgs)> f);
	void OnReceive(std::function<void(OnReceiveEventArgs)> f);
	void receiveLoop();
	void setColor(ChessColor team);
	void swapTurn() { m_onTurn = !m_onTurn; }
	bool send(const std::string& data);
	void sendImportant(const std::string& data, float delayInSeconds = 0.1f);
	bool onTurn() { return m_onTurn; }
	
	NetworkRole role() const { return network_role; }
	ChessColor getColor() { return m_team; }


private:
	ChessColor m_team;
	bool m_onTurn;
	sf::TcpListener listener;
	sf::TcpSocket socket;
	sf::Thread thread;
	NetworkRole network_role;

	std::vector<std::function<void(OnClientConnectEventArgs)>> onClientConnectCallbacks;
	std::vector<std::function<void(OnReceiveEventArgs)>> onReceiveCallbacks;
};

struct OnClientConnectEventArgs {
public:
	OnClientConnectEventArgs(const sf::IpAddress& client_ip): ip(client_ip)
	{}

	const sf::IpAddress& ip;
};

struct OnReceiveEventArgs {
public:
	OnReceiveEventArgs(const std::string& data, size_t size, const sf::IpAddress& from_ip) :
		fromIp(from_ip), data(data), size(size)
	{
	}

	const sf::IpAddress& fromIp;
	size_t size;
	const std::string& data;

};

