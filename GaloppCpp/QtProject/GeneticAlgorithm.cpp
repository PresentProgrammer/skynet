#include "GeneticAlgorithm.h"
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <QCoreApplication>

GeneticAlgorithm::GeneticAlgorithm(
                   // Genetic Algorithm parameters:
                   int number_of_individuals_in_generation,
                   int number_of_generations,
                   bool do_arithmetic_crossover,
                   double probability_of_crossover,
                   double probability_of_mutation,
                   bool do_elitism,
                   double mutation_strength,
                   int number_of_games_in_tournament,
                   int number_of_coef_in_eval_fun,
                   bool do_simulation_of_movement,
                   int simulate_move_distance,
                   int moves_look_forward,

                   // Game parameters:
                   int player_count,
                   int horse_count,
                   int distance,
                   int points_for_1_horse,
                   int points_for_2_horse,

                   // Technical attributes:
                   int wait_time,
                   bool console_output,
                   bool display_progress,
                   QProgressBar * progress_bar
                   ) :
                     NUMBER_OF_INDIVIDUALS_IN_GENERATION(number_of_individuals_in_generation),
                     NUMBER_OF_GENERATIONS(number_of_generations),
                     DO_ARITHMETIC_CROSSOVER(do_arithmetic_crossover),
                     PROBABILITY_OF_CROSSOVER(probability_of_crossover),
                     PROBABILITY_OF_MUTATION(probability_of_mutation),
                     DO_ELITISM(do_elitism),
                     MUTATION_STRENGTH(mutation_strength),
                     NUMBER_OF_GAMES_IN_TOURNAMENT(number_of_games_in_tournament),
                     NUMBER_OF_COEF_IN_EVAL_FUN(number_of_coef_in_eval_fun),
                     DO_SIMULATION_OF_MOVEMENT(do_simulation_of_movement),
                     SIMULATE_MOVE_DISTANCE(simulate_move_distance),
                     MOVES_LOOK_FORWARD(moves_look_forward),

                     PLAYER_COUNT(player_count),
                     HORSE_COUNT(horse_count),
                     DISTANCE(distance),
                     POINTS_FOR_1_HORSE(points_for_1_horse),
                     POINTS_FOR_2_HORSE(points_for_2_horse),

                     WAIT_TIME(wait_time),
                     CONSOLE_OUTPUT(console_output),
                     DISPLAY_PROGRESS(display_progress),
                     progressBar(progress_bar)
{}

bool GeneticAlgorithm::CheckParameters() const
{
  if (NUMBER_OF_GENERATIONS < 0 ||
      PROBABILITY_OF_CROSSOVER < 0.0 || PROBABILITY_OF_CROSSOVER > 1.0 ||
      PROBABILITY_OF_MUTATION < 0.0 || PROBABILITY_OF_MUTATION > 1.0 ||
      MUTATION_STRENGTH < 0.0 || MUTATION_STRENGTH > 1.0 ||
      NUMBER_OF_GAMES_IN_TOURNAMENT < 1 ||
      MOVES_LOOK_FORWARD < 0 ||
      SIMULATE_MOVE_DISTANCE < 0 || SIMULATE_MOVE_DISTANCE > 6 ||

      PLAYER_COUNT < 2 ||
      DISTANCE < 1 ||
      POINTS_FOR_1_HORSE < 1 ||
      POINTS_FOR_2_HORSE < 1 ||

      WAIT_TIME < 0
      )
  {
    Console::PrintErrorMessage(QString("Kļūda!"), QString("Viens vai vairāki parametri nav pieņemami!"));
    return false;
  }

  if (HORSE_COUNT * (HORSE_COUNT - 1) < PLAYER_COUNT)
  {
    Console::PrintErrorMessage(QString("Kļūda!"), QString("Zirgu skaits nav pietiekams šim spēlētāju skaitam!"));
    return false;
  }

  if (NUMBER_OF_INDIVIDUALS_IN_GENERATION < PLAYER_COUNT * 2)
  {
    Console::PrintErrorMessage(QString("Kļūda!"), QString("Indivīdu skaitam jābūt vismaz divreiz lielākam, nekā spēlētāju skaits!"));
    return false;
  }

  if (Game::MAX_DICE_NUMBER != 6)
  {
    Console::PrintErrorMessage(QString("Kļūda kodā!!!"), QString("Game::MAX_DICE_NUMBER jābūt vienādam ar 6!"));
    return false;
  }

  // if no errors were detected, the return true.
  return true;
}

