#include <iostream>
#include <vector>
#include <string>
#include "Variables.h"

using namespace std;

void AITuning_start(string layer);
void AITuning_addUserDefinedPerformanceVar(UserDefinedPerformanceVar *ud);
void AITuning_readPerformanceVariables();
void AITuning_setControlVariables();
void AITuning_setPerformanceVariables();
vector<Statistics *> AITuning_generateStatistics();
