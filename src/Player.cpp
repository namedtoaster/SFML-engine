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

Player::Player() : _posX(PLAYER_START_X), _posY(PLAYER_START_Y), _falling(true), _velX(0.0f), _velY(0.0f), _accelX(0.0f), _accelY(0.0f) {
    if (!_texture.loadFromFile("assets/steve.png")) {
      return;
    }
    
    // Initialize sprite/texture
    _sprite.setTexture(_texture);
    _sprite.scale(0.3f, 0.3f);
    
    // Initialize members vars
    _texWidth = _texture.getSize().x;
    _texHeight = _texture.getSize().y;

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

	// TODO: set member var for player w/h
	float playerW = _sprite.getGlobalBounds().width;
	float playerH = _sprite.getGlobalBounds().height;

	// Check four corners
	_checkTilePosition(map, collideTilePosition, _posX, _posY);
	_checkTilePosition(map, collideTilePosition, _posX + playerW, _posY);
	_checkTilePosition(map, collideTilePosition, _posX, _posY + playerW);
	_checkTilePosition(map, collideTilePosition, _posX + playerW, _posY + playerW);
		

	for (int i = 0; i < collideTilePosition.size(); i++) {
		_collideWithTile(collideTilePosition[i]);
	}

	_updatePosition();
}

void Player::_checkTilePosition(const Map& map,
	std::vector<sf::Vector2f>& collideTilePosition, 
	float x, float y) {

	sf::Vector2i cornerPos = sf::Vector2i(std::floor(x / TILE_W_H), std::floor(y / TILE_W_H));

	if (map._tiles[cornerPos.y][cornerPos.x].tileType != 0) {
		collideTilePosition.push_back(sf::Vector2f((float)TILE_W_H * cornerPos.x + (TILE_W_H / 2), (float)TILE_W_H * cornerPos.y + (TILE_W_H / 2)));
	}
	else _falling = true;
}

void Player::_collideWithTile(sf::Vector2f pos) {
	const float playerRadius = (float)_sprite.getGlobalBounds().width / 2.f;
	const float tileRadius = (float)TILE_W_H / 2.f;
	const float minDistance = playerRadius + tileRadius;

	sf::Vector2f centerPlayerPos = sf::Vector2f(_posX, _posY) 
		+ sf::Vector2f(playerRadius, playerRadius);
	sf::Vector2f distVec = centerPlayerPos - pos;

	float xdepth = minDistance - abs(distVec.x);
	float ydepth = minDistance - abs(distVec.y);

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
