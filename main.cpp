#include <stdio.h>   // Standard Input/Output Header
#include <stdlib.h>  // C Standard General Utilities Library
#include <algorithm>
#include <iostream>
#include <time.h>    //time
#include <string>

#include "testio.h"  // Test Input/Output Header
#include "localisation.h"
#include "kcombinationiterator.h"
#include "genetic.h"
#include "kcombination.h"
#include "grasp.h"
#include "traces.h"
#include "generalstats.h"


void Run(std::string iArgument1, std::string iArgument2)
{
  if (iArgument2=="GeneralStats")
    GeneralStats(iArgument1);
  else if (iArgument2=="")
  {
    std::string Instance = iArgument1;
    int PopSize = 16;
    int MaxHamming = 3;
    int RCLLength = 3;
    double MutationRate = 0.1;
    double TransmitionRate = 0.2;
    int MaxNbGenerations = 200;
    double InfMeanDiff = 0.002;
    Traces ExecTraces;
    ExecTraces.Initialize(PopSize, MaxNbGenerations);
  
    GRASP myGRASP(Instance, PopSize, MaxHamming, RCLLength, MutationRate, TransmitionRate, MaxNbGenerations, InfMeanDiff, &ExecTraces);
    ExecTraces._BeginPopBuilt_UserTime = get_wall_time();
    ExecTraces._BeginPopBuilt_CPUTime = get_cpu_time();
    myGRASP.Construction();
    ExecTraces._EndPopBuilt_CPUTime = get_cpu_time();
    ExecTraces._EndPopBuilt_UserTime = get_wall_time();

    Localisation * TmpBestLoc = myGRASP.GetBestLocalisation();
    if (TmpBestLoc)
      ExecTraces._GRASPBestCost = TmpBestLoc->GetLocalisationCost();

    ExecTraces._BeginGenetic_UserTime = get_wall_time();
    ExecTraces._BeginGenetic_CPUTime = get_cpu_time();
    myGRASP.GeneticAlgorithm();
    ExecTraces._EndGenetic_CPUTime = get_cpu_time();
    ExecTraces._EndGenetic_UserTime = get_wall_time();

    TmpBestLoc = myGRASP.GetBestLocalisation();
    if (TmpBestLoc)
      ExecTraces._GeneticBestCost = TmpBestLoc->GetLocalisationCost();

    std::cout << "===== Parameters\n";
    std::cout << "Size of the population: " << PopSize << "\n";
    std::cout << "Maximal Hamming Distance: " << MaxHamming << "\n";
    std::cout << "Length of RCl (restricted candidates list): " << RCLLength << "\n";
    std::cout << "Mutation rate: " << MutationRate << "\n";
    std::cout << "Transmition rate: " << TransmitionRate << "\n";
    std::cout << "Maximal number of generation in genetic algorithm: " << MaxNbGenerations << "\n";
    std::cout << "Mean difference of the costs of the population from which stop: " << InfMeanDiff << "\n";
    std::cout << "\n";
    std::cout << "===== Result of the metaheuristic\n";
    myGRASP.PrintBestLocalisation();
    ExecTraces.PostTreatment();

    TmpBestLoc = 0;
  }
}


int main (int argc, char const *argv[]){
  /* initialize random seed: */
  srand (time(NULL));

  std::string Argument1 = argc>1 ? argv[1] : "TestCases/Input/cap71.txt";
  std::string Argument2 = argc>2 ? argv[2] : "";

  Run(Argument1, Argument2);

  return EXIT_SUCCESS;
}

