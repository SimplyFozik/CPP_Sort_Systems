// SortingAlgorithms.h
/*
    Fozik's Code Team
    Author: Fozik
    Version: 1.0.2
    Project: SA/SS
*/

#pragma once
#include <vector>
#include <algorithm>

template <typename ElementType>
void bubbleSort(std::vector<ElementType>& sortingArray)
{
    const int containerSize = sortingArray.size();

    for (int currentPass = 0; currentPass < containerSize; currentPass++)
    {
        bool swapped = false;
        for (int comparisonIndex = 0; comparisonIndex < containerSize - 1 - currentPass; comparisonIndex++)
        {
            if (sortingArray[comparisonIndex] > sortingArray[comparisonIndex + 1])
            {
                std::swap(sortingArray[comparisonIndex], sortingArray[comparisonIndex + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

template <typename ElementType>
void selectionSort(std::vector<ElementType>& sortingArray)
{
    const int containerSize = sortingArray.size();

    for (int currentPosition = 0; currentPosition < containerSize; currentPosition++)
    {
        int minimumIndex = currentPosition;
        for (int searchIndex = currentPosition + 1; searchIndex < containerSize; searchIndex++)
        {
            if (sortingArray[searchIndex] < sortingArray[minimumIndex])
            {
                minimumIndex = searchIndex;
            }
        }
        std::swap(sortingArray[currentPosition], sortingArray[minimumIndex]);
    }
}

template <typename ElementType>
void insertionSort(std::vector<ElementType>& sortingArray)
{
    const int containerSize = sortingArray.size();

    for (int currentIndex = 1; currentIndex < containerSize; currentIndex++)
    {
        int comparePosition = currentIndex - 1;
        while (comparePosition >= 0 && sortingArray[comparePosition] > sortingArray[comparePosition + 1])
        {
            std::swap(sortingArray[comparePosition], sortingArray[comparePosition + 1]);
            comparePosition--;
        }
    }
}

template <typename ElementType>
int medianOfThree(std::vector<ElementType>& sortingArray, int lowerBound, int upperBound)
{
    const int middlePosition = lowerBound + (upperBound - lowerBound) / 2;

    if (sortingArray[lowerBound] > sortingArray[middlePosition])
        std::swap(sortingArray[lowerBound], sortingArray[middlePosition]);
    if (sortingArray[lowerBound] > sortingArray[upperBound])
        std::swap(sortingArray[lowerBound], sortingArray[upperBound]);
    if (sortingArray[middlePosition] > sortingArray[upperBound])
        std::swap(sortingArray[middlePosition], sortingArray[upperBound]);

    return middlePosition;
}

template <typename ElementType>
int partition(std::vector<ElementType>& sortingArray, int lowerBound, int upperBound)
{
    const int pivotIndex = medianOfThree(sortingArray, lowerBound, upperBound);
    ElementType pivotValue = sortingArray[pivotIndex];

    std::swap(sortingArray[pivotIndex], sortingArray[lowerBound]);

    int leftPointer = lowerBound - 1;
    int rightPointer = upperBound + 1;

    while (true)
    {
        do { leftPointer++; } while (sortingArray[leftPointer] < pivotValue);

        do { rightPointer--; } while (sortingArray[rightPointer] > pivotValue);

        if (leftPointer >= rightPointer)
            return rightPointer;

        std::swap(sortingArray[leftPointer], sortingArray[rightPointer]);
    }
}

template <typename ElementType>
void quickSortRecursive(std::vector<ElementType>& sortingArray, int lowerBound, int upperBound)
{
    if (lowerBound < upperBound)
    {
        const int partitionIndex = partition(sortingArray, lowerBound, upperBound);
        quickSortRecursive(sortingArray, lowerBound, partitionIndex);
        quickSortRecursive(sortingArray, partitionIndex + 1, upperBound);
    }
}

template <typename ElementType>
void quickSort(std::vector<ElementType>& sortingArray)
{
    if (!sortingArray.empty())
    {
        quickSortRecursive(sortingArray, 0, sortingArray.size() - 1);
    }
}