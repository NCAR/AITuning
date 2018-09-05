typedef void* Probe_C;
typedef void* PerformanceVariable_C;

extern "C" Probe_C newProbe(PerformaceVariableC perf_var);
extern "C" void registerValue(Probe_C probe, double val);

extern "C" PerformanceVariable_C newPerfVar(char* name, char* filename);
