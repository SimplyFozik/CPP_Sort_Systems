/*
    Fozik's Code Team
    Author: Fozik
    Version: 1.0.2
    Project: SA
*/

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <string>
#include "SortingSource.h"

using namespace std;
using namespace chrono;

template <typename ElementType>
void populateContainer(vector<ElementType>& container)
{
    srand(time(0));
    for (int index = 0; index < container.size(); index++)
    {
        container[index] = rand() % 100;
    }
}

class PerformanceTimer
{
public:
    steady_clock::time_point measurementStart;
    steady_clock::time_point measurementEnd;

    void startMeasurement() { measurementStart = steady_clock::now(); }
    void stopMeasurement() { measurementEnd = steady_clock::now(); }

    float getDuration(const int timeUnit) const
    {
        switch (timeUnit)
        {
        case TIME_UNIT_SECONDS:
            return duration_cast<duration<float>>(measurementEnd - measurementStart).count();
        case TIME_UNIT_MILLIS:
            return duration_cast<duration<float, milli>>(measurementEnd - measurementStart).count();
        case TIME_UNIT_MICROS:
            return duration_cast<duration<float, micro>>(measurementEnd - measurementStart).count();
        case TIME_UNIT_NANOS:
            return duration_cast<duration<float, nano>>(measurementEnd - measurementStart).count();
        default:
            return 0.0f;
        }
    }

    template <typename ContainerType>
    float calculateAverageDuration(const int timeUnit, const int algorithmType,
        const int iterations, vector<ContainerType>& data)
    {
        float totalDuration = 0.0f;
        for (int iteration = 0; iteration < iterations; iteration++)
        {
            populateContainer(data);

            switch (algorithmType)
            {
            case SORT_BUBBLE:
                startMeasurement();
                bubbleSort(data);
                stopMeasurement();
                break;
            case SORT_SELECTION:
                startMeasurement();
                selectionSort(data);
                stopMeasurement();
                break;
            case SORT_INSERTION:
                startMeasurement();
                insertionSort(data);
                stopMeasurement();
                break;
            case SORT_QUICK:
                startMeasurement();
                quickSort(data);
                stopMeasurement();
                break;
            }

            totalDuration += getDuration(timeUnit);
        }

        return totalDuration / iterations;
    }

private:
    enum TimeUnits {
        TIME_UNIT_SECONDS = 1,
        TIME_UNIT_MILLIS,
        TIME_UNIT_MICROS,
        TIME_UNIT_NANOS
    };

    enum SortingAlgorithms {
        SORT_BUBBLE = 1,
        SORT_SELECTION,
        SORT_INSERTION,
        SORT_QUICK
    };
};

template <typename ElementType>
void printContainer(const vector<ElementType>& container, const string& label)
{
    cout << endl << label << " elements: ";
    for (const auto& element : container)
    {
        cout << element << ' ';
    }
}

template <typename ContainerType>
void executeAsyncCalculation(const int timeUnit, const int algorithmType,
    const int iterations, vector<ContainerType>& data)
{
    auto futureResult = async(launch::async, [timeUnit, algorithmType, iterations, &data]() {
        PerformanceTimer timer;
        return timer.calculateAverageDuration(timeUnit, algorithmType, iterations, data);
        });

    cout << futureResult.get() << " ms";
}

int main()
{
    PerformanceTimer benchmark;
    vector<int> dataset(1000, 0);
    populateContainer(dataset);

    cout << "Calculating average sorting algorithm execution time..." << endl;
    executeAsyncCalculation(2, 2, 1000, dataset);
}