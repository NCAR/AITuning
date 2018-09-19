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
    if(var->isRelative())
      var->readOriginalValFromFile();

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

  void dumpCollectionOnFile()
  {
    ofstream outfile;
    outfile.open("control_first_run.txt");

    for(int i=0; i<(signed int)controlVarsList_.size(); i++)
      outfile << controlVarsList_[i]->getValue() << " ";

    outfile.close();
  }

  void readCollectionFromFile()
  {
    ifstream infile;
    infile.open("control_first_run.txt");
    int val;

    for(int i=0; i<(signed int)controlVarsList_.size(); i++)
      {
	infile >> val;
	controlVarsList_[i]->setValue(val);
      }
    
    infile.close();
  }

  void readAIChanges()
  {
    ifstream infile;
    infile.open("changes.txt");
    int val;

    for(int i=0; i<(signed int)controlVarsList_.size(); i++)
      {
	infile >> val;
	if(val == -1)
	  controlVarsList_[i]->decrementVar();
	else if(val == 1)
	  controlVarsList_[i]->incrementVar();
      }
    
    infile.close();
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
