//Hide terminal inputs
#include <string>

using namespace std;
void HideStdinKeystrokes();
void ShowStdinKeystrokes();

class Player {
  public:
    int _score;
    bool _guess;
    bool _active;
    string _name;
};

/* Main game class - this will start, manage and end the game instance. Data required for the game is stored in the Game_data class. */
class Game_shell {
  public:
    Game_shell();
    void init();
    void run();
    void option(int choice);
    void playerSwitch();
    void playerScore();
    bool _quit;
    int _games;
    Player _p1;
    Player _p2;
    Player _guess;
    Player _word;
    bool _multiplayer;
  private:
    int _attempts;
};


/* Stores all the variables and performs all the logic required for the game. Each instance will be scrapped after each round, allowing for a score system to be eventually implemented */
class Game_data {
  public:
    Game_data();
    void genWord();
    void addWord(Player guess, Player word);
    void display();
    void showAns();
    bool playerGuess();
    bool endGame();
    char _guess;
    string _incorrect;
    string _partialSol;
    string _word;

    bool multiplayer;
    
};
