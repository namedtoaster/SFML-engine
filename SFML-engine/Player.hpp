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

class Player {
public:
    // Default constructor
    Player();
    
    // Member methods
    
        // Movement
    bool isJumping();
    void moveRight();
    void moveLeft();
    void jump();
    void setVelY(float);
    void updatePosition();
    sf::Vector2f getPosition();
    
        // Drawing
    sf::Sprite getSprite();
    
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
    
        // Drawing
    sf::Sprite _sprite;
    sf::Texture _texture;
    
    // Member methods
    
        // Movement
    void _setPosition(float, float);
};

#endif /* Player_hpp */
