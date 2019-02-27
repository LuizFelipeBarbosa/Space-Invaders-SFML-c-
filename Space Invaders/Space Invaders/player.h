#pragma once
#include <SFML/Graphics.hpp>

class player {
public:
	sf::Sprite player1;
	sf::Texture playertexture;
	sf::IntRect rect[3];

	int count = 0;

	int lives = 3;

	enum collision1 { YES, NONE };

	player() {

		rect[0] = sf::IntRect(0, 0, 11, 8);
		rect[1] = sf::IntRect(11, 0, 11, 8);
		rect[2] = sf::IntRect(22, 0, 11, 8);

		playertexture.loadFromFile("Textures/player.png");
		player1.setTexture(playertexture);
		player1.setTextureRect(rect[0]);
		player1.setScale(3,3);
		player1.setPosition(500, 700);

	}

	int playerState() {
		if (count < 2) {
			count++;
		}
		else {
			count = 1;
		}
		return count;
	}

	void animatePlayer() {
		player1.setTextureRect(rect[count]);
	}
};
