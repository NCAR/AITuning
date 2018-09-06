#include <iostream>
#include <vector>
#include <string>
using namespace std;

#ifndef QUANTIZER_H
#define QUANTIZER_H

// Abstract class
class Quantizer
{
public:
  virtual double quantize(double x) = 0;
};
  
class UniformQuantizer : public Quantizer
{
private:
  double step_;
public:
  UniformQuantizer(double step);
  double quantize(double val);
};
#endif
