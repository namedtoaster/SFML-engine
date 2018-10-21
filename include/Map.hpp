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
#include "Animation.h"
#include "AnimatedSprite.h"
#include <vector>

class Map {
public:
    Map(const std::string&);

	void update(sf::Time);
	void draw(sf::RenderWindow&, bool);
	sf::Texture* getTextures();
	std::vector<sf::Sprite> getSprites();
public:
	// TODO: combine the sprites into the tile class (I don't know why I did it this way)
	std::vector<std::vector<Tile> > _tiles;

private:
	int _numSprites;
	float _tileW = 50.f;
	float _tileH = 50.f;
    std::vector<sf::IntRect> _texRects;
    std::vector<sf::Sprite> _tileSprites;
	sf::Texture _textures[3];
	// TODO: Yeaaaah, this is definitely super inefficient to have enemy and player classes all over the place
	// I need to put them all under one roof
	// In retrospect, it also makes zero sense since you still need to draw the tiles where the enemies are
	Animation *_currentAnimation;
	Animation _enemyAnimation;
	sf::Texture _enemySpriteSheet;
	std::vector<AnimatedSprite> _enemies;
};

#endif
