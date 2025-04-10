/*
    Fozik's Code Team
    Author: Fozik
    Version: 1.0.0
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
#include "SortingSource.h" // sorting algorithms

using namespace std;
using namespace chrono;

template <typename S>
void fillArray(vector<S>& SOURCE_ARRAY)
{
    srand(time(0));
    //cout << "Source Array : ";
    for (int i = 0; i < SOURCE_ARRAY.size(); i++)
    {
        SOURCE_ARRAY[i] = rand() % 100;
        //cout << SOURCE_ARRAY[i] << ' ';
    }
}

class Time
{
public:

    steady_clock::time_point START_CLOCK;
    steady_clock::time_point STOP_CLOCK;

    void StartTime() { START_CLOCK = steady_clock::now(); }

    void StopTime() { STOP_CLOCK = steady_clock::now(); }

    float CountTime(int TYPE)
    {
        switch (TYPE)
        {
        case 1: 
            return duration_cast<duration<float>>(STOP_CLOCK - START_CLOCK).count();
        case 2: 
            return duration_cast<duration<float, milli>>(STOP_CLOCK - START_CLOCK).count();
        case 3: 
            return duration_cast<duration<float, micro>>(STOP_CLOCK - START_CLOCK).count();
        case 4: 
            return duration_cast<duration<float, nano>>(STOP_CLOCK - START_CLOCK).count();
        default: 
            return 0.0f;
        }
    }

    template <typename A>
    float CountAverage(int TIME_TYPE, int SORT_TYPE, int REPEAT_VALUE,  vector<A>& SOURCE_ARRAY)
    {
        float AVERAGE_TIME = 0;
        for (int i = 0; i < REPEAT_VALUE; i++)
        {
            fillArray(SOURCE_ARRAY);

            switch (SORT_TYPE)
            {
            case 1:
                StartTime();
                BubbleSort(SOURCE_ARRAY);
                StopTime();
                break;
            case 2:
                StartTime();
                SelectionSort(SOURCE_ARRAY);
                StopTime();
            case 3:
                StartTime();
                InsertionSort(SOURCE_ARRAY);
                StopTime();
            default:
                break;
            }

            AVERAGE_TIME += CountTime(TIME_TYPE);
        }

        AVERAGE_TIME /= REPEAT_VALUE;

        return AVERAGE_TIME;
    }
};

template <typename R>
void returnArray(vector<R>& SOURCE_ARRAY, string TYPE)
{
    cout << endl << TYPE << " Array: ";
    for (int i = 0; i < SOURCE_ARRAY.size(); i++)
    {
        cout << SOURCE_ARRAY[i] << ' ';
    }
}

template <typename A>
void createThread(int TIME_TYPE, int SORT_TYPE, int REPEAT_VALUE, vector<A>& SOURCE_ARRAY)
{
    auto THREAD = async(launch::async, [TIME_TYPE, SORT_TYPE, REPEAT_VALUE, &SOURCE_ARRAY]() {
        Time ThreadWorker;
        return ThreadWorker.CountAverage(TIME_TYPE, SORT_TYPE, REPEAT_VALUE, SOURCE_ARRAY);
        });

    cout << THREAD.get() << " ms";
}

int main()
{
    Time Program;
    vector<int> SOURCE_ARRAY(3,0);
    fillArray(SOURCE_ARRAY);
    returnArray(SOURCE_ARRAY, "Source");
    //QuickSort(SOURCE_ARRAY,0, SOURCE_ARRAY.size());
    //returnArray(SOURCE_ARRAY, "Sorted");
    //cout << "Calculating average time of sorting algorithm..." << endl;
    //createThread(2, 2, 100, SOURCE_ARRAY);
}
