#pragma once
#include <SFML/Graphics.hpp>

class playerbullet {
public:
	sf::Sprite bullet;

	sf::Texture explosionTexture;
	sf::Texture bulletTexture;

	sf::IntRect rect4[2];

	playerbullet() {
		bulletTexture.loadFromFile("Textures/playerbullet.png");
		explosionTexture.loadFromFile("Textures/explosion.png");

		rect4[0] = sf::IntRect(0, 0, 12, 8);
		rect4[1] = sf::IntRect(0, 0, 5, 9);

	}

	void bulletExplosion() {
		bullet.setScale(3,3);
		bullet.setTextureRect(rect4[0]);
		bullet.setTexture(explosionTexture);
	}
	void normal() {
		bullet.setTextureRect(rect4[1]);
		bullet.setTexture(bulletTexture);
		bullet.setScale(1, 2.25);
	}

};