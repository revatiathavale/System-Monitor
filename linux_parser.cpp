#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
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
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
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
  float totalmemory;
  float freememory;
  string line;
  string key;
  float value;
  std::ifstream filestream(kProcDirectory + kMemFilename);
    if(filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
        while(linestream >> key >> value) {
          if(key == "MemTotal:") {
            totalmemory = value;
          }
          else if(key == "MemFree:") {
            freememory = value;
          }
        }
      }
    }
  return (totalmemory-freememory) / totalmemory; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  string totalUpTime;
  float returnUpTime = 0;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
    if(filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
        if(linestream >> totalUpTime) {
          returnUpTime = stof(totalUpTime);
        }
      }
    }
  return returnUpTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  return LinuxParser::UpTime() * sysconf(_SC_CLK_TCK);
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line;
  string utime;
  string stime;
  string cutime;
  string cstime;
  float totalJiffies = 0;
  std::ifstream filestream(kProcDirectory + k<pid>StatFilename);
  if(filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      if(linestream >> utime) {
        totalJiffies += stof(utime);
      }
      if(linestream >> stime) {
        totalJiffies += stof(stime);
      }
      if(linestream >> cutime) {
        totalJiffies += stof(cutime);
      }
      if(linestream >> cstime) {
        totalJiffies += stof(cstime);
      }
    }
  }
  return totalJiffies; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string line;
  string cpu;
  float jiffies = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
    if(filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
        if(linestream >> cpu) {
            jiffiesString = cpu;
            int space1 = jiffiesString.find(" ");
            string j2 = jiffiesString.substr(space1 + 1);
            int space2 = j2.find(" ");
            string j3 = jiffiesString.substr(space2 + 1);
            int space3 = j3.find(" ");
            string j4 = jiffiesString.substr(space3 + 1);
            int space4 = j4.find(" ");
            string j5 = jiffiesString.substr(space4 + 1);
            int space5 = j5.find(" ");
            string j6 = jiffiesString.substr(space5 + 1);
            int space6 = j6.find(" ");
            string j7 = jiffiesString.substr(space6 + 1);
            int space7 = j7.find(" ");
            jiffies = jiffies + stol(jiffiesString.substr(0, space1 - 1)) + stol(jiffiesString.substr(space1 + 1, space2 - 1)) + stol(jiffiesString.substr(space2 + 1, space3 - 1)) + stol(jiffiesString.substr(space5 + 1, space6 - 1)) + stol(jiffiesString.substr(space6 + 1, space7 - 1)) + stol(jiffiesString.substr(space7 + 1, jiffiesString.length()));
        }
      }
    }
  return jiffies;
}

long ActiveJiffiesHelper(string jiffiesString) {
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  string line;
  string cpu;
  string jiffiesString;
  float jiffies = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
    if(filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::istringstream linestream(line);
        if(linestream >> cpu) {
          jiffiesString = cpu;
          int space1 = jiffiesString.find(" ");
          string j2 = jiffiesString.substr(space1 + 1);
          int space2 = j2.find(" ");
          string j3 = jiffiesString.substr(space2 + 1);
          int space3 = j3.find(" ");
          string j4 = jiffiesString.substr(space3 + 1);
          int space4 = j4.find(" ");
          string j5 = jiffiesString.substr(space4 + 1);
          int space5 = j5.find(" ");
          jiffies = jiffies + stol(jiffiesString.substr(space3 + 1, space4 - 1)) + stol(jiffiesString.substr(space4 + 1, space5 - 1));
      }
    }
  return jiffies;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
