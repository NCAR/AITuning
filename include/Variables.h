#include <iostream>
#include <string>
#include <Serializable_Log.hpp>
#include "Quantizer.h"

using namespace std;

#ifndef VARIABLES_H
#define VARIABLES_H

// Abstract class
class ControlVariable
{
protected:
  string name_;
  int value_;
public:
  ControlVariable(){;}
  virtual void setValue(int) = 0;
  virtual int getValue() = 0;
  virtual void incrementVar() = 0;
  virtual void printVar() = 0;
};

class PerformanceVariable
{
protected:
  string name_;
  PerformanceVariableLog *log_;
  Quantizer *quantizer = NULL;
public:
  
  string getName(){
    return name_;
  }

  double getLastValue()
  {
    return log_->getLastLog();
  }

  PerformanceVariableLog *getPerformanceVariableLog()
  {
    return log_;
  }
  
  void logPerformanceValue(double val)
  {
    double quantized_val = quantizer->quantize(val);
    log_->logValue(quantized_val);
  }
  
  void saveLog()
  {
    log_->saveHistory();
  }

  void loadLog()
  {
    log_->loadHistory();
  }
};

class UserDefinedPerformanceVar : public PerformanceVariable
{
public:
  UserDefinedPerformanceVar(char* name, char* filename, double step = 0.01){
    std::string tmp_name = name;
    std::string tmp_filename = filename;
    name_ = tmp_name;
    log_ = new PerformanceVariableLog(tmp_filename);
    quantizer = new UniformQuantizer(step);
  }
};

#endif
