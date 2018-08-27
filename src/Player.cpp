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

Player::Player() : _posX(PLAYER_START_X), _posY(PLAYER_START_Y), _falling(true), _velX(0.0f), _velY(0.0f), _accelX(0.0f), _accelY(0.0f) {
    if (!_texture.loadFromFile("assets/steve.png")) {
      return;
    }
    
    // Initialize sprite/texture
    _sprite.setTexture(_texture);
    _sprite.scale(0.15f, 0.15f);
    
    // Initialize members vars
    _texWidth = _texture.getSize().x;
    _texHeight = _texture.getSize().y;
	_width = _sprite.getGlobalBounds().width;
	_height = _sprite.getGlobalBounds().height;

	// Load the text
	_posFont.loadFromFile("assets/chintzy.ttf");
	_posText.setString(std::to_string((int)_sprite.getPosition().x) + ", " + std::to_string((int)_sprite.getPosition().y));
	_posText.setPosition(_posX, _posY - 20);
	_posText.setFont(_posFont);
	_posText.setCharacterSize(20);
	_posText.setStyle(sf::Text::Bold);
	_posText.setFillColor(sf::Color::Red);
}

void Player::moveRight() {
	_posX += MOVE_D;
}

void Player::moveLeft() {
    _posX -= MOVE_D;
}

void Player::moveUp() {
	_posY -= MOVE_D;
}

void Player::moveDown() {
	_posY += MOVE_D;
}

sf::Sprite Player::getSprite() {
    return _sprite;
}

sf::Text Player::getPosText() {
	return _posText;
}

void Player::testDraw(sf::RenderWindow &_window)
{
	sf::Vector2f centerPlayerPos = sf::Vector2f(_posX - 5.f, _posY - 5.f) + sf::Vector2f(_width / 2.f, _height / 2.f);

	sf::CircleShape shape(5);

	// set the shape color to green
	shape.setFillColor(sf::Color(100, 250, 50));
	shape.setPosition(centerPlayerPos);

	_window.draw(shape);
}

void Player::_setPosition(float x, float y) {
    _sprite.setPosition(x, y);
}

void Player::jump() {
    _velY = JUMP_AMT;
	_falling = true;
}

void Player::update(const Map& map) {
	_applyGravity();
	_checkCollisions(map);
	_updatePosition();
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
	_checkTilePosition(map, collideTilePosition, _posX + _width, _posY); // top right
	_checkTilePosition(map, collideTilePosition, _posX, _posY + _height); // bottom left
	_checkTilePosition(map, collideTilePosition, _posX + _width, _posY + _height); // bottom right

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

	_updatePosition();
}

void Player::_checkTilePosition(const Map& map, std::vector<sf::Vector2f>& collideTilePosition, float x, float y) {

	sf::Vector2i cornerPos = sf::Vector2i(std::floor(x / TILE_W_H), std::floor(y / TILE_W_H));

	if (map._tiles[cornerPos.y][cornerPos.x].tileType != 0) {
		collideTilePosition.push_back(sf::Vector2f((float)TILE_W_H * cornerPos.x + (TILE_W_H / 2), (float)TILE_W_H * cornerPos.y + (TILE_W_H / 2)));
	}
	else _falling = true;
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

void Player::_updatePosition() {
    // Update the player's position
    _setPosition(_posX, _posY);
}

sf::Vector2f Player::getPosition() {
    return sf::Vector2f(_posX, _posY);
}

bool Player::isFalling() {
    return _falling;
}

sf::Vector2u Player::getSize() {
    return _texture.getSize();
}
