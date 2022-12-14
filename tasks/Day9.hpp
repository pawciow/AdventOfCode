#pragma once
#include "../TaskBase.hpp"

#include <vector>
#include <cassert>
#include <fstream>
#include <list>
#include <queue>
#include <set>
#include <math.h>

class Day9 : public TaskBase{
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
        assert(firstResult == 6190);

        auto secondResult = solveSecondTask();
        assert(secondResult == 2516);
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
        m_orders = {};
        m_tailPositions = {{0,0}};
        m_rope=std::vector<Position>(2,{0,0});
        unsigned int result = 0;
        readData();
        parseInput();

        while (not m_orders.empty())
        {
            auto order = m_orders.front();
            for(auto i = 0; i < order.m_amount; i++)
            {
                auto& head = m_rope[0];
                auto& tail = m_rope[1];

                simpleMove(order.m_direction, head);
                moveTail(head, tail);
            }
            m_orders.pop();
        }
        result = m_tailPositions.size();
        std::cout << "For my first star result is: " << result << std::endl;
        return result;
    }

    unsigned int solveSecondTask() override
    {
        m_orders = {};
        m_tailPositions = {{0,0}};
        m_rope=std::vector<Position>(10,{0,0});
        unsigned int result = 0;
        readData();
        parseInput();
        while (not m_orders.empty())
        {
            auto order = m_orders.front();
            for(auto i = 0; i < order.m_amount; i++)
            {
                simpleMove(order.m_direction,m_rope[0]);
                for(auto it = 0; it < m_rope.size()-1; it++)
                {
                    moveTail(m_rope[it], m_rope[it+1]);
                }
            }
            m_orders.pop();
        }
        result = m_tailPositions.size();
        std::cout << "For my second star result is: " << result << std::endl;
        return result;
    }

private:
    std::string m_inputFileName;
    std::vector<std::string> m_input;

    std::queue<MoveOrder> m_orders;

    std::set<Position> m_tailPositions{ {0,0}};
    std::vector<Position> m_rope{2,{0,0}};

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

    void moveTail(Position& head, Position& tail)
    {
        if(tailNotNeedsMoving(head, tail))
        {
            return;
        }

        findNewPosition(head,tail);
        m_tailPositions.insert(m_rope.back());
    }

    void findNewPosition(const Position& head, Position& tail)
    {
        if(head.first > tail.first)
        {
            tail.first++;
        }
        else if(head.first < tail.first)
        {
            tail.first--;
        }

        if(head.second > tail.second)
        {
            tail.second++;
        }
        else if(head.second < tail.second)
        {
            tail.second--;
        }
    }
    bool tailNotNeedsMoving(Position left, Position right)
    {
        if(left == right)
            return true;
        auto x_distance = abs(left.first - right.first);
        auto y_distance = abs(left.second - right.second);
        if(x_distance == 2)
            return false;
        if(y_distance == 2)
            return false;

        return true;
    }

    void parseInput()
    {
        m_orders = {};
        unsigned short amount;
        std::stringstream ss;
        std::string direction;
        for(const auto el: m_input)
        {
            ss << el;
            ss >> direction >> amount;
            auto order = fetchOrder(direction,amount);
            m_orders.push(order);
            ss.clear();
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