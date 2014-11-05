//==============================================================================
// 
// Class Kcombination:
//   Randomly give a k-combinations from a set of n elements.
//
//==============================================================================

#ifndef KCOMBINATION_H
#define KCOMBINATION_H

class Kcombination
{
public:
  /** Default constructor */
  Kcombination();
  
  /**
   * Constructor
   * @param iK: number of elements to chose
   * @param iN: number of elements in the set
   */
  Kcombination(int iK,int iN);
  
  /** Destructor */
  ~Kcombination();

  /**
   * Return an array containing a ramdom k-combinations from a set of n elements
   * @return the array of k elements
   */
  int * Random();
   
  /** Print the k-combination */
  void Print();
   
protected:
  int _k;     // Number of elements to chose
  int _n;     // Number of elements in the set
  int * _a;   // Indexes of elements
};

#endif
