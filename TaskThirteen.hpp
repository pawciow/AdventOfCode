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
#include <variant>

class TaskThirteen : public TaskBase {

    struct Packets : std::variant<unsigned int, std::vector<Packets>>{

        Packets* parent;

        using std::variant<unsigned int, std::vector<Packets>>::variant;

        std::vector<Packets>& getList()
        {
            return std::get<std::vector<Packets>>(*this);
        }
        unsigned int& getInt()
        {
            return std::get<unsigned int>(*this);
        }

        friend std::ostream& operator<<(std::ostream& s, Packets& packet) {
            if(packet.index() == 0)
            {
                s << packet.getInt();
                return s;
            }
            auto vec = packet.getList();
            s << "[";
            for(auto& el : vec)
            {
                   s << el << ",";
            }
            s << "]";
            return s;
        }
    };

    void assertResults() override {
        auto firstResult = solveFirstTask();
        assert(firstResult == 13); //

//        auto secondResult = solveSecondTask();
//        assert(secondResult == 39109444654);
    }

    void readData() override {
        m_input.clear();
        std::ifstream ss(getInput(m_inputFileName));
        for (std::string line; getline(ss, line);) {
            m_input.push_back(line);
        }
    }

    void provideFileName(std::string fileName) override {
        m_inputFileName = fileName;
    }

    virtual unsigned int solveFirstTask() override {
        unsigned int result = 1;
        readData();
        parseData();
        for(auto el: m_data)
            std::cout << el;
        std::cout << "For my first star result is: " << result << std::endl;
        return result;
    }

    virtual unsigned int solveSecondTask() override {
        unsigned int result = 0;
        return result;
    }

private:
    void parseNextPackets(int& j, std::string& line, Packets& packets)
    {
        auto& list = packets.getList();
        for(; j < line.size(); )
        {
            if(line[j] == '[')
            {
                j++;
                Packets child = std::vector<Packets>{};
                child.parent = &packets;
                list.push_back(child);
                parseNextPackets(j,line,list.back());
            }
            else if (line[j] == ']')
            {
                j++;
                if(packets.parent)
                {
                    if(j+1 == ',')
                    {
                        j +=2;
                    }
                    parseNextPackets(j, line, *packets.parent);
                }
            }
            else {
                auto num = extractNumber(j,line);
                list.push_back(num);
            }
        }
    }

    unsigned int extractNumber(int& j, std::string& line)
    {
        for(int it = j+1; it < line.size(); it++)
        {
            if(line[it] == ',' or line[it] == ']')
            {
                std::string num(line.begin()+j, line.begin()+it);
//                std::cout << "Before: " << num << std::endl;
//
                while (num.starts_with(',') or num.starts_with('['))
                    num.erase(0,1);
                std::cout << num << std::endl;
                j = it;
                return std::stoi(num);
            }
        }
        j = line.size();
        std::string lastInt(line.end()-1, line.end());
        return std::stoi(lastInt);
    }
    void parseData()
    {
        std::stringstream ss;
        for(auto& line : m_input)
        {
            line.pop_back(); // to remove newline
            Packets packets = std::vector<Packets>{};

            for(int j = 0; j < line.size(); j++)
            {
                if(line[j]=='[')
                {
                    parseNextPackets(j,line, packets);
                }
            }
            m_data.push_back(packets);
        }
    }
//    unsigned int findBeginofNextList(std::string& line)
//    {
//        for(int i = 0; i < line.size(); i++)
//        {
//            if(line[i] == '[')
//                return i;
//            throw std::runtime_error("Messed up finding begin of this list!");
//        }
//    }
    unsigned int findEndOfNextList(std::string& line)
    {
        for(int i = 0; i <line.size(); i++)
        {
            auto character = line[i];
            if(character == ']')
                return i;
        }
        throw std::runtime_error("Messed up finding end of this list!");
    }

    std::vector<std::string> split (const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (getline(ss, item, delim)) {
            result.push_back(item);
        }

        return result;
    }
    std::string m_inputFileName;
    std::vector<std::string> m_input;

    std::vector<Packets> m_data;
};