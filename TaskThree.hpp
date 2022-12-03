#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include "TaskBase.hpp"


class TaskThree : public TaskBase{
public:
    void assertResults() override
    {
        auto firstResult = solveFirstTask();
        assert(firstResult == 7793);

        auto secondResult = solveSecondTask();
        assert(secondResult == 2499);
    }

    void provideFileName(std::string fileName) override
    {
        m_inputFileName = fileName;
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

    unsigned int solveFirstTask() override
    {
        readData();
        std::vector<char> finalResult;
        for(const auto & line: m_input)
        {
            std::vector<char> intersection_result;  // need separate vector to move to final results only one element
                                                    // e.g. for rsFMfFZSrLrFZsSL and jqHRNqRjqzjGDLGL
                                                    // intersection returns [L, L] and i need only one letter

            auto firstHalf = line.substr(0, line.length() / 2);
            auto secondHalf = line.substr(line.length() / 2);

            auto a = prepareVectorToIntersect(firstHalf);
            auto b = prepareVectorToIntersect(secondHalf);

            std::set_intersection(a.begin(), a.end(),
                                  b.begin(), b.end(),
                                  std::back_inserter(intersection_result));

            finalResult.push_back(intersection_result[0]);
        }

        unsigned int result =0;
        for(const auto & el: finalResult)
        {
            result += convertCharToClassNumber(el);
        }
        std::cout << " For my first star result is: " << result << std::endl;
        return result;
    }

    unsigned int solveSecondTask() override
    {
        readData();
        std::vector<char> finalResult;
        std::cout << m_input.size() << std::endl;
        for(unsigned int i = 0; i < m_input.size(); i+=3)
        {
            std::vector<char> intersection_result;
            std::vector<char> first_intersection;

            auto a = prepareVectorToIntersect(m_input[i]);
            auto b = prepareVectorToIntersect(m_input[i+1]);
            auto c = prepareVectorToIntersect(m_input[i+2]);


            std::set_intersection(a.begin(), a.end(),
                                  b.begin(), b.end(),
                                  std::back_inserter(first_intersection));

            std::sort(first_intersection.begin(), first_intersection.end());
            std::set_intersection(first_intersection.begin(), first_intersection.end(),
                                  c.begin(), c.end(),
                                  std::back_inserter(intersection_result));
            finalResult.push_back(intersection_result[0]);
        }

        unsigned int result = 0;
        for(const auto & el: finalResult)
        {
            result += convertCharToClassNumber(el);
        }
        std::cout << " For my second star result is: " << result << std::endl;

        return 0;
    }
private:
    std::string m_inputFileName;
    std::vector<std::string > m_input;
    static unsigned int convertCharToClassNumber(char val)
    {
        // https://en.cppreference.com/w/cpp/language/ascii
        auto converted = static_cast<unsigned int>(val);
        if(val >= 'A' && val <= 'Z')
        {
            converted -= '@';
            converted += 26; // because A is after z
        }
        else if( val >= 'a'  and val <= 'z')
        {
            converted -= '`';
        }
        else
        {
            throw std::runtime_error("Messed up converting action!");
        }
        return  converted;
    }

    static std::vector<char> prepareVectorToIntersect(std::string val)
    {
        std::vector<char> toReturn(val.begin(), val.end());
        std::sort(toReturn.begin(), toReturn.end());
        return toReturn;
    }
};