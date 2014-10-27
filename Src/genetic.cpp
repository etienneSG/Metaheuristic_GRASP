#include "genetic.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


#ifndef INFINITY
#define INFINITY 1e+50
#endif


Genetic::Genetic() :
  _PopSize(0),
  _apLoc (0),
  _MutationRate(0),
  _TransmitionRate(0)
{
}


Genetic::Genetic(int iPopSize, Localisation ** iapLocalisation, double iMutationRate, double iTransmitionRate) :
  _PopSize(iPopSize),
  _apLoc(iapLocalisation),
  _MutationRate(iMutationRate),
  _TransmitionRate(iTransmitionRate),
  _Population(iPopSize-1, iPopSize),
  _GeneToTransmit( int(iTransmitionRate*iapLocalisation[0]->GetNbFactories()), iapLocalisation[0]->GetNbFactories() )
{
}


Genetic::~Genetic()
{
  _apLoc = 0;
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


  int Compt = 0;        // Number of generations
  double Average = 0;   // Average of cost
  double MeanDiff = 1;  // Mean difference of the costs in the population

  while(Compt<1000 && MeanDiff > 0.005) 
  {
    Compt++;
    // Create the list of individuals to cross. (Shuffle the indexes)
    int * IdxOfIndividuals = _Population.Random();

    int i;
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
      Individual2->ComputeLocalisationCost();
    }

    // Shutoff parameter
    Average = 0;
    MeanDiff = 0;
    for (i = 0; i < _PopSize; i++)
      Average+=_apLoc[i]->GetLocalisationCost();
    Average/=_PopSize;
    for (i = 0; i < _PopSize; i++)
      MeanDiff+=fabs(_apLoc[i]->GetLocalisationCost()-Average);
    MeanDiff/=(_PopSize*Average);
  }
}
