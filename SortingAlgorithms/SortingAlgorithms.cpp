/*
    Fozik's Code Team
    Author: Fozik
    Version: 1.1.0
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

constexpr float CPU_LOAD_FACTOR = 1.0f;

template <typename ElementType>
void populateContainer(vector<ElementType>& container)
{
    for (int i = 0; i < container.size(); ++i) {
        container[i] = rand() % 10000;
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
    float calculateAverageDuration(const int timeUnit, const int algorithmType, const int iterations, vector<ContainerType>& data)
    {
        float totalDuration = 0.0f;
        for (int iteration = 0; iteration < iterations; iteration++)
        {
            auto iterationStart = steady_clock::now();

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

            auto workDuration = steady_clock::now() - iterationStart;
            auto sleepTime = workDuration * (1.0f / CPU_LOAD_FACTOR - 1);
            totalDuration += getDuration(timeUnit);

            this_thread::sleep_for(sleepTime);
            
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
    const int maxThreads = thread::hardware_concurrency();
    const int activeThreads = max(1, static_cast<int>(maxThreads * CPU_LOAD_FACTOR));

    vector<future<float>> futures;
    vector<vector<int>> threadData(activeThreads, data);
    const int iterationsPerThread = (iterations + activeThreads - 1) / activeThreads;

    for (int i = 0; i < activeThreads; ++i) 
    {
        futures.push_back(async(launch::async, [&, i]() {
            PerformanceTimer timer;
            return timer.calculateAverageDuration(
                timeUnit,
                algorithmType,
                iterationsPerThread,
                threadData[i]
            );
            }));
    }

    float totalTime = 0;
    for (auto& f : futures) totalTime += f.get();
    cout << totalTime / activeThreads << " ms (avg across " << activeThreads << " threads)";
}

int main()
{
    PerformanceTimer benchmark;
    vector<int> dataset(10000, 0);
    populateContainer(dataset);
    //printContainer(dataset, "Source");
    //quickSort(dataset);
    //printContainer(dataset,"Sorted");


    cout << "Calculating average sorting algorithm execution time..." << endl;
    executeAsyncCalculation(2, 4, 10000, dataset);
}