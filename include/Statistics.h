#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics{
private:
  double min_ = 0.0;
  double max_ = 0.0;
  double mean_ = 0.0;
  double median_ = 0.0;
  vector<double> data_;
public:
  Statistics(PerformanceVariableLog *log){
    data_ = log->getRecentLog();
  }

  double getMin()
  {
    if(min_ > 0.0)
      return min_;
    min_ = *min_element(data_.begin(), data_.end());
    return min_;
  }

  double getMax()
  {
    if(max_ > 0.0)
      return max_;
    max_ = *max_element(data_.begin(), data_.end());
    return max_;
  }

  double getMean()
  {
    if(mean_ > 0.0)
      return mean_;
    int size_data = data_.size();
    double sum = std::accumulate(data_.begin(), data_.end(), 0.0);
    mean_ = sum / size_data;
    return mean_;
  }

  double getMedian()
  {
    int size_data = data_.size();
    if(median_ > 0.0)
      return median_;
    
    sort(data_.begin(), data_.end());
    if (size_data % 2 == 0)
      median_ =  (data_[size_data / 2 - 1] + data_[size_data / 2]) / 2;
    else 
      median_ = data_[size_data / 2];
    return median_;
  }
  
};
#endif
