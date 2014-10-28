#include "genetic.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#ifdef __linux__
#include <omp.h> // Open Multi-Processing Library (Linux only)
#endif

#ifndef INFINITY
#define INFINITY 1e+50
#endif


Genetic::Genetic() :
_PopSize(0),
_apLoc (0),
_MutationRate(0),
_TransmitionRate(0),
_MaxNbGenerations(0),
_InfMeanDiff(0),
_Average(0),
_MeanDiff(0),
_pTraces(0)
{
}


Genetic::Genetic(int iPopSize, Localisation ** iapLocalisation, double iMutationRate, double iTransmitionRate, int iMaxNbGenerations, double iInfMeanDiff, Traces * ipTraces) :
_PopSize(iPopSize),
_apLoc(iapLocalisation),
_MutationRate(iMutationRate),
_TransmitionRate(iTransmitionRate),
_MaxNbGenerations(iMaxNbGenerations),
_InfMeanDiff(iInfMeanDiff),
_Population(iPopSize-1, iPopSize),
_GeneToTransmit( int(iTransmitionRate*iapLocalisation[0]->GetNbFactories()), iapLocalisation[0]->GetNbFactories() ),
_Average(0),
_MeanDiff(0),
_pTraces(ipTraces)
{
}


Genetic::~Genetic()
{
  _apLoc = 0;
  _pTraces = 0;
}


Localisation * Genetic::GetBestLocalisation()
{
  int IdxBestLoc = -1;
  double BestCost = INFINITY;
  int i;
  for (i = 0; i < _PopSize; i++)
  {
    if (_apLoc[i] && BestCost > _apLoc[i]->GetLocalisationCost())
    {
      IdxBestLoc = i;
      BestCost = _apLoc[i]->GetLocalisationCost();
    }
  }
  return IdxBestLoc==-1 ? 0 : _apLoc[IdxBestLoc];
}


void Genetic::ComputeAverageAndMeanDiff()
{
  double average = 0;
  double meandiff = 0;
  int i;
  #ifdef __linux__
  #pragma omp parallel for reduction(+:average) schedule(static,1)
  #endif
  for (i = 0; i < _PopSize; i++)
    average = average + _apLoc[i]->GetLocalisationCost();
  _Average = average/_PopSize;
  #ifdef __linux__
  #pragma omp parallel for reduction(+:meandiff) schedule(static,1)
  #endif
  for (i = 0; i < _PopSize; i++)
    meandiff+=fabs(_apLoc[i]->GetLocalisationCost()-_Average);
  _MeanDiff = meandiff/(_PopSize*_Average);
}


void Genetic::Algorithm()
{
  // Error detection
  if (!_apLoc)
  {
    std::cout << "Population is empty : you have not built it. Do it before perform genetic algorithm.\n";
    return;
  }
  else
  {
    int i;
    for (i = 0; i < _PopSize; i++)
    {
      if (!_apLoc[i])
      {
        std::cout << "Localisation " << i << " was not built. Do it before perform genetic algorithm.\n";
        return;
      }
    }
  }
  
  
  int Compt = 0; // Number of generations
  ComputeAverageAndMeanDiff();
  _pTraces->AddMeanDiff(_MeanDiff);
  
  while(Compt<_MaxNbGenerations && _MeanDiff > _InfMeanDiff) 
  {
    Compt++;
    // Create the list of individuals to cross. (Shuffle the indexes)
    int * IdxOfIndividuals = _Population.Random();
    
    int i;
    //#ifdef __linux__
    //#pragma omp parallel for schedule(dynamic,_PopSize/8)
    //#endif
    for (i = 0; i < int(_PopSize/2); i++)
    {
      Localisation * Individual1 = _apLoc[ IdxOfIndividuals[2*i] ];
      Localisation * Individual2 = _apLoc[ IdxOfIndividuals[2*i+1] ];
      
      // Check that Indivudual1 is better than Individual2
      if (Individual1->GetLocalisationCost() > Individual2->GetLocalisationCost())
      {
        Individual1 = _apLoc[ IdxOfIndividuals[2*i+1] ];
        Individual2 = _apLoc[ IdxOfIndividuals[2*i] ];
      }
      
      //reproduction: replace random factories of Individual2 by some of Individual1
      int NbGenesToTransmit = int(_TransmitionRate*_apLoc[0]->GetNbFactories());
      int * IdxOfGenes = _GeneToTransmit.Random();
      int j;
      for (j = 0; j < NbGenesToTransmit; j++)
      {
        (*Individual2)(IdxOfGenes[j]) = (*Individual1)(IdxOfGenes[j]);
      }
      
      // Mutation
      if (rand()*1./RAND_MAX < _MutationRate)
        Individual2->Complement( rand()%_apLoc[0]->GetNbFactories() );
      
      // Update the cost of Individual2
      Individual2->ComputeLocalisationCost(true);
      
      Individual1 = 0;
      Individual2 = 0;
    }
    
    // Shutoff parameter
    ComputeAverageAndMeanDiff();
    _pTraces->AddMeanDiff(_MeanDiff);
  }
}
