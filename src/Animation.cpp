#include <iostream>
#include <cmath>
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

    // Slashing frames
    frames.clear();
    /*frames.push_back(sf::IntRect(160, 193, 23, 28));
    frames.push_back(sf::IntRect(210, 194, 24, 27));
    frames.push_back(sf::IntRect(259, 193, 25, 28));
    frames.push_back(sf::IntRect(309, 193, 25, 28));
    frames.push_back(sf::IntRect(7, 236, 27, 22));
    frames.push_back(sf::IntRect(58, 238, 25, 20));*/
    frames.push_back(sf::IntRect(115, 222, 34, 36));
    frames.push_back(sf::IntRect(165, 222, 27, 36));
    frames.push_back(sf::IntRect(215, 226, 19, 32));
    this->addAnimation(frames);
}

void Animation::setTexture(sf::Texture &texture) {
    uvRect.width = texture.getSize().x / float(imageCount.x);
    uvRect.height = texture.getSize().y / float(imageCount.y);
}

void Animation::update(int index, float deltaTime, bool faceRight, float &y) {
    this->faceRight = faceRight;
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
        _updateFloor(y);

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
        uvRect.left = uvRect.left + uvRect.width;
        uvRect.width = -abs(uvRect.width);
    }
}

void Animation::addAnimation(std::vector<sf::IntRect> animation)
{
    frames.push_back(std::vector<sf::IntRect>());

    frames[frames.size() - 1] = animation;
}

sf::Vector2u& Animation::getCurrentImage()
{
    return currentImage;
}

std::vector<std::vector<sf::IntRect>>& Animation::getFrames()
{
    return frames;
}

void Animation::_updateFloor(float &y)
{
    int animRow = currentImage.y;
    int animCol = currentImage.x;
    int endIndex = frames[animRow].size() - 1;
    int prevHeight = (animCol == 0 ? frames[animRow][endIndex].height : frames[animRow][animCol - 1].height);
    int currHeight = frames[animRow][animCol].height;

    float diff = prevHeight - currHeight;

    if (diff < 0) y -= abs(diff);
    else if (diff > 0) y += abs(diff);
}
