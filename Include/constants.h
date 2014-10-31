//==============================================================================
// 
// Constants of the program
//
//==============================================================================


// Number of processor cores
#ifdef __linux__
#ifndef NB_PROC
#include <omp.h>
#define NB_PROC omp_get_num_procs()
#endif
#endif

// Constant infinity
#ifndef INFINITY
#define INFINITY 1e+50
#endif

// Precision of calculs
#ifndef EPSILON
#include <limits>
#define EPSILON 1e-7
#endif

// Constant to limit the time of a complete local search
#ifndef LOCAL_SEARCH_LIMIT
#define LOCAL_SEARCH_LIMIT 120
#endif

