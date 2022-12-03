#include <iostream>
#include "FirstTask.hpp"
#include "SecondTask.hpp"
#include "TaskThree.hpp"

void checkResults(TaskBase& task, std::string fileName)
{
    task.provideFileName(fileName);
    task.assertResults();
}
int main() {
    std::cout << "Hello, World!" << std::endl;

//    FirstTask task;
//    checkResults(task, "inputs/taskOne.txt");

    SecondTask task;
    checkResults(task, "inputs/taskTwo.txt");

//    TaskThree task;
//    checkResults(task, "inputs/taskThree.txt");


    return 0;
}
