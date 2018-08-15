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
    Map(const std::string&);
    int getNumSprites();
    sf::Sprite getSprite(int);
private:
    std::vector<int> _tiles;
    std::vector<sf::IntRect> _texRects; // this defines the rectangular region that the tile occupies
    std::vector<sf::Sprite> _sprites;
    int _numSprites;
    int _tileW = 100;
    int _tileH = 100;
    sf::Texture _texture; // there's only one texture that's loaded. each sprite comes from one texture
};

#endif /* Map_hpp */
