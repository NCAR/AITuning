#include <iostream>
#include <vector>
#include <string>

#include "Variables.h"

using namespace std;

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
  SingleProbe(string name, PerformanceVariable *perf_var)
  {
    name_ = name;
    perf_var_ = perf_var;
  }
  void registerValue(double val)
  {
    perf_var_->logPerformanceValue(val);
  }
};
