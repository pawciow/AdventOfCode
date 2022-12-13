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

// Unfortunately the parsing was a nightmare, so I looked up to solution https://gist.github.com/ParadoxsHorizon/a5a783a3d867cc9151f0bc70a4bb4559#file-day13-cpp
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

        std::weak_ordering compare(Packets& other) {
            if(index()==0 and other.index()==0)
                return getInt() <=> other.getInt();

            std::vector<Packets> left;
            if(index() == 0)
            {
                left.push_back(getInt());
            } else{
                left = this->getList();
            }

            std::vector<Packets> right;
            if(other.index() == 0)
            {
                right.push_back(other.getInt());
            } else{
                right = other.getList();
            }

            auto size = std::min(right.size(), left.size());
            for(auto i = 0; i < size; i++)
            {
                auto ordering = left[i].compare(right[i]);
                if(ordering != std::weak_ordering::equivalent)
                {
                    return ordering;   // It will return if items are not equal
                }
            }

            if(left.size() < right.size())
                return std::weak_ordering::less;
            if(left.size() > right.size())
                return std::weak_ordering::greater;

            return std::weak_ordering::equivalent;
        }
    };

    void assertResults() override {
        auto firstResult = solveFirstTask();
        assert(firstResult == 6415); //

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
        unsigned int result = 0;
        m_data = {};
        readData();
        parseData();

        unsigned int pairNumber=0;
        for(unsigned int i = 0; i < m_data.size(); i+=2)
        {
            pairNumber++;
            auto ordering = m_data[i].compare(m_data[i+1]);
            if(ordering == std::weak_ordering::less)
            {
                result += pairNumber;
                std::cout << "Pair number " << pairNumber << " is correct" << std::endl;
            }
        }
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
                while (num.starts_with(',') or num.starts_with('['))
                    num.erase(0,1);
                std::cout << num << std::endl;
                j = it;
                if(num.empty())
                    return {};
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
            if(line == "\r")
                continue;
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