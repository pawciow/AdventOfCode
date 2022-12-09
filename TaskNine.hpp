#pragma once
#include "TaskBase.hpp"

#include <vector>
#include <cassert>
#include <fstream>
#include <list>
#include <queue>
#include <set>
#include <math.h>

class TaskNine : public TaskBase{
public:

    using Position = std::pair<int,int>;
    struct MoveOrder{
        enum class Direction{
            up,
            down,
            left,
            right
        };
        Direction m_direction;
        unsigned short m_amount;
    };

    void assertResults() override
    {
        auto firstResult = solveFirstTask();
//        assert(firstResult == 13); // for input 6190 for test1 13

        auto secondResult = solveSecondTask();
        assert(secondResult == 36);
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
        unsigned int result = 0;
        readData();
        parseInput();
        while (not m_orders.empty())
        {
            auto order = m_orders.front();
            processMove(order);
            m_orders.pop();
        }
        result = m_tailPositions.size();
        std::cout << "For my first star result is: " << result << std::endl;
        return result;
    }

    unsigned int solveSecondTask() override
    {
        unsigned int result = 0;
        readData();
        parseInput();
        while (not m_orders.empty())
        {
            auto order = m_orders.front();
            processMove(order);
            m_orders.pop();
        }
        result = m_tailPositions.size();
        std::cout << "For my first star result is: " << result << std::endl;
        return result;
    }

private:
    std::string m_inputFileName;
    std::vector<std::string> m_input;

    std::queue<MoveOrder> m_orders;

    Position m_TailPosition = {0,0};
    Position m_HeadPosition = {0,0};
    std::set<Position> m_tailPositions{m_TailPosition};

    void processMove(MoveOrder order)
    {
        for(auto i = 0; i < order.m_amount; i++)
        {
            auto lastHeadPosition = m_HeadPosition;
            simpleMove(order.m_direction, m_HeadPosition);
            moveTail(order.m_direction,lastHeadPosition);
//            std::cout << "Positions after move: " << m_TailPosition.first << "," << m_TailPosition.second <<
//                  " head: " << m_HeadPosition.first << "," << m_HeadPosition.second << std::endl;
        }
    }

    void simpleMove(MoveOrder::Direction direction, Position& position)
    {
        switch (direction)
        {
            case MoveOrder::Direction::up:
                position.second++;
                break;
            case MoveOrder::Direction::down:
                position.second--;
                break;
            case MoveOrder::Direction::left:
                position.first--;
                break;
            case MoveOrder::Direction::right:
                position.first++;
                break;
            default:
                throw std::runtime_error("Messed up processing move!");
                break;
        }
    }

    void moveRope(MoveOrder::Direction direction)
    {

    }
    void moveTail(MoveOrder::Direction direction, Position& lastHeadPosition)
    {
        if(tailNotNeedsMoving())
        {
            return;
        }
//        std::cout << "Needs to move for positions tail: " << m_TailPosition.first << "," << m_TailPosition.second <<
//                  " head: " << m_HeadPosition.first << "," << m_HeadPosition.second << std::endl;
//        if(m_HeadPosition.first == m_TailPosition.first or m_HeadPosition.second == m_TailPosition.second)
//        {
//            simpleMove(direction, m_TailPosition);
//        }
//        else
        {
            m_TailPosition = lastHeadPosition;
        }
        m_tailPositions.insert(m_TailPosition);
    }

    bool tailNotNeedsMoving()
    {
        if(m_HeadPosition == m_TailPosition)
            return true;
        auto x_distance = abs(m_HeadPosition.first - m_TailPosition.first);
        auto y_distance = abs(m_HeadPosition.second - m_TailPosition.second);
        if(x_distance == 2)
            return false;
        if(y_distance == 2)
            return false;
//        if(x_distance y_distance)
//            return false;
        return true;
    }

    void parseInput()
    {
        std::stringstream ss;
        std::string direction;
        unsigned short amount;
        for(const auto el: m_input)
        {
            ss << el;
            ss >> direction >> amount;
            auto order = fetchOrder(direction,amount);
            m_orders.push(order);
        }
    }

    MoveOrder fetchOrder(std::string direction, unsigned short amount)
    {
        MoveOrder toReturn;
        toReturn.m_amount = amount;

        if(direction == "U")
            toReturn.m_direction = MoveOrder::Direction::up;
        else if(direction == "D")
            toReturn.m_direction = MoveOrder::Direction::down;
        else if(direction == "L")
            toReturn.m_direction = MoveOrder::Direction::left;
        else if(direction == "R")
            toReturn.m_direction = MoveOrder::Direction::right;
        else
            throw std::runtime_error("Messed up fetching order!");
        return toReturn;
    }
};