#include "Animation.h"

Animation::Animation(sf::Vector2u imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.f;
	currentImage.x = 0;
}

void Animation::setTexture(sf::Texture &texture) {
	uvRect.width = texture.getSize().x / float(imageCount.x);
	uvRect.height = texture.getSize().y / float(imageCount.y);
}

void Animation::update(int row, float deltaTime, bool faceRight) {
	this->faceRight = faceRight;
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight) {
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else {
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}