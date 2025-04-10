#pragma once
#include <vector>

template <typename S>
void Switch(S sourceIndex, S destIndex, std::vector<S>& sourceArray)
{
    S bufferIndex = sourceArray[destIndex];
    sourceArray[destIndex] = sourceArray[sourceIndex];
    sourceArray[sourceIndex] = bufferIndex;
}

template <typename BS>
void BubbleSort(std::vector<BS>& sourceArray)
{
    int arraySize = sourceArray.size();

    for (int i = 0; i < arraySize; i++)
    {
        int swaps = 0;
        for (int j = 0; j < arraySize - 1 - i; j++)
        {
            if (sourceArray[j] > sourceArray[j + 1])
            {
                Switch(j, j + 1, sourceArray);
                swaps++;
            }
        }
        if (swaps == 0) { break; }
    }
}

template <typename SS>
void SelectionSort(std::vector<SS>& sourceArray)
{
    int arraySize = sourceArray.size();
    int minIndex;

    for (int i = 0; i < arraySize; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < arraySize; j++)
        {
            if (sourceArray[j] < sourceArray[minIndex])
            {
                minIndex = j;
            }
        }
        Switch(i, minIndex, sourceArray);
    }
}

template <typename IS>
void InsertionSort(std::vector<IS>& sourceArray)
{
    int arraySize = sourceArray.size();

    for (int i = 1; i < arraySize; i++)
    {
        int j = i - 1;
        while (j >= 0 && sourceArray[j] > sourceArray[j + 1])
        {
            Switch(j, j + 1, sourceArray);
            j--;
        }
    }
}

template <typename MoT>
int MedianOfThree(std::vector<MoT>& sourceArray)
{
    size_t firstIndex = 0;
    size_t lastIndex = sourceArray.size() - 1;
    size_t midIndex = firstIndex + (lastIndex - firstIndex) / 2;

    if ((sourceArray[firstIndex] < sourceArray[midIndex] && sourceArray[midIndex] < sourceArray[lastIndex]) ||
        (sourceArray[lastIndex] < sourceArray[midIndex] && sourceArray[midIndex] < sourceArray[firstIndex]))
    {
        return midIndex;
    }
    else if ((sourceArray[midIndex] < sourceArray[firstIndex] && sourceArray[firstIndex] < sourceArray[lastIndex]) ||
        (sourceArray[lastIndex] < sourceArray[firstIndex] && sourceArray[firstIndex] < sourceArray[midIndex]))
    {
        return firstIndex;
    }
    else
    {
        return lastIndex;
    }
}

template <typename QP>
int HoarePartition(std::vector<QP>& sourceArray, int pivotIndex, int lowBound, int highBound) // Hoare Partition Scheme
{
    QP pivotValue = sourceArray[pivotIndex];

    int leftPtr = lowBound - 1;
    int rightPtr = highBound + 1;

    while (true)
    {
        do
        {
            leftPtr++;
        } while (sourceArray[leftPtr] < pivotValue);

        do
        {
            rightPtr--;
        } while (sourceArray[rightPtr] > pivotValue);

        if (leftPtr >= rightPtr)
        {
            return rightPtr;
        }

        Switch(sourceArray[leftPtr], sourceArray[rightPtr]);
    }
}

template <typename QS>
void QuickSort(std::vector<QS>& sourceArray)
{
    int pivotIndex = MedianOfThree(sourceArray);
}
