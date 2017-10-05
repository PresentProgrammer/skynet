#include "Console.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

void Console::ReadParameter(const string & line, int & parameter)
{
  istringstream iss(line);
  string temp;
  iss >> temp;  // write paramater name
  iss >> temp;   // write "="
  iss >> parameter;
  if (iss.fail())
  {
    Console::PrintMessage("From Console::ReadParameter:\n");
    Console::PrintMessage("Cannot read parameter value from line\n");
    Console::PrintMessage(line.c_str());
    Console::PrintMessage("\nPlease, make sure that file with parameters is valid\n");
    Console::WaitForEnterButton();
    exit(EXIT_FAILURE);
  }
}

void Console::ReadParameter(const string & line, double & parameter)
{
  istringstream iss(line);
  string temp;
  iss >> temp;  // write paramater name
  iss >> temp;  // write "="
  iss >> parameter;
  if (iss.fail())
  {
    Console::PrintMessage("From Console::ReadParameter:\n");
    Console::PrintMessage("Cannot read parameter value from line\n");
    Console::PrintMessage(line.c_str());
    Console::PrintMessage("\nPlease, make sure that file with parameters is valid\n");
    Console::WaitForEnterButton();
    exit(EXIT_FAILURE);
  }
}

void Console::ReadParameter(const string & line, bool & parameter)
{
  istringstream iss(line);
  string temp;
  iss >> temp;  // write paramater name
  iss >> temp;   // write "="
  iss >> parameter;
  if (iss.fail())
  {
    Console::PrintMessage("From Console::ReadParameter:\n");
    Console::PrintMessage("Cannot read parameter value from line\n");
    Console::PrintMessage(line.c_str());
    Console::PrintMessage("\nPlease, make sure that file with parameters is valid\n");
    Console::WaitForEnterButton();
    exit(EXIT_FAILURE);
  }
}



void Console::PrintMessage(const char * str)
{
  cout << str;
}

void Console::PrintDouble(const double d)
{
  cout << d;
}


void Console::DisplayPlayersHorses(const vector<int> & firstHorsesOfPlayers,
                                   const vector<int> & secondHorsesOfPlayers)
{
  cout << "First horses:  ";
  for (vector<int>::const_iterator iter = firstHorsesOfPlayers.begin();
    iter != firstHorsesOfPlayers.end(); iter++)
      cout << (*iter) << ";  ";

  cout << endl << "Second horses:  ";
  for (vector<int>::const_iterator iter = secondHorsesOfPlayers.begin();
    iter != secondHorsesOfPlayers.end(); iter++)
      cout << (*iter) << ";  ";

  cout << endl << endl;
}


void Console::DisplayGameState(const vector<int> & positionsOfHorses,
                               int diceNumber,
                               const vector<bool> & availableHorsesToMove,
                               int playersTurn,
                               int playersMove)
{
  cout << "Positions of horses:  ";
  for (unsigned int i = 0; i < positionsOfHorses.size(); i++)
    cout << i << ") " << positionsOfHorses[i] << ";  ";
  cout << endl << "Dice number = " << diceNumber << endl
       << "Player " << playersTurn << " moved the horse " << playersMove << '.' << endl;
  cout << "Available horses to move:  ";
  for (unsigned int i = 0; i < availableHorsesToMove.size(); i++)
    if (availableHorsesToMove[i])
      cout << i << "  ";

  cout << endl << endl;
}


void Console::ClearBuffer()
{
  while (cin.get() != '\n')
    continue;
}


void Console::DisplayPoints(const vector<int> & points, int choice, int numberOfGames)
{
  if (choice == Console::POINTS)
    cout << "Points:\n";
  else if (choice == Console::GAME_POINTS)
    cout << "Game points:\n";
  else if (choice == Console::TOURNAMENT_POINTS)
  {
    cout << "Tournament points:";
    if (numberOfGames > 0)
      cout << "  Games: " << numberOfGames;
    cout << endl;
  }

  for (unsigned int i = 0; i < points.size(); i++)
  {
    cout << "Player " << i << " score: " << points[i] << ";\n";
  }
  cout << endl;
}


void Console::PrintPointsToFile(const vector<int> & points, const char * fileName, int choice, int numberOfGames)
{
  ofstream fout(fileName);
  if (choice == Console::POINTS)
    fout << "Points:\n";
  else if (choice == Console::GAME_POINTS)
    fout << "Game points:\n";
  else if (choice == Console::TOURNAMENT_POINTS)
  {
    fout << "Tournament points:";
    if (numberOfGames > 0)
      fout << "  Games: " << numberOfGames;
    fout << endl;
  }

  for (unsigned int i = 0; i < points.size(); i++)
  {
    fout << "Player " << i << " score: " << points[i] << ";\n";
  }
  fout << endl;
  fout.close();
}


void Console::WarnThatTournamentIsNotComplete()
{
  cout << "Warning!\nThe tournament, you are trying to get the points from, is not yet complete!";
  cout << endl <<endl;
}


void Console::DisplayParameters(const vector<double> & parameterValues)
{
  cout << "Parameter values:\n";
  for (unsigned int i = 0; i < parameterValues.size(); i++)
    cout << i << ") " << parameterValues[i] << endl;
  cout << endl;
}


void Console::WaitForEnterButton()
{
  cout << "Press [ENTER] to continue...";
  cin.get();
  cout << endl;
}


void Console::DisplayGeneration(const vector<vector<double> > & generation, int generationNumber)
{
  cout << "Generation number: " << generationNumber << endl << endl;

  int individualNumber = 0;
  for(vector<vector<double> >::const_iterator individualIter = generation.begin();
    individualIter != generation.end(); individualIter++)
  {
    cout << "Individual: " << individualNumber << ":\n";
    int geneNumber = 0;
    for (vector<double>::const_iterator geneIter = individualIter->begin();
      geneIter != individualIter->end(); geneIter++)
    {
      cout << geneNumber << ")\t" << (*geneIter) << endl;
      geneNumber++;
    }
    cout << endl;
    individualNumber++;
  }
  cout << "\n// ----------------------------------------------------------- //\n\n";
}


void Console::PrintGenerationToFile(const vector<vector<double> > & generation, int generationNumber)
{
  ofstream fout;
  const char * DATA_OUT = "generations.txt";

  if (generationNumber == 0)
    fout.open(DATA_OUT, std::ios_base::trunc);
  else
    fout.open(DATA_OUT, std::ios_base::app);

  fout << "Generation number: " << generationNumber << endl << endl;

  int individualNumber = 0;
  for(vector<vector<double> >::const_iterator individualIter = generation.begin();
    individualIter != generation.end(); individualIter++)
  {
    fout << "Individual: " << individualNumber << ":\n";
    int geneNumber = 0;
    for (vector<double>::const_iterator geneIter = individualIter->begin();
      geneIter != individualIter->end(); geneIter++)
    {
      fout << geneNumber << ")\t" << (*geneIter) << endl;
      geneNumber++;
    }
    fout << endl;
    individualNumber++;
  }
  fout << "\n// ----------------------------------------------------------- //\n\n";

  fout.close();
}


void Console::DisplayVectorOfDoubles(const vector<double> & vect)
{
  for(int i = 0; i < (int) vect.size(); i++)
    cout << i << ")\t" << vect[i] << endl;
}


void Console::DisplayVectorOfInts(const vector<int> & vect)
{
  for(int i = 0; i < (int) vect.size(); i++)
    cout << i << ")\t" << vect[i] << endl;
}


void Console::DisplayDouble(double d)
{
  cout << d;
}
















