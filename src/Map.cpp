//
//  Map.cpp
//  SFML-engine
//
//  Created by Dave Campbell on 8/5/18.
//  Copyright © 2018 Dave Campbell. All rights reserved.
//

#include "Map.hpp"
#include <fstream>
#include <iostream>

Map::Map(const std::string &filename) {
    std::ifstream input(filename);
    std::string line;

	int i = 0;
    while (getline(input, line)) {
		_tiles.push_back(std::vector<Tile>());
		for (int j = 0; j < line.size(); j++) {
			if (line[j] - '0' == 3) {
				_enemies.push_back(AnimatedSprite(sf::seconds(0.18), true, false));
				// TODO: get actual size of sprite and have it get updated through playing of animation
				// Probably need to have an option in that in the animation class
				_enemies[_enemies.size() - 1].setPosition((float)j * _tileW, (float)i * _tileH);
			}
			else _tiles[i].push_back(Tile(line[j] - '0', (float)j * _tileW, (float)i * _tileH));
		}
		i++;
    }
    
	// TODO: Find a much more dynamic and neat way of doing this
    // load the textures - 0 = wall, 1 = ground, 2 = lava, 3 = enemy
	if (!_textures[0].loadFromFile("assets/BrickGrey.png"))
		return;
	if (!_textures[1].loadFromFile("assets/purple-brick.png"))
		return;
	if (!_textures[2].loadFromFile("assets/lava.png"))
		return;

	// Apply the textures to the sprites
	sf::Sprite wall; sf::Sprite ground; sf::Sprite lava;

	_tileSprites.push_back(wall); _tileSprites.push_back(ground); _tileSprites.push_back(lava);

	_tileSprites[0].setTexture(_textures[0]); _tileSprites[1].setTexture(_textures[1]); _tileSprites[2].setTexture(_textures[2]);

	// Create enemy animation
	// TODO: Should probably have some sort of error handling when loading files and such
	if (!_enemySpriteSheet.loadFromFile("assets/random.png")) {
		return;
	}

	_enemyAnimation.setSpriteSheet(_enemySpriteSheet);
	_enemyAnimation.addFrame(sf::IntRect(342, 55, 35, 29));
	_enemyAnimation.addFrame(sf::IntRect(386, 58, 52, 26));
	_enemyAnimation.addFrame(sf::IntRect(449, 59, 47, 26));
	_enemyAnimation.addFrame(sf::IntRect(503, 58, 35, 28));
	_currentAnimation = &_enemyAnimation;
}

std::vector<sf::Sprite> Map::getSprites() {
    return _tileSprites;
}

sf::Texture* Map::getTextures() {
	return _textures;
}

void Map::update(sf::Time frameTime)
{
	for (int i = 0; i < _enemies.size(); i++) {
		
		_enemies[i].play(*_currentAnimation);
		_enemies[i].update(frameTime, false);
	}
}

void Map::draw(sf::RenderWindow &window, bool drawGrid) {
	// Draw the tiles
	for (int i = 0; i < _tiles.size(); i++) {
		for (int j = 0; j < _tiles[i].size(); j++) {
			_tileSprites[_tiles[i][j].tileType].setPosition(_tiles[i][j].x, _tiles[i][j].y);
			window.draw(_tileSprites[_tiles[i][j].tileType]);
		}
	}

	// Draw the enemies
	for (int i = 0; i < _enemies.size(); i++) {
		window.draw(_enemies[i]);
	}

	// Draw the grid
	if (drawGrid) {
		std::vector<std::vector<std::vector<sf::Vertex>>> _vertices;
		for (int i = 0; i < _tiles.size(); i++) {
			for (int j = 0; j < _tiles[i].size(); j++) {
				sf::Vertex vertices[4] = {
					sf::Vertex(sf::Vector2f(j * _tileW, i * _tileH)),
					sf::Vertex(sf::Vector2f(j * _tileW + _tileW, i * _tileH)),
					sf::Vertex(sf::Vector2f(j * _tileW + _tileW, i * _tileH + _tileH)),
					sf::Vertex(sf::Vector2f(j * _tileW, i * _tileH + _tileH))
				};

				window.draw(vertices, 4, sf::LineStrip);
			}
		}
	}
}