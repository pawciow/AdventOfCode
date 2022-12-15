#include <iostream>
#include "tasks/Day1.hpp"
#include "tasks/Day2.hpp"
#include "tasks/Day3.hpp"
#include "tasks/Day4.hpp"
#include "tasks/Day5.hpp"
#include <regex>
#include <string>
#include "tasks/Day6.hpp"
#include "tasks/Day7.hpp"
#include "tasks/Day8.hpp"
#include "tasks/Day9.hpp"

#include "tasks/Day11.hpp"
#include "tasks/Day12.hpp"
#include "tasks/Day13.hpp"
#include "tasks/Day14.hpp"
#include "tasks/Day15.hpp"

void checkResults(TaskBase& task, std::string fileName)
{
    task.provideFileName(fileName);
    task.assertResults();
}

void checkAll()
{
    Day1 task1;
    checkResults(task1, "inputs/taskOne.txt");

    Day2 task2;
    checkResults(task2, "inputs/taskTwo.txt");

    Day3 task3;
    checkResults(task3, "inputs/taskThree.txt");

    Day4 task4;
    checkResults(task4, "inputs/taskFour.txt");

    Day5 task5;
    checkResults(task5, "inputs/taskFive.txt");

    Day6 task6;
    checkResults(task6, "inputs/taskSix.txt");

    Day7 task7;
    checkResults(task7, "inputs/taskSeven.txt");

    Day8 task8;
    checkResults(task8, "inputs/taskEight.txt");

    Day9 task9;
    checkResults(task9, "inputs/taskNine.txt");

    Day11 task11;
    checkResults(task11, "inputs/taskEleven.txt");

    Day12 task12;
    checkResults(task12, "inputs/taskTwelve.txt");

    Day13 task13;
    checkResults(task13, "inputs/taskThirteen.txt");

    Day14 task14;
    checkResults(task14, "inputs/taskFourteen.txt");
}


int main()
{
    std::cout << "Hello, World!" << std::endl;

    Day15 task15;
    checkResults(task15, "inputs/taskFifteen.txt");

//    checkAll(); // Be sure that You put all inputs with correct names in folder inputs/
    return 0;
}
