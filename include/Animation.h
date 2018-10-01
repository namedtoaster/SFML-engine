#pragma once

#include <SFML/Graphics.hpp>

class Animation {
public:
	Animation(sf::Vector2u imageCount, float switchTime);

	void setTexture(sf::Texture&);
	void update(int, float, bool);
	void addAnimation(std::vector<sf::IntRect>);
public:
	sf::IntRect uvRect;
	std::vector<std::vector<sf::IntRect>> frames;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;
	bool faceRight;
};
