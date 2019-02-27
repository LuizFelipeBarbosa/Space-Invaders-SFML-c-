#pragma once
#include <SFML/Graphics.hpp>

class sheild {

public:

	int count = 0;

	sf::VertexArray quad;

	sheild(int posx, int posy) {

		quad.setPrimitiveType(sf::Quads);

		quad.resize(64);

		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				quad[count].position = sf::Vector2f(posx + x, posy + y);
				count++;
			}
		}
	}
};