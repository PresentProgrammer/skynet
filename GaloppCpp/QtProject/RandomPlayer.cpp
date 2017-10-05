#include "Player.h"
#include <cstdlib>
#include <qglobal.h>

int RandomPlayer::MakeMove(const vector<int> & firstHorsesOfPlayers,
                           const vector<int> & secondHorsesOfPlayers,
                           const vector<int> & positionsOfHorses,
                           int diceNumber,
                           const vector<bool> & availableHorsesToMove,
                           int playersTurn,
                           int distance
                           ) const
{
  // The method shall generate a horse index, that will be moved.
  // The generated number must be equal to the index of the element of
  // vector availableHorsesToMove, which value is true.
  // Other parameters are not used.

  // Unused parameters:
  Q_UNUSED(firstHorsesOfPlayers);
  Q_UNUSED(secondHorsesOfPlayers);
  Q_UNUSED(positionsOfHorses);
  Q_UNUSED(diceNumber);
  Q_UNUSED(playersTurn);
  Q_UNUSED(distance);

  // Create a vector with all possible moves, so that it would be easy to randomly choose one of them
  vector<int> availableMoves;
  for (unsigned int i = 0; i < availableHorsesToMove.size(); i++)
    if (availableHorsesToMove[i] == true)
      availableMoves.push_back(i);

  int randomIndex = rand() % availableMoves.size();

  return availableMoves[randomIndex];
}
