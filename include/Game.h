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
#include "Player.h"
#include "Map.h"

#include <iostream>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum GameState { PLAY, QUIT, PAUSE };

class Game {
public:
    Game();

private:
    void _init();
	void _initializeSystem();
	void _initializeMedia();
	void _run();
	void _updateWindow();
    void _updateView();
	void _updatePlayers(sf::Time);
	void _drawBackground();
	void _drawMap();
	void _drawPlayers();
	void _drawScreenEffects();
	void _drawHUDandMenus();
  void _draw();
	void _zoom(float);
  void _pauseGame();
	void _pauseMenuSelect();
private:
	float _deltaTime;
	float _zoomLevel;
    bool _isJumping;
	std::vector<void(*)()> _drawfucntions;

    sf::RenderWindow _window;
	sf::Image _icon;
    sf::View _view;
	sf::Clock _clock;
	sf::Sprite _bg;
	sf::Texture _bgTexture;
	sf::Sprite _pauseSword;
	sf::Texture _pauseSwordTexture;
	sf::Sprite _vignette;
	sf::Texture _vignetteTexture;
	sf::Text _score;
  sf::Font _font;
  sf::Text pause, resume, options;

  Player _player;
  GameState _state;
  Map _map;
	friend class Player;
};

#endif /* Game_hpp */
