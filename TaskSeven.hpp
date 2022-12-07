#pragma once

#include "TaskBase.hpp"
#include <vector>
#include <cassert>
#include <fstream>
#include <list>
#include <string>
#include <string_view>
#include <ranges>
#include <iomanip>
#include <iostream>


class TaskSeven : public TaskBase{
public:
    TaskSeven()
    {
        Node root("/", {});
        m_root = std::make_shared<Node>(root);
    }
    void assertResults() override {
        auto firstResult = solveFirstTask();
        assert(firstResult == 0);

        auto secondResult = solveSecondTask();
        assert(secondResult == 0);
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

    void parseInput()
    {
        std::shared_ptr<Node> processedNode = m_root;
        std::string type, name;
        unsigned int size;
        for(const auto& line : m_input)
        {
            std::stringstream ss;
            ss << line;
            ss >> type;
            if(type == "$")
            {
                ss >> type;
                if(type == "ls")
                {
                    continue;
                }
                ss >> name;
                if(type == "cd")
                {
                    if(name == "..")
                    {
                        processedNode = processedNode->m_parent.lock();
                        if(processedNode == nullptr)
                        {
                            throw std::runtime_error("Messed up finding parent!");
                        }
                        continue;
                    }
                    processedNode = processedNode->getChild(name);
                    continue;
                }
            }
            if(type == "dir")
            {
                ss >> name;
                processedNode->m_nodes.push_back(std::make_shared<Node>(name, processedNode));
                continue;
            }
            size = std::stoi(type);
            ss >> name;
            processedNode->m_nodes.push_back(std::make_shared<File>(name,size, processedNode));
        }
    }
    struct Node {
    public:
        Node(std::string name, std::weak_ptr<Node> parent) : m_name(name), m_parent(parent) {}
        std::string m_name;
        std::weak_ptr<Node> m_parent;
        std::vector<std::shared_ptr<Node>> m_nodes;

        std::shared_ptr<Node> getChild(const std::string& childName)
        {
            for(const auto& node : m_nodes)
            {
                if(node->m_name == childName)
                    return node;
            }
            throw std::runtime_error("Messed up finding child!");
            return {};
        }
        virtual unsigned int getSize()
        {
            unsigned int result = 0;
            for(const auto node : m_nodes)
            {
                std::cout << "Visiting node: " << node->m_name << std::endl;
                result += node->getSize();
            }
            return result;
        }

        unsigned int getSizeIfLessThan(unsigned int threshold = 100000)
        {
            unsigned int result = 0;
            for(const auto& node : m_nodes)
            {
                auto nodeSize = node->getSize();
                std::cout << "Node: " << node->m_name << " contains: " << nodeSize << std::endl;
                if(nodeSize < threshold)
                {
                    result += nodeSize;
                }
            }
            auto isHasSubdirectories = [](const std::shared_ptr<Node> nodePtr){
                return nodePtr->m_nodes.size() != 0;
            };
            for(const auto& node: m_nodes | std::views::filter(isHasSubdirectories))
            {
                std::cout << "Shoudl visit node : " << node->m_name;
            }
            return result;
        }
    };

    struct File : public Node{
        File(std::string name, unsigned int size, std::weak_ptr<Node> parent) : Node(name, parent), m_size(size) {}
        unsigned int m_size;
        virtual unsigned int getSize() override
        {
            return m_size;
        }

    };

    unsigned int solveFirstTask() override
    {
        readData();
        parseInput();

        auto result = m_root->getSizeIfLessThan();
        std::cout << "For my first star result is: " << result << std::endl;

        return {};
    }
    unsigned int solveSecondTask() override
    {
        return {};
    }

private:
    std::shared_ptr<Node> m_root;

    std::string m_inputFileName;
    std::vector<std::string> m_input;
};