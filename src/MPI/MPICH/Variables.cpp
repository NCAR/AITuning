#include <iostream>
#include <string>
#include "MPI_T_Obj.h"
#include "MPICH/Variables.h"
#include "mpi.h"

using namespace std;

PerformanceVariableMPICH::PerformanceVariableMPICH(string name, int var_class, MPI_T_Manager *mpi_t_manager)
{
  int err;
  name_ = name;
  mpi_t_manager_ = mpi_t_manager;
  var_class_ = var_class;
  err = MPI_T_pvar_get_index(name_.c_str(), var_class_, &index_);
  if(err != MPI_SUCCESS)
    perror ("Error in PerformanceVariable Contructor");
}

PerformanceVariableLog PerformanceVariableMPICH::getPerformanceVariableLog(){;}

void PerformanceVariableMPICH::logPerformanceValue(double val){
  log_.logValue(val);
}

void PerformanceVariableMPICH::saveLog(){
  ;
}

ControlVariableMPICHInt::ControlVariableMPICHInt(string name, int inc, MPI_T_Manager *mpi_t_manager)
{
  int err;
  name_ = name;
  increment_ = inc;
  mpi_t_manager_ = mpi_t_manager;
  c_handle = mpi_t_manager_->getControlHandle(name_, &index_);
  if(err != MPI_SUCCESS)
    perror ("Error in ControlVariable Contructor");
  value_ = mpi_t_manager_->getControlVar<int>(c_handle);
}

int ControlVariableMPICHInt::getValue()
{
  return value_;
}

void ControlVariableMPICHInt::setValue(int val)
{
  mpi_t_manager_->setControlVar<int>(c_handle, val);
  value_ = mpi_t_manager_->getControlVar<int>(c_handle);
  if (value_ != val)
    perror("Set on control variable unsuccessful");
}

void ControlVariableMPICHInt::setIncrement(int inc)
{
  increment_ = inc;
}

void ControlVariableMPICHInt::incrementVar()
{
  int new_val;
  new_val = value_ + increment_;
  setValue(new_val);
}

void ControlVariableMPICHInt::printVar()
{
  printf("%s: %d\n",name_.c_str(),value_);
}
