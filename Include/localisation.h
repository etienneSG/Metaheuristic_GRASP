//==============================================================================
// 
// Class Localisation: (chosen factories)
// - encoding of chosen factories
//
//==============================================================================

#ifndef LOCALISATION_H
#define LOCALISATION_H

#include "testio.h"
#include <assert.h>
#include <iostream>
#include "traces.h"

class Localisation
{
public:
  /** Constructor */
  Localisation();
  
  /**
   * Constructor from an instance
   * @param iInstance       : Instance of the problem
   * @param iChosenFactories: Array of chosen factories. 
   *    If null, every factory is initialize with false.
   * @param ipTraces        : Traces of the execution
   */
  Localisation(Testio &iInstance, bool* iChosenFactories, Traces * ipTraces);
  
  /**
   * Copy constructor
   * @param iLoc: Localisation to copy
   */
  Localisation(Localisation &iLoc);
  
  /** Destructor */
  ~Localisation();
  
  /**
   * Create the same localisation except for the the factory iFactory
   * @param iFactory: factory to complement (add/remove)
   * return: the localisation created
   */
  Localisation CreateComplementedLocalisation(int iFactory);
  
  /**
   * Add a factory to the chosen ones if it not belong to its and remove it otherwise
   * @param iFactory: Number of factory to add/remove
   */
  inline void Complement(int iFactory);
  
  /**
   * Reading and writing access to factories
   * @param iFactory : Index of the factory
   */
  inline bool& operator()(int iFactory);
  inline const bool& operator()(int iFactory)const;
  
  /**
   * Return the distance between a client and the closest chosen factory of the localisation
   * (Assume that each distance is positive.)
   * @param iClient: index of the client
   * @return: minimal distance to the factories if there are chosen factories
   *          +infinity otherwise
   */
  double MinDistance(int iClient);
	
  /**
   * Compute the cost of the localisation
   * @param iUpdate: if true actualize the member _AcutlLocalisationCost
   */
  double ComputeLocalisationCost(bool iUpdate = false);

  /** Return the number of factories in the localisation */
  inline int GetNbFactories();
  
  /** Return the cost of the localisation (without recalculate it) */
  inline double GetLocalisationCost();
  
  /**
   * Creates an intial factory with ony one factory for now (loop to be added)
   * @param iRCLLenght: Lenght of restricted candidate list
   */
  void Construction(int iRCLLength);

  /**
   * Search the best localisation in the neighbourhood of current localisation
   * and actualize the current localisation.
   * @param iNSize: size of the Neighbourhood
   * @return: true if a better solution was found
   *          false otherwise
   */
  bool NeighbourhoodSearch(int iNSize);
  
  /**
   * Perform the whole local search and actualize the localisation
   * @param iMaxSize: maximal size of the neighbourhood size (hamming distance)
   */
  void LocalSearchAlgorithm(int iMaxSize);
  
  /** Print the array of chosen factories */
  void PrintChosenFactories();
  
protected:
  Testio* _pInstance;             // Instance of the problem
  bool* _aChosenFactories;        // Array of chosen factories
  int _LastAddedFactory;          // Last factory added during the greedy construction
  double _ActualLocalisationCost; // Cost of the localisation
  
public:
  Traces * _pTraces; // Traces of the execution
};


/** Check if the localisations have the same chosen factories */
bool IsEqual(Localisation &iLoc1, Localisation &iLoc2);

/**
 * Sort a array of localisations
 * @param iapLoc: array of pointers on localisations
 * @param iBegin: index of begining of the array
 * @param iEnd  : index of end of the array
 */
void QuickSort(Localisation ** iapLoc, int iBegin, int iEnd);


//==============================================================================
// Implementation of inline methods
//==============================================================================


inline void Localisation::Complement(int iFactory) {
  assert(0 <= iFactory && iFactory < _pInstance->NbFactories());
  _aChosenFactories[iFactory] = !_aChosenFactories[iFactory];
}


inline double Localisation::GetLocalisationCost() {
  return _ActualLocalisationCost;
}


inline int Localisation::GetNbFactories() {
  return _pInstance->NbFactories();
}


inline bool& Localisation::operator()(int iFactory)
{
  assert(0<=iFactory && iFactory<_pInstance->NbFactories());
  return _aChosenFactories[iFactory];
}


inline const bool& Localisation::operator()(int iFactory)const
{
  assert(0<=iFactory && iFactory<_pInstance->NbFactories());
  return _aChosenFactories[iFactory];
}


#endif
