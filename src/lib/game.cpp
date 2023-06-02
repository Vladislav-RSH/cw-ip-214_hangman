#include <lib/game.h>
#include <lib/term.h>
#include <stdio.h>
#include <stdlib.h>

#include <array>
#include <fstream>
#include <iostream>
#include <string>

#define FILELENGTH 1386
#define GAMELENGTH 9

std::array<std::string, GAMELENGTH> stage = {
    "",
    "________\n",
    "|\n|\n|\n|\n|\n|_______\n",
    "_______\n|/\n|\n|\n|\n|\n|______\n",
    "_______\n|/    |\n|\n|\n|\n|\n|______\n",
    "_______\n|/    |\n|     O\n|\n|\n|\n|______\n",
    "_______\n|/    |\n|     O\n|     |\n|\n|\n|______\n",
    "_______\n|/    |\n|     O\n|    /|\\\n|\n|\n|______\n",
    "_______\n|/    |\n|     O\n|    /|\\\n|    / \\\n|\n|_______\n"};

Game_shell::Game_shell() {
  Quit = false;
  P1.Score = 0;
  P1.Name = "Player 1";
  P1.Guess = true;
  P2.Score = 0;
  P2.Name = "Player 2";
  Guess = P1;
  Word = P2;
}

void Game_shell::init() {
  int options = 3;
  int select;
  std::cout << "\n!!HANGMAN!!\n\nSelect an option:"
            << "\n1.Single Player"
            << "\n2.Multiplayer"
            << "\n3.Exit" << std::endl;
  std::cin >> select;
  option(select);
  if (select == 1) {
    std::cout << "\nSelected CPU opponent!" << std::endl;
  } else if (select == 2) {
    std::cout << "\nSelected human opponent!" << std::endl;
  }
  if (select < 1 || select > options) {
    std::cout << "\nPlease select a valid input option!" << std::endl;
    init();
  } else if (select == options) {
    std::cout << "Exiting..." << std::endl;
    Quit = true;
    return;
  }
}

void Game_shell::run() {
  Attempts = 0;
  Game_data session;
  if (!Multiplayer) {
    session.genWord();
  } else {
    session.addWord(Guess, Word);
  }
  while (Attempts < GAMELENGTH - 1) {
    session.display();
    if (!session.playerGuess()) {
      Attempts++;
      std::cout << std::endl << stage.at(Attempts) << std::endl << std::endl;
      // cout << Attempts;        //DEBUG
    }
    if (session.endGame()) {
      std::cout << "\nCongratulations " << Guess.Name << "- You won!!"
                << std::endl;
      Guess.Score++;
      break;
    }
  }
  if (!session.endGame()) {
    std::cout << "\nGAME OVER " << Guess.Name << "- You lose!!!" << std::endl;
    Word.Score++;
  }
  session.showAns();
  if (Multiplayer) {
    playerSwitch();
  }
  playerScore();
}

void Game_shell::option(int choice) {
  switch (choice) {
    case 1:
      //   std::cout << "\nSelected CPU opponent!" << std::endl;
      Multiplayer = false;
      Word.Score = 0;

      P2.Active = false;
      Word.Active = false;
      break;
    case 2:
      //   std::cout << "\nSelected human opponent!" << std::endl;
      Multiplayer = true;
      P2.Active = true;
      break;
    case 3:
      break;
    default:
      throw "\nUnrecognised input... Congrats, you broke it.\n";
  }
}

void Game_shell::playerSwitch() {
  if (P1.Guess == true) {
    P1.Score += Guess.Score;
    P2.Score += Word.Score;
    P1.Guess = false;
    P2.Guess = true;
    Guess = P1;
    Word = P2;
  } else {
    P2.Score += Guess.Score;
    P1.Score += Word.Score;
    P2.Guess = false;
    P1.Guess = true;
    Guess = P2;
    Word = P1;
  }
  Guess.Score = 0;
  Word.Score = 0;
}

void Game_shell::playerScore() {
  std::cout << std::endl << P1.Name << ": " << P1.Score << std::endl;
  if (P2.Active) {
    std::cout << std::endl << P2.Name << ": " << P2.Score << std::endl;
  }
}

Game_data::Game_data() { PartialSol = ""; }

void Game_data::genWord() {
  int ranNum = rand() % FILELENGTH;
  int lineNum = 0;
  std::string line;
  std::ifstream wordList("../src/lib/words.txt");
  while (getline(wordList, line)) {
    ++lineNum;
    if (lineNum == ranNum) {
      Word = line;
      // std::cout << line;   //DEBUG
    }
  }
  PartialSol.append(Word.size(), '.');
  // std::cout << PartialSol;   //DEBUG
}

void Game_data::addWord(Player guess, Player word) {
  HideStdinKeystrokes();
  std::cout << "\n"
            << word.Name << " - Please provide a word for " << guess.Name
            << " to guess:";
  std::cin >> Word;
  ShowStdinKeystrokes();
  // std::cout << word;     //DEBUG
  PartialSol.append(Word.size(), '.');
  // std::cout << PartialSol;   //DEBUG
}

void Game_data::display() {
  std::cout << std::endl;
  std::cout << PartialSol << std::endl;
  std::cout << "\nIncorrect guesses: " << Incorrect.size() << std::endl;
  for (unsigned int i = 0; i < Incorrect.size(); i++) {
    std::cout << Incorrect.at(i) << ", ";
  }
  std::cout << std::endl;
  return;
}

// Fires when the guessing player loses the game
void Game_data::showAns() {
  std::cout << "\nThe correct answer was:\n" << Word << std::endl;
}

bool Game_data::playerGuess() {
  std::cout
      << "\n\nPlease guess a letter (Only the first character provided will "
         "be read):"
      << std::endl;
  std::cin >> Guess;
  bool ans = false;
  for (unsigned int i = 0; i < Incorrect.size(); i++) {
    if (Guess == Incorrect.at(i)) {
      std::cout << "\nYou've already guessed that letter!" << std::endl;
      ans = true;
    }
  }
  for (unsigned int i = 0; i < PartialSol.size(); i++) {
    if (Guess == PartialSol.at(i)) {
      std::cout << "\nYou've already guessed that letter!" << std::endl;
      ans = true;
    } else if (Guess == Word.at(i)) {
      PartialSol.at(i) = Guess;
      ans = true;
    }
  }
  if (!ans) {
    Incorrect.push_back(Guess);
  }
  return ans;
}

bool Game_data::endGame() {
  if (PartialSol == Word) {
    return true;
  } else {
    return false;
  }
}