#include <iostream>
#include <vector>
#include <string>

#include "Variables.h"

using namespace std;

#ifndef PROBES_H
#define PROBES_H

// Abstract class
class Probe
{
protected:
  string name_;
  PerformanceVariable *perf_var_;
public:
  virtual void registerValue(double val) = 0;
};
  
class SingleProbe : public Probe
{
public:
  SingleProbe(char *name, PerformanceVariable *perf_var)
  {
    perf_var_ = perf_var;
    std::string tmp_name = name;
    name_ = tmp_name;
  }
  void registerValue(double val)
  {
    perf_var_->logPerformanceValue(val);
  }
};
#endif