void GeneticAlgorithm::GenerateFirstGeneration()
{
  // The method randomly generates the individuals of the first generation.

  // Create a vector with NUMBER_OF_COEF_IN_EVAL_FUN elements:
  vector<double> randomlyGeneratedIndividual(NUMBER_OF_COEF_IN_EVAL_FUN);

  // These 2 constants will serve for generating numbers in interval [-1; 1].
  const double lowerLimit = -1.0;
  const double intervalLength = 2.0;

  // Each iteration a new individual is randomly generated:
  for (int i = 0; i < NUMBER_OF_INDIVIDUALS_IN_GENERATION; i++)
  {
    // Each individual's gene is generated randomly (= random number in interval [-1; 1]):
    for (int j = 0; j < NUMBER_OF_COEF_IN_EVAL_FUN; j++)
      randomlyGeneratedIndividual[j] =
        lowerLimit + (double) rand() / (( (double) RAND_MAX / intervalLength));

    // Individual is added to the current generation:
    currentGenerationIndividuals.push_back(randomlyGeneratedIndividual);
  }

  currentGenerationNumber = 0;

  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("From GenerateFirstGeneration() method:\n");
    Console::DisplayGeneration(currentGenerationIndividuals, currentGenerationNumber);
    Console::WaitForEnterButton();
  }

  // Console::PrintGenerationToFile(currentGenerationIndividuals, currentGenerationNumber);
}


