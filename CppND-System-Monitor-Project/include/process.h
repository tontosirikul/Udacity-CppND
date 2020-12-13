#ifndef PROCESS_H
#define PROCESS_H

#include <string>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  //define constructor
  Process(int pid);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_;
  std::string user_;
  float CpuUtilization_;
  long UpTime_;
  std::string Command_;
  std::string Ram_;
};

#endif