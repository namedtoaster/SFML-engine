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
    if (!getline(input, line));
        // get the number of sprites included in the data
    _numSprites = std::stoi(&line[0]);
        // set the size of the tiles. we'll do 100x100 for now
    // already set in the header file
    
    // read the data
        // starting with a specified line (have a default that's used to determine when this is reached), start reading in each number
        // simply push each line onto the vector for the tile type
		// then push the position for each sprite based on its index and tile size
	std::cout << _numSprites << std::endl;
	int i = 0;
    while (getline(input, line)) {
		for (int j = 0; j < line.size(); j++) {
			_tiles.tileType[i][j] = line[j] - '0';
			_tiles.x[i][j] = ((float)j * _tileW);
			_tiles.y[i][j] = ((float)i * _tileH);
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
