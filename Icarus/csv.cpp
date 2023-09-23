#include "Icarus.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void Icarus::loadCSV(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "ERROR: Unable to open file " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        while (std::getline(iss, token, ','))
        {
            std::cout << token << "\t";
        }
        std::cout << std::endl;
    }

    file.close();
}
