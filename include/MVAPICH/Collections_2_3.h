#include <iostream>
#include <vector>
#include <string>
#include "Collections.h"
#include "MVAPICH/Variables.h"
#include "MPI_T_Obj.h"

using namespace std;

#ifndef COLLECTIONS_2_3_H
#define COLLECTIONS_2_3_H

class CollectionCreatorMVAPICH : public CollectionCreator
{
private:
  MPI_T_Manager mpi_t_manager;
  CollectionControlVar *control_vars_;
  CollectionPerformanceVar *performance_vars_;
public:
  CollectionCreatorMVAPICH();
  CollectionPerformanceVar *createCollectionPerformanceVar();
  CollectionControlVar *createCollectionControlVar();
};

#endif
