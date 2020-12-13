#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"
#include "format.h"
#include <unistd.h>
using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
Process::Process (int pid) {
    pid_ = pid;
    user_ = LinuxParser::User(pid);
    UpTime_ = LinuxParser::UpTime(pid);
    Command_ = LinuxParser::Command(pid);
    Ram_ = LinuxParser::Ram(pid);
    CpuUtilization_ = (LinuxParser::ActiveJiffies(pid)/sysconf(_SC_CLK_TCK))/(float)UpTime_;
}

int Process::Pid() { 
    return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const {
    return CpuUtilization_  ;
}
// TODO: Return the command that generated this process
string Process::Command() { return Command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return Ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return UpTime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return a.CpuUtilization() < CpuUtilization() ;
}