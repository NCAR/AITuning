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
  CollectionControlVar *control_vars;
  CollectionPerformanceVar *performance_vars;
public:
  CollectionCreatorMPICH();
  CollectionPerformanceVar *createCollectionPerformanceVar(){;}  
  CollectionControlVal *createCollectionControlVar(){;}
};

#endif
