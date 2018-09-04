#include <iostream>
#include <string>
#include "MPI_T_Obj.h"
#include "MPICH/Variables.h"
#include "mpi.h"

using namespace std;

PerformanceVariableMPICH::PerformanceVariableMPICH(string name, int var_class, MPI_T_Manager *mpi_t_manager)
{
  int err=-1;
  name_ = name;
  mpi_t_manager_ = mpi_t_manager;
  var_class_ = var_class;
  err = MPI_T_pvar_get_index(name_.c_str(), var_class_, &index_);
  if(err != MPI_SUCCESS)
    perror ("Error in PerformanceVariable Contructor");
}

MPICHIntControlVariable::MPICHIntControlVariable(string name, int inc, MPI_T_Manager *mpi_t_manager)
{
  name_ = name;
  increment_ = inc;
  mpi_t_manager_ = mpi_t_manager;
  c_handle = mpi_t_manager_->getControlHandle(name_, &index_);
  value_ = mpi_t_manager_->getControlVar(c_handle);
}

int MPICHIntControlVariable::getValue()
{
  return value_;
}

void MPICHIntControlVariable::setValue(int val)
{
  mpi_t_manager_->setControlVar(c_handle, val);
  value_ = mpi_t_manager_->getControlVar(c_handle);
  if (value_ != val)
    perror("Set on control variable unsuccessful");
}

void MPICHIntControlVariable::setIncrement(int inc)
{
  increment_ = inc;
}

void MPICHIntControlVariable::incrementVar()
{
  int new_val = -1;
  new_val = value_ + increment_;
  setValue(new_val);
}

void MPICHIntControlVariable::printVar()
{
  printf("%s: %d\n",name_.c_str(),value_);
}

MPICHBoolControlVariable::MPICHBoolControlVariable(string name, MPI_T_Manager *mpi_t_manager)
{
  name_ = name;
  mpi_t_manager_ = mpi_t_manager;
  c_handle = mpi_t_manager_->getControlHandle(name_, &index_);
  if(c_handle == NULL)
    perror ("Error in ControlVariable Contructor");
  value_ = mpi_t_manager_->getControlVar(c_handle);
}

int MPICHBoolControlVariable::getValue()
{
  return value_;
}

void MPICHBoolControlVariable::setValue(int val)
{  
  mpi_t_manager_->setControlVar(c_handle, val == 0 ? 0 : 1);
  value_ = mpi_t_manager_->getControlVar(c_handle);
  if (value_ != val)
    perror("Set on control variable unsuccessful");
}

void MPICHBoolControlVariable::incrementVar()
{
  if(value_ == 1)
    {
      mpi_t_manager_->onOffControlVar(c_handle,0);
      value_ = 0;
    }
  else
    {
      mpi_t_manager_->onOffControlVar(c_handle,1);
      value_ = 1;
    }
}

void MPICHBoolControlVariable::printVar()
{
  printf("%s: %d\n",name_.c_str(),value_);
}
