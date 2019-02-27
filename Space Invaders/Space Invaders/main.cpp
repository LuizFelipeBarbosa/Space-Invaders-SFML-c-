#include <SFML/Graphics.hpp>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <ctime>
#include "playerProjectile.h"
#include "enemy.h"
#include "enemyProjectile.h"
#include "player.h"
#include "sheild.h"

int random(int x);
void setEnemies();

enemy enemy1[55];

int main() {

	sheild fuck(125,500);

	sheild fuck1(452, 500);

	sheild fuck2(774, 500);


	sf::RenderWindow window(sf::VideoMode(1024, 768), "Space Invaders");

	sf::Vector2f playermove(sf::Vector2f(0, 0));
	sf::Vector2f bulletmove(sf::Vector2f(0, 0));
	sf::Vector2f enemybulletmove(sf::Vector2f(0, 0));

	sf::Clock animateClock;
	sf::Clock bulletClock;
	sf::Clock explosionClock;
	sf::Clock playerdeadClock;
	sf::Clock playeranimateClock;
	sf::Clock ufoClock;

	sf::Event event;

	sf::Font font;
	font.loadFromFile("font/space_invaders.ttf");
	
	sf::Text livetext;
	livetext.setFont(font);
	livetext.setPosition(700, 10);
	livetext.setFillColor(sf::Color::White);
	livetext.setScale(0.85, 0.85);
	
	sf::Text score;
	score.setFont(font);
	score.setPosition(50, 10);
	score.setFillColor(sf::Color::White);
	score.setScale(0.85, 0.85);

	enemybullet fred;
	playerbullet a;

	enemy ufo;

	ufo.ufoSprite.setPosition(1035, 65);

	player player1;
	player playerdisplay[3];

	enum menus {
		MAINMENU,
		MENU,
		GAME,
		LEVEL
	};

	enemybulletmove.y = 0.25;

	menus menu = GAME;

	bool explosion = false;
	bool playerdead = false;

	int bulletWidth = 10;

	int rand1 = 0;
	int rand2 = 0;
	int rand = 0;
	int ufocount = 0;
	int enemyshoot[11];
	int playersize = 34;
	int enemiesalive = 0;
	int deadEnemy = 0;
	int pscore = 0;
	int rand3 = 0;

	int ufox = 0;
	int ufoy = 0;

	double movespeed = 0.3;
	double bulletspeed = -0.6;

	float animateTimer = 0.0f;
	float explosionTimer = 0.0f;
	float bulletTimer = 0.0f;
	float playerdeadTimer = 0.0f;
	float playeranimateTimer = 0.0f;
	float ufoTimer = 0.0f;

	playerdisplay[0].player1.setPosition(850,10);
	playerdisplay[1].player1.setPosition(900, 10);
	playerdisplay[2].player1.setPosition(950, 10);

	rand2 = random(30);

	a.normal();

	setEnemies();

	while (window.isOpen()) {
		switch (menu) {
		case MAINMENU:
			break;
		case MENU:
			break;
		case GAME:

			//Sheild




			livetext.setString("Lives: " + std::to_string(player1.lives));
			score.setString("Score: " + std::to_string(pscore));

			rand1 = random(11);

			rand3 = random(2);

			if (rand3 == 1) {
				fred.bullet3 = false;
				fred.bullet2 = true;
			}
			else {
				fred.bullet2 = false;
				fred.bullet3 = true;
			}

			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
						std::cout << enemiesalive;
					}
				}
			}

			//UFO

			if (ufo.ufoSprite.getPosition().x < -100) {
				
				if (ufocount == 0) {
					ufoClock.restart();
					ufocount = 1;
				}

				ufoTimer = ufoClock.getElapsedTime().asSeconds();

				if (ufoTimer > rand2) {
					rand2 = random(30);
					ufo.ufoSprite.setPosition(-70,65);
					ufo.right = true;
					ufo.left = false;
					ufocount = 0;
				}
				else {
					ufo.right = false;
					ufo.left = false;
				}
			}
			if (ufo.ufoSprite.getPosition().x > 1050) {
				
				if (ufocount == 0) {
					ufoClock.restart();
					ufocount = 1;
				}

				ufoTimer = ufoClock.getElapsedTime().asSeconds();

				if (ufoTimer > rand2) {
					rand2 = random(30);
					ufo.ufoSprite.setPosition(1035, 65);
					ufo.right = false;
					ufo.left = true;
					ufocount = 0;
				}
				else {
					ufo.right = false;
					ufo.left = false;
				}
			}

			ufo.ufoMove(0.1);

			//Enemy Move

			for (int i = 0; i < 55; i++) {
				if (enemy1[i].alive == true) {
					if (enemy1[i].enemysprite1.getPosition().x < 0) {
						for (int i = 0; i < 55; i++) {
							enemy1[i].right = true;
							enemy1[i].left = false;
							enemy1[i].down = true;
						}
					}

					if (enemy1[i].enemysprite1.getPosition().x > 991) {
						for (int i = 0; i < 55; i++) {
							enemy1[i].left = true;
							enemy1[i].right = false;
							enemy1[i].down = true;
						}
					}
				}
			}

			for (int i = 0; i < 55; i++) {
				if (enemiesalive > 25) {
					enemy1[i].enemyMove(0.03);
				}
				else if (enemiesalive > 10) {
					enemy1[i].enemyMove(0.05);
				}
				else if (enemiesalive > 5) {
					enemy1[i].enemyMove(0.07);
				}
				else if (enemiesalive > 1) {
					enemy1[i].enemyMove(0.08);
				}
				else if (enemiesalive > 0) {
					enemy1[i].enemyMove(1);
				}
				enemy1[i].down = false;
			}

			//Enemies alive
			
			enemiesalive = 0;

			for (int i = 0; i < 55; i++) {
				if (enemy1[i].alive == true) {
					enemiesalive += 1;
				}
			}

			//Player Die Animation

			playerdeadTimer = playerdeadClock.getElapsedTime().asSeconds();
			playeranimateTimer = playeranimateClock.getElapsedTime().asSeconds();

			if (playeranimateTimer < 0.5f) {
				if (player1.count == 2) {
					fred.bulletSprite.setPosition(-15, -20);
				}
			}

			if (playeranimateTimer > 0.5f) {
				if (player1.count == 2) {
					playerdead = false;
					player1.player1.setPosition(500, 700);
					player1.count = 0;
				}
				playeranimateClock.restart();
			}

			if (fred.bulletSprite.getGlobalBounds().intersects(player1.player1.getGlobalBounds())) {
				fred.bulletSprite.setPosition(1000, 2000);
				playerdead = true;
				player1.lives--;
			}

			if (playerdead) {
				if (playerdeadTimer > 0.18f) {
					player1.playerState();
					playerdeadClock.restart();
				}
			}

			player1.animatePlayer();

			//Enemy Shoot

			for (int i = 44; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[0] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}
			for (int i = 45; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[1] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}
			for (int i = 46; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[2] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}
			for (int i = 47; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[3] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}
			for (int i = 48; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[4] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}
			for (int i = 49; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[5] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}
			for (int i = 50; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[6] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}
			for (int i = 51; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[7] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}
			for (int i = 52; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[8] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}
			for (int i = 53; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[9] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}
			for (int i = 54; i > 0; i -= 11) {
				if (enemy1[i].alive) {
					enemy1[i].shoot = true;
					enemyshoot[10] = i;
					i = -10;
				}
				else {
					enemy1[i].shoot = false;
				}
			}

			if (!(fred.bulletSprite.getPosition().x > -20 && fred.bulletSprite.getPosition().y < 768)) {
				if (enemy1[enemyshoot[rand1]].alive) {
					fred.bulletSprite.setPosition(enemy1[enemyshoot[rand1]].enemysprite1.getPosition().x + 10, enemy1[enemyshoot[rand1]].enemysprite1.getPosition().y);
				}
			}

			//Player Move

			if (!(a.bullet.getPosition().x > 0 && a.bullet.getPosition().y > 0 && a.bullet.getPosition().x < 1024)) {
				if (player1.count == 0) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						a.bullet.setPosition(player1.player1.getPosition().x + playersize / 2 - bulletWidth / 2, player1.player1.getPosition().y - bulletWidth - 2);
						bulletmove.y = bulletspeed;
					}
				}
			}
			if (player1.count == 0) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { playermove.x = -movespeed; }
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { playermove.x = movespeed; }
				else { playermove.x = 0; }
			}
			else { playermove.x = 0; }

			if (player1.player1.getPosition().x < 0) { player1.player1.setPosition(0, player1.player1.getPosition().y); }
			if (player1.player1.getPosition().x + playersize > 1024) { player1.player1.setPosition(1024 - playersize, player1.player1.getPosition().y); }

			player1.player1.move(playermove.x, playermove.y);
			a.bullet.move(bulletmove.x, bulletmove.y);
			fred.bulletSprite.move(enemybulletmove.x, enemybulletmove.y);

			if (a.bullet.getPosition().y < -20) {
				bulletmove.y = 0;
			}

			//Enemy die

			for (int i = 0; i < 55; i++) {
				if (a.bullet.getGlobalBounds().intersects(enemy1[i].enemysprite1.getGlobalBounds())) {
					if (enemy1[i].alive == true) {
						if (enemy1[i].enemy1) {
							pscore += 10;
						}
						if (enemy1[i].enemy2) {
							pscore += 20;
						}
						if (enemy1[i].enemy3) {
							pscore += 30;
						}
						enemy1[i].alive = false;
						enemy1[i].shoot = false;
						enemy1[i].count = 0;
						explosionClock.restart();
						explosion = true;
						deadEnemy = i;
					}
				}
			}

			if (a.bullet.getGlobalBounds().intersects(ufo.ufoSprite.getGlobalBounds())) {
				explosionClock.restart();
				deadEnemy = -1;
				explosion = true;
				ufox = ufo.ufoSprite.getPosition().x + 8;
				ufoy = ufo.ufoSprite.getPosition().y;
				if (ufo.left) {
					ufo.ufoSprite.setPosition(-101, 65);
				}
				else {
					ufo.ufoSprite.setPosition(1051, 65);
				}

				rand3 = random(4);

				switch (rand3) {
				case 0:
					pscore += 150;
					break;
				case 1:
					pscore += 200;
					break;
				case 2:
					pscore += 250;
					break;
				case 3:
					pscore += 300;
					break;
				}
			}

			//Aninate enemy

			animateTimer = animateClock.getElapsedTime().asSeconds();
			bulletTimer = bulletClock.getElapsedTime().asSeconds();
			explosionTimer = explosionClock.getElapsedTime().asSeconds();

			if (ufo.alive) {
				if (animateTimer > 0.4f) {
					ufo.ufoState();
				}
			}

			ufo.animateEnemy();

			for (int i = 0; i < 55; i++) {
				if (enemy1[i].alive) {
					if (animateTimer > 0.4f) {
						enemy1[i].enemyState();
						animateClock.restart();
					}
				}
				enemy1[i].animateEnemy();
			}

			if (bulletTimer > 0.18f) {
				fred.bulletState();
				bulletClock.restart();

			}
			fred.animateBullet();

			//Window Draw

			window.clear();

			for (int i = 0; i < 55; i++) {
				if (enemy1[i].alive == true) {
					window.draw(enemy1[i].enemysprite1);
				}
			}
			
			if (explosion) {
				if (explosionTimer < 0.6f) {
					a.bulletExplosion();
					if (deadEnemy == -1) {
						std::cout << 1;
						a.bullet.setPosition(ufox, ufoy);
					}
					else {
						a.bullet.setPosition(enemy1[deadEnemy].enemysprite1.getPosition().x, enemy1[deadEnemy].enemysprite1.getPosition().y);
					}
				}
				else {
					a.normal();
					explosion = false;
					a.bullet.setPosition(a.bullet.getPosition().x, -23);
					explosionClock.restart();
				}
			}
			else {
				if (enemiesalive == 0) {
					setEnemies();
				}
			}

			window.draw(a.bullet);

			if (player1.lives == 3) {
				window.draw(playerdisplay[0].player1);
				window.draw(playerdisplay[1].player1);
				window.draw(playerdisplay[2].player1);
			}
			if (player1.lives == 2) {
				window.draw(playerdisplay[0].player1);
				window.draw(playerdisplay[1].player1);
			}
			if (player1.lives == 1) {
				window.draw(playerdisplay[0].player1);
			}
			else {

			}

			window.draw(ufo.ufoSprite);
			window.draw(score);
			window.draw(livetext);
			window.draw(fred.bulletSprite);
			window.draw(player1.player1);
			window.draw(fuck.quad);
			window.draw(fuck1.quad); 
			window.draw(fuck2.quad);
			window.display();
			break;
		case LEVEL:
			break;
		}
	}
}

void setEnemies() {
	for (int i = 0; i < 55; i++) {
		enemy1[i].alive = true;
		if (i <= 10) {
			enemy1[i].enemysprite1.setPosition(60 * (i + 2), 125);
			enemy1[i].enemy3 = true;
		}
		else if (i >= 11 && i <= 21) {
			enemy1[i].enemysprite1.setPosition(60 * (i - 9), 175);
			enemy1[i].enemy2 = true;
		}
		else if (i >= 22 && i <= 32) {
			enemy1[i].enemysprite1.setPosition(60 * (i - 20), 225);
			enemy1[i].enemy2 = true;
		}
		else if (i >= 33 && i <= 43) {
			enemy1[i].enemysprite1.setPosition(60 * (i - 31), 275);
			enemy1[i].enemy1 = true;
		}
		else if (i >= 44 && i <= 55) {
			enemy1[i].enemysprite1.setPosition(60 * (i - 42), 325);
			enemy1[i].enemy1 = true;
		}
		enemy1[i].setEnemy();
	}
}

int random(int x) {
	srand(time(NULL));
	return rand() % x;
}

