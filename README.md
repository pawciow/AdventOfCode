# AdventOfCode
This is my repository for Advent of Code 2022. I wanted to participate to train my algorthmics and learn C++20 features in practice.

# What is AdventOfCode
This is a competition held every year during the Advent, available on https://adventofcode.com/
> Advent of Code is an Advent calendar of small programming puzzles for a variety of skill sets and skill levels that can be solved in any programming language you like.

# Minimal requirements to build
- C++20
- GCC 11.0
- Boost

# How to build
1. Navigate to project folder 
2. Create build folder 
> mkdir _build
3. Create "inputs" folder
> mkdir inputs
4. Navigate to build folder 
> cd _build
5. Run cmake 
> cmake ..
6. Make project 
> make

# How it works

In main function you can create a class associated to specific day during the competition. After creation you can pass it down to a helper function called _"checkResults()"_ with corresponding input file name. 
Remember to download input file and put it in inputs folder.

For task five it should look like this:
* in main.cpp:
```c
int main() {
    TaskFive task;
    checkResults(task, "inputs/taskFive.txt");
}
```

# Example output
Example output for example given in previous section:
> Task path is "/mnt/c/projects/AdventOfCode/inputs/taskFive.txt" <br>
> For my first star result is: ZWHVFWQWW <br>
> Task path is "/mnt/c/projects/AdventOfCode/inputs/taskFive.txt" <br>
> For my second star result is: HZFZCCWWV <br>
