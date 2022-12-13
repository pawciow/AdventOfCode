#include <iostream>
#include "FirstTask.hpp"
#include "SecondTask.hpp"
#include "TaskThree.hpp"
#include "TaskFour.hpp"
#include "TaskFive.hpp"
#include <regex>
#include <string>
#include "TaskSix.hpp"
#include "TaskSeven.hpp"
#include "TaskEight.hpp"
#include "TaskNine.hpp"

#include "TaskEleven.hpp"
#include "TaskTwelve.hpp"
#include "TaskThirteen.hpp"

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

//    TaskFour task;
//    checkResults(task, "inputs/taskFour.txt");
//
//    TaskFive task;
//    checkResults(task, "inputs/taskFive.txt");

//    TaskSix task;
//    checkResults(task, "inputs/taskSix.txt");

//    TaskSeven task;
//    checkResults(task, "inputs/taskSeven.txt");

//    TaskEight task;
//    checkResults(task, "inputs/taskEight.txt");

//    TaskEleven task;
//    checkResults(task, "inputs/taskEleven.txt");

    TaskTwelve task;
    checkResults(task, "inputs/taskTwelve.txt");

//    TaskThirteen task;
//    checkResults(task, "inputs/taskThirteen.txt");

    return 0;
}
