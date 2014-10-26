//==============================================================================
// 
// Class Testio: (Test Input/Output Header)
// - test instance reading
// - output writing
//
//==============================================================================

#ifndef TESTIO_H
#define TESTIO_H

#include "array2d.h"
#include <string>
#include <assert.h>


class Testio
{
public:
  /** Default constructor */
  Testio();
  
  /**
   * Constructor from a file
   * @param iFile: file containing the instance of the proble
   */
  Testio(std::string iFile);
  
  /** Destructor */
  ~Testio();
  
  /** Return the number of clients */
  inline int NbClients();

  /** Return the number of factories */
  inline int NbFactories();
  
  /**
   * Return the array of implantation costs of factories
   * @param iFactory: index of the factory implanted
   */
  inline double ImplantationCost(int iFactory);
  
  /**
   * Return the double array of distance between clients and factories
   * @param iClient : index of the client
   * @param iFactory: index of the factory
   */
  inline double DistanceCF(int iClient, int iFactory);
  
protected:
  int _NbClients;                 // Number of clients
  int _NbFactories;               // Number of factories
  double* _aImplantationCost;     // Array of implantation costs of factories
  Array2d _ClientFactoryDistance; // Array of distances between clients and factories
};


//==============================================================================
// Implementation of inline methods
//==============================================================================

inline int Testio::NbClients() {
  return _NbClients;
}

inline int Testio::NbFactories() {
  return _NbFactories;
}

inline double Testio::ImplantationCost(int iFactory) {
  assert(0 <= iFactory && iFactory < _NbFactories);
  return _aImplantationCost[iFactory];
}

inline double Testio::DistanceCF(int iClient, int iFactory) {
  return _ClientFactoryDistance(iClient, iFactory);
}


#endif
