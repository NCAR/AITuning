#include <math.h>
#include "Quantizer.h"

using namespace std;

UniformQuantizer::UniformQuantizer(double step)
{
  step_ = step;
}

double UniformQuantizer::quantize(double x)
{
  return floor((x/step_) + 0.5) * step_;
}
