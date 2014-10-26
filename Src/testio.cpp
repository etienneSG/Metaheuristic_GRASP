#include "testio.h"

#include <fstream>
#include <iostream>
#include <string.h>
#include <string>

Testio::Testio():
  _NbClients(0),
  _NbFactories(0),
  _aImplantationCost(0),
  _ClientFactoryDistance()
{
}
  
Testio::~Testio()
{
  if (_aImplantationCost)
    delete [] _aImplantationCost; _aImplantationCost=0;
}


Testio::Testio(std::string iFile):
  _NbClients(0),
  _NbFactories(0),
  _aImplantationCost(0),
  _ClientFactoryDistance()
{
  std::ifstream fichier(iFile.c_str(), std::ios::in); // Openning file

  if(fichier)
  {
    fichier >> _NbFactories >> _NbClients;

    // Creation of the array of implantation costs
    if (_NbFactories) {
      _aImplantationCost = new double[_NbFactories];
      memset(_aImplantationCost, 0, _NbFactories*sizeof(double));
    }

    // Creation of the array of distance costs
    _ClientFactoryDistance.Resize(_NbClients, _NbFactories);

    // Filling implantation costs
    int i;
    for (i = 0; i < _NbFactories; i++)
    {
      double capacity, cost;
      fichier >> capacity >> cost;
      _aImplantationCost[i]=cost;
    }

    // Filling distance between clients and factories
    for (i = 0; i < _NbClients; i++)
    {
      double demand, distance;
      fichier >> demand;
      int j;
      for (j = 0; j < _NbFactories; j++)
      {
	fichier >> distance;
	_ClientFactoryDistance(i,j) = distance;
      }
    }

    fichier.close(); // Closing file

  }
  else
  {
    std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
  }
}

