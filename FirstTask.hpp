//
// Created by Paweł on 01.12.2022.
//

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <queue>
#include <cassert>
#include "TaskBase.hpp"

class FirstTask : public TaskBase{
public:
    void provideFileName(std::string fileName) override
    {
        m_inputFileName = fileName;
    }

    void assertResults() override
    {
        auto firstResult = solveFirstTask();
        assert(firstResult == 71934);

        auto secondResult = solveSecondTask();
        assert(secondResult == 211447);
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

    unsigned int solveFirstTask() override {
        readData();
        unsigned int calories = 0;
        for (const auto &line: m_input) {
            if (line == "\r") {
                std::cout << "Elf number: " << elvesCalories.size() + 1 << " harvested " << calories << " calories."
                          << '\n';
                elvesCalories.push(calories);
                calories = 0;
            } else {
                calories += std::stoi(line);
            }
        }
        std::cout << "For first star: \n Largest collected calories is: " << elvesCalories.top() << std::endl;
        return elvesCalories.top();
    }

    unsigned int solveSecondTask() override
    {
        unsigned int largestThree = 0;
        for(int i = 0; i < 3; i++)
        {
             largestThree += elvesCalories.top();
             elvesCalories.pop();
        }

        std::cout << "For second star: \n Sum of best three is: " << largestThree << std::endl;
        return largestThree;
    }

private:
    std::priority_queue<int> elvesCalories;
    std::string m_inputFileName;
    std::vector<std::string > m_input;
};