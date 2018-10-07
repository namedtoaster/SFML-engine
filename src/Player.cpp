//
//  Player.cpp
//  SFML-test
//
//  Created by Dave Campbell on 7/27/18.
//  Copyright © 2018 Dave Campbell. All rights reserved.
//

#include "Player.hpp"
#include "Map.hpp"
#include "Tile.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Player::Player() :
	_posX(PLAYER_START_X),
	_posY(PLAYER_START_Y),
	_falling(true),
	_velX(0.0f),
	_velY(0.0f),
	_accelX(0.0f),
	_accelY(0.0f),
	_canJump(true),
	_facingRight(true),
	_resizeFactor(1.f),
	_slashing(false),
	animatedSprite(sf::seconds(0.18), true, false)
{
    // Initialize members vars
    _texWidth = _texture.getSize().x;
    _texHeight = _texture.getSize().y;

	// Scale as desired
	//_setSpriteScale(_resizeFactor);


	// Load the sprite sheet
	if (!_texture.loadFromFile("assets/adventurer-Sheet.png")) {
		return;
	}

	// Set idle animation
	_idleAnimation.setSpriteSheet(_texture);
	_idleAnimation.addFrame(sf::IntRect(14, 7, 19, 29));
	_idleAnimation.addFrame(sf::IntRect(66, 6, 17, 30));
	_idleAnimation.addFrame(sf::IntRect(115, 6, 19, 30));
	_idleAnimation.addFrame(sf::IntRect(163, 7, 20, 29));

	// Set running animation
	_runningAnimation.setSpriteSheet(_texture);
	_runningAnimation.addFrame(sf::IntRect(67, 45, 20, 28));
	_runningAnimation.addFrame(sf::IntRect(116, 46, 20, 27));
	_runningAnimation.addFrame(sf::IntRect(166, 48, 20, 25));

	// Set slashing animation
	_slashingAnimation.setSpriteSheet(_texture);
	_slashingAnimation.addFrame(sf::IntRect(115, 222, 34, 36));
	_slashingAnimation.addFrame(sf::IntRect(165, 222, 27, 36));
	_slashingAnimation.addFrame(sf::IntRect(215, 226, 19, 32));

	_currentAnimation = &_idleAnimation;
	animatedSprite.setLooped(false);
}

void Player::update(sf::RenderWindow &window, const Map& map, sf::Time frameTime) {
	// Movement and collisions
	_applyGravity();
	_checkCollisions(map); // TODO: make work when player is bigger than tiles -- super buggy when it is right now
	_processEvents(window);
	_updatePosition();

	// Animation stuff
	animatedSprite.play(*_currentAnimation);
	animatedSprite.setPosition(sf::Vector2f(_posX, _posY));
	animatedSprite.update(frameTime);
	animatedSprite.pause();
}

void Player::_processEvents(sf::RenderWindow &window) {
	if (!_slashing) {
		_currentAnimation = &_idleAnimation;

		// Move right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// Update the player position
			_moveRight();
			_facingRight = true;
			_currentAnimation = &_runningAnimation;
		}
		// Move left
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			// Update the player position
			_moveLeft();
			_facingRight = false;
			_currentAnimation = &_runningAnimation;
		}
		// Slash
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			_currentAnimation = &_slashingAnimation;
			_slashing = true;
		}
	}
	else {
		if (animatedSprite.m_currentFrame == 2)
			_slashing = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!_falling)
			_jump();
	}
}

// TODO: get delta from main update function 
// - multiply it by a speed variable to get new pos 
// (see animation SFML tutorial on youtube)
void Player::_moveRight() {
	_posX += MOVE_D;
}

void Player::_moveLeft() {
	_posX -= MOVE_D;
}

void Player::_moveUp() {
	_posY -= MOVE_D;
}

void Player::_moveDown() {
	_posY += MOVE_D;
}

void Player::_jump() {
	_velY = JUMP_AMT;
	_falling = true;
}

void Player::_applyGravity() {
	if (_falling) {
		_velY += GRAVITY;
		_posY += _velY;
	}
	else {
		_velY = 0;
		_falling = false;
	}
}

