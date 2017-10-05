#include "Player.h"
#include <iostream>
#include <qglobal.h>

using namespace std;

void Player::BadMove(const vector<int> & positionsOfHorses,
                     int diceNumber,
                     const vector<bool> & availableHorsesToMove,
                     int playersTurn,
                     int playersMove) const
{
  Q_UNUSED(positionsOfHorses);
  Q_UNUSED(diceNumber);
  Q_UNUSED(availableHorsesToMove);
  Q_UNUSED(playersTurn);
  Q_UNUSED(playersMove);

  Console::PrintErrorMessage(QString("Kļūda!"), QString("Kļūda kodā!\nAutomātiskais spēlētājs izdarija neiespējamo gājienu!\n"));
}


Player::~Player()
{ }
