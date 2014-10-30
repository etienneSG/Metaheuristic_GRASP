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



/** Mets tes tests dedans Tristan :) */
void Test_Tristan()
{
  Testio myTestio("TestCases/Input/cap71.txt");
  Traces myTraces;
  myTraces.Initialize(10, myTestio.NbFactories());
  Localisation myLoc(myTestio, 0, &myTraces);
  for (int i = 0; i < myTestio.NbFactories(); i++) {
    std::cout << myTestio.ImplantationCost(i) << std::endl;
  }
  myLoc.Construction(3);
  myLoc.PrintChosenFactories();
  myLoc.NeighbourhoodSearch(1);
  myLoc.PrintChosenFactories();
  myLoc.LocalSearchAlgorithm(2);
  myLoc.PrintChosenFactories();
}

/** Mets tes tests dedans Etienne :) */
void Test_Etienne()
{
/*
  int a;
  Testio myTestio("TestCases/Input/cap71.txt");
  Localisation ** myArrayLoc = new Localisation*[18];
  //#pragma omp parallel for schedule(dynamic,3)
  for (int i = 0; i < 18; i++)
  {
    myArrayLoc[i] = new Localisation(myTestio);
    myArrayLoc[i]->Construction(3);
    //myArrayLoc[i]->LocalSearchAlgorithm(3);
  }
  Genetic myGenetic(myTestio.NbFactories(), myArrayLoc, 0.3, 0.5, 1000, 0.001);
  myGenetic.Algorithm();
  
  
  while (!I.IsEnded())
  {
    std::cout << I(0) << I(1) << I(2) << std::endl;
    I.Print();
    ++I;
  }
  printf("Nombre de processeurs : %d \n",omp_get_num_procs());
  printf("Nombre de thread actifs : %d \n",omp_get_num_threads());
  int n;
  #pragma omp parallel for schedule(dynamic,2)
  for(n=0;n<18;n++){
    printf("Element %d traité par le thread %d \n",n,omp_get_thread_num());
  }
*/
}


void Run(std::string iArgument1)
{
  if (iArgument1=="GeneralStats")
    GeneralStats();
  else
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
  
    ExecTraces._BeginGenetic_UserTime = get_wall_time();
    ExecTraces._BeginGenetic_CPUTime = get_cpu_time();
    myGRASP.GeneticAlgorithm();
    ExecTraces._EndGenetic_CPUTime = get_cpu_time();
    ExecTraces._EndGenetic_UserTime = get_wall_time();

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
  }
}


int main (int argc, char const *argv[]){
  /* initialize random seed: */
  srand (time(NULL));

  std::string Argument1 = argv[1] ? argv[1] : "TestCases/Input/cap71.txt";

  Run(Argument1);
  //Test_Tristan();
  //Test_Etienne();
  

  return EXIT_SUCCESS;
}

