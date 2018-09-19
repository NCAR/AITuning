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
void AITuning_dumpControlVariablesOnFile();
void AITuning_readControlVariablesFromFile();
void AITuning_readAIChanges();
void AITuning_cleanRelativePerfVars();
vector<Statistics *> AITuning_generateStatistics();
