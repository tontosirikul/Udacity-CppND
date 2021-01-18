#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#define FILENAME "record.txt"
class System
{
public:
    void initialSetup();
    std::string getPlayerName();
    void saveScore(int c);

private:
    std::string playerName_;
};

#endif
