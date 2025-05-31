// Copyright 2025 atikdd.ru

#include <max_heap.h>
#include <min_heap.h>
#include <massive.h>
#include <cstddef>
#include <iostream>
#include <algorithm>

void heapSort(int arr[], size_t n) {
    MaxHeap<int> heap(n, arr);

    for (int i = n - 1; i >= 0; i--) {
        arr[i] = heap.remove_top();
    }
}

void sortKSorted(int arr[], int n, int k) {
    MinHeap<int> minHeap;

    int sortedIndex = 0;

    for (int i = 0; i <= k; i++) {
        minHeap.insert(arr[i]);
    }

    for (int i = k + 1; i < n; i++) {
        arr[sortedIndex++] = minHeap.remove_top();
        minHeap.insert(arr[i]);
    }

    while (!minHeap.is_empty()) {
        arr[sortedIndex++] = minHeap.remove_top();
    }
}

template <typename T>
void printArray(const T* arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

TMassive<int> findKLargest(int arr[], int n, int k) {
    MaxHeap<int> heap(n, arr);
    TMassive<int> result;
    for (int i = 0; i < k; i++) {
        result.insert(heap.remove_top(), i);
    }
    return result;
}

TMassive<int> findKSmallest(int arr[], int n, int k) {
    MinHeap<int> heap(n, arr);
    TMassive<int> result;
    for (int i = 0; i < k; i++) {
        result.insert(heap.remove_top(), i);
    }
    return result;
}

TMassive<int> mergeKSortedArrays(
    const TMassive<TMassive<int>>& kSortedArrays) {
    MinHeap<int> minHeap;
    TMassive<int> mergedArray;

    for (size_t i = 0; i < kSortedArrays.size(); i++) {
        for (size_t j = 0; j < kSortedArrays[i].size(); j++) {
            minHeap.insert(kSortedArrays[j][i]);
        }
        while (!minHeap.is_empty()) {
            int minValue = minHeap.remove_top();
            mergedArray.push_back(minValue);
        }
    }

    return mergedArray;
}

int main() {
    std::cout << "----------------------"
              << " HEAP SORT"
              << "--------------------------" << std::endl;
    int heap_sort[] = {5, 2, 9, 1, 5, 6};
    size_t heap_sort_size = sizeof(heap_sort) / sizeof(heap_sort[0]);
    std::cout << "Original array: ";
    printArray(heap_sort, heap_sort_size);
    heapSort(heap_sort, heap_sort_size);
    std::cout << "Sorted array: ";
    printArray(heap_sort, heap_sort_size);

    std::cout << "\n-----------------"
              << " Almost Sorted Array Sort "
              << "----------------" << std::endl;
    int ksort[] = {6, 5, 3, 2, 8, 10, 9};
    size_t ksort_size = sizeof(ksort) / sizeof(ksort[0]);
    int k = 3;
    std::cout << "Original array: ";
    printArray(ksort, ksort_size);
    sortKSorted(ksort, ksort_size, k);
    std::cout << "Sorted array: ";
    printArray(ksort, ksort_size);

    std::cout << "\n--------------------"
              << " K Largest Elements "
              << "-------------------" << std::endl;
    int kLargest_el[] = {6, 5, 3, 2, 8, 10, 9};
    size_t kLargest_el_size = sizeof(kLargest_el) / sizeof(kLargest_el[0]);
    int kLargest = 3;
    std::cout << "Original array: ";
    printArray(kLargest_el, kLargest_el_size);
    TMassive<int> kLargestResult = findKLargest(
        kLargest_el, kLargest_el_size, kLargest);
    std::cout << kLargest << " largest elements: "
              << kLargestResult << std::endl;

    std::cout << "\n-------------------"
              << " K Smallest Elements "
              << "-------------------" << std::endl;
    int kSmallest_el[] = {6, 5, 3, 2, 8, 10, 9};
    size_t kSmallest_el_size = sizeof(kSmallest_el) / sizeof(kSmallest_el[0]);
    int kSmallest = 3;
    std::cout << "Original array: ";
    printArray(kSmallest_el, kSmallest_el_size);
    TMassive<int> kSmallestResult = findKSmallest(
        kSmallest_el, kSmallest_el_size, kSmallest);
    std::cout << kSmallest << " smallest elements: "
              << kSmallestResult << std::endl;

    std::cout << "\n-------------------"
                << " Merging K sorted arrays "
                << "-------------------" << std::endl;
    TMassive<TMassive<int>> kSortedArrays;
    int arr1[] = {1, 4, 7};
    int arr2[] = {2, 5, 8};
    int arr3[] = {3, 6, 9};
    kSortedArrays.push_back(TMassive<int>().insert(arr1, 3, 0));
    kSortedArrays.push_back(TMassive<int>().insert(arr2, 3, 0));
    kSortedArrays.push_back(TMassive<int>().insert(arr3, 3, 0));
    std::cout << "Original arrays: " << std::endl;
    for (size_t i = 0; i < kSortedArrays.size(); i++) {
        std::cout << "Array " << i + 1 << ": "
                  << kSortedArrays[i] << std::endl;
    }
    TMassive<int> mergedArray = mergeKSortedArrays(kSortedArrays);
    std::cout << "Merged array: " << mergedArray << std::endl;
    return 0;
}
