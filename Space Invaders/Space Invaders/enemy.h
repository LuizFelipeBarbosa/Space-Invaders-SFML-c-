#pragma once
#include <SFML/Graphics.hpp>

class enemy {
public:

	enum collision1 { YES, NONE };

	sf::Texture explosionTexture;
	sf::Texture enemytexture1;
	sf::Texture ufoTexture;

	sf::Sprite enemysprite1;
	sf::Sprite ufoSprite;

	sf::IntRect rect1[2];
	sf::IntRect rect2[2];
	sf::IntRect rect3[2];
	sf::IntRect ufoRect[4];

	bool shoot = false;

	int randEnemy;

	int count = 0;
	int count1 = 0;

	bool enemy1 = false;
	bool enemy2 = false;
	bool enemy3 = false;

	bool left = true;
	bool right = false;
	bool down = false;

	bool alive = true;

	bool explosion = false;

	enemy() {
		enemytexture1.loadFromFile("Textures/invaders.png");
		ufoTexture.loadFromFile("Textures/ufo.png");

		rect1[0] = sf::IntRect(0, 0, 12, 8);
		rect1[1] = sf::IntRect(12, 0, 12, 8);

		rect2[0] = sf::IntRect(0, 8, 12, 8);
		rect2[1] = sf::IntRect(12, 8, 12, 8);

		rect3[0] = sf::IntRect(0, 16, 12, 8);
		rect3[1] = sf::IntRect(12, 16, 12, 8);

		ufoRect[0] = sf::IntRect(0, 0, 16, 8);
		ufoRect[1] = sf::IntRect(16, 0, 16, 8);
		ufoRect[2] = sf::IntRect(0, 0, 16, 8);
		ufoRect[3] = sf::IntRect(32, 0, 16, 8);

		ufoSprite.setTexture(ufoTexture);
		ufoSprite.setScale(3.5,3.5);

		enemysprite1.setTexture(enemytexture1);
		enemysprite1.setScale(3, 3);

	}

	int randomEnemy() {
		randEnemy = rand() % 11;
	}

	int enemyState() {
		if (count < 1) {
			count++;
		}
		else {
			count = 0;
		}
		return count;
	}

	int ufoState() {
		if (count1 < 3) {
			count1++;
		}
		else {
			count1 = 0;
		}
		return count1;
	}

	void setEnemy() {
		enemysprite1.setTexture(enemytexture1);
		if (enemy1) {
			enemysprite1.setTextureRect(rect1[0]);
		}
		if (enemy2) {
			enemysprite1.setTextureRect(rect2[0]);
		}
		if (enemy3) {
			enemysprite1.setTextureRect(rect3[0]);
		}
	}

	void animateEnemy() {
		if (enemy1) {
			enemysprite1.setTextureRect(rect1[count]);
		}
		if (enemy2) {
			enemysprite1.setTextureRect(rect2[count]);
		}
		if (enemy3) {
			enemysprite1.setTextureRect(rect3[count]);
		}
		ufoSprite.setTextureRect(ufoRect[count1]);
	}

	void enemyMove(float x) {
		if (left) {
			enemysprite1.setPosition(enemysprite1.getPosition().x - x, enemysprite1.getPosition().y);
		}
		if (down) {
			enemysprite1.setPosition(enemysprite1.getPosition().x, enemysprite1.getPosition().y + 10);
		}
		if (right) {
			enemysprite1.setPosition(enemysprite1.getPosition().x + x, enemysprite1.getPosition().y);
		}
	}
	void ufoMove(float x) {
		if (left) {
			ufoSprite.setPosition(ufoSprite.getPosition().x - x, ufoSprite.getPosition().y);
		}
		if (down) {
			ufoSprite.setPosition(ufoSprite.getPosition().x, ufoSprite.getPosition().y + 10);
		}
		if (right) {
			ufoSprite.setPosition(ufoSprite.getPosition().x + x, ufoSprite.getPosition().y);
		}
	}
};
