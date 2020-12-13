#include <string>
#include <sstream>
#include <iomanip>
#include "format.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::setfill;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hour = seconds/3600;
	seconds = seconds%3600;
	int min = seconds/60;
	seconds = seconds%60;
	int sec = seconds;
	std::stringstream h,m,s;
	h << std::setfill('0') << std::setw(2) << hour;
	m << std::setfill('0') << std::setw(2) << min;
	s << std::setfill('0') << std::setw(2) << sec;
    return h.str() + ":" + m.str() + ":" + s.str(); 
}