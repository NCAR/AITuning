#include <iostream>
#include "MPI_T_Obj.h"
#include "Probes.h"
#include "mpi.h"
#include "MPICH/Collections_3_2_1.h"
#include "MPICH/Variables.h"
#include "Controller.h"
#include "C_wrapper.h"

using namespace std;

enum layer = {MPICH=1};

extern "C" 
{
  Probe_C newProbe(PerformanceVariableC perf_var)
  {
    return reinterpret_cast<void*>(new SingleProbe(reinterpret_cast<PerformanceVariable *>perf_var));
  }

  PerformanceVariable_C newPerfVar(char* name, char* filename)
  {
    return reinterpret_cast<void*>(new UserDefinedPerformanceVar(name,filename));
  }
  
  void registerValue(Probe_C probe, double value)
  {
    reinterpret_cast<SingleProbe *>(probe)->registerValue(value);
  }
  
  void AITuning_init(layer l)
  {
    string layer_version = "NONE";
    if(l == layer.MPICH)
      layer_version = "MPICH";
    
    AITuning_start(layer_version);
  }
}
