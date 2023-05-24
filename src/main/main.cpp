// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;

// Private includes
#include "../src/lib/game.h"
#include "../src/lib/term.h"
// Globals

int main() {
  char restart;
  srand(time(NULL));
  Game_shell game;
  for (;;) {
    game.init();
    if (game._quit == true) {
      break;
    }
    for (;;) {
      game.run();
      // After game ends, offer chance to replay
      cout << "Play again? (y/N)";
      cin >> restart;
      if (restart != 'y') {
        break;
      }
    }
  }
  // Clean up - re-enable echo
  return 0;
}