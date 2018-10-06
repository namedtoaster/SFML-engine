//
//  Game.cpp
//  SFML-test
//
//  Created by Dave Campbell on 7/8/18.
//  Copyright © 2018 Dave Campbell. All rights reserved.
//

#include "Game.hpp"
#include "Animation.h"
//#include "Constants.h"

Game::Game() : 
	_window(sf::VideoMode(WIDTH, HEIGHT), "SFML test"),
	_map("assets/data"),
	_state(PLAY),
	_isJumping(false),
	_deltaTime(0.f),
	_view(sf::FloatRect(0, 0, WIDTH, HEIGHT)),
	_zoomLevel(.7f)
{
	// Load images
	sf::Texture bgTxt, swordTxt;
	bgTxt.loadFromFile("assets/stars.jpg");
	_bg.setTexture(bgTxt);
	swordTxt.loadFromFile("assets/pause-sword.png");
	_pauseSword.setTexture(swordTxt);
	_pauseSword.scale(2.f, 2.f);

    
    // Load font
    if (!_font.loadFromFile("assets/chintzy.ttf"))
        std::cout << "Cannot load font" << std::endl;
    _score.setFont(_font);
	_score.setString("0");
    _score.setPosition(LEFT_MARG, TOP_MARG);
    
	// Vignette
	sf::Texture text;
	text.loadFromFile("assets/vignette.png");
	_vignette.setTexture(text);
	_vignette.scale(float(WIDTH) / 1510.f, float(HEIGHT) / 1000.f);

    _init();
}

void Game::run() {
    while (_window.isOpen()) {
		_deltaTime = _clock.restart().asSeconds();

		_updateWindow();
		_updateView();
        
        if (_state == PLAY)
            _updatePlayers();
        
        _draw();
    }
}

void Game::_init() {
    // Window initialization
    _window.setFramerateLimit(60);
    _window.setVerticalSyncEnabled(true);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("assets/icon.png")) {
      return;
    }
    _window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Zoom in a bit
	_zoom(_zoomLevel);
    
    // Run the game
    run();
}

void Game::_updateWindow() {
    // Process events
    sf::Event event;
    
    // The reason that key press events aren't in the while loop (with the exception of the Escape key) is because this won't give smooth input for player movement
    while (_window.pollEvent(event)) {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (_state == PLAY)
                _state = PAUSE;
            else if (_state == PAUSE)
                _state = PLAY;
        }

		// TODO: figure out how to smoothly incorporate this
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LControl)
			_player.doneSlashing();
    }
    
    // Window resize
    if (event.type == sf::Event::Resized) {
        //sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
		//_view.reset(visibleArea);

		int x_pos = _player.getPosition().x;
		int y_pos = _player.getPosition().y;

		_view.setCenter(sf::Vector2f(x_pos, y_pos + _player.getHeight()));
		_view.setSize(sf::Vector2f(event.size.width, event.size.height));

		_zoom(_zoomLevel);
        
        // TODO: Prevent the window from being shurnk smaller than the height of the map and a set width
    }
}

// Keep view centered around player
void Game::_updateView() {
	sf::Event event;
	
	int x_pos = _player.getPosition().x;
	int y_pos = _player.getPosition().y;

	// Center on player
	_view.setCenter(x_pos, y_pos + _player.getHeight());
}

void Game::_updatePlayers() {
	sf::Event event;
	_player.update(_window, _map, _deltaTime);
}

// TODO: Find a more elegant way of drawing everything (maybe find or make a way to stack order of drawings -- things that move and things that don't)
void Game::_draw() {
    // Clear the window and draw solid color (defaults to black)
	_window.clear();

	// Draw bg
	_window.draw(_bg);
	_window.setView(_view);

	// Draw tiles
	_map.draw(_window, false);

	// Draw player
	_player.draw(_window, false);
    // TODO: Create different functions for drawing the character, drawing enemies, drawing the onscreen text, and more

	_window.setView(_window.getDefaultView());
	// Vignette test
	_window.draw(_vignette);

	// Draw text
	_window.draw(_score);

	// TODO: make a menu class or something
	// TODO: this relates to the TODO at the top of the draw function, but I need to figure out a better way to separate the pause logic from the draw function
	if (_state == PAUSE) {
		_pauseGame();
	}

    // Display all items that have been drawn
    _window.display();
}

void Game::_zoom(float factor)
{
	_zoomLevel = factor;
	_view.zoom(_zoomLevel);
}

void Game::_pauseGame() {
	// TODO: I will definitely need to create a class for this if I end up creating lots of text
	// It's only a pause menu so there shouldn't be much, but still something to think about

	// Create the text to be drawn
	sf::Text pause, resume, options;
	pause.setFont(_font);
	resume.setFont(_font);
	options.setFont(_font);
	pause.setString("PAUSE");
	resume.setString("RESUME");
	options.setString("OPTIONS");

	//pause.scale(1.5f, 1.5f);
	pause.setCharacterSize(60);
	sf::FloatRect textRect = pause.getLocalBounds();
	pause.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	textRect = resume.getLocalBounds();
	resume.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	textRect = options.getLocalBounds();
	options.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	textRect = _pauseSword.getLocalBounds();
	_pauseSword.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);


	float textPosX = _window.getSize().x / 2;
	float textPosY = _window.getSize().y / 2;
	pause.setPosition(sf::Vector2f(textPosX, textPosY -50));
	resume.setPosition(pause.getPosition().x, pause.getPosition().y + MENU_TXT_MARG * 2);
	options.setPosition(resume.getPosition().x, resume.getPosition().y + MENU_TXT_MARG);
	_pauseSword.setPosition(resume.getPosition().x - resume.getLocalBounds().width / 2 - 30, resume.getPosition().y);

	_window.draw(pause);
	_window.draw(resume);
	_window.draw(options);
	_window.draw(_pauseSword);
}

void Game::_pauseMenuSelect()
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) {
		
	}*/
}
