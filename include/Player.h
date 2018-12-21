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
#include "Map.h"
#include "Animation.h"
#include "Animation.h"
#include "AnimatedSprite.h"

// TODO: Put variable and function definitions in a logical order
class Player {
public:
  Player();
    
	void update(const Map&, const sf::Time);
	void draw(sf::RenderWindow&, const bool);
	const float getHeight();
  const sf::Vector2f getPosition();
  void canJump();

private:
	void _processEvents();
	void _moveRight();
	void _moveLeft();
	void _moveDown();
	void _moveUp();
	void _jump();
	void _applyGravity();
	void _checkCollisions(const Map&);
	void _checkTilePosition(const Map&, std::vector<sf::Vector2f>&, float, float);
	void _collideWithTile(const sf::Vector2f);
	void _setPosition(const float, const float);
	void _updatePosition(const Map&);
	void _setSpriteScale(const float);
	void _initializeMedia();
	void _initializeAnimations();
private:
	sf::Sprite _sprite;
	sf::Texture _texture;

	const Animation* _currentAnimation;
	Animation _idleAnimation;
	Animation _runningAnimation;
	Animation _slashingAnimation;
	AnimatedSprite animatedSprite;
	friend class Animation;

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
  bool _colliding;
};

#endif /* Player_hpp */
