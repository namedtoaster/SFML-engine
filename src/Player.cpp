//
//  Player.cpp
//  SFML-test
//
//  Created by Dave Campbell on 7/27/18.
//  Copyright © 2018 Dave Campbell. All rights reserved.
//

#include "Player.hpp"
#include <iostream>

Player::Player() : _posX(PLAYER_START_X), _posY(PLAYER_START_Y), _isJumping(false), _velX(0.0f), _velY(0.0f), _accelX(0.0f), _accelY(0.0f) {
    if (!_texture.loadFromFile("pixar.jpg")) {
        return EXIT_FAILURE;
    }
    
    // Initialize sprite/texture
    _sprite.setTexture(_texture);
    _sprite.scale(0.5f, 0.5f);
    
    // Initialize members vars
    _texWidth = _texture.getSize().x;
    _texHeight = _texture.getSize().y;
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

void Player::_setPosition(float x, float y) {
    _sprite.setPosition(x, y);
}

void Player::jump() {
    _velY = JUMP_AMT;
    _isJumping = true;
}

void Player::updatePosition() {
    if(_posY < PLAYER_START_Y)                  //If you are above ground
        _velY += GRAVITY;    //Add gravity
    else if(_posY > PLAYER_START_Y) {             //If you are below ground
        _isJumping = false;
        _posY = PLAYER_START_Y;                 //That's not supposed to happen, put him back up
    }
    
    _velX += _accelX;
    _velY += _accelY;
    
    _posX += _velX;
    _posY += _velY;
    
    // Update the player's position
    _setPosition(_posX, _posY);
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
