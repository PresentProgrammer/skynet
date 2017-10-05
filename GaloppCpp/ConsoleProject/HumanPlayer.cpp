#include "Player.h"
#include <iostream>

using namespace std;


int HumanPlayer::MakeMove(const vector<int> & firstHorsesOfPlayers,
                          const vector<int> & secondHorsesOfPlayers,
                          const vector<int> & positionsOfHorses,
                          int diceNumber,
                          const vector<bool> & availableHorsesToMove,
                          int playersTurn,
                          int distance
                          ) const
{
  // The method shall display all the necessary info about the game so that
  // a human player could make the right move. The method returns the index of
  // the horse, correspondingly to player's move.

  // Print the game state to console:
  // --------------------------------------------- //
  cout << "Game state:\n";

  cout << "First horses:  ";
  for (vector<int>::const_iterator iter = firstHorsesOfPlayers.begin();
    iter != firstHorsesOfPlayers.end(); iter++)
      cout << (*iter) << ";  ";

  cout << endl << "Second horses:  ";
  for (vector<int>::const_iterator iter = secondHorsesOfPlayers.begin();
    iter != secondHorsesOfPlayers.end(); iter++)
      cout << (*iter) << ";  ";

  cout << endl << "You are player " << playersTurn << ". Your horses are: "
       << firstHorsesOfPlayers[playersTurn] << " and " << secondHorsesOfPlayers[playersTurn];

  cout << endl << "Positions of horses:  ";
  for (unsigned int i = 0; i < positionsOfHorses.size(); i++)
    cout << endl << i << ") " << positionsOfHorses[i] << ";";

  cout << endl << "Distance = " << distance;

  cout << endl << "Dice number = " << diceNumber;

  cout << ";  Available horses to move:  ";
  for (unsigned int i = 0; i < availableHorsesToMove.size(); i++)
    if (availableHorsesToMove[i])
      cout << i << "  ";

  // ========================================= //

  cout << "\nPlease, make your move: ";
  char humanPlayerCharMove;
  cin >> humanPlayerCharMove;
  Console::ClearBuffer();
  cout << endl << endl;

  int humanPlayerMove = humanPlayerCharMove - '0';
  return humanPlayerMove;
}


void HumanPlayer::BadMove(const vector<int> & positionsOfHorses,
                          int diceNumber,
                          const vector<bool> & availableHorsesToMove,
                          int playersTurn,
                          int playersMove) const
{
  cout << "Sorry, but your move is incorrect.\n";
  cout << "Please, enter one of these numbers: ";
  for (unsigned int i = 0; i < availableHorsesToMove.size(); i++)
    if (availableHorsesToMove[i])
      cout << i << "  ";
  cout << endl << endl;
}
