#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "linux_parser.h"

using std::stof;
using std::stoi;
using std::stol;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> version;
  }
  return version;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;
  float MemTotal = 0;
  float MemFree = 0;
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  while (std::getline(filestream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::replace(line.begin(), line.end(), 'k', ' ');
    std::replace(line.begin(), line.end(), 'B', ' ');
    std::istringstream linestream(line);
    while (linestream >> key >> value) {
      if (key == "MemTotal") {
        MemTotal = stof(value);
      }
      else if (key == "MemFree") {
        MemFree = stof(value);
      }
    }
  }
  return (MemTotal-MemFree)/MemTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  string uptime;
  string idletime;
  std::ifstream filestream(kProcDirectory+kUptimeFilename); 
  while (std::getline(filestream, line)) {
    std::istringstream linestream(line);
    linestream >> idletime >> uptime;
  }
  return stol(idletime);
}

// TODO: Read and return the number of jiffies for the system
//long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::ActiveJiffies(int pid) {
  string line;
  string unuse,utime,stime,cutime,cstime; 
  string current_pid = to_string(pid);
  std::ifstream filestream(kProcDirectory+current_pid+kStatFilename);  
  while (std::getline(filestream, line)) {
    std::istringstream linestream(line);
    for (int i = 1 ; i < 14 ; i++) {
      linestream >> unuse;
    }
    
    linestream >> utime >> stime >> cutime >> cstime;
    
    return stof(utime) + stof(stime) + stof(cutime) + stof(cstime);

  }
  return -1;
}

// TODO: Read and return the number of active jiffies for the system
//long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
//long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
//vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string value;
  bool reach = false;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  while (std::getline(filestream, line)) {
    std::istringstream linestream(line);
    while (linestream >> value ) {
      if (reach == true) {
        return stoi(value);
      }
      else if (value == "processes") {
        reach = true;
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string value;
  bool reach = false;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  while (std::getline(filestream, line)) {
    std::istringstream linestream(line);
    while (linestream >> value ) {
      if (reach == true) {
        return stoi(value);
      }
      else if (value == "procs_running") {
        reach = true;
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  string current_pid = to_string(pid);
  std::ifstream filestream(kProcDirectory+current_pid+kCmdlineFilename);
  while (std::getline(filestream, line)) {
    return line;
  } 
  return "null"; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string key,value,line;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
  while (std::getline(filestream, line)) {
    std::istringstream linestream(line);
    while(linestream>>key>>value) {
      if(key == "VmSize:") {
        int mb = stol(value)/1000;
        return to_string(mb);
      }
    }
  }
  return "null"; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you def=ine the function
string LinuxParser::Uid(int pid) {
  string key,value,line;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatusFilename);
  while (std::getline(filestream, line)) {
    std::istringstream linestream(line);
    while(linestream>>key>>value) {
      if(key == "Uid:") {
        return value;
      }
    }
  }
  return "null"; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string key,value,x,line;
  string userid = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  while (std::getline(filestream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::istringstream linestream(line);
    while(linestream>>key >> x >> value) {
      if(value == userid) {
        return key;
      }
    }
  }
  return "null";
}
// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  string unuse,processtime;
  string current_pid = to_string(pid);
  std::ifstream filestream(kProcDirectory+current_pid+kStatFilename);
  while (std::getline(filestream, line)) {
    std::replace(line.begin(), line.end(), '(', ' ');
    std::replace(line.begin(), line.end(), ')', ' ');
    std::istringstream linestream(line);
    for (int i = 1 ; i < 22 ; i++) {
      linestream >> unuse;
    }
    linestream >> processtime;
    long uptime = LinuxParser::UpTime();
    long second = uptime - (stol(processtime)/sysconf(_SC_CLK_TCK));
    return second;
  }
  return 0.0;
}