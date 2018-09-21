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

  void cleanRelativePerformanceVariables()
  {
    for(int it = 0; it != (int)performanceVarsList_.size(); ++it)
      if(performanceVarsList_.at(it)->isRelative())
	performanceVarsList_.at(it)->deleteOriginalValOnFile();
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

  void dumpCollectionOnFile(bool first_run)
  {
    ofstream outfile;
    if(first_run)
      outfile.open("control_first_run.txt");
    else
      outfile.open("control_variables.txt");

    for(int i=0; i<(signed int)controlVarsList_.size(); i++)
      outfile << controlVarsList_[i]->getName() << "=" << controlVarsList_[i]->getValue() << endl;

    outfile.close();
  }

  void readCollectionFromFile()
  {
    ifstream infile;
    infile.open("control_variables.txt");
    string name_read, tmp;

    for(int i=0; i<(signed int)controlVarsList_.size(); i++)
      {
	if( std::getline( infile, name_read , '=') )
	  if( std::getline( infile, tmp) )
	    controlVarsList_[i]->setValue(stoi(tmp));
      }
    
    infile.close();
  }

  void readAIChanges()
  {
    ifstream infile;
    string tmp, name_read;
    infile.open("changes.txt");
    int val = 0;

    for(int i=0; i<(signed int)controlVarsList_.size(); i++)
      {
	if( std::getline( infile, name_read , '=') )
	  if( std::getline( infile, tmp ) )
	    val = stoi(tmp);

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
