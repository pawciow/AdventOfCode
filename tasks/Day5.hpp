#pragma once

#include "../TaskBase.hpp"
#include <vector>
#include <stack>
#include <cassert>
#include <fstream>
#include <queue>
#include <ranges>

class Day5 : public TaskBase{
public:

    struct MoveOrder{
        unsigned int amount;
        unsigned int start;
        unsigned int destination;
    };

    void assertResults() override
    {
        auto firstResult = solveFirstTask();
        assert(firstResult == 0);

        auto secondResult = solveSecondTask();
        assert(secondResult == 0);
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
        parseInputData();
        while (not m_orders.empty())
        {
            processMoveOrder(m_orders.front());
            m_orders.pop();
        }
        auto result = getResult();
        std::cout << "For my first star result is: " << result << std::endl;
        return {};
    }
    unsigned int solveSecondTask() override
    {
        readData();
        parseInputData();
        while (not m_orders.empty())
        {
            processMoveOrderWithRetainedOrder(m_orders.front());
            m_orders.pop();
        }
        auto result = getResult();
        std::cout << "For my second star result is: " << result << std::endl;
        return {};
    }
private:

    std::string getResult()
    {
        std::string result;
        std::stringstream  ss;

        for(const auto el : m_stacks)
        {
            ss << el.top();
        }
        ss >> result;

        return result;
    }

    void processMoveOrderWithRetainedOrder(MoveOrder order)
    {
        std::stack<char> tmp_stack;
        for(auto i = 0; i < order.amount; i++)
        {
            auto elementToMove = m_stacks[order.start].top();
            m_stacks[order.start].pop();
            tmp_stack.push(elementToMove);
//            std::cout << "Moved " << elementToMove << " from " << order.start + 1 << " to " << order.destination + 1 << std::endl;
        }
        while(not tmp_stack.empty())
        {
            auto elementToMove = tmp_stack.top();
            tmp_stack.pop();
            m_stacks[order.destination].push(elementToMove);
        }
    }

    void processMoveOrder(MoveOrder order)
    {
        for(auto i = 0; i < order.amount; i++)
        {
            auto elementToMove = m_stacks[order.start].top();
            m_stacks[order.start].pop();
            m_stacks[order.destination].push(elementToMove);
//            std::cout << "Moved " << elementToMove << " from " << order.start + 1 << " to " << order.destination + 1 << std::endl;
        }
    }

    void parseInputData()
    {
        parseStacks();
        parseOrders();
    }

    void parseOrders()
    {
        auto ordersView = std::ranges::subrange(m_input.begin() + m_descriptionNumber + 2, m_input.end());

        std::string move, from, to;
        unsigned int amount,start,destination;
        std::stringstream stringStream;
        for(const auto& el: ordersView)
        {
            stringStream << el;
            stringStream >> move >> amount >> from >> start >> to >> destination;
            assert(start != 0);
            assert(destination != 0);
            MoveOrder order{amount,start -1 ,destination -1}; // We count from 0, input is from 1
            m_orders.push(order);
        }
    }

    void parseStacks()
    {
        m_descriptionNumber = findStacksDescriptionLineNumber();
        if(m_descriptionNumber == 0)
            throw std::runtime_error("Messed up finding descriptions!");

        auto stacks = m_input | std::ranges::views::take(m_descriptionNumber) | std::views::reverse;

        m_descriptionLine = m_input[m_descriptionNumber];
        std::vector<unsigned int> stackPosition = findStackPositions();
        fetchStacks(stacks, stackPosition);
    }

    std::vector<unsigned int> findStackPositions()
    {
        std::vector<unsigned int> stackPosition; // Need to find position on the string for each stack
        for(auto i = 0; i < m_descriptionLine.size(); i++)
        {
            if(m_descriptionLine[i] != ' ')
            {
                stackPosition.push_back(i);
            }
        }
        return stackPosition;
    }

    void fetchStacks(const auto stacks, std::vector<unsigned int> &stackPosition)
    {
        m_stacks.clear();
        m_orders = {};
        for(const auto el: stackPosition)
        {
            m_stacks.push_back({});
        }

        for(const auto& stack: stacks)
        {
            for(int i = 0; i < stackPosition.size(); i++)
            {
                auto element = stack[stackPosition[i]];
                if(element != ' ')
                {
                    m_stacks[i].push(element);
                }
            }
        }
    }

    unsigned int findStacksDescriptionLineNumber()
    {
        for(auto i = 0; i < m_input.size(); i++)
        {
            if(m_input[i][1] == '1')
            {
                return i;
            }
        }
        return 0;
    }

    std::string m_inputFileName;
    std::vector<std::string> m_input;

    std::string m_descriptionLine;
    unsigned int m_descriptionNumber = 0;

    std::queue<MoveOrder> m_orders;
    std::vector<std::stack<char>> m_stacks;
};