#pragma once

#include <cassert>
#include <vector>
#include <fstream>
#include "TaskBase.hpp"
#include <algorithm>

class TaskFour : public TaskBase{
public:
    void assertResults() override
    {
//        auto firstResult = solveFirstTask();
//        assert(firstResult == 448);

        auto secondResult = solveSecondTask();
        assert(secondResult == 0);
    }

    void provideFileName(std::string fileName) override
    {
        m_inputFileName = fileName;
    }

    void readData() override
    {
        m_input.clear();
        std::ifstream ss(getInput(m_inputFileName));
        std::string line;
        while(ss >> line)
        {
            m_input.push_back(line);
        }
    }

    struct Assignment{
        unsigned int lowestSectionId;
        unsigned int highestSectionId;
    };

    unsigned int solveFirstTask() override
    {
        unsigned int result = 0;
        parseInput();
        result = std::ranges::count_if(m_data.begin(), m_data.end(), doesAssignmentsFullyOverlap);
        std::cout << "For my first star result is: " << result << std::endl;
        return result;
    }
    unsigned int solveSecondTask() override
    {
        unsigned int result = 0;
        parseInput();
        result = std::ranges::count_if(m_data.begin(), m_data.end(), doesAssignmentOverlap);
        std::cout << "For my second star result is: " << result << std::endl;
        return result;
    }

private:
    void parseInput()
    {
        readData();
        m_data.clear();
        for(const auto & line : m_input)
        {
            auto a = line.substr(0, line.find(","));
            auto b = line.substr(line.find(",")+1);

            unsigned int lowestA = std::stoi(a.substr(0,a.find("-")));
            unsigned int highestA = std::stoi(a.substr(a.find("-")+1));;
            unsigned int lowestB = std::stoi(b.substr(0,b.find("-")));
            unsigned int highestB = std::stoi(b.substr(b.find("-")+1));;

            Assignment firstAssignment{lowestA,highestA};
            Assignment secondAssignment{lowestB,highestB};
            m_data.push_back({firstAssignment,secondAssignment});
        }
    }
    static bool doesAssignmentsFullyOverlap(std::pair<Assignment,Assignment> pair)
    {
        auto lhs = pair.first;
        auto rhs = pair.second;
        return lhs.lowestSectionId <= rhs.lowestSectionId and lhs.highestSectionId >= rhs.highestSectionId or
            rhs.lowestSectionId <= lhs.lowestSectionId and rhs.highestSectionId >= lhs.highestSectionId;
    }

    static bool doesAssignmentOverlap(std::pair<Assignment,Assignment> pair)
    {
        auto lhs = pair.first;
        auto rhs = pair.second;
        return lhs.lowestSectionId <= rhs.highestSectionId and lhs.highestSectionId >= rhs.lowestSectionId or
            rhs.lowestSectionId <= lhs.highestSectionId and rhs.highestSectionId >= lhs.lowestSectionId;
    }

    std::string m_inputFileName;
    std::vector<std::string> m_input;
    std::vector<std::pair<Assignment, Assignment>> m_data;
};