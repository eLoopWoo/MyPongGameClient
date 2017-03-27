#include <SFML/Graphics.hpp>
#include <iostream>
#include <ball.h>
#include <paddle.h>
#include "Client.h"
#include <string> //For std::string

ball* pointer;

paddle* me1;
paddle* me2;

sf::RenderWindow* p;

Client myClient("127.0.0.1", 1111); //Create client to localhost ("127.0.0.1") on port 1111


void refresh() {
	while (true){
		(*me1).set_y(myClient.player_y1);
		(*me2).set_y(myClient.player_y2);
		(*pointer).set_x(myClient.ball_x);
		(*pointer).set_y(myClient.ball_y);
		(*me1).set_score(myClient.player1_score);
		(*me2).set_score(myClient.player2_score);
		Sleep(10);
	}
}


int main() {


	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
	p = &window;

	sf::Event event;


	sf::RectangleShape border_top(sf::Vector2f(512,10));
	border_top.setFillColor(sf::Color(224, 224, 224));
	border_top.setPosition(sf::Vector2f((640-512)/2, (480-384)/2));
	sf::RectangleShape border_bottom(sf::Vector2f(512,10));
	border_bottom.setFillColor(sf::Color(224, 224, 224));
	border_bottom.setPosition(sf::Vector2f((640 - 512)/2, (480 - 384) / 2+384));

	sf::RectangleShape border_left(sf::Vector2f(10, 384));//100
	border_left.setFillColor(sf::Color(224, 224, 224));
	border_left.setPosition(sf::Vector2f((640 - 512)/2, (480 - 384) / 2));
	sf::RectangleShape border_right(sf::Vector2f(10, 384));//500
	border_right.setFillColor(sf::Color(224, 224, 224));
	border_right.setPosition(sf::Vector2f(512+ (640 - 512) / 2, (480 - 384) / 2));




	paddle paddle1(p,94,250);
	paddle paddle2(p, 556, 250);
	sf::RectangleShape *x = paddle1.my_paddle;
	(*x).setFillColor(sf::Color(102, 178, 255));
	x= paddle2.my_paddle;
	(*x).setFillColor(sf::Color(255, 102, 102));
	me1 = &paddle1;
	me2 = &paddle2;

	ball ball1(p, 300, 300);
	pointer = &ball1;

	sf::Text* string;





	sf::Font fonts;
	fonts.loadFromFile("C:\\abc.ttf");
	// Create a text
	sf::Text texts("Created by eLoopWoo", fonts);
	texts.setCharacterSize(30);
	texts.setStyle(sf::Text::Bold);
	texts.setPosition(sf::Vector2f(300, 450));

	std::string input0;
	std::string input1;
	int input2;
	std::cout << "Enter 1 to choose IP or 0 for deafult ip 127.0.0.1 port 1111:" << std::endl;
	std::cin >> input0;
	if (input0 == "1") {
		std::cout << "Enter IP:" << std::endl;
		std::cin >> input1;
		myClient.setIP(input1, 1111);
		std::cout << "Enter Port:" << std::endl;
		std::cin >> input2;
		myClient.setIP(input1, input2);
	}

	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)refresh, NULL, NULL, NULL); //Create the client thread that will receive any data that the server sends.



	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		

			if (GetAsyncKeyState(0x57)) {
				if (!myClient.SendMoveUP1()) //Send string: userinput, If string fails to send... (Connection issue)
					continue; //If send string failed (if connection was closed), leave this loop since we have lost connection to the server
				Sleep(10);
			}

			if (GetAsyncKeyState(0x53)) {
				if (!myClient.SendMoveDOWN1()) //Send string: userinput, If string fails to send... (Connection issue)
					continue; //If send string failed (if connection was closed), leave this loop since we have lost connection to the server
				Sleep(10);
			}


			if (GetAsyncKeyState(VK_UP)) {
				if (!myClient.SendMoveUP2()) //Send string: userinput, If string fails to send... (Connection issue)
					continue; //If send string failed (if connection was closed), leave this loop since we have lost connection to the server
				Sleep(10);
			}

			if (GetAsyncKeyState(VK_DOWN)) {
				if (!myClient.SendMoveDOWN2()) //Send string: userinput, If string fails to send... (Connection issue)
					continue; //If send string failed (if connection was closed), leave this loop since we have lost connection to the server
				Sleep(10);
			}
			window.clear(sf::Color(64, 64, 64));

			string = (*me1).toString();
			(*string).setPosition(sf::Vector2f(220, 10));
			window.draw(*string);


			string = (*me2).toString();
			(*string).setPosition(sf::Vector2f(400, 10));
			window.draw(*string);

			window.draw(texts);
			ball1.print();
			paddle1.print();
			paddle2.print();
			window.draw(border_top);
			window.draw(border_bottom);
			window.draw(border_left);
			window.draw(border_right);

			window.display();
			Sleep(10);

		}


		
	}
