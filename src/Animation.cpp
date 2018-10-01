#include <iostream>
#include "Animation.h"

Animation::Animation(sf::Vector2u imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.f;
	currentImage.x = 0;

	// Standing frames
	std::vector<sf::IntRect> frames;
	frames.push_back(sf::IntRect(14, 7, 19, 29));
	frames.push_back(sf::IntRect(66, 6, 17, 30));
	frames.push_back(sf::IntRect(115, 6, 19, 30));
	frames.push_back(sf::IntRect(163, 7, 20, 29));
	this->addAnimation(frames);

	// Move right frames
	frames.clear();
	frames.push_back(sf::IntRect(67,45,20,28));
	frames.push_back(sf::IntRect(116,46,20,27));
	frames.push_back(sf::IntRect(166,48,20,25));
	this->addAnimation(frames);
}

void Animation::setTexture(sf::Texture &texture) {
	uvRect.width = texture.getSize().x / float(imageCount.x);
	uvRect.height = texture.getSize().y / float(imageCount.y);
}

void Animation::update(int index, float deltaTime, bool faceRight) {
	this->faceRight = faceRight;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= frames[index].size() - 1) {
			currentImage.x = 0;
		}
	}

	uvRect = frames[index][currentImage.x];

	if (faceRight) {
		//uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else {
		uvRect.left = frames[index][currentImage.x].left + uvRect.width;
		uvRect.width = -abs(uvRect.width);
	}
}

void Animation::addAnimation(std::vector<sf::IntRect> animation)
{
	frames.push_back(std::vector<sf::IntRect>());

	frames[frames.size() - 1] = animation;
}
