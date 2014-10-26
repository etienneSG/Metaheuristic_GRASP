//==============================================================================
// 
// Class Genetic:
//   Perform an genetic algorithm on a population of localisation
//
//==============================================================================

#ifndef GENETIC_H
#define GENETIC_H

#include "localisation.h"
#include "kcombination.h"

class Genetic
{
public:
  /** Default constructor */
  Genetic();
  
  /** 
   * Constructor
   * @param iPopSize        : Size of the population
   * @param iapLocalisation : Array of the localisation composing the population
   * @param iMutationRate   : Mutation rate at each generation
   * @param iTransmitionRate: Rate of genes transmitted by the worst parent
   */
  Genetic(int iPopSize, Localisation ** iapLocalisation, double iMutationRate, double iTransmitionRate);
  
  /** Destructor */
  ~Genetic();
  
  /** Return the best localisation of the population */
  Localisation * GetBestLocalisation();
  
  /** Perform genetic algorithm */
  void Algorithm();

protected:
  int _PopSize;             // Size of the array of localisation
  Localisation ** _apLoc;   // Array of localisation
  double _MutationRate;     // Probability of mutation
  double _TransmitionRate;  // Rate of genes transmitted by the worst parent
  
  Kcombination _Population;     // To ramdomly chose in the population of localisation
  Kcombination _GeneToTransmit; // To ramdomly chose the gene to transmit
};


#endif
