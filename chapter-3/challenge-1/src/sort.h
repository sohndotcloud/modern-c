#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "main.h"
#include "util.h"

void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

#endif