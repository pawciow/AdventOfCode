#pragma once
#include "TaskBase.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>
#include <functional>
#include <ranges>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string_view>


#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

class TaskFourteen : public TaskBase{
public:
    using Coords = std::pair<unsigned int, unsigned int>;
    void assertResults() override
    {
        auto firstResult = solveFirstTask();
        assert(firstResult == 24); // test

        auto secondResult = solveSecondTask();
//        assert(secondResult == 522);
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
        m_tiles = {};
        m_rockPositions={};
        readData();
        createEmptyTiles();
        parseInput();
        fetchRocksFromInputToTiles();

        printTilesFromRange(494,503,0,9);

        auto startingCoords = m_sandProducingHole;
        for(int i = 0; i < 8; i++)
        {
            processMove(startingCoords);
            printTilesFromRange(494,503,0,9);
        }

        return {};
    }
    unsigned int solveSecondTask() override
    {
        return {};
    }

private:
    enum class Tile{
        air,
        rock,
        sand
    };

    friend std::ostream& operator << (std::ostream& os, const Tile& obj)
    {
        switch(obj)
        {
            case Tile::air:
            {
                os << ".";
                break;
            }
            case Tile::rock:
            {
                os << "#";
                break;
            }
            case Tile::sand:
            {
                os << "o";
                break;
            }
        }
        return os;
    }

    Coords m_sandProducingHole = {500,0};
    unsigned int max_y = 100;
    unsigned int max_x = 600;

    std::vector<std::vector<Tile>> m_tiles;
    std::vector<Coords> m_rockPositions;

    void processMove(Coords& position)
    {
        auto& [x, y] = position;

        if(isTileEmpty({x,y+1}))
        {
            m_tiles[y][x] = Tile::air;
            position.second += 1;
            m_tiles[y][x] = Tile::sand;
        }
    }

    bool isTileEmpty(const Coords& position)
    {
        auto& [x, y] = position;
        return m_tiles[y][x] == Tile::air;
    }

    void createEmptyTiles()
    {
        for(auto y = 0; y < max_y; y++)
        {
            std::vector<Tile> row(max_x, Tile::air);
            m_tiles.push_back(row);
        }
    }

    void fetchRocksFromInputToTiles()
    {
        for(const auto& [x,y] : m_rockPositions)
        {
            m_tiles[y][x] = Tile::rock;
        }
    }

    void printTilesFromRange(const unsigned int x_low, const unsigned int x_high,
                             const unsigned int y_low,const unsigned int y_high)
    {
        for(int it_y = y_low; it_y <= y_high; it_y++)
        {
            std::cout << it_y << "  ";
            for(auto it_x = x_low; it_x <= x_high; it_x++)
            {
                std::cout << m_tiles[it_y][it_x];
            }
            std::cout << std::endl;
        }
    }
    std::string m_inputFileName;
    std::vector<std::string> m_input;

    void parseInput()
    {
        auto filterEmptyLines = [](const std::string& str){return not str.empty();};
        for (const auto& line : m_input)
        {
            std::vector<Coords> rockPositionsContours;
            std::vector<std::string> instructions; // std::views::split not works
            boost::split(instructions, line, boost::is_any_of("->"));
            for(const auto el: instructions | std::views::filter(filterEmptyLines))
            {
                std::vector<std::string> coords; // std::views::split not works
                boost::split(coords, el, boost::is_any_of(","));
                if(coords.size() == 2)
                {
                    rockPositionsContours.push_back({std::stoi(coords[0]),std::stoi(coords[1])});
                }
            }

            if(not rockPositionsContours.empty())
            {
                for(auto it = 0; it < rockPositionsContours.size() - 1; it++)
                {
                    auto [first_x, first_y] = rockPositionsContours[it];
                    auto [second_x, second_y] = rockPositionsContours[it+1];

                     if(first_x == second_x)
                     {
                         for(auto y = std::min(first_y, second_y); y <= std::max(first_y, second_y); y++)
                         {
                             m_rockPositions.push_back({first_x,y});
                         }
                     }
                     if(first_y == second_y)
                     {
                         for(auto x = std::min(first_x, second_x); x <= std::max(first_x, second_x); x++)
                         {
                             m_rockPositions.push_back({x,first_y});
                         }
                     }
                }
            }
        }
    }
};