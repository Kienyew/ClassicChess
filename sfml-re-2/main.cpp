// HI! Greet to you and wish you have a nice day!
// This is my first project in C++/SFML. 
// I made this for no reason, just giving my self a try
// As the author of this project, I really don't suggest you to look around these code
// Many of the codes are redundant and may not be a good example for you, provided that you have enough patient to dive into the mess below :P
// That's all. Thanks for downloading. <3 Programming

#include <map>
#include <vector>
#include <cctype>
#include <clocale>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "Node.h"
#include "TextureTiles.h"
#include "UserMouse.h"
#include "UserKeyboard.h"
#include "ChessBoard.h"
#include "Chess.h"
#include "Chesses.h"
#include "ChessSet.h"
#include "Networker.h"
#include "DrawingBoard.h"

using namespace std;

typedef sf::Vector2i v2i;
typedef sf::Vector2u v2u;
typedef sf::Vector2f v2f;


// Functions Declaration
void cmd_mv(const string& chess_name, const string& x, const string& y);
void cmd_setclr(char c);
void cmd_turn();
void resolveCommands(const std::string& many_cmd);
bool command(const string& line);
void start();
void update();
void handleEvent(sf::RenderWindow& win);

enum GameMode {
	Play, Draw
};

// Instantiations
sf::RenderWindow window(sf::VideoMode(400, 400), "Title", sf::Style::Titlebar | sf::Style::Close);
sf::CircleShape opMouseCircle(5.f);
sf::CircleShape myMouseCircle(5.f);
UserMouse mouse(&window);
UserKeyboard keyboard;
GameMode mode = Play;
ChessBoard board(8, 8, 400, 400);
ChessSet chesses(&board);
Networker* player;
DrawingBoard drawingBoard(400, 400);
ofstream logFile;

// Function Definition

// mv: move target chess to specific coordinate. params(chess_name, x, y) eg: 'mv WhiteKing 3 4'
void cmd_mv(const string& chess_name, const string& x, const string& y)
{
	v2u targetCoord = { stoul(x), stoul(y) };
	Chess* selected_chess = chesses[chess_name];
	Chess* chessOn = board.chessOn(targetCoord);
	if (selected_chess->tryMoveTo(targetCoord)) {
		if (chessOn != nullptr) {
			chessOn->kill(selected_chess);
		}
	}
}

// setclr: set chess color. w - White, b - Black. params(color) eg: 'setclr w'
void cmd_setclr(char c) {
	sf::Color blackColor(30, 50, 60, 210);
	sf::Color whiteColor(230, 255, 255, 210);

	if (c == 'w') {
		player->setColor(White);
		myMouseCircle.setFillColor(whiteColor);
		opMouseCircle.setFillColor(blackColor);
	}
	else {
		player->setColor(Black);
		myMouseCircle.setFillColor(blackColor);
		opMouseCircle.setFillColor(whiteColor);
	}


}

// swap turn. eg: 'turn'
void cmd_turn() {
	player->swapTurn();
	string who_turn_color;
	if (player->onTurn()) {
		if (player->getColor() == White) who_turn_color = "white";
		else who_turn_color = "black";
	}
	else {
		if (player->getColor() == White) who_turn_color = "black";
		else who_turn_color = "white";
	}

	cout << who_turn_color << "'s turn" << endl;
}

// opponent mouse move. x and y is in range[0..1] eg: 'mm 0.182 0.854'
void cmd_mm(const string& x, const string& y) {
	opMouseCircle.setPosition(stof(x) * window.getSize().x, stof(y) * window.getSize().y);
}

inline void cmd_msg(const string& msg) {
	cout << "<- Msg: "<< msg << endl;
}

void cmd_drwln(const string& x, const string& y) {
	drawingBoard.append({ stof(x) * window.getSize().x, stof(y) * window.getSize().y });
}

inline void cmd_newln() {
	drawingBoard.newLine();
}

inline void cmd_clear() {
	drawingBoard.clear();
}

inline void cmd_killclose() {
	window.close();
}

