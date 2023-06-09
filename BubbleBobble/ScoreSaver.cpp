#include "ScoreSaver.h"
#include <fstream>
#include <sstream>
#include <iostream>

const std::vector<aze::ScoreEntry>& aze::ScoreSaver::ReadScoreEntries(const std::string& filePath)
{
    std::ifstream inputFile{filePath};
    if (!inputFile.is_open()) 
    {
        std::cerr << "Failed to open file: " << filePath << "\n";
        return m_ScoreEntries;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::istringstream iss{ line };
        std::string entry;

        while (std::getline(iss, entry, ','))
        {
            std::string name{entry.substr(0, 3)};
            std::string scoreStr{entry.substr(3)};

            uint16_t score{ 0 };
            try 
            {
                score = static_cast<uint16_t>(std::stoi(scoreStr));
            }
            catch (const std::exception&) 
            {
                std::cerr << "Failed to convert score to integer for entry: " << entry << "\n";
                continue;
            }

            m_ScoreEntries.emplace_back(name, score);
        }
    }

    inputFile.close();
    return m_ScoreEntries;
}

aze::ScoreSaver& aze::ScoreSaver::WriteScoreEntries(const std::string& filePath)
{
    std::ofstream outputFile{filePath};
    if (!outputFile.is_open()) 
    {
        std::cerr << "Failed to open file for writing: " << filePath << "\n";
        return *this;
    }

    for (const ScoreEntry& entry : m_ScoreEntries)
    {
        outputFile << entry.name[0] << entry.name[1] << entry.name[2] << entry.score << ",";
    }

    outputFile.close();
    return *this;
}

void aze::ScoreSaver::AddNewScoreEntry(const ScoreEntry& scoreEntry)
{
    m_ScoreEntries.emplace_back(scoreEntry);
}
