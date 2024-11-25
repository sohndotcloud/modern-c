#include <stdio.h>
#include "main.h"
#include "sort.h"

int main(int argc, char * argv[argc+1]) {
    int arr[] = { 12, 11, 12, 12, 6 , 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    merge_sort(arr, 0, n - 1);

    foreach(int *v, arr) {
        printf("%d ", *v);
    }
    printf("\n");

    return 0;
}