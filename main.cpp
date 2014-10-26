#include <stdio.h>   // Standard Input/Output Header
#include <stdlib.h>  // C Standard General Utilities Library
#include <omp.h>     // Open Multi-Processing Library
#include <algorithm>
#include <iostream>
#include <time.h>    //time
#include <string>

#include "testio.h"  // Test Input/Output Header
#include "localisation.h"
#include "kcombinationiterator.h"
#include "genetic.h"
#include "kcombination.h"


/**
 * Look for the best solution using the GRASP metaheuristics
 * and completing it with a genetic algorithm on the population.
 * @param iFile      : instance of the problem
 * @param iPopSize   : Size of the population of solution to generate and use
 * @param iMaxHamming: Maximal size of the Hamming distance in the neighbourhood search
 */
void GRASP(std::string iFile, int iPopSize, int iMaxHamming)
{
  Testio myTestio(iFile);
  Localisation ** myArrayLoc = iPopSize ? new Localisation*[iPopSize] : 0;
  
  // Creation of the population
  //#pragma omp parallel for schedule(dynamic,3)
  for (int i = 0; i < iPopSize; i++)
  {
    myArrayLoc[i] = new Localisation(myTestio);
    myArrayLoc[i]->Construction(iMaxHamming);
    //myArrayLoc[i]->LocalSearchAlgorithm(iMaxHamming);
  }
  
  // Genetic algorithm performed on the population
  Genetic myGenetic(iPopSize, myArrayLoc, 0.3, 0.5);
  myGenetic.Algorithm();
  
  // Local search around the best solution of the population
  Localisation * BestLoc = myGenetic.GetBestLocalisation();
  BestLoc->LocalSearchAlgorithm(iMaxHamming);
  
  BestLoc->PrintChosenFactories();
  
  // Clear memory
  if (myArrayLoc)
  {
    int j;
    for (j = 0; j < iPopSize; j++) {
      if (myArrayLoc[j])
	delete myArrayLoc[j];
      myArrayLoc[j] = 0;
    }
    delete [] myArrayLoc; myArrayLoc = 0;
  }

}


/** Mets tes tests dedans Tristan :) */
void Test_Tristan()
{
  Testio myTestio("TestCases/Input/cap71.txt");
  Localisation myLoc(myTestio);
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
  Testio myTestio("TestCases/Input/cap71.txt");
  Localisation ** myArrayLoc = new Localisation*[18];
  //#pragma omp parallel for schedule(dynamic,3)
  for (int i = 0; i < 18; i++)
  {
    myArrayLoc[i] = new Localisation(myTestio);
    myArrayLoc[i]->Construction(3);
    //myArrayLoc[i]->LocalSearchAlgorithm(3);
  }
  Genetic myGenetic(myTestio.NbFactories(), myArrayLoc, 0.3, 0.5);
  myGenetic.Algorithm();

  /*
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


int main (int argc, char const *argv[]){
  /* initialize random seed: */
  srand (time(NULL));
  
  Kcombination myComb(17,18);
  myComb.Random();
  myComb.Print();
  myComb.Random();
  myComb.Print();
  myComb.Random();
  myComb.Print();
  myComb.Random();
  myComb.Print();
  GRASP("TestCases/Input/capa.txt", 18, 3);

  //Test_Tristan();
  //Test_Etienne();
  
  return EXIT_SUCCESS;
}

