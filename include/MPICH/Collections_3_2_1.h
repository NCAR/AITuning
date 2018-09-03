#include <iostream>
#include <vector>
#include <string>

#include "Variables.h"
#include "Collections.h"
#include "MPICH/Variables.h"
#include "MPI_T_Obj.h"

using namespace std;

#ifndef COLLECTIONS_3_2_1_H
#define COLLECTIONS_3_2_1_H

class CollectionCreatorMPICH : public CollectionCreator
{
private:
  MPI_T_Manager mpi_t_manager;
public:
  CollectionCreatorMPICH()
  {
    mpi_t_manager.initialize_MPI_T();
  }
  
  CollectionPerformanceVar createCollectionPerformanceVar()
  {
    CollectionPerformanceVar perf_collection("MPICH","3.2.1");
    
    return perf_collection;
  }
  
  CollectionControlVal createCollectionControlVar()
  {
    CollectionControlVar control_collection("MPICH","3.2.1");

    
    control_collection.addControlVariable();
  
    return control_collection;
  }
  
};

#endif
