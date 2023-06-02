// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

// Private includes
#include "lib/game.h"
#include "lib/term.h"
// Globals

int main() {
  char restart;
  srand(time(NULL));
  Game_shell game;
  for (;;) {
    game.init();
    if (game.Quit == true) {
      break;
    }
    for (;;) {
      game.run();
      std::cout << "Play again? (y/N)";
      std::cin >> restart;
      if (restart != 'y') {
        break;
      }
    }
  }
  return 0;
}