#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "util.h"
#include "sort.h"

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *leftArr = sliceIntArray(arr, left, mid + 1, NULL);
    int *rightArr = sliceIntArray(arr, mid + 1, right + 1, NULL);

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < n1) {
        arr[k++] = leftArr[i++];
    }

    while (j < n2) {
        arr[k++] = rightArr[j++];
    }

    free(leftArr);
    free(rightArr);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);        
        merge(arr, left, mid, right);
    }
}

void swap(int *v1, int *v2) {
    int temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

void quicksort_recursion(int arr[], int low, int high) {
    if (low < high) {
        int pivot_index = partition(arr, low, high);
        quicksort_recursion(arr, low, pivot_index - 1);
        quicksort_recursion(arr, pivot_index + 1, high);
    }
}

int partition(int array[], int low, int high) {
    int mid = low + (high - low) / 2;
    int i = low;
    swap(&array[mid], &array[high]);
    int pivot = array[high];
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            swap(&array[j], &array[i++]);
        }
    }
    
    swap(&array[i], &array[high]);

    return i;
}