#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <algorithm>



namespace seneca
{

class SpellChecker {
    std::string m_badWords[6];
    std::string m_goodWords[6];
    size_t m_replacements[6]{};

public:
    SpellChecker(const char* filename) 
    {
        std::ifstream file(filename);
        if (!file)
            throw "Bad file name!";

        std::string line;
        size_t index = 0;

        while (std::getline(file, line) && index < 6) 
        {
            std::istringstream iss(line);
            iss >> m_badWords[index] >> m_goodWords[index];
            ++index;
        }
    }

    void operator()(std::string& text) 
    {
        for (size_t i = 0; i < 6; ++i) 
        {
            size_t pos = 0;
            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) 
            {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                pos += m_goodWords[i].length(); 
                ++m_replacements[i];
            }
        }
    }

    void showStatistics(std::ostream& out) const 
    {
        for (size_t i = 0; i < 6; ++i) 
        {
            out << std::right << std::setw(15) << m_badWords[i]
                << ": " << m_replacements[i] << " replacements" << std::endl;
        }
    }
};

}


#endif
