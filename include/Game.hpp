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

enum GameState { PLAY, QUIT, PAUSE };

class Game {
public:
    Game();
 
    void run();

private:
    void _init();
	void _updateWindow();
    void _updateView();
	void _updatePlayers();
    void _draw();
	void _zoom(float);
    void _pauseGame();
	void _pauseMenuSelect();
private:
	float _deltaTime;
	float _zoomLevel;
    bool _isJumping;
    sf::RenderWindow _window;
    sf::View _view;
	sf::Clock _clock;
	sf::Sprite _bg;
	sf::Sprite _pauseSword;
	sf::Sprite _vignette;
	sf::Text _score;
    sf::Font _font;
    Player _player;
    GameState _state;
    Map _map;
	friend class Player;
};

#endif /* Game_hpp */
