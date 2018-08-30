#include <iostream>
#include <vector>

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
  std::vector<PerformanceVariable> performanceVarsList;
 public:
  void addPerformanceVariable(PerformanceVariable var);
}

class CollectionControlVar
{
 private:
  std::vector<ControlVariable> controlVarsList;
 public:
  void addControlVariable(ControlVariable var);
}
