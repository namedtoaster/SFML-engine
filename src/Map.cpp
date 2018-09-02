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
			_tiles[i].push_back(Tile(line[j] - '0', (float)j * _tileW, (float)i * _tileH));
		}
		i++;
    }
    
    // load the textures - 0 = wall, 1 = ground, 2 = lava
	if (!_textures[0].loadFromFile("assets/BrickGrey.png"))
		return;
	if (!_textures[1].loadFromFile("assets/CommTerminal.png"))
		return;
	if (!_textures[2].loadFromFile("assets/lava.png"))
		return;

	// Apply the textures to the sprites
	sf::Sprite wall; sf::Sprite ground; sf::Sprite lava;
	_sprites.push_back(wall); _sprites.push_back(ground); _sprites.push_back(lava);
	_sprites[0].setTexture(_textures[0]); _sprites[1].setTexture(_textures[1]); _sprites[2].setTexture(_textures[2]);
}

std::vector<sf::Sprite> Map::getSprites() {
    return _sprites;
}

sf::Texture* Map::getTextures() {
	return _textures;
}

void Map::draw(sf::RenderWindow &window) {
	for (int i = 0; i < _tiles.size(); i++) {
		for (int j = 0; j < _tiles[i].size(); j++) {
			_sprites[_tiles[i][j].tileType].setPosition(_tiles[i][j].x, _tiles[i][j].y);
			window.draw(_sprites[_tiles[i][j].tileType]);
		}
	}
}