#pragma once

#include <cassert>
#include <vector>
#include "../TaskBase.hpp"
#include <fstream>
#include <set>
#include <algorithm>
class Day6 : public TaskBase{
public:
    void assertResults() override
    {
        auto firstResult = solveFirstTask();
        assert(firstResult == 1198);

        auto secondResult = solveSecondTask();
        assert(secondResult == 3120);
    }

    void readData() override
    {
        m_input.clear();
        std::ifstream ss(getInput(m_inputFileName));
        for (std::string line; getline(ss, line);)
        {
            m_input.push_back(line);
        }
    }

    void provideFileName(std::string fileName) override
    {
        m_inputFileName = fileName;
    }

    unsigned int solveFirstTask() override
    {
        readData();
        unsigned int result = 0;
        for(auto it = m_input[0].begin(); it != m_input[0].end(); it++) // it + 4 can be out of scope, i assume it always has an answer
        {
            std::set<char> set(it, it+4);
            if(set.size() == 4)
            {
                result += 4;
                break;
            }
            result++;
        }
        std::cout << "For my first star result is: " << result << std::endl;
        return result;
    }

    unsigned int solveSecondTask() override
    {
        readData();
        auto sizeOfWindow = 14;
        unsigned int result = 0;
        for(auto it = m_input[0].begin(); it != (m_input[0].end() + sizeOfWindow) ; it++)
        {
            std::set<char> set(it, it+sizeOfWindow);
            if(set.size() == sizeOfWindow)
            {
                result += sizeOfWindow;
                break;
            }
            result++;
        }

        std::cout << "For my second star result is: " << result << std::endl;
        return result;
    }
private:
    std::string m_inputFileName;
    std::vector<std::string> m_input;
};