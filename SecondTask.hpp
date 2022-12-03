#pragma once
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "TaskBase.hpp"

class SecondTask : public TaskBase{
private:
    enum class Actions{
        rock,
        paper,
        scissors
    };
    std::unordered_map<Actions, Actions> thisActionCounters{
            {Actions::rock, Actions::scissors},
            {Actions::paper, Actions::rock},
            {Actions::scissors, Actions::paper}
    };
    std::string m_inputFileName;
    std::vector<std::string > m_input;

public:
    void assertResults() override
    {
        auto firstResult = solveFirstTask();
        assert(firstResult == 11906);

        auto secondResult = solveSecondTask();
        assert(secondResult == 11186);
    }

    void provideFileName(std::string fileName) override
    {
        m_inputFileName = fileName;
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

    unsigned int solveFirstTask() override
    {
        readData();
        std::vector<std::string> instructions;
        unsigned int endScore = 0;
        for (std::string line : m_input)
        {
            boost::split(instructions, line, boost::is_any_of(" "));
            instructions[1].erase(std::remove(instructions[1].begin(), instructions[1].end(), '\r'), instructions[1].cend());
            endScore += resultForFirstExample(instructions);
        }

        std::cout << "For my second star, my score is : " << endScore << std::endl;
        return endScore;
    }

    unsigned int solveSecondTask() override
    {
        readData();
        std::vector<std::string> instructions;
        unsigned int endScore = 0;
        for (std::string line : m_input)
        {
            boost::split(instructions, line, boost::is_any_of(" "));
            instructions[1].erase(std::remove(instructions[1].begin(), instructions[1].end(), '\r'), instructions[1].cend());
            endScore += result(instructions);
        }

        std::cout << "For my second star, my score is : " << endScore << std::endl;
        return endScore;
    }

    Actions convertToAction(std::string action)
    {
        if(action == "A" or action == "X")
        {
            return Actions::rock;
        }
        if(action == "B" or action == "Y")
        {
            return Actions::paper;
        }
        if(action == "C" or action == "Z")
        {
            return Actions::scissors;
        }
        throw std::runtime_error("Messed up converting action!");
    }

    Actions calculateMyAction(Actions enemyAction, std::string expectedResult)
    {
        if(expectedResult == "X") // lose
        {
            return thisActionCounters[enemyAction];
        }
        if(expectedResult == "Y") // draw
        {
            return enemyAction;
        }
        if(expectedResult == "Z") // win
        {
            auto counter = std::find_if(thisActionCounters.begin(), thisActionCounters.end(), [enemyAction](auto pair){
                return pair.second == enemyAction;
            });
            return (*counter).first;
        }
        throw std::runtime_error("Messed up converting my action!");
    }

    unsigned int calculateResult(Actions enemyAction, Actions myAction)
    {
        if(thisActionCounters[enemyAction] == myAction)
            return 0;
        if(enemyAction == myAction)
            return 3;
        if(thisActionCounters[myAction] == enemyAction)
            return 6;
        throw std::runtime_error("Messed up calculating result!");
    }

    unsigned int pointsForMyAction(Actions myAction)
    {
        if (myAction == Actions::rock)
            return 1;
        if(myAction == Actions::paper)
            return 2;
        if(myAction == Actions::scissors)
            return 3;
        throw std::runtime_error("Messed up pointsForMyAction!");
    }
    unsigned int resultForFirstExample(std::vector<std::string> actions)
    {
        Actions enemyAction = convertToAction(actions[0]);
        Actions myAction = convertToAction(actions[1]);
        return calculateResult(enemyAction,myAction) + pointsForMyAction(myAction);
    }
    unsigned int result(std::vector<std::string> actions)
    {
        Actions enemyAction = convertToAction(actions[0]);
        Actions myAction = calculateMyAction(enemyAction,actions[1]);
        return calculateResult(enemyAction,myAction) + pointsForMyAction(myAction);
    }
};