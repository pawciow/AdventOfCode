#include <iostream>
#include "FirstTask.hpp"
#include "SecondTask.hpp"
#include "TaskThree.hpp"
#include "TaskFour.hpp"
#include <regex>
#include <string>
void checkResults(TaskBase& task, std::string fileName)
{
    task.provideFileName(fileName);
    task.assertResults();
}
int main() {
    std::cout << "Hello, World!" << std::endl;

//    FirstTask task;
//    checkResults(task, "inputs/taskOne.txt");

//    SecondTask task;
//    checkResults(task, "inputs/taskTwo.txt");

//    TaskThree task;
//    checkResults(task, "inputs/taskThree.txt");

    TaskFour task;
    checkResults(task, "inputs/taskFour.txt");
    return 0;
}
