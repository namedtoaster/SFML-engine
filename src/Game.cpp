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
	_deltaTime(0.f)
{
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
	_view.zoom(0.5f);



    
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
    }
    
    // Window resize
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
		_view.reset(visibleArea);
        
        // TODO: Prevent the window from being shurnk smaller than the height of the map and a set width
    }
}

// Keep view centered around player
void Game::_updateView() {
	sf::Event event;
	
	int x_pos = _player.getPosition().x;
	int y_pos = _player.getPosition().y;

	_view.setCenter(x_pos, y_pos);
}

void Game::_updatePlayers() {
	sf::Event event;
	_player.update(_window, _map, event, _deltaTime);
}

void Game::_draw() {
    // Clear the window and draw solid color (defaults to black)
    _window.clear();
	_window.setView(_view);
    
	// Draw tiles
	_map.draw(_window, false);

	// Draw player
	_player.draw(_window);

    // TODO: Create different functions for drawing the character, drawing enemies, drawing the onscreen text, and more

	_window.setView(_window.getDefaultView());

    // Display all items that have been drawn
    _window.display();
}
