#include <iostream>
#include <string>
#include "../Variables.h"
#include "../MPI_T_Obj.h"
#include "mpi.h"

using namespace std;

#ifndef MPICH_VARS_H
#define MPICH_VARS_H

class PerformanceVariableMPICH : public PerformanceVariable
{
private:
  string name_;
  int index_;
  int var_class_;
  MPI_Datatype dt_;
  MPI_T_Manager *mpi_t_manager_ = NULL;
public:
  PerformanceVariableMPICH(string name, int var_class, MPI_T_Manager *mpi_t_manager);
  PerformanceVariableLog getPerformanceVariableLog();
  void logPerformanceValue(double val);
  void saveLog();
};

class MPICHIntControlVariable : public ControlVariable<int>
{
private:
  string name_;
  int index_;
  int value_; //Read from MPI_T
  int increment_;
  MPI_Datatype dt_;
  MPI_T_Manager *mpi_t_manager_ = NULL;
  MPI_T_cvar_handle c_handle;
public:
  MPICHIntControlVariable(string name, int inc, MPI_T_Manager *mpi_t_manager);
  int getValue();
  void setValue(int val);
  void setIncrement(int inc);
  void incrementVar();
  void printVar();
};
#endif
