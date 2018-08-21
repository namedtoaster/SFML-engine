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

Player::Player() : _posX(PLAYER_START_X), _posY(PLAYER_START_Y), _isJumping(false), _velX(0.0f), _velY(0.0f), _accelX(0.0f), _accelY(0.0f) {
    if (!_texture.loadFromFile("pixar.jpg")) {
      return;
    }
    
    // Initialize sprite/texture
    _sprite.setTexture(_texture);
    _sprite.scale(0.5f, 0.5f);
    
    // Initialize members vars
    _texWidth = _texture.getSize().x;
    _texHeight = _texture.getSize().y;

	_isJumping = false;
	_isColliding = false;

	colliding.up = false;
	colliding.down = false;
	colliding.left = false;
	colliding.right = false;

	// Load the text
	_posFont.loadFromFile("chintzy.ttf");
	_posText.setString(std::to_string((int)_sprite.getPosition().x) + ", " + std::to_string((int)_sprite.getPosition().y));
	_posText.setPosition(_posX, _posY - 20);
	_posText.setFont(_posFont);
	_posText.setCharacterSize(20);
	_posText.setStyle(sf::Text::Bold);
	_posText.setFillColor(sf::Color::Red);
}

void Player::moveRight() {
    _posX += MOVE_D;
    _setPosition(_posX, _posY);
}

void Player::moveLeft() {
    _posX -= MOVE_D;
    _setPosition(_posX, _posY);
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
    _isJumping = true;
}

void Player::checkCollisions(Map &map) {
	_isColliding = false;
	colliding.up = false;
	colliding.down = false;
	colliding.left = false;
	colliding.right = false;

	sf::FloatRect object = _sprite.getGlobalBounds();
	int leftTile = object.left / TILE_W_H;
	int rightTile = (object.left + object.width) / TILE_W_H;
	int topTile = object.top / TILE_W_H;
	int botTile = (object.top + object.height) / TILE_W_H;

	for (int i = topTile; i <= botTile; i++)
	{
		for (int j = leftTile; j <= rightTile; j++)
		{
			Tile t = map._tiles[i][j];
			if (t.tileType != 0)
			{
				_isColliding = true;

				if (i == topTile) colliding.up = true;
				if (i == botTile) colliding.down = true;
				if (j == leftTile) colliding.left = true;
				if (j == rightTile) colliding.right = true;

				if (_isColliding) break;
			}
		}
		if (_isColliding) break;
	}
	_posText.setString("left: " + std::to_string(colliding.left)
		+ " right: " + std::to_string(colliding.right)
		+ " top: " + std::to_string(colliding.up)
		+ " bot: " + std::to_string(colliding.down));

	_updatePosition();
}

void Player::_updatePosition() {
    
    //_velX += _accelX; // already done in move function
    //_velY += _accelY;
    
    //_posX += _velX;

	_oldPos.y = _posY;

	_velY += GRAVITY;

    _posY += _velY;

	if (colliding.down) {
		_posY = _oldPos.y;
	}
    
    // Update the player's position
    _setPosition(_posX, _posY);

	// ...and the text (testing)
	_posText.setPosition(_posX, _posY - 20);
}

sf::Vector2f Player::getPosition() {
    return sf::Vector2f(_posX, _posY);
}

void Player::setVelY(float newY) {
    _velY = newY;
}

bool Player::isJumping() {
    return _isJumping;
}

sf::Vector2u Player::getSize() {
    return _texture.getSize();
}
