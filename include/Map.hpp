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
#include "Tile.h"
#include <vector>

class Map {
public:
    Map(const std::string&);

	void draw(sf::RenderWindow&);
	sf::Texture* getTextures();
	std::vector<sf::Sprite> getSprites();
public:
	std::vector<std::vector<Tile> > _tiles;

private:
	int _numSprites;
	float _tileW = 50.f;
	float _tileH = 50.f;
    std::vector<sf::IntRect> _texRects;
    std::vector<sf::Sprite> _sprites;
	sf::Texture _textures[3];
};

#endif /* Map_hpp */
