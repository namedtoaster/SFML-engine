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
    std::string path = "/Users/dave/Documents/programming/cpp/practice/SFML-test/";
    path.append(filename);
    std::ifstream input(filename);
    std::string line;
    if (!getline(input, line));
        // get the number of sprites included in the data
    _numSprites = std::stoi(&line[0]);
        // set the size of the tiles. we'll do 100x100 for now
    // already set in the header file
    
    // read the data
        // starting with a specified line (have a default that's used to determine when this is reached), start reading in each number
        // simply push each number onto the vector
    while (getline(input, line)) {
        for (int i = 0; i < line.length(); i++) {
            _tiles.push_back(line[i]);
        }
    }
    
    // load the texture - there will only be one
    // by default, just use 10 sprites per "row"
    if (!_texture.loadFromFile("sewer_1.png")) {
      return;
    }
    
    for (int i = 0; i < _numSprites; i++) {
        _texRects.push_back(sf::IntRect(i * TILE_W_H, i / TILES_PER_ROW * TILE_W_H, TILE_W_H, TILE_W_H));
        _sprites.push_back(sf::Sprite(_texture));
        _sprites[i].setTextureRect(_texRects[i]);
    }
    
    // for testing - set different positions for the tiles
    for (int i = 0; i < _numSprites; i++) {
        _sprites[i].setPosition(i * 100, i * 100);
    }
}

int Map::getNumSprites() {
    return _numSprites;
}

sf::Sprite Map::getSprite(int index) {
    return _sprites[index];
}
