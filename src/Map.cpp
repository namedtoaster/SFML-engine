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
    // load the file
		// read the metadata
    std::ifstream input(filename);
    std::string line;
    
		// read the data
	int i = 0;
    while (getline(input, line)) {
		_tiles.tileType.push_back(std::vector<int>());
		_tiles.x.push_back(std::vector<float>());
		_tiles.y.push_back(std::vector<float>());
		for (int j = 0; j < line.size(); j++) {
			_tiles.tileType[i].push_back(line[j] - '0');
			_tiles.x[i].push_back((float)j * _tileW);
			_tiles.y[i].push_back((float)i * _tileH);
		}
		i++;
    }
    
    // load the textures - 0 = wall, 1 = ground, 2 = lava
	if (!_textures[0].loadFromFile("wall.png"))
		return;
	if (!_textures[1].loadFromFile("ground.png"))
		return;
	if (!_textures[2].loadFromFile("lava.png"))
		return;

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
