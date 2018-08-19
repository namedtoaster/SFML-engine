//
//  Map.hpp
//  SFML-engine
//
//  Created by Dave Campbell on 8/5/18.
//  Copyright © 2018 Dave Campbell. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include "Constants.h"
#include <vector>

class Map {
public:
	struct {
		// TODO: find a way to dyanmically size the arrays based on the map data (maybe use vectors?)
		std::vector<std::vector<int> > tileType;
		std::vector<std::vector<float> > x;
		std::vector<std::vector<float> > y;
	} _tiles;
public:
    Map(const std::string&);
	sf::Texture* getTextures();
	std::vector<sf::Sprite> getSprites();
private:
    std::vector<sf::IntRect> _texRects; // this defines the rectangular region that the tile occupies
    std::vector<sf::Sprite> _sprites;
    int _numSprites;
    float _tileW = 50.f;
    float _tileH = 50.f;
    sf::Texture _textures[3]; // there's only one texture that's loaded. each sprite comes from one texture
};

#endif /* Map_hpp */
