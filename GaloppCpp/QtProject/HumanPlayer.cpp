#include "Player.h"
#include <iostream>
#include <qglobal.h>
#include "humanplayerinterface.h"

using namespace std;

HumanPlayer::HumanPlayer(GamingPhase * gpt) : Player(), gamingPhasePtr(gpt)
{}

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

  // Unused parameters:
  Q_UNUSED(distance);

  HumanPlayerInterface humanPlayerInterface(firstHorsesOfPlayers,
                                            secondHorsesOfPlayers,
                                            positionsOfHorses,
                                            diceNumber,
                                            availableHorsesToMove,
                                            playersTurn,
                                            gamingPhasePtr, Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  humanPlayerInterface.setModal(true);
  return humanPlayerInterface.exec();
}


void HumanPlayer::BadMove(const vector<int> & positionsOfHorses,
                          int diceNumber,
                          const vector<bool> & availableHorsesToMove,
                          int playersTurn,
                          int playersMove) const
{
  // Unused parameters:
  Q_UNUSED(positionsOfHorses);
  Q_UNUSED(diceNumber);
  Q_UNUSED(availableHorsesToMove);
  Q_UNUSED(playersTurn);
  Q_UNUSED(playersMove);

  Console::PrintErrorMessage(QString("Kļūda!!!"), QString("Cilvēks izdarīja nepareizo gājienu.\nKļūda kodā!"));
}