// may be many commands chain in one line when receive from network, seperate by NULL_CHARACTER ('\0')
void resolveCommands(const std::string& many_cmd) {
	istringstream line(many_cmd);
	string tmp;
	ostringstream one_cmd;
	size_t offset = 0;
	do {
		size_t nul_offset = many_cmd.find('\0', offset);
		command(many_cmd.substr(offset, nul_offset - offset));
		offset = nul_offset + 1;
	} while (offset != 0);
}

// run one command only. 
bool command(const string& line) {
	istringstream iss(line);
	string cmd;
	iss >> cmd;

	if (cmd == "mv")
	{
		string chess_name, x, y;
		iss >> chess_name >> x >> y;
		cmd_mv(chess_name, x, y);
	}
	else if (cmd == "setclr") {
		char color;
		iss >> color;
		cmd_setclr(color);
	}
	else if (cmd == "turn") {
		cmd_turn();
	}
	else if (cmd == "mm") {
		string x, y;
		iss >> x >> y;
		cmd_mm(x, y);
	}
	else if (cmd == "msg") {
		string message;
		getline(iss, message);
		cmd_msg(message);
	}
	else if (cmd == "drwln") {
		string x, y;
		iss >> x >> y;
		cmd_drwln(x, y);
	}
	else if (cmd == "newln") {
		cmd_newln();
	}
	else if (cmd == "clear") {
		cmd_clear();
	}
	else if (cmd == "killclose") {
		cmd_killclose();
	}
	else {
		return false;
	}

	return true;
}