void GeneticAlgorithm::Evolve()
{
  // Method produces the next generation.
  // Includes selection, crossover, mutation and elitism (optional).
  // In the end of the method's execution the next generation becomes the current one.

  // Randomly select individuals from current generation to take part in 2 tournaments:
  // -------------------------------------------------------------- //

  // check for a bug:
  if ( (int) currentGenerationIndividuals.size() < PLAYER_COUNT * 2)
  {
    Console::PrintErrorMessage(QString("Kļūda kodā!!!"), QString("Zirgu skaits nav pietiekams šim spēlētāju skaitam!"));
    exit(EXIT_FAILURE);
  }

  // create vector which will hold the individuals of the next generation:
  vector<vector<double> > nextGenerationIndividuals;

  // this vector will be used to hold the indexes of selected individuals for tournaments:
  vector<int> selectedIndividualIndexes(PLAYER_COUNT * 2, -1);

  // vectors will be used to hold the indexes of individuals for particular tournaments:
  vector<int> firstTournamentIndividualIndexes(PLAYER_COUNT, -1);
  vector<int> secondTournamentIndividualIndexes(PLAYER_COUNT, -1);

  // Iteratively create the next generation:
  while ( (int) nextGenerationIndividuals.size() < NUMBER_OF_INDIVIDUALS_IN_GENERATION)
  {
    // fill selectedIndividualIndexes vector with '-1':
    fill(selectedIndividualIndexes.begin(), selectedIndividualIndexes.end(), -1);

    // randomly generate PLAYER_COUNT * 2 unique numbers and place them
    // in selectedIndividualIndexes:
    // ----------------------------------------------------------------------- //
    for (int i = 0; i < PLAYER_COUNT * 2; i++)
    {
      int randomIndex;
      int j;
      do
      {
        randomIndex = rand() % currentGenerationIndividuals.size();
        j = 0;
        while (j < i && randomIndex != selectedIndividualIndexes[j])
          j++;
      }
      while (j < i);
      selectedIndividualIndexes[i] = randomIndex;
    }
    // ======================================================================== //


    // Perform tournament selection:
    // ---------------------------------------------------------------- //

    // prepare vectors that are used to hold the indexes of individuals for particular tournaments:
    for (int i = 0; i < PLAYER_COUNT; i++)
    {
      firstTournamentIndividualIndexes[i] = selectedIndividualIndexes[i];
      secondTournamentIndividualIndexes[i] = selectedIndividualIndexes[i + PLAYER_COUNT];
    }

    // parameter for TournamentSelection() makes the method to return the best individual index
    const bool FIND_BEST = true;

    // First tournament:
    // -------------------------- //

    if (CONSOLE_OUTPUT)
    {
      Console::PrintMessage("From GeneticAlgorithm::Evolve():\n");
      Console::PrintMessage("Selected individuals for tournament 1:\n");
      Console::DisplayVectorOfInts(firstTournamentIndividualIndexes);
    }

    int firstParentIndex = this->TournamentSelection(firstTournamentIndividualIndexes,
                                              NUMBER_OF_GAMES_IN_TOURNAMENT, FIND_BEST);
    const vector<double> & firstParent =
      currentGenerationIndividuals[firstTournamentIndividualIndexes[firstParentIndex]];

    if (CONSOLE_OUTPUT)
    {
      Console::PrintMessage("From GeneticAlgorithm::Evolve():\n");
      Console::PrintMessage("The winner of the tournament 1: individual ");
      Console::DisplayDouble(firstTournamentIndividualIndexes[firstParentIndex]);
      Console::PrintMessage("\n");
    }

    // ========================= //

    // Second tournament:
    // --------------------------- //

    if (CONSOLE_OUTPUT)
    {
      Console::PrintMessage("From GeneticAlgorithm::Evolve():\n");
      Console::PrintMessage("Selected individuals for tournament 2:\n");
      Console::DisplayVectorOfInts(secondTournamentIndividualIndexes);
    }

    int secondParentIndex = this->TournamentSelection(secondTournamentIndividualIndexes,
                                            NUMBER_OF_GAMES_IN_TOURNAMENT, FIND_BEST);
    const vector<double> & secondParent =
      currentGenerationIndividuals[secondTournamentIndividualIndexes[secondParentIndex]];

    if (CONSOLE_OUTPUT)
    {
      Console::PrintMessage("From GeneticAlgorithm::Evolve():\n");
      Console::PrintMessage("The winner of the tournament 2: individual ");
      Console::DisplayDouble(secondTournamentIndividualIndexes[secondParentIndex]);
    }

    // ============================ //

    // ================================================================ //

    // Create children with unidentified chromosomes:
    vector<double> firstChild;
    vector<double> secondChild;

    // Crossover (probability shal be checked):
    // ---------------------------------------------------------- //
    double crossoverProbabilityCheck = (double) rand() / ((double) RAND_MAX);
    if (crossoverProbabilityCheck <= PROBABILITY_OF_CROSSOVER)
    {
      if (DO_ARITHMETIC_CROSSOVER)
        this->ArithmeticCrossover(firstParent, secondParent, firstChild, secondChild);
      else
        this->FlatCrossover(firstParent, secondParent, firstChild, secondChild);
    }
    else  // if no crossover has been made:
    {
      firstChild = firstParent;
      secondChild = secondParent;
    }

    // ========================================================== //

    // Mutation of children (probability is checked inside the method be checked):
    // ------------------------------------------------------ //
    if (PROBABILITY_OF_MUTATION > 0.0)
    {
      this->Mutation(firstChild);
      this->Mutation(secondChild);
    }

    // ====================================================== //

    // Add children to the next generation:
    nextGenerationIndividuals.push_back(firstChild);
    nextGenerationIndividuals.push_back(secondChild);


    // needed for GUI:
    QCoreApplication::processEvents();

  }  // while (nextGenerationIndividuals.size() < NUMBER_OF_INDIVIDUALS_IN_GENERATION)

  // If elitism is done, then find the best individual in the current generation
  // and copy it to the next generation:
  if (DO_ELITISM)
  {
    vector<double> bestIndividual = this->FindBestFromGeneration();
    nextGenerationIndividuals.push_back(bestIndividual);
  }

  // The next generation becomes the current generation:
  currentGenerationIndividuals = nextGenerationIndividuals;
}


