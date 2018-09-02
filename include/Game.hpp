//
//  Game.hpp
//  SFML-test
//
//  Created by Dave Campbell on 7/8/18.
//  Copyright © 2018 Dave Campbell. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

//#include "Constants.h"
#include "Player.hpp"
#include "Map.hpp"

#include <iostream>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum GameState { PLAY, QUIT };

class Game {
public:
    Game();
 
    void run();

private:
    void _init();
    void _processEvents();
	void _updateWindow();
    void _updateView();
	void _updatePlayers();
    void _draw();
private:
	float _deltaTime;
    bool _isJumping;
    sf::RenderWindow _window;
    sf::View _view;
	sf::Clock _clock;
    Player _player;
    GameState _state;
    Map _map;
	friend class Player;
};

#endif /* Game_hpp */
