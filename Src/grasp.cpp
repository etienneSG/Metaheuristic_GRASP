#include "grasp.h"

#include <string.h>
#include <iostream>
#include "genetic.h"


GRASP::GRASP() :
  _PopSize(0),
  _MaxHamming(0),
  _RCLLength(0),
  _MutationRate(0),
  _TransmitionRate(0),
  _apLoc(0),
  _pBestLoc(0),
  _aEqualLoc(0)
{
}


GRASP::GRASP(std::string iFile, int iPopSize, int iMaxHamming, int iRCLLength, double iMutationRate, double iTransmitionRate) :
  _Instance(iFile),
  _PopSize(iPopSize),
  _MaxHamming(iMaxHamming),
  _RCLLength(iRCLLength),
  _MutationRate(iMutationRate),
  _TransmitionRate(iTransmitionRate),
  _apLoc(0),
  _pBestLoc(0),
  _aEqualLoc(0)
{
  if (_PopSize>0)
  {
    _apLoc = new Localisation*[_PopSize];
    memset(_apLoc, 0, _PopSize*sizeof(Localisation*));
    _aEqualLoc = new bool[_PopSize];
    memset(_aEqualLoc, 0, _PopSize*sizeof(bool));
  }
}


GRASP::~GRASP()
{
  if (_apLoc)
  {
    int j;
    for (j = 0; j < _PopSize; j++) {
      if (_apLoc[j])
	delete _apLoc[j];
      _apLoc[j] = 0;
    }
    delete [] _apLoc; _apLoc = 0;
  }

  if (_aEqualLoc)
    delete [] _aEqualLoc; _aEqualLoc = 0;

  _pBestLoc = 0;
}


void GRASP::Construction()
{
  // Greedy construction of each localisation
  #pragma omp parallel for schedule(dynamic,3)
  for (int i = 0; i < _PopSize; i++)
  {
    _apLoc[i] = new Localisation(_Instance);
    _apLoc[i]->Construction(_RCLLength);
  }

  // Optimisation: If there are equal solutions, only perform a local search for one
  QuickSort(_apLoc, 0, _PopSize-1);
  for (int i = 1; i < _PopSize; i++)
  {
    if (IsEqual(*(_apLoc[i-1]),*(_apLoc[i])))
      _aEqualLoc[i] = true;
  }

  // Local Search around each localisation
  #pragma omp parallel for schedule(dynamic,3)
  for (int i = 0; i < _PopSize; i++)
  {
    if (!_aEqualLoc[i])
      _apLoc[i]->LocalSearchAlgorithm(_MaxHamming);
  }

  // Optimisation: Remplace the localisation which were already computed
  for (int i = 0; i < _PopSize; i++)
  {
    if (_aEqualLoc[i])
    {
      if (_apLoc[i])
	delete _apLoc[i];
      _apLoc[i] = new Localisation(*(_apLoc[i-1]));
    }
  }

}


void GRASP::GeneticAlgorithm()
{
  Genetic myGenetic(_PopSize, _apLoc, 0.3, 0.5);
  myGenetic.Algorithm();

  // Local search around the best solution of the population
  _pBestLoc = myGenetic.GetBestLocalisation();
  _pBestLoc->LocalSearchAlgorithm(_MaxHamming);
}

void GRASP::PrintBestLocalisation()
{
  if (_pBestLoc)
    _pBestLoc->PrintChosenFactories();
  else
    std::cout << "You are stupid ! You did not perform algoithm !\n";
}