int GeneticAlgorithm::TournamentSelection(const vector<int> & individualIndexes,
    const int number_of_games_in_tournament, const bool find_best) const
{
  // Method performs a tournament and returns the best or the worst individual.

  // Construct players, that will use evaluation function of the corresponding individuals:
  // ------------------------------------------------------------------------- //

  const Player ** tournamentPlayers = new const Player * [PLAYER_COUNT];
  for (int i = 0; i < PLAYER_COUNT; i++)
    tournamentPlayers[i] = new EvaluationFunctionPlayer(
            currentGenerationIndividuals[individualIndexes[i]],  // selected evaluation function
            DO_SIMULATION_OF_MOVEMENT,
            SIMULATE_MOVE_DISTANCE,
            MOVES_LOOK_FORWARD,
            CONSOLE_OUTPUT);

  // ======================================================================== //

  // Players take part in two tournaments:
  // The evaluation fucntion of the winner becomes a parent.
  // ------------------------------------------------------------------------- //
  Tournament * tournament = new Tournament(tournamentPlayers, PLAYER_COUNT,
    HORSE_COUNT, DISTANCE, POINTS_FOR_1_HORSE, POINTS_FOR_2_HORSE, number_of_games_in_tournament,
    WAIT_TIME, CONSOLE_OUTPUT);
  tournament->Compete();
  int neededIndividualIndex;
  if (find_best)
    neededIndividualIndex = tournament->ReturnBestPlayer();
  else
    neededIndividualIndex = tournament->ReturnWorstPlayer();

  // ======================================================================== //

  // Free memory:
  // ----------------------------------------- //
  delete tournament;

  for (int i = 0; i < PLAYER_COUNT; i++)
    delete tournamentPlayers[i];
  delete [] tournamentPlayers;

  // ========================================= //

  return neededIndividualIndex;
}


void GeneticAlgorithm::ArithmeticCrossover(const vector<double> & parent1, const vector<double> & parent2,
                                   vector<double> & child1, vector<double> & child2) const
{
  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("From GeneticAlgorithm::Crossover():\n");
    Console::PrintMessage("Parents:\nFirst parent:\n");
    Console::DisplayVectorOfDoubles(parent1);
    Console::PrintMessage("\n\nSecond parent:\n");
    Console::DisplayVectorOfDoubles(parent2);
  }

  // copy genes of parents to children:
  child1 = parent1;
  child2 = parent2;

  // choose random variable i [0; NUMBER_OF_COEF_IN_EVAL_FUN)
  // i - is an index of the gene which will be "crossovered"
  int i = rand() % NUMBER_OF_COEF_IN_EVAL_FUN;

  // randomly generate alpha [0; 1]:
  double alpha = (double) rand() / ((double) RAND_MAX);

  // make changes in chromosomes:
  child1[i] = alpha * parent2[i] + (1.0 - alpha) * parent1[i];
  child2[i] = alpha * parent1[i] + (1.0 - alpha) * parent2[i];

  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("alpha = ");
    Console::DisplayDouble(alpha);
    Console::PrintMessage(";  i = ");
    Console::DisplayDouble(i);
    Console::PrintMessage("\nChilren:\nFirst child:\n");
    Console::DisplayVectorOfDoubles(child1);
    Console::PrintMessage("\n\nSecond child:\n");
    Console::DisplayVectorOfDoubles(child2);
    Console::WaitForEnterButton();
  }
}


void GeneticAlgorithm::FlatCrossover(const vector<double> & parent1, const vector<double> & parent2,
                                   vector<double> & child1, vector<double> & child2) const
{
  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("From GeneticAlgorithm::FlatCrossover():\n");
    Console::PrintMessage("Parents:\nFirst parent:\n");
    Console::DisplayVectorOfDoubles(parent1);
    Console::PrintMessage("\n\nSecond parent:\n");
    Console::DisplayVectorOfDoubles(parent2);
  }

  // copy genes of parents to children:
  child1 = parent1;
  child2 = parent2;

  // Each gene of child chromosomes is calculated as a random number between
  // corresponding genes of parents
  for (int i = 0; i < NUMBER_OF_COEF_IN_EVAL_FUN; i++)
  {
    // randomly generate r1 and r2 in interval [0; 1]:
    double r1 = (double) rand() / ((double) RAND_MAX);
    double r2 = (double) rand() / ((double) RAND_MAX);

    // do flat crossover:
    child1[i] = r1 * parent1[i] + (1.0 - r1) * parent2[i];
    child2[i] = r2 * parent1[i] + (1.0 - r2) * parent2[i];

    if (CONSOLE_OUTPUT)
    {
      Console::DisplayDouble(i);
      Console::PrintMessage(") r1 = ");
      Console::DisplayDouble(r1);
      Console::PrintMessage(";  r2 = ");
      Console::DisplayDouble(r2);
      Console::PrintMessage(";\n");
    }
  }

  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("\nChilren:\nFirst child:\n");
    Console::DisplayVectorOfDoubles(child1);
    Console::PrintMessage("\n\nSecond child:\n");
    Console::DisplayVectorOfDoubles(child2);
    Console::WaitForEnterButton();
  }
}


