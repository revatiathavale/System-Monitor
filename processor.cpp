#include "processor.h"
#include "linux_parser.cpp"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { return LinuxParser::CpuUtilization(); }
