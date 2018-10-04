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
	// Load background
	sf::Texture bgText;
	bgText.loadFromFile("assets/stars.jpg");
	_bg.setTexture(bgText);
	// Vignette
	sf::Texture text;
	text.loadFromFile("assets/vignette.png");
	_vignette.setTexture(text);
	_vignette.scale(float(WIDTH) / 1510.f, float(HEIGHT) / 1000.f);

	// Load text
	sf::Font font;
	font.loadFromFile("assets/chintzy.ttf");
	score.setFont(font);
	score.setString("x1000");
	score.setPosition(LEFT_MARG, TOP_MARG);

    _init();
}

void Game::run() {
    while (_window.isOpen()) {
		_deltaTime = _clock.restart().asSeconds();

		_updateWindow();
		_updateView();
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
            _window.close();
        }

		// TODO: figure out how to smoothly incorporate this
		/*if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LControl)
			_player.doneSlashing();*/
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

void Game::_draw() {
    // Clear the window and draw solid color (defaults to black)
	_window.clear();

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

	_window.draw(score);

    // Display all items that have been drawn
    _window.display();
}

void Game::_zoom(float factor)
{
	_zoomLevel = factor;
	_view.zoom(_zoomLevel);
}
