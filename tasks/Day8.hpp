#pragma once

#include <vector>
#include <ranges>
#include <cassert>
#include <fstream>
#include <algorithm>

#include "../TaskBase.hpp"

class Day8 : public TaskBase{
public:
    void assertResults() override
    {
        auto firstResult = solveFirstTask();
        assert(firstResult == 1715);

        auto secondResult = solveSecondTask();
        assert(secondResult == 374400);
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

    void provideFileName(std::string fileName) override
    {
        m_inputFileName = fileName;
    }

    unsigned int solveFirstTask() override
    {
        unsigned int result = 0;
        readData();
        parseInput();
        for(int x = 0; x < m_data.size(); x++)
        {
            for(int y = 0; y < m_data[x].size(); y++)
            {
                if(isTreeVisible(x,y))
                    result++;
            }
        }
        std::cout << "For my first star result is: " << result << std::endl;
        return result;
    }

    unsigned int solveSecondTask() override
    {
        unsigned int result = 0;
        readData();
        parseInput();
        for(int x = 1; x < m_data.size(); x++)
        {
            for(int y = 1; y < m_data[x].size(); y++)
            {
                auto score = calculateScenicScore(x,y);
                result = std::max(result,score);
            }
        }

        std::cout << "For my second star result is: " << result << std::endl;
        return result;
    }
private:
    unsigned int calculateScenicScore(unsigned int x_position, unsigned int y_position)
    {
        auto verticallyUp = countTreesSeenVerticallyUp(x_position, y_position);
        auto verticallyDown = countTreesSeenVerticallyDown(x_position, y_position);
        auto horizontallyRight = countTreesSeenHorizontallyRight(x_position, y_position);
        auto horizontallyLeft = countTreesSeenHorizontallyLeft(x_position, y_position);
        return verticallyUp * verticallyDown * horizontallyRight * horizontallyLeft;
    }
    unsigned int countTreesSeenVerticallyUp(unsigned int x_position, unsigned int y_position)
    {
        unsigned int result = 0;
        auto value = m_data[x_position][y_position];
        for(auto uprightIt = x_position; uprightIt > 0; uprightIt--)
        {
            result++;
            auto tmp = m_data[uprightIt - 1][y_position];
            if (value <= tmp)
                break;
        }
        return result;
    }

    unsigned int countTreesSeenVerticallyDown(unsigned int x_position, unsigned int y_position)
    {
        unsigned int result = 0;
        auto value = m_data[x_position][y_position];
        for(auto downrightIt = x_position+1; downrightIt < m_data.size(); downrightIt++)
        {
            result++;
            auto tmp =m_data[downrightIt][y_position];
            if(value <= tmp)
                break;
        }
        return result;
    }

    unsigned int countTreesSeenHorizontallyRight(unsigned int x_position, unsigned int y_position)
    {
        unsigned int result = 0;
        auto value = m_data[x_position][y_position];
        for(auto right = y_position+1; right < m_data[x_position].size(); right++)
        {
            result++;
            if(value <= m_data[x_position][right])
                break;
        }
        return result;
    }
    unsigned int countTreesSeenHorizontallyLeft(unsigned int x_position, unsigned int y_position)
    {
        unsigned int result = 0;
        auto value = m_data[x_position][y_position];
        for(auto left = y_position; left > 0; left--)
        {
            result++;
            auto tmp = m_data[x_position][left-1];
            if(value <= tmp)
                break;
        }
        return result;
    }

    bool isTreeVisible(unsigned int x_position, unsigned int y_position)
    {
        if(isPositionedOnTheEdge(x_position) or isPositionedOnTheEdge(y_position))
            return true;
        auto horizontally = checkVisibilityHorizontally(x_position,y_position);
        auto vertically = checkVisibilityVertically(x_position, y_position);
        auto isVisible = (horizontally or vertically);
        return isVisible;
    }

    bool checkVisibilityHorizontally(unsigned int x_position, unsigned int y_position)
    {
        auto maxRight =  std::max_element(m_data[x_position].begin() + y_position + 1,
                                     m_data[x_position].end());
        auto maxLeft = std::max_element(m_data[x_position].begin(),
                                        m_data[x_position].begin() + y_position);
        auto value = m_data[x_position][y_position];
        return value > *maxRight or value > *maxLeft;
    }

    bool checkVisibilityVertically(unsigned int x_position, unsigned int y_position)
    {
        auto value = m_data[x_position][y_position];
        bool isVisibleUpright = true;
        for(auto uprightIt = x_position; uprightIt > 0; uprightIt--)
        {
            auto tmp = m_data[uprightIt-1][y_position];
            if(value <= tmp)
                isVisibleUpright = false;
        }

        bool isDownright = true;
        for(auto downrightIt = x_position+1; downrightIt < m_data.size(); downrightIt++)
        {
            if(value <= m_data[downrightIt][y_position])
                isDownright = false;
        }
        return isVisibleUpright or isDownright;
    }

    bool isPositionedOnTheEdge(unsigned int position)
    {
        return position == 0 or position == m_data[0].size() - 1;
    }
    void parseInput()
    {
        m_data.clear();
        for(auto val : m_input)
        {
            std::vector<short> toAdd;
            for(const auto digit : val)
            {
                toAdd.push_back(digit - '0');
            }
            m_data.push_back(toAdd);
        }
    }
    std::string m_inputFileName;
    std::vector<std::string> m_input;

    std::vector<std::vector<short>> m_data;
};
