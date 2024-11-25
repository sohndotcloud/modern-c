#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "main.h"
#include "util.h"

void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void swap(int *v1, int *v2);
void quicksort_recursion(int arr[], int low, int high);
int partition(int array[], int low, int high);

#endif