/*
    Fozik's Code Team
    Author: Fozik
    Version: 1.1.4
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
void fillContainer(vector<ElementType>& vector)
{
    for (int i = 0; i < vector.size(); ++i) {
        vector[i] = rand() % 10000;
    }
}

class PerformanceTimer
{
public:
    steady_clock::time_point measurementStart;
    steady_clock::time_point measurementEnd;

    void startMeasurement() { measurementStart = steady_clock::now(); }
    void stopMeasurement() { measurementEnd = steady_clock::now(); }

    float returnTime(int timeUnit)
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

    static string getAlgorithmName(int algorithmType) {
        switch (algorithmType) {
        case SORT_BUBBLE:    return "Bubble Sort";
        case SORT_SELECTION: return "Selection Sort";
        case SORT_INSERTION: return "Insertion Sort";
        case SORT_QUICK:     return "Quick Sort";
        default:            return "Unknown Algorithm";
        }
    }

    static string getTimeUnitName(int timeUnit) {
        switch (timeUnit) {
        case TIME_UNIT_SECONDS: return "s";
        case TIME_UNIT_MILLIS:  return "ms";
        case TIME_UNIT_MICROS:  return "μs";
        case TIME_UNIT_NANOS:   return "ns";
        default:               return "";
        }
    }

    template <typename ContainerType>
    float calculateAverageTime(int timeUnit, int algorithmType, int iterations, vector<ContainerType>& data)
    {
        
        float totalDuration = 0.0f;

        for (int iteration = 0; iteration < iterations; iteration++)
        {
            fillContainer(data);
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

            totalDuration += returnTime(timeUnit); // Calculating the average time of sorting between threads
        }

        return totalDuration / iterations;
    }

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
void printContainer(vector<ElementType>& container, string& label)
{
    cout << endl << label << " elements: ";
    for (auto& element : container)
    {
        cout << element << ' ';
    }
}

void printResults(string algorithm, string unit, int dataSize, unsigned int iterations, unsigned short activeThreads, float totalTime, float minTime, float maxTime)
{
    cout << " Benchmark Results:\n";
    cout << "────────────────────────────────────────────────\n";
    cout << " Algorithm:        " << algorithm << endl;
    cout << " Data size:        " << dataSize << " elements\n";
    cout << " Total iterations: " << iterations << "\n";
    cout << " Threads used:     " << activeThreads << "\n";
    cout << "────────────────────────────────────────────────\n";
    cout << " Average time:   " << totalTime / activeThreads << " " << unit << endl;
    cout << " Total time:     " << totalTime << " " << unit << endl;
    cout << " Fastest thread: " << minTime << " " << unit << endl;
    cout << " Slowest thread: " << maxTime << " " << unit << endl;
    cout << "────────────────────────────────────────────────\n\n";
}

template <typename ContainerType>
void executeAsyncCalculation(int timeUnit, int algorithmType, int iterations, unsigned short activeThreads ,vector<ContainerType>& data)
{
    vector<future<float>> futures;
    vector<vector<int>> threadData(activeThreads, data);
    vector<float> threadTimes;
    int iterationsPerThread = iterations / activeThreads; // uniform calculation of how many iterations should be done by each of the threads

    for (int i = 0; i < activeThreads; ++i) 
    {
        futures.push_back(async(launch::async, [&, i]() 
            {
                PerformanceTimer timer;
                float result = timer.calculateAverageTime(timeUnit, algorithmType, iterationsPerThread, threadData[i]);
                threadTimes.push_back(result);
                return result;
            }));
    }

    float totalTime = 0;
    float minTime = numeric_limits<float>::max(); // maximum available value (like math.huge in lua)
    float maxTime = 0;

    for (auto& f : futures)
    {
        float threadTime = f.get();
        totalTime += threadTime;
        if (threadTime < minTime) { minTime = threadTime; }
        if (threadTime > maxTime) { maxTime = threadTime; }
    }
    
    printResults(PerformanceTimer::getAlgorithmName(algorithmType), PerformanceTimer::getTimeUnitName(timeUnit), data.size(), iterations, activeThreads, totalTime, minTime, maxTime);
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8"); // add support of special characters

    PerformanceTimer programExecutionTime;
    vector<int> dataset(1000, 0);
    fillContainer(dataset);

    //printContainer(dataset, "Source");
    //quickSort(dataset);
    //printContainer(dataset,"Sorted");

    executeAsyncCalculation(PerformanceTimer::TIME_UNIT_MILLIS, PerformanceTimer::SORT_QUICK, 1000, 16, dataset);
}