#include "Banimation.h"

Banimation::Banimation() : m_texture(NULL)
{

}

void Banimation::addFrame(sf::IntRect rect)
{
	m_frames.push_back(rect);
}

void Banimation::setSpriteSheet(const sf::Texture& texture)
{
	m_texture = &texture;
}

const sf::Texture* Banimation::getSpriteSheet() const
{
	return m_texture;
}

std::size_t Banimation::getSize() const
{
	return m_frames.size();
}

const sf::IntRect& Banimation::getFrame(std::size_t n) const
{
	return m_frames[n];
}