#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "system.h"

void System::initialSetup()
{
    std::string name;
    std::cout << "Welcome to snake game\n";
    std::cout << "What I should call you ?\n";
    std::cin >> name;
    playerName_ = std::move(name);
}

std::string System::getPlayerName()
{
    return playerName_;
}

void System::saveScore(int c)
{
    std::vector<std::string> namelist{};
    std::vector<std::string> scorelist{};
    std::string line;
    std::string name;
    std::string score;

    std::ifstream f;
    f.open(FILENAME);
    if (f)
    {
        while (getline(f, line))
        {
            std::istringstream lineStream(line);
            lineStream >> name;
            lineStream >> score;
            namelist.push_back(name);
            scorelist.push_back(score);
        }
        f.close();
    }
    std::ofstream fout;
    fout.open(FILENAME, std::ofstream::trunc);
    for (auto it1 = namelist.begin(), it2 = scorelist.begin(); it1 != namelist.end(); ++it1, ++it2)
    {
        fout << *it1 << " " << *it2 << std::endl;
    }

    fout << playerName_ << " " << std::to_string(c) << std::endl;
    fout.close();
}