#pragma once

#include <SFML/Graphics.hpp>

class Animation {
public:
	Animation(sf::Vector2u imageCount, float switchTime);

	void setTexture(sf::Texture&);
	void update(int, float, bool);
public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;
	bool faceRight;
};