void GeneticAlgorithm::Mutation(vector<double> & chromosome) const
{
  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("From GeneticAlgorithm::Mutation():\n");
    Console::PrintMessage("Before mutation:\n");
    Console::DisplayVectorOfDoubles(chromosome);
  }

  // Change each gene with a fixed probability:
  for (vector<double>::iterator geneIter = chromosome.begin();
    geneIter != chromosome.end(); geneIter++)
  {
    double mutationProbabilityCheck = (double) rand() / ((double) RAND_MAX);
    if (mutationProbabilityCheck <= PROBABILITY_OF_MUTATION)
    {
      // generate a random number from [-MUTATION_STRENGTH; +MUTATION_STRENGTH]
      double mutationValue =
        -MUTATION_STRENGTH + (double) rand() / (( (double) RAND_MAX / (MUTATION_STRENGTH * 2)));

      // Add the generated number to the gene value:
      (*geneIter) += mutationValue;

      // The value of the gene shall stay in interval [-1; +1].
      if ((*geneIter) < -1.0)
        (*geneIter) = -1.0;
      else if ((*geneIter) > 1.0)
        (*geneIter) = 1.0;
    }
  }

  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("After mutation:\n");
    Console::DisplayVectorOfDoubles(chromosome);
    Console::WaitForEnterButton();
  }
}


