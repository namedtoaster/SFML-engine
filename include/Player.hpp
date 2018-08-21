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

class Player {
public:
    // Default constructor
    Player();
    
    // Member methods
    
        // Movement
    bool isJumping();
    void moveRight();
    void moveLeft();
	void moveDown();
	void moveUp();
    void jump();
    sf::Vector2f getPosition();
	void checkCollisions(const Map&);
    
        // Drawing
    sf::Sprite getSprite();
	sf::Text getPosText();
    
        // Tex/Sprite data
    sf::Vector2u getSize();
private:
    // Member variables
    
        // Movement
    float _posX;
    float _posY;
    float _velX;
    float _velY;
    float _accelX;
    float _accelY;
    int _texWidth;
    int _texHeight;
    bool _isJumping;
	bool _isColliding;

	struct {
		bool up;
		bool down;
		bool left;
		bool right;
	} colliding;
    
        // Drawing
    sf::Sprite _sprite;
    sf::Texture _texture;
	sf::Text _posText;
	sf::Font _posFont;
    
    // Member methods
    
        // Movement
    void _setPosition(float, float);
	void _updatePosition();
	void _checkTilePosition(const Map&, std::vector<sf::Vector2f>&, float, float);
	void _collideWithTile(sf::Vector2f);
	sf::Vector2f _oldPos;
};

#endif /* Player_hpp */
