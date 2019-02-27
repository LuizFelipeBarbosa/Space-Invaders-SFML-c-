#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.h"

class enemybullet {
	bool explosion = false;
	sf::IntRect rect4[1];
	sf::IntRect rect5[2];
	sf::IntRect rect6[2];
	
public:

	bool bullet2 = false;
	bool bullet3 = false;

	int count = 0;
	int randomBullet;

	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;

	enemybullet() {
		rect5[0] = sf::IntRect(0, 8, 3, 8);
		rect5[1] = sf::IntRect(3, 8, 6, 8);

		rect6[0] = sf::IntRect(0, 16, 3, 8);
		rect6[1] = sf::IntRect(3, 16, 6, 8);

		bulletTexture.loadFromFile("Textures/projectile.png");
		bulletSprite.setTexture(bulletTexture);
		bulletSprite.setPosition(1000,2000);
		bulletSprite.setScale(3,3);
		bulletSprite.setTextureRect(rect5[0]);

	}


	int bulletState() {
		if (count < 1) {
			count++;
		}
		else {
			count = 0;
		}
		return count;
	}

	void animateBullet() {
		if (bullet2) {
			bulletSprite.setTextureRect(rect5[count]);
		}
		if (bullet3) {
			bulletSprite.setTextureRect(rect6[count]);
		}
	}

	enum enemyBulletcollision { YES, NONE };

	enemyBulletcollision enemybulletcollision(sf::Sprite Sprite) {

		if (!bulletSprite.getGlobalBounds().intersects(Sprite.getGlobalBounds())) { return enemyBulletcollision::NONE; }
		else if (bulletSprite.getGlobalBounds().intersects(Sprite.getGlobalBounds())) { return enemyBulletcollision::YES; }

	}
};