vector<double> GeneticAlgorithm::FindBestFromGeneration(const bool is_last_generation) const
{
  // The method finds the best individual from the current generation by performing
  // tournaments. Individuals are selected randomly for competing in a tournament.
  // Each tournament one worst individual is dropped from the set of individiuals
  // that have a right to compete, until PLAYER_COUNT individuals are left in the set. Then
  // these individuals compete in the last tournament, and the winner is assumed to be the
  // best (the fittest) individual.

  vector<int> individualsThatCanCompete;
  for (int i = 0; i < (int) currentGenerationIndividuals.size(); i++)
    individualsThatCanCompete.push_back(i);

  // this vector will be used to hold the indexes of randomly selected
  // individualsThatCanCompete vector elements:
  vector<int> selectedIndividualThatCanCompeteIndexes(PLAYER_COUNT, -1);

  // this vector will hold indexes of individuals that will compete in a tournament:
  vector<int> tournamentIndividualIndexes(PLAYER_COUNT, -1);

  while ( (int) individualsThatCanCompete.size() > PLAYER_COUNT)
  {
    // fill selectedIndividualIndexes vector with '-1':
    fill(selectedIndividualThatCanCompeteIndexes.begin(),
      selectedIndividualThatCanCompeteIndexes.end(), -1);

    // randomly generate PLAYER_COUNT unique numbers and place them
    // in selectedIndividualThatCanCompeteIndexes:
    // ----------------------------------------------------------------------- //
    for (int i = 0; i < PLAYER_COUNT; i++)
    {
      int randomIndex;
      int j;
      do
      {
        randomIndex = rand() % individualsThatCanCompete.size();
        j = 0;
        while (j < i && randomIndex != selectedIndividualThatCanCompeteIndexes[j])
          j++;
      }
      while (j < i);
      selectedIndividualThatCanCompeteIndexes[i] = randomIndex;
    }
    // ======================================================================== //

    // Prepare tournamentIndividualIndexes vector:
    for (int i = 0; i < PLAYER_COUNT; i++)
      tournamentIndividualIndexes[i] =
        individualsThatCanCompete[selectedIndividualThatCanCompeteIndexes[i]];

    if (CONSOLE_OUTPUT)
    {
      Console::PrintMessage("From GeneticAlgorithm::FindBestFromGeneration():\n");
      Console::PrintMessage("Selected individuals for tournament:\n");
      Console::DisplayVectorOfInts(tournamentIndividualIndexes);
    }

    // parameter for TournamentSelection() makes the method to return the worst individual index
    const bool FIND_WORST = false;

    // parameter for TournamentSelection() determines the number of games in the tournament.
    int numberOfGamesInTournament;
    if (is_last_generation)
      numberOfGamesInTournament = NUMBER_OF_GAMES_IN_TOURNAMENT * 10;
    else
      numberOfGamesInTournament = NUMBER_OF_GAMES_IN_TOURNAMENT;

    // find the worst individual from the selected few by performing a tournament:
    int worstIndividualIndex = this->TournamentSelection(tournamentIndividualIndexes,
                                       numberOfGamesInTournament, FIND_WORST);

    if (CONSOLE_OUTPUT)
    {
      Console::PrintMessage("From GeneticAlgorithm::FindBestFromGeneration():\n");
      Console::PrintMessage("Individual No ");
      Console::DisplayDouble(individualsThatCanCompete[selectedIndividualThatCanCompeteIndexes[worstIndividualIndex]]);
      Console::PrintMessage(" is dropped.\n");
      Console::WaitForEnterButton();
    }

    // Drop the individual, that performed the worst in the tournament:
    individualsThatCanCompete.erase(
      individualsThatCanCompete.begin() + selectedIndividualThatCanCompeteIndexes[worstIndividualIndex]);

    // needed for GUI:
    QCoreApplication::processEvents();
  }

  // Now only PLAYER_COUNT individuals are left, and they will compete for the 1st place:
  // --------------------------------------------------------------------------------------- //

  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("From GeneticAlgorithm::FindBestFromGeneration():\n");
    Console::PrintMessage("Selected individuals for FINAL tournament:\n");
    Console::DisplayVectorOfInts(individualsThatCanCompete);
  }

  // parameter for TournamentSelection() makes the method to return the best individual index
  const bool FIND_BEST = true;

  // parameter for TournamentSelection() determines the number of games in the tournament.
  int numberOfGamesInTournament;
  if (is_last_generation)
    numberOfGamesInTournament = NUMBER_OF_GAMES_IN_TOURNAMENT * 30;
  else
    numberOfGamesInTournament = NUMBER_OF_GAMES_IN_TOURNAMENT * 10;

  int bestIndividualIndex = this->TournamentSelection(individualsThatCanCompete,
                                      numberOfGamesInTournament, FIND_BEST);
  const vector<double> & bestIndividual =
    currentGenerationIndividuals[individualsThatCanCompete[bestIndividualIndex]];

  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("From GeneticAlgorithm::FindBestFromGeneration():\n");
    Console::PrintMessage("The winner of the FINAL tournament: individual ");
    Console::DisplayDouble(individualsThatCanCompete[bestIndividualIndex]);
    Console::PrintMessage("\n");
  }

  return bestIndividual;

  // ======================================================================================= //
}


