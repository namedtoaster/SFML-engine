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
#include "Animation.h"
#include "AnimatedSprite.h"

class Player {
public:
    Player();
    
	void update(sf::RenderWindow&, const Map&, sf::Time);
	void draw(sf::RenderWindow&, bool);
	float getHeight();
    sf::Vector2f getPosition();

private:
	void _processEvents(sf::RenderWindow&);
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
	void _setSpriteScale(float);
	void _idle();
private:
    float _posX;
    float _posY;
	float _width;
	float _height;
    float _velX;
    float _velY;
    float _accelX;
    float _accelY;
	float _resizeFactor;
    int _texWidth;
    int _texHeight;
    bool _falling;
	bool _canJump;
	bool _facingRight;
	bool _slashing;
    sf::Sprite _sprite;
	sf::Texture _texture;
	const Animation* _currentAnimation;
	Animation _idleAnimation;
	Animation _runningAnimation;
	Animation _slashingAnimation;
	AnimatedSprite animatedSprite;
	friend class Animation;
};

#endif /* Player_hpp */
