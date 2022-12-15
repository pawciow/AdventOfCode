#pragma once
#include "../TaskBase.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>
#include <functional>
#include <ranges>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string_view>

#include <boost/lexical_cast.hpp>

class Day15 : public TaskBase {
public:
    using Coords = std::pair<int64_t , int64_t>;
    struct Sensor{
        Coords position;
        Coords nearestBeaconPosition;

        uint64_t scanRange;
    };

    friend std::ostream& operator << (std::ostream& os, const Sensor& obj)
    {
        os << "(" << obj.position.first << "," <<obj.position.second << ")" << " range: " << obj.scanRange;
        return os;
    }

    void assertResults() override {
        auto firstResult = solveFirstTask();
        assert(firstResult == 26); // test data
//        assert(firstResult == 698); //

//        auto secondResult = solveSecondTask();
//        assert(secondResult == 93); // test data
//        assert(secondResult == 28594);
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

    unsigned int solveFirstTask() override
    {
        readData();
        parseInputData();
        firstExampleWantedLine = std::vector<bool>(3414925*2, false);
        auto reachableSensors = [&](const Sensor& sensor){
            return this->canSensorReachMarkedLine(sensor);
        };
        for(const auto& sensor : m_sensors | std::views::filter(reachableSensors))
        {
            std::cout << "Sensor with coordinates:" << sensor << std::endl;
            markReachableTiles(sensor);
        }
        for(const auto& sensor: m_sensors)
        {
            if(sensor.nearestBeaconPosition.second == firstExampleWantedNum)
            {
                firstExampleWantedLine[sensor.nearestBeaconPosition.first] = false; // because its not possible to place beacon on beacon
            }
        }
        auto result = std::count_if(firstExampleWantedLine.begin(), firstExampleWantedLine.end(), [](const auto& el){
           return el;
        });
        return result;
    }
    unsigned int solveSecondTask() override
    {
        return {};
    }

private:
    bool canSensorReachMarkedLine(const Sensor& sensor)
    {
        if(sensor.position.second <= firstExampleWantedNum)
            return sensor.position.second + sensor.scanRange >= firstExampleWantedNum;
        else{
            return sensor.position.second - sensor.scanRange <= firstExampleWantedNum;
        }
    }
    void markReachableTiles(const Sensor& sensor)
    {
        auto [x, y] = sensor.position;
        int64_t y_distance = 0;
        int64_t rangeToSpare = 0;

        if (y > firstExampleWantedNum)
        {
            y_distance = y - firstExampleWantedNum;
        }
        else
        {
            y_distance = firstExampleWantedNum - y;
        }
        rangeToSpare = sensor.scanRange - y_distance;
        markAlongXAxis(x,rangeToSpare);
        std::cout << "Distance : " << y_distance << " spare range: " << rangeToSpare << std::endl;
    }
    void markAlongXAxis(int64_t x_position, int64_t distance)
    {
        assert(x_position-distance > 0);
        for(int i = x_position - distance; i <= x_position+distance;i++)
        {
            firstExampleWantedLine[i] = true;
        }
    }

    void parseInputData()
    {
        std::string sensor,at,x_sensor_pos, y_sensor_pos, closest, beacon, is, _at, x_beacon_pos, y_beacon_pos;
        for(const auto& line : m_input)
        {
            std::stringstream ss;
            ss << line;
            ss >> sensor >> at >> x_sensor_pos >> y_sensor_pos
                >> closest >> beacon >>  is >>  _at >>  x_beacon_pos >>  y_beacon_pos;

            trimCoordinate(x_sensor_pos);
//            auto x_sensor_pos_num = ;
            trimCoordinate(y_sensor_pos);
            trimCoordinate(x_beacon_pos);
            trimCoordinate(y_beacon_pos);

            Sensor sensor1;
//            sensor1.position = std::make_pair(std::stoll(x_sensor_pos) + offsetXToRemoveMinusValues,std::stoll(y_sensor_pos));
            sensor1.position = std::make_pair( boost::lexical_cast<uint64_t>(x_sensor_pos) + offsetXToRemoveMinusValues,std::stoll(y_sensor_pos));
            sensor1.nearestBeaconPosition = std::make_pair(std::stoll(x_beacon_pos) + offsetXToRemoveMinusValues,std::stoll(y_beacon_pos));
            sensor1.scanRange = abs(sensor1.position.first - sensor1.nearestBeaconPosition.first)
                    + abs(sensor1.position.second - sensor1.nearestBeaconPosition.second);

            m_sensors.push_back(sensor1);

        }
    }
    void trimCoordinate(std::string& str)
    {
        str.erase(0,2);
        if(str.back() == ',' or str.back() == ':' or str.back() == '\r')
            str.pop_back();
    }

    std::string m_inputFileName;
    std::vector<std::string> m_input;

    std::vector<Sensor> m_sensors;

    const unsigned int offsetXToRemoveMinusValues = 1442554/2;
//    const unsigned int offsetYToRemoveMinusValues = 20;
//    const int64_t firstExampleWantedLine = 2000000;

    std::vector<bool> firstExampleWantedLine;
//    const int64_t firstExampleWantedNum = 10;
    const int64_t firstExampleWantedNum = 2000000;
};