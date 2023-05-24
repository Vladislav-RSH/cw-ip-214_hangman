#include <../src/lib/game.h>
#include <../src/lib/term.h>
#include <../thirdparty/ctest.h>

#include <string>

using namespace std;

CTEST(game_shell_constructor_test, initialize_game_1)
{
    Game_shell game;
    ASSERT_FALSE(game._quit);
    ASSERT_EQUAL(0, game._p1._score);
    ASSERT_TRUE(game._p1._guess);
}

CTEST(game_shell_constructor_test, initialize_game_2)
{
    Game_shell game;
    ASSERT_FALSE(game._quit);
    ASSERT_EQUAL(0, game._p2._score);
    ASSERT_FALSE(game._p2._guess);
}

CTEST(game_shell_option_test, option_selected_1)
{
    Game_shell game;
    game.option(1);
    ASSERT_FALSE(game._multiplayer);
}

CTEST(game_shell_option_test, option_selected_2)
{
    Game_shell game;
    game.option(2);
    ASSERT_TRUE(game._multiplayer);
    ASSERT_TRUE(game._p2._active);
}

CTEST(game_shell_option_test, option_selected_3)
{
    Game_shell game;
    game.option(3);
    ASSERT_FALSE(game._p2._active);
}

CTEST(game_shell_player_switch_test, player_guessing_1)
{
    Game_shell game;
    game.playerSwitch();
    ASSERT_FALSE(game._p1._guess);
    ASSERT_TRUE(game._p2._guess);
}

CTEST(game_shell_player_switch_test, player_guessing_2)
{
    Game_shell game;
    game.playerSwitch();
    game.playerSwitch();
    ASSERT_TRUE(game._p1._guess);
    ASSERT_FALSE(game._p2._guess);
}

CTEST(game_shell_player_switch_test, scores_updated)
{
    Game_shell game;
    game._p1._score = 5;
    game._p2._score = 10;
    game._guess._score = 3;
    game._word._score = 4;
    game.playerSwitch();
    ASSERT_EQUAL(14, game._p2._score);
    ASSERT_EQUAL(8, game._p1._score);
    ASSERT_EQUAL(0, game._guess._score);
    ASSERT_EQUAL(0, game._word._score);
}

CTEST(game_data_genWord_test, generate_word)
{
    Game_data game;
    game.genWord();
    ASSERT_EQUAL(game._word.size(), game._partialSol.size());
}