// run on program start
void start()
{
	opMouseCircle.setOrigin(opMouseCircle.getRadius(), opMouseCircle.getRadius());
	myMouseCircle.setOrigin(myMouseCircle.getRadius(), myMouseCircle.getRadius());

	cout << "[s|c]: ";
	char c;
	cin >> c;
	cin.ignore(10000, '\n');

	if (c == 's' || c == 'S') {
		player = new Networker(Server);
	}
	else if (c == 'c' || c == 'C') {
		player = new Networker(Client);
	}
	else {
		exit(-1);
	}

	player->OnClientConnect([](OnClientConnectEventArgs args) {
		cout << ":: " << args.ip << endl;
		player->sendImportant(string("setclr ") + (player->getColor() == White ? "b" : "w") + " ; ");
	});
	player->OnReceive([](OnReceiveEventArgs args) {
		resolveCommands(args.data);
		if (logFile.is_open()) {
			logFile << args.data << endl;
		}
	});

	if (player->role() == Server) {
		char color;
		cout << "[w|b]: ";
		cin >> color;
		cin.ignore(10000, '\n');
		resolveCommands(std::string("setclr ") + color + " ; ");
		cout << ":: " << sf::IpAddress::getLocalAddress() << " ..." << endl;
		player->acceptOne(3753);


	}
	else if (player->role() == Client) {
		sf::IpAddress ip;
		cout << "::-> ";
		cin >> ip;
		cin.ignore(10000, '\n');
		cout << endl;
		player->connect(ip, 3753);
	}

	mouse.onMouseMove([](MouseMoveEventArgs args) {
		v2u coord = board.mapPosToCoord(v2f(args.pos));
		myMouseCircle.setPosition(float(args.pos.x), float(args.pos.y));
		string sx = to_string(float(args.pos.x) / window.getSize().x);	sx = sx.substr(0, sx.length() - 3);
		string sy = to_string(float(args.pos.y) / window.getSize().y);	sy = sy.substr(0, sy.length() - 3);
		player->send("mm " + sx + " " + sy);
		if (mode == Draw) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				string sx = to_string(float(args.pos.x) / window.getSize().x);	sx = sx.substr(0, sx.length() - 3);
				string sy = to_string(float(args.pos.y) / window.getSize().y);	sy = sy.substr(0, sy.length() - 3);
				string cmd = "drwln " + sx + " " + sy;
				player->sendImportant(cmd);
				resolveCommands(cmd);
			}
		}
	});
	mouse.onMouseDown([](MouseDownEventArgs args) {
		if (mode == Play) {
			v2u targetCoord = board.mapPosToCoord(v2f(args.pos));
			Chess* chessOnTarget = board.chessOn(targetCoord);
			if (args.button == sf::Mouse::Right) {
				mouse.selected(chessOnTarget);
				if (chessOnTarget != nullptr && chessOnTarget->color() == player->getColor()) cout << "select: " << chessOnTarget->name() << endl;
			}
			else if (args.button == sf::Mouse::Left)
			{
				Chess* selected_chess = mouse.selected();
				if (selected_chess != nullptr && selected_chess->color() == player->getColor() && player->onTurn())
				{
					if (selected_chess->canMoveTo(targetCoord)) {
						v2u ori_coord = selected_chess->getCoordinate();
						const string& cmdstr = "mv " + mouse.selected()->name() + " " + to_string(targetCoord.x) + " " + to_string(targetCoord.y);
						resolveCommands(cmdstr);
						player->sendImportant(cmdstr);
						resolveCommands("turn");
						player->sendImportant("turn");

					}
					else {
						cout << selected_chess->name() << " -> [" << targetCoord.x << ", " << to_string(targetCoord.y) << "] fail." << endl;
					}
				}
			}
		}
	});

	mouse.onMouseUp([](MouseUpEventArgs args) {
		if (mode == Draw) {
			if (args.button == sf::Mouse::Left) {
				string cmd = "newln";
				resolveCommands(cmd);
				player->sendImportant(cmd);
			}
		}
	});

	keyboard.onKeyDown([](KeyDownEventArgs args) {
		if (args.keyCode == sf::Keyboard::Backspace) {
			mode = Play;
			cout << "mode: Play" << endl;
		}
		else if (args.keyCode == sf::Keyboard::Space) {
			cout << "Resize" << endl;
			v2u oldSize = window.getSize();
			size_t m = min(oldSize.x, oldSize.y);
			m = max(200, int(50 + (m % 600)));
			window.setView(sf::View(sf::FloatRect(0, 0, float(m), float(m))));
			window.setSize({ m, m });
			board.resize({ float(m),float(m) });
			drawingBoard.resize(float(m), float(m));
			chesses.iter([](Chess* chess) {
				sf::Vector2f newpos = board.mapCoordToPos(chess->getCoordinate());
				chess->resize(sf::FloatRect(newpos.x, newpos.y, board.nodeSize().x, board.nodeSize().y));
			});
		}
		
		if (keyboard.lastNChars(4) == "draw") {
			mode = Draw;
			cout << "mode: Draw" << endl;
		}
		else if (keyboard.lastNChars(3) == "msg") {
			cout << "-> Msg: ";
			string message;
			getline(cin, message);
			player->sendImportant("msg " + message);
		}
		else if (keyboard.lastNChars(5) == "clear") {
			string cmd = "clear";
			player->sendImportant(cmd);
			resolveCommands(cmd);
		}
		else if (keyboard.lastNChars(9) == "killclose") {
			player->sendImportant("killclose");
		}


	});

	window.setVerticalSyncEnabled(true);
}

// run every frame
void update()
{
	handleEvent(window);
	window.clear();
	window.draw(board);
	window.draw(chesses);
	window.draw(opMouseCircle);
	window.draw(myMouseCircle);
	window.draw(drawingBoard);
	window.display();

}

// poll event
void handleEvent(sf::RenderWindow& win)
{
	sf::Event evt;
	while (window.pollEvent(evt))
	{
		if (evt.type == evt.Closed) {
			window.close();
		}

		mouse.update(evt);
		keyboard.update(evt);
	}
}

int main(int argc, char* argv[])
{
	if (argc == 2) {
		std::setlocale(LC_ALL, "en_US.UTF-8");
		try {
			logFile.open(argv[1]);
		}
		catch (exception e) {
			cout << e.what() << endl;
			sf::sleep(sf::seconds(1));
			_exit(-2);
		}
	}
	start();
	while (window.isOpen())
	{
		update();
	}
}