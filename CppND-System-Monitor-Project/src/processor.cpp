#include "processor.h"
#include "linux_parser.h"
#include <iostream>

using std::stof;
using std::stoi;
using std::stol;
using std::string;
using std::to_string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    string cpu, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    string line;
    float cpu_percentage;
    std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
        break;
    }
    
    int idled = stoi(idle) + stoi(iowait);
    int nidled = stoi(user) + stoi(nice) + stoi(system) + stoi(irq) + stoi(softirq) + stoi(steal);
    float totald = idled + nidled;
    cpu_percentage = (totald - idled)/totald;
    return cpu_percentage;
}