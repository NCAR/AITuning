#include <iostream>
#include "MPI_T_Obj.h"
#include "Probes.h"
#include "mpi.h"
#include "MPICH/Collections_3_2_1.h"
#include "MPICH/Variables.h"
#include "Controller.h"

using namespace std;

enum layer = {MPICH=1};

extern "C" 
{
  struct probe_wrapper
  {
    Probe *real_probe;
  };
  
  void AITuning_init(layer l)
  {
    string layer_version = "NONE";
    if(l == layer.MPICH)
      layer_version = "MPICH";
    
    AITuning_start(layer_version);
  }
}
