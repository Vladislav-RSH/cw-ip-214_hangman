// Hide terminal inputs
#include <string>

void HideStdinKeystrokes();
void ShowStdinKeystrokes();

class Player {
 public:
  int Score;
  bool Guess;
  bool Active;
  std::string Name;
};

class Game_shell {
 public:
  Game_shell();
  void init();
  void run();
  void option(int choice);
  void playerSwitch();
  void playerScore();
  bool Quit;
  int Games;
  Player P1;
  Player P2;
  Player Guess;
  Player Word;
  bool Multiplayer;

 private:
  int Attempts;
};

class Game_data {
 public:
  Game_data();
  void genWord();
  void addWord(Player guess, Player word);
  void display();
  void showAns();
  bool playerGuess();
  bool endGame();
  char Guess;
  std::string Incorrect;
  std::string PartialSol;
  std::string Word;

  bool multiplayer;
};
