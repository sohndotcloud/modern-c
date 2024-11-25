#include <stdio.h>
#include "main.h"
#include "sort.h"

int main(int argc, char * argv[argc+1]) {
    int arr[] = { 12, 11, 12, 12, 6 , 7};
    int n = sizeof(arr) / sizeof(0);
    merge_sort(arr, 0, n - 1);

    foreach(int *v, arr) {
        printf("%d ", *v);
    }
    printf("\n");

    int array[] = { 1, 6, 3, 2, 9, 10, 2, 3, 4, 7 };
    int length = sizeof(array) / sizeof(0);
    quicksort_recursion(array, 0, length - 1);

    int max = 0;
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
        if (max > array[i]) {
            break;
        } else {
            max = array[i];
        }
    }
    printf("\n");

    if (max != array[length - 1]) {
        printf("List not sorted\n");
    } else {
        printf("List is sorted\n");
    }

    return 0;
}