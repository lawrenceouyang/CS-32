//Lawrence Ouyang
//504128219
//Project 1: Zombie Exterminator

#include <cstdlib>
#include <ctime>

#include "Game.h"
using namespace std;

int main()
{
      // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 40);

      // Play the game
    g.play();
}
