#include "Player.h"
#include <iostream>

using namespace std;

void Player::BadMove(const vector<int> & positionsOfHorses,
                     int diceNumber,
                     const vector<bool> & availableHorsesToMove,
                     int playersTurn,
                     int playersMove) const
{
  Console::PrintMessage("WARNING! Automated player made an invalid move!\n");
  Console::DisplayGameState(positionsOfHorses, diceNumber, availableHorsesToMove,
                              playersTurn, playersMove);
  Console::WaitForEnterButton();
  exit(EXIT_FAILURE);
}


Player::~Player()
{ }
