#include "Player.h"
#include <cstdlib>

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

  // Create a vector with all possible moves, so that it would be easy to randomly choose one of them
  vector<int> availableMoves;
  for (unsigned int i = 0; i < availableHorsesToMove.size(); i++)
    if (availableHorsesToMove[i] == true)
      availableMoves.push_back(i);

  int randomIndex = rand() % availableMoves.size();

  return availableMoves[randomIndex];
}
