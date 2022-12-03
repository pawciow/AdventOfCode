#pragma once

#include <filesystem>
#include <iostream>

class TaskBase{
public:
    virtual void provideFileName(std::string fileName) = 0;
    virtual unsigned int solveFirstTask() = 0;
    virtual unsigned int solveSecondTask() = 0;
    virtual void assertResults() = 0;
protected:
    virtual void readData() = 0;
    std::filesystem::path getInput(std::string fileName)
    {
        auto currentPath = std::filesystem::current_path();
        auto filePath = currentPath.parent_path().append(fileName);
        std::cout << "Task path is " << filePath << '\n';
        return filePath;
    };
};