vector<double> GeneticAlgorithm::ExecuteAlgorithm()
{
  if (!this->CheckParameters())
    return vector<double> (0);

  this->GenerateFirstGeneration();

  // Variables are used only if DISPLAY_PROGRESS = true:
  time_t beginning;
  time_t ending;
  double seconds;

  // get current time:
  if (DISPLAY_PROGRESS)
    time(&beginning);

  while (currentGenerationNumber < NUMBER_OF_GENERATIONS)
  {
    Evolve();
    currentGenerationNumber++;

    // For testing:
    if (CONSOLE_OUTPUT)
    {
      Console::PrintMessage("From GeneticAlgorithm::ExecuteAlgorithm():\n");
      Console::DisplayGeneration(currentGenerationIndividuals, currentGenerationNumber);
      Console::WaitForEnterButton();
    }

    // For progress monitoring:
    if (DISPLAY_PROGRESS)
    {
      Console::PrintMessage("current generation number = ");
      Console::DisplayDouble(currentGenerationNumber);

      // get current time:
      time(&ending);

      // calculate the time difference in seconds:
      seconds = difftime(ending, beginning);
      Console::PrintMessage(". Evolved in ");
      Console::DisplayDouble(seconds);
      Console::PrintMessage(" seconds;\n");

      // time will be used in the next iteration
      beginning = ending;
    }

    if (progressBar != 0)
    {
      progressBar->setValue(currentGenerationNumber * 100 / NUMBER_OF_GENERATIONS);
      QCoreApplication::processEvents();
    }
  }

  if (DISPLAY_PROGRESS)
    Console::PrintMessage("Done!\n");

  // Save generation in the file:
  Console::PrintGenerationToFile(currentGenerationIndividuals, currentGenerationNumber);

  const bool is_last_generation = true;

  return this->FindBestFromGeneration(is_last_generation);
}


bool GeneticAlgorithm::SaveResult(const vector<double> & eval_fun, const string & file_name) const
{
  // Method saves the evaluation function coefficients in the file. Also the method saves
  // all parameters of Genetic Algorithms that were used to get these coefficients.

  ofstream fout(file_name.c_str());
  if (!fout.is_open())
    return false;

  for(vector<double>::const_iterator coefIter = eval_fun.begin();
    coefIter != eval_fun.end(); coefIter++)
  {
    fout << (*coefIter) << endl;
  }

  fout << endl;
  fout << "# Parameters, that were used:\n"
       << "#   Genetic Algorithm parameters:\n"
       << "#     NUMBER_OF_INDIVIDUALS_IN_GENERATION = " << NUMBER_OF_INDIVIDUALS_IN_GENERATION << endl
       << "#     NUMBER_OF_GENERATIONS = " << NUMBER_OF_GENERATIONS << endl
       << "#     DO_ARITHMETIC_CROSSOVER = " << DO_ARITHMETIC_CROSSOVER << endl
       << "#     PROBABILITY_OF_CROSSOVER = " << PROBABILITY_OF_CROSSOVER << endl
       << "#     PROBABILITY_OF_MUTATION = " << PROBABILITY_OF_MUTATION << endl
       << "#     DO_ELITISM = " << DO_ELITISM << endl
       << "#     MUTATION_STRENGTH = " << MUTATION_STRENGTH << endl
       << "#     NUMBER_OF_GAMES_IN_TOURNAMENT = " << NUMBER_OF_GAMES_IN_TOURNAMENT << endl
       << "#     NUMBER_OF_COEF_IN_EVAL_FUN = " << NUMBER_OF_COEF_IN_EVAL_FUN << endl
       << "#     DO_SIMULATION_OF_MOVEMENT = " << DO_SIMULATION_OF_MOVEMENT << endl
       << "#     SIMULATE_MOVE_DISTANCE = " << SIMULATE_MOVE_DISTANCE << endl
       << "#     MOVES_LOOK_FORWARD = " << MOVES_LOOK_FORWARD << endl
       << "#" << endl
       << "#   Game parameters:\n"
       << "#     PLAYER_COUNT = " << PLAYER_COUNT << endl
       << "#     HORSE_COUNT = " << HORSE_COUNT << endl
       << "#     DISTANCE = " << DISTANCE << endl
       << "#     POINTS_FOR_1_HORSE = " << POINTS_FOR_1_HORSE << endl
       << "#     POINTS_FOR_2_HORSE = " << POINTS_FOR_2_HORSE << endl;

  fout.close();
  return true;
}



bool GeneticAlgorithm::AddIndividualToGeneration(const vector<double> & newIndividual)
{
  // Method adds an individual to the current generation:
  // Method returns false if the new individual has wrong number of genes (number of
  // coefficients in evaluation function), and true otherwise.

  if ( (int) newIndividual.size() != NUMBER_OF_COEF_IN_EVAL_FUN)
    return false;
  else
  {
    currentGenerationIndividuals.push_back(newIndividual);
    return true;
  }
}


























