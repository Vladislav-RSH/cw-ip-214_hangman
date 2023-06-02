#include <../src/lib/game.h>
#include <../src/lib/term.h>
#include <../thirdparty/ctest.h>

#include <string>

using namespace std;

CTEST(game_shell_constructor_test, initialize_game_1) {
  Game_shell game;
  ASSERT_FALSE(game.Quit);
  ASSERT_EQUAL(0, game.P1.Score);
  ASSERT_TRUE(game.P1.Guess);
}

CTEST(game_shell_constructor_test, initialize_game_2) {
  Game_shell game;
  ASSERT_FALSE(game.Quit);
  ASSERT_EQUAL(0, game.P2.Score);
  ASSERT_FALSE(game.P2.Guess);
}

CTEST(game_shell_option_test, option_selected_1) {
  Game_shell game;
  game.option(1);
  ASSERT_FALSE(game.Multiplayer);
}

CTEST(game_shell_option_test, option_selected_2) {
  Game_shell game;
  game.option(2);
  ASSERT_TRUE(game.Multiplayer);
  ASSERT_TRUE(game.P2.Active);
}

CTEST(game_shell_option_test, option_selected_3) {
  Game_shell game;
  game.option(3);
  ASSERT_FALSE(game.P2.Active);
}

CTEST(game_shell_player_switch_test, player_guessing_1) {
  Game_shell game;
  game.playerSwitch();
  ASSERT_FALSE(game.P1.Guess);
  ASSERT_TRUE(game.P2.Guess);
}

CTEST(game_shell_player_switch_test, player_guessing_2) {
  Game_shell game;
  game.playerSwitch();
  game.playerSwitch();
  ASSERT_TRUE(game.P1.Guess);
  ASSERT_FALSE(game.P2.Guess);
}

CTEST(game_shell_player_switch_test, scores_updated) {
  Game_shell game;
  game.P1.Score = 5;
  game.P2.Score = 10;
  game.Guess.Score = 3;
  game.Word.Score = 4;
  game.playerSwitch();
  ASSERT_EQUAL(14, game.P2.Score);
  ASSERT_EQUAL(8, game.P1.Score);
  ASSERT_EQUAL(0, game.Guess.Score);
  ASSERT_EQUAL(0, game.Word.Score);
}

CTEST(game_data_genWord_test, generate_word) {
  Game_data game;
  game.genWord();
  ASSERT_EQUAL(game.Word.size(), game.PartialSol.size());
}
