//
//  Player.hpp
//  SFML-test
//
//  Created by Dave Campbell on 7/27/18.
//  Copyright © 2018 Dave Campbell. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Constants.h"
#include "Map.hpp"
#include "Animation.h"

class Player {
public:
    Player();
    
	void update(sf::RenderWindow&, const Map&, sf::Event&, float);
	void draw(sf::RenderWindow&);
    sf::Vector2f getPosition();

private:
	void _move(sf::RenderWindow&, sf::Event&, float);
	void _moveRight();
	void _moveLeft();
	void _moveDown();
	void _moveUp();
	void _jump();
	void _applyGravity();
	void _checkCollisions(const Map&);
	void _checkTilePosition(const Map&, std::vector<sf::Vector2f>&, float, float);
	void _collideWithTile(sf::Vector2f);
	void _setPosition(float, float);
	void _updatePosition();
private:
    float _posX;
    float _posY;
	float _width;
	float _height;
    float _velX;
    float _velY;
    float _accelX;
    float _accelY;
    int _texWidth;
    int _texHeight;
    bool _falling;
	bool _canJump;
    sf::Sprite _sprite;
	sf::Texture _texture;
	Animation _animation;
	friend class Animation;
};

#endif /* Player_hpp */
