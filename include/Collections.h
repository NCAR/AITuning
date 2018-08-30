#include <iostream>
#include <vector>
#include <string>

#include "Variables.h"

using namespace std;

// Abstract class
class CollectionCreator
{
 public:
  virtual CollectionPerformanceVar createCollectionPerformanceVar();
  virtual CollectionControlVar createCollectionControlVar();
}

class CollectionPerformanceVar
{
 private:

  string transport_layer;
  string version;
  std::vector<PerformanceVariable> performanceVarsList;

public:

  CollectionPerformanceVar(string name, string ver)
  {
    transport_layer = name;
    version = ver;
  }
  
  void addPerformanceVariable(PerformanceVariable var)
  {
    performanceVarsList.push_back(var);
  }
}

class CollectionControlVar
{
 private:

  string transport_layer;
  string version;
  std::vector<ControlVariable> controlVarsList;
  
 public:

  CollectionControlVar(string name, string ver)
  {
    transport_layer = name;
    version = ver;
  }
  
  void addControlVariable(ControlVariable var)
  {
    controlVarsList.push_back(var);
  }
}
