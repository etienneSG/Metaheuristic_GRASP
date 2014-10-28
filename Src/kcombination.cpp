#include "kcombination.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

Kcombination::Kcombination() :
_k(0),
_n(0),
_a(0)
{
}


Kcombination::Kcombination(int iK,int iN) :
_k(iK),
_n(iN),
_a(0)
{
  if (_n > 0)
  {
    _a = new int[_n];
    int i;
    for (i = 0; i < _n; i++)
      _a[i] = i;
  }
}


Kcombination::~Kcombination()
{
  if (_a)
    delete [] _a; _a = 0;
}

int * Kcombination::Random()
{
  int i;
  for (i = 0; i < _k && i < _n-1; i++) {
    int idx = (rand()%(_n-i)) + i;
    int tmp = _a[idx];
    _a[idx] = _a[i];
    _a[i] = tmp;
  }
  return _a;
}


void Kcombination::Print()
{
  int i;
  for(i = 0; i < _k; i++)
    std::cout << _a[i] << " ";
  std::cout << "\n";   
}
