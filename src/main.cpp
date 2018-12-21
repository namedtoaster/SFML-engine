
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <typeinfo>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

int main(int argc, char const** argv)
{
    Game myGame;

	std::vector<Player*> players;
	Player* test = new Player;
	Enemy* test1 = new Enemy;
	test1->val = 1;
	
	players.push_back(test);
	players.push_back(test1);

	std::cout << typeid(players[0]).name() << std::endl;

    return 0;
}
