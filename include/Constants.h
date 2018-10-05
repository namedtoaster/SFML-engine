//
//  Constants.h
//  SFML-test
//
//  Created by Dave Campbell on 7/8/18.
//  Copyright © 2018 Dave Campbell. All rights reserved.
//

#ifndef Constants_h
#define Constants_h

#include <SFML/Graphics.hpp>

// TODO: Load start screen image and we height to image height
const int WIDTH = 1000;
const int HEIGHT = 600;

const int VIEW_WIDTH = WIDTH;
const int VIEW_HEIGHT = HEIGHT;

// Positioning constants
const float MOVE_D = 3.0f;
const float GRAVITY = 1.f;
const float JUMP_AMT = -17.0f;

// Get a linking error with this for some reason
//const char* PLAYER_TEXTURE = "pixar.jpg";
const float PLAYER_START_X = 80.0f;
const float PLAYER_START_Y = 60.f;

// Tiling constants
const int TILE_W_H = 50;
const int TILES_PER_ROW = 10;

// Text/font constants
const float TOP_MARG = 15, BOT_MARG = 15, LEFT_MARG = 15, RIGHT_MARG = 15;
const float MENU_TXT_MARG = 30;

// TODO: Make this work. For some reason it gives me a linker error when I try to do this
/*sf::Keyboard::Key RIGHT = sf::Keyboard::D;
sf::Keyboard::Key LEFT = sf::Keyboard::A;*/

#endif /* Constants_h */
