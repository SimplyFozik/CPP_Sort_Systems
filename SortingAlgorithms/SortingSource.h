/*
 * Copyright [2025] [Fozik]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 /*
     E11Force Team
     Author: Fozik
     Version: 1.1.5
     Project: AlgorithmsForce [Library File]
 */

#pragma once
#include <vector>
#include <algorithm>

template <typename DataType>
void bubbleSort(std::vector<DataType>& sortingArray)
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

template <typename DataType>
void selectionSort(std::vector<DataType>& sortingArray)
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

template <typename DataType>
void insertionSort(std::vector<DataType>& sortingArray)
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

template <typename DataType>
int medianOfThree(std::vector<DataType>& sortingArray, int lowerBound, int upperBound)
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

template <typename DataType>
int partition(std::vector<DataType>& sortingArray, int lowerBound, int upperBound)
{
    const int pivotIndex = medianOfThree(sortingArray, lowerBound, upperBound);
    DataType pivotValue = sortingArray[pivotIndex];

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

template <typename DataType>
void quickSortRecursive(std::vector<DataType>& sortingArray, int lowerBound, int upperBound)
{
    if (lowerBound < upperBound)
    {
        const int partitionIndex = partition(sortingArray, lowerBound, upperBound);
        quickSortRecursive(sortingArray, lowerBound, partitionIndex);
        quickSortRecursive(sortingArray, partitionIndex + 1, upperBound);
    }
}

template <typename DataType>
void quickSort(std::vector<DataType>& sortingArray)
{
    if (!sortingArray.empty())
    {
        quickSortRecursive(sortingArray, 0, sortingArray.size() - 1);
    }
}