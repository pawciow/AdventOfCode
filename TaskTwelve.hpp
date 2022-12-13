#pragma once
#include "TaskBase.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>
#include <functional>
#include <stack>
#include <queue>
#include <limits>
#include <optional>

class TaskTwelve : public TaskBase{
public:
    using Coords = std::pair<unsigned int, unsigned int>;
    void assertResults() override
    {
        auto firstResult = solveFirstTask();
        assert(firstResult == 31); //

//        auto secondResult = solveSecondTask();
//        assert(secondResult == 39109444654);
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
        unsigned int result = 0;
        readData();
        parseData();
        result = createGraph();
        std::cout << "For my first star result is: " << result << std::endl;
        return result;
    }
    unsigned int solveSecondTask() override
    {
        unsigned int result = 0;
        return result;
    }
private:
    void parseData()
    {
        for(auto line : m_input)
        {
            std::vector<char> vec(line.begin(), line.end());
            if(vec.back() == '\r')
            vec.pop_back();
            m_data.push_back(vec);
        }
    }

    static bool checkIfPossibleToClimb(char lhs, char rhs)
    {
        return lhs == rhs
                or lhs > rhs
                or abs(lhs - rhs) == 1
                or lhs == 'z' and rhs == 'E'
                or lhs == 'S';
    }

    unsigned int createGraph()
    {
        myGraph graph(m_data);
        graph.calculateShortestPaths();
         return graph.tiles[20][158].shortestPath;
    }

    std::string m_inputFileName;
    std::vector<std::string> m_input;

    std::vector<std::vector<char>> m_data;

    struct myGraph{
        struct Tile{
            char name;
            unsigned int x,y;
            unsigned int shortestPath = std::numeric_limits<unsigned int >::max() ;
        };
        using PQueue =  std::priority_queue<Coords, std::vector<Coords>, std::function<bool(Coords, Coords)>>;
        Tile& getTile(Coords coordinates)
        {
            return tiles[coordinates.first][coordinates.second];
        }

        std::vector<std::vector<Tile>> tiles;

        explicit myGraph(const std::vector<std::vector<char>>& vec)
        {
            for(auto y = 0; y < vec.size(); y++)
            {
                std::vector<Tile> rowVec;
                for(auto x = 0; x < vec[y].size(); x++)
                {
                    Tile tile;
                    tile.name = vec[y][x];
                    tile.x = x;
                    tile.y = y;
                    rowVec.push_back(tile);
                }
                tiles.push_back(rowVec);
            }
        }
        void calculateShortestPaths()
        {
            auto start = findTile('S');
            auto end = findTile('E');
            std::cout << " End at " << end.y <<  "," << end.x << std::endl;

            auto largestVisited = 'a';
            start.shortestPath = 0;
            tiles[start.y][start.x].shortestPath = 0;
            auto cmp = [&](Coords lhs, Coords rhs){
                return  tiles[lhs.first][lhs.second].shortestPath > tiles[rhs.first][rhs.second].shortestPath;
            };

            PQueue tileQueue(cmp);
            tileQueue.push( {start.y,start.x});
            while (not tileQueue.empty())
            {
                auto pair = tileQueue.top();
                auto& node = getTile(pair);
                largestVisited = std::max(largestVisited, node.name);
                tileQueue.pop();

                auto neighbours = getNeighbours(pair);
                for(auto& neighbour : neighbours)
                {
                    handleNeighbour(node.shortestPath, neighbour, tileQueue);
                }
            }
            std::cout << "Largest visited is: " << largestVisited << std::endl;
        }

        std::vector<std::optional<Coords>> getNeighbours(const Coords& tile)
        {
            auto top = getTopNeighbour(tile);
            auto bottom = getBottomNeighbour(tile);
            auto left = getLeftNeighbour(tile);
            auto right = getRightNeighbour(tile);

            return {top,bottom,left,right};
        }

        std::optional<Coords>  getBottomNeighbour(const Coords& currentCoords)
        {
            if( currentCoords.first + 1 < this->tiles.size())
            {
                Tile currentTile = getTile(currentCoords);

                auto bottomNeighbourCoords = currentCoords;
                bottomNeighbourCoords.first +=1;
                auto& bottomNeighbour = getTile(bottomNeighbourCoords);

                if(checkIfPossibleToClimb(currentTile.name, bottomNeighbour.name))
                    return {bottomNeighbourCoords};
            }
            return {};
        }
        std::optional<Coords> getTopNeighbour(const Coords& currentCoords)
        {
            if( currentCoords.first  > 0)
            {
                Tile currentTile = getTile(currentCoords);

                auto topNeighbourCoords = currentCoords;
                topNeighbourCoords.first -=1;
                auto& topNeighbour = getTile(topNeighbourCoords);

                if(checkIfPossibleToClimb(currentTile.name, topNeighbour.name))
                    return {topNeighbourCoords};
            }
            return {};
        }
        std::optional<Coords>  getRightNeighbour(const Coords& currentCoords)
        {
            if( currentCoords.second + 1 < this->tiles[0].size())
            {
                Tile currentTile = getTile(currentCoords);

                auto rightNeighbourCoords = currentCoords;
                rightNeighbourCoords.second +=1;
                auto& rightNeighbour = getTile(rightNeighbourCoords);

                if(checkIfPossibleToClimb(currentTile.name, rightNeighbour.name))
                    return {rightNeighbourCoords};
            }
            return {};
        }
        std::optional<Coords>  getLeftNeighbour(const Coords& currentCoords)
        {
            if( currentCoords.second > 0)
            {
                Tile currentTile = getTile(currentCoords);

                auto leftNeighbourCoords = currentCoords;
                leftNeighbourCoords.second -=1;
                auto& leftNeighbour = getTile(leftNeighbourCoords);

                if(checkIfPossibleToClimb(currentTile.name, leftNeighbour.name))
                    return {leftNeighbourCoords};
            }
            return {};
        }

        void printNotVisitedTiles()
        {
            for(const auto& col : tiles)
            {
                for(const auto& row : col)
                {
                    printTile(row);
                }
            }
        }
        void printTile(const Tile& tile)
        {
            std::cout << tile.name << " on coords: " << tile.y << "," << tile.x << std::endl;
        }
        Tile findTile(char toFind)
        {
            for(const auto& col : tiles)
            {
                for(const auto& row : col)
                {
                    if(row.name == toFind)
                    {
                        return row;
                    }
                }
            }
            return {};
        }
        void handleNeighbour(unsigned int nodeShortestPath, std::optional<Coords>& neighbourTileCoords, PQueue & queue)
        {
            if(neighbourTileCoords.has_value())
            {
                auto& neighbourTile = getTile(neighbourTileCoords.value());
                auto possibleShortestPath =  nodeShortestPath + 1;
                if(neighbourTile.shortestPath > possibleShortestPath)
                {
                    neighbourTile.shortestPath = possibleShortestPath;
                    queue.push(neighbourTileCoords.value());
                }
            }
        }
    };
};