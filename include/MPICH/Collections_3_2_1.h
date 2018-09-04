#include <iostream>
#include <vector>
#include <string>
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
  CollectionControlVar *control_vars_;
  CollectionPerformanceVar *performance_vars_;
public:
  CollectionCreatorMPICH();
  CollectionPerformanceVar *createCollectionPerformanceVar();
  CollectionControlVar *createCollectionControlVar();
};

#endif