void Player::_checkCollisions(const Map &map) {
	std::vector<sf::Vector2f> collideTilePosition;

	// Check four corners
	_checkTilePosition(map, collideTilePosition, _posX, _posY); // top left
	_checkTilePosition(map, collideTilePosition, _posX + _width, _posY);
	_checkTilePosition(map, collideTilePosition, _posX, _posY + _height);
	_checkTilePosition(map, collideTilePosition, _posX + _width, _posY + _height);

	sf::Vector2i indices;
	// Check top edge to top right
	for (int i = _posX + TILE_W_H; i < (_width + _posX); i += TILE_W_H) {
		_checkTilePosition(map, collideTilePosition, i, _posY);
	}
	// Check left edge to bottom left
	for (int i = _posY + TILE_W_H; i < (_height + _posY); i += TILE_W_H) {
		_checkTilePosition(map, collideTilePosition, _posX, i);
	}
	// Check bottom edge to bottom right
	int bottomY = _posY + _height;
	for (int i = _posX + TILE_W_H; i < (_width + _posX); i += TILE_W_H) {
		_checkTilePosition(map, collideTilePosition, i, bottomY);
	}
	// Check right edge to bottom right
	int rightX = _posX + _width;
	for (int i = _posY + TILE_W_H; i < (_height + _posY); i += TILE_W_H) {
		_checkTilePosition(map, collideTilePosition, rightX, i);
	}


	const float tileRadius = (float)TILE_W_H / 2.f;
	sf::Vector2f centerPlayerPos = sf::Vector2f(_posX, _posY) + sf::Vector2f(_width / 2.f, _height / 2.f);

	// Sort coords by closest to player center pos
	// TODO: This would be so much easier if I was using glm and had built in sorting functions...
	for (int i = 0; i < collideTilePosition.size(); i++) {
		for (int j = i + 1; j < collideTilePosition.size(); j++) {
			sf::Vector2f diffVec1 = centerPlayerPos - collideTilePosition[i];
			float diff1 = std::sqrt(std::pow(diffVec1.x, 2.f) + std::pow(diffVec1.y, 2.f));

			sf::Vector2f diffVec2 = centerPlayerPos - collideTilePosition[j];
			float diff2 = std::sqrt(std::pow(diffVec2.x, 2.f) + std::pow(diffVec2.y, 2.f));

			if (diff2 < diff1) {
				sf::Vector2f tmp = collideTilePosition[i];
				collideTilePosition[i] = collideTilePosition[j];
				collideTilePosition[j] = tmp;
			}
		}

	}

	for (int i = 0; i < collideTilePosition.size(); i++) {
		_collideWithTile(collideTilePosition[i]);
	}
}

void Player::_checkTilePosition(const Map& map, std::vector<sf::Vector2f>& collideTilePosition, float x, float y) {

	sf::Vector2i cornerPos = sf::Vector2i(std::floor(x / TILE_W_H), std::floor(y / TILE_W_H));

	if (cornerPos.y < map._tiles.size() && cornerPos.x < map._tiles[cornerPos.y].size()) {
		if (map._tiles[cornerPos.y][cornerPos.x].tileType != 0) {
			collideTilePosition.push_back(sf::Vector2f((float)TILE_W_H * cornerPos.x + (TILE_W_H / 2), (float)TILE_W_H * cornerPos.y + (TILE_W_H / 2)));
		}
		else _falling = true;
	}
}

void Player::_collideWithTile(sf::Vector2f pos) {
	const float tileRadius = (float)TILE_W_H / 2.f;
	const float minDistanceX = _width / 2 + tileRadius;
	const float minDistanceY = _height / 2 + tileRadius;

	sf::Vector2f centerPlayerPos = sf::Vector2f(_posX, _posY) + sf::Vector2f(_width / 2.f, _height / 2.f);
	sf::Vector2f distVec = centerPlayerPos - pos;

	float xdepth = minDistanceX - abs(distVec.x);
	float ydepth = minDistanceY - abs(distVec.y);

	if (xdepth > 0 || ydepth > 0) {
		if (std::max(xdepth, 0.f) < std::max(ydepth, 0.f)) {
			if (distVec.x < 0) {
				_posX -= xdepth;
			}
			else {
				_posX += xdepth;
			}
		}
		else {
			_falling = false;
			if (distVec.y < 0) {
				_posY -= ydepth;
			}
			else {
				_posY += ydepth;
			}
		}
	}
}

sf::Vector2f Player::getPosition() {
	return sf::Vector2f(_posX, _posY);
}

void Player::_updatePosition() {
	// TODO: make this more accurate (get width/height from current frame)
	_width = _currentAnimation->getFrame(0).width;//_idleAnimation.getFrame(0).width;
	_height = _currentAnimation->getFrame(0).height; //_idleAnimation.getFrame(0).height;

    // Update the player's position
    _setPosition(_posX, _posY);
}

void Player::_setSpriteScale(float scale)
{
	_resizeFactor = scale;

	_sprite.setScale(sf::Vector2f(scale, scale));
	_width *= scale;
	_height *= scale;
}

void Player::_setPosition(float x, float y) {
	_sprite.setPosition(x, y);
}

void Player::draw(sf::RenderWindow &window, bool drawBorder)
{
	// Test new animation stuff
	window.draw(animatedSprite);

	if (drawBorder) {
		sf::FloatRect border = _sprite.getGlobalBounds();
		sf::Vertex vertices[5] = {sf::Vector2f(border.left, border.top), sf::Vector2f(border.left + border.width, border.top),
			sf::Vector2f(border.left + border.width, border.top + border.height), sf::Vector2f(border.left, border.top + border.height),
			sf::Vector2f(border.left, border.top)};

		window.draw(vertices, 5, sf::LinesStrip);
	}
}

float Player::getHeight()
{
	return _height;
}
