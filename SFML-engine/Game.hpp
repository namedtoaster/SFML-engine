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
    ~Game();
    
    void run();
private:
    // Member methods
    void _init();
    void _processEvents();
    void _addSprite(const char*);
    void _updateViewPos();
    void _updateTextPos();
    void _draw();
    void _drawPlayer();
    void _drawSprites();
    void _drawBackground();
    void _drawBGTest();
    void _drawText();
    bool _moveRight();
    bool _moveLeft();
    
    // Member variables
    int _bgWidth;
    int _bgHeight;
    bool _isJumping;
    sf::Image _icon;
    sf::RenderWindow _window;
    sf::Music _backgroundMusic;
    sf::Font _font;
    sf::Text _text;
    sf::View _view;
    sf::Sprite _background;
    sf::Texture _bgTexture;
    Player _player;
    GameState _state;
    Map _map;
    std::vector<sf::Sprite*> _sprites;
};

#endif /* Game_hpp */
