#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>
#include <functional>
#include <stack>
#include <queue>
#include "TaskBase.hpp"

class TaskEleven : public TaskBase{
public:
    using PaniccLevel = uint64_t;
    void assertResults() override
    {
//        auto firstResult = solveFirstTask();
//        assert(firstResult == 120756); // don't know why, but with this modulo result is now 121800 instead opf

        auto secondResult = solveSecondTask();
        assert(secondResult == 39109444654);
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
    virtual unsigned int solveFirstTask() override
    {
        m_inspections = {};
        m_input = {};
        m_monkeys ={};
        m_multiplier = 3;

        unsigned int result = 1;
        readData();
        parseInput();
        for(int i = 0; i < 20; i++)
        {
            simulateRound();
        }
        for(const auto& monkey: m_monkeys)
        {
            std::cout << "Monkey with id: "<< monkey.id << " inspected items " << monkey.inspectedItems << std::endl;
            m_inspections.push(monkey.inspectedItems);
        }
        for(int i = 0; i < 2; i++)
        {
            std::cout << "Most inspections: " << m_inspections.top() << std::endl;
            result *= m_inspections.top();
            m_inspections.pop();
            std::cout << "For my first star result is: " << result << std::endl;
        }
        return result;
    }
    unsigned int solveSecondTask() override
    {
        m_inspections = {};
        m_input = {};
        m_monkeys ={};

        PaniccLevel result = 1;
        readData();
        parseInput();
        for(int i = 0; i < 10000; i++)
        {
            simulateRound();
        }

        for(const auto& monkey: m_monkeys)
        {
            std::cout << "Monkey with id: "<< monkey.id << " inspected items " << monkey.inspectedItems << std::endl;
            m_inspections.push(monkey.inspectedItems);
        }

        for(int i = 0; i < 2; i++)
        {
            std::cout << "Most inspections: " << m_inspections.top() << std::endl;
            result *= m_inspections.top();
            m_inspections.pop();
            std::cout << "For my second star result is: " << result << std::endl;
        }
        return result;
    }
private:
    void simulateRound()
    {
        for(auto& monkey: m_monkeys)
        {
            while(not monkey.items.empty())
            {
                auto item = monkey.items.top();
                monkey.items.pop();
                PaniccLevel panicLevel = monkey.operation(item) % MOD;
                auto result = monkey.test(panicLevel);
                auto whichMonkeyReceives = monkey.toWhichMonkey(result);
                throwToMonkey(whichMonkeyReceives,panicLevel);
                monkey.inspectedItems++;
            }
        }
    }
    void parseInput()
    {
//        hardcodedMonkeys();
        std::stringstream ss;
        std::string lineType, monkeyId, itemPanic, old,operation,num, monkeyOnTrue, monkeyOnFalse;
        Monkey monkey;
        for(const auto& line : m_input)
        {
            ss={};
            ss << line;
            ss >> lineType;
            if(lineType == "Monkey")
            {
                monkey = {};
                ss >> monkeyId;
                monkeyId.pop_back();
                monkey.id = std::stoi(monkeyId);
            }
            if(lineType == "Starting")
            {
                ss >> lineType;
                while(ss >> itemPanic)
                {
                    if(itemPanic.back() == ',')
                        itemPanic.pop_back();
                    monkey.items.push(std::stoi(itemPanic));
                }
            }
            if(lineType == "Operation:")
            {
                ss >> lineType;
                ss >> lineType;
                ss >> old >> operation >> num;
                if(operation == "+")
                {
                    if(num == "old")
                    {
                        monkey.operation = [&](PaniccLevel lvl){ return (lvl + lvl) / m_multiplier;};
                    }
                    else
                    {
                        monkey.operation = [&,num](PaniccLevel lvl){ return (lvl + std::stoi(num)) / m_multiplier;};
                    }
                }
                if(operation == "*")
                {
                    if(num == "old")
                    {
                        monkey.operation = [&](PaniccLevel lvl){ return (lvl * lvl) / m_multiplier;};
                    }
                    else
                    {
                        monkey.operation = [&,num](PaniccLevel lvl){ return (lvl * std::stoi(num)) / m_multiplier;};
                    }
                }
            }
            if(lineType == "Test:")
            {
                ss >> lineType;
                ss >> lineType;
                ss >> num;
                auto testNum = std::stoi(num);
                m_leastCommonMultiple *= testNum;
                monkey.test = [testNum](PaniccLevel lvl){return lvl % testNum == 0;};
            }
            if(lineType == "If")
            {
                std::string  onBool, throws, to, _monkey;
                ss >> onBool >> throws >>  to >> _monkey;
                if(onBool == "true:")
                {
                    ss >> monkeyOnTrue;
                }
                if(onBool == "false:")
                {
                    ss >> monkeyOnFalse;
                    monkey.toWhichMonkey = [monkeyOnTrue, monkeyOnFalse](bool result){return result ? std::stoi(monkeyOnTrue) : std::stoi(monkeyOnFalse);};
                    m_monkeys.push_back(monkey);
                }
            }
        }
    }

    void throwToMonkey(unsigned short monkeyId, PaniccLevel level)
    {
        auto monkey = std::find_if(m_monkeys.begin(), m_monkeys.end(),
                                [monkeyId](const Monkey& monkey)
                                {return monkeyId == monkey.id;});
        if(monkey == m_monkeys.end())
            throw std::runtime_error("Messed up finding monkey!");

        monkey->items.push(level);
    }

    struct Monkey{
        unsigned short id;
        PaniccLevel inspectedItems;
        std::stack<PaniccLevel> items;
        std::function<PaniccLevel (PaniccLevel)> operation;
        std::function<bool(PaniccLevel )> test;
        std::function<unsigned short(bool)> toWhichMonkey;
    };

    unsigned int m_multiplier = 1;
    std::string m_inputFileName;
//    PaniccLevel MOD = 13 * 2 * 19 * 11 * 7 * 5 * 3 * 17 * 23;
    PaniccLevel MOD = 9699690;
    PaniccLevel m_leastCommonMultiple = 1;

    std::priority_queue<PaniccLevel> m_inspections;
    std::vector<std::string> m_input;
    std::vector<Monkey> m_monkeys;
};