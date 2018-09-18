#include <iostream>
#include <vector>
#include <string>

#include "Variables.h"

using namespace std;

#ifndef COLLECTIONS_H
#define COLLECTIONS_H

class CollectionPerformanceVar
{
 private:

  string transport_layer_;
  string version_;
  std::vector<PerformanceVariable*> performanceVarsList_;

public:

  CollectionPerformanceVar(string name, string ver)
  {
    transport_layer_ = name;
    version_ = ver;
  }

  vector<Statistics *> generateStatistics()
  {
    vector<Statistics *> ret;
    int i;

    for(i = 0; i < (signed int)performanceVarsList_.size(); i++)
      ret.push_back(performanceVarsList_[i]->generateStatistics());

    return ret;
  }
  
  void addPerformanceVariable(PerformanceVariable *var)
  {
    performanceVarsList_.push_back(var);
  }

  void registerPerformanceVariables()
  {
    for(int it = 0; it != (int)performanceVarsList_.size(); ++it)
      performanceVarsList_.at(it)->logPerformanceValue();
  }
};

class CollectionControlVar
{
 private:

  string transport_layer_;
  string version_;
  std::vector<ControlVariable*> controlVarsList_;
  
 public:

  CollectionControlVar(string name, string ver)
  {
    transport_layer_ = name;
    version_ = ver;
  }
  
  void addControlVariable(ControlVariable *var)
  {
    controlVarsList_.push_back(var);
  }

  ControlVariable * getControlVariable(int index)
  {
    return controlVarsList_.at(index);
  }
};

// Abstract class
class CollectionCreator
{
 public:
  virtual CollectionPerformanceVar *createCollectionPerformanceVar() = 0;
  virtual CollectionControlVar *createCollectionControlVar() = 0;
};

#endif
