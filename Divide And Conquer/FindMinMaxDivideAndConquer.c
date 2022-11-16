#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int minimum(int a, int b) { return (a < b) ? a : b; }
int maximum(int a, int b) { return (a > b) ? a : b; }

int findMin(int *arr, int low, int high) {
    if(high - low + 1 == 1) return arr[low];
    if(high - low + 1 == 2) return (arr[low] < arr[low + 1]) ? arr[low] : arr[low + 1];
    int mid = low + (high - low) / 2;
    return minimum(findMin(arr, low, mid), findMin(arr, mid + 1, high));
}

int findMax(int *arr, int low, int high) {
    if(high - low + 1 == 1) return arr[low];
    if(high - low + 1 == 2) return (arr[low] > arr[low + 1]) ? arr[low] : arr[low + 1];
    int mid = low + (high - low) / 2;
    return maximum(findMax(arr, low, mid), findMax(arr, mid + 1, high));
}

int main() {
    int n;
    printf("Enter the size of the array : ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter the numbers : ");
    for(int i = 0 ; i < n ; i++) scanf("%d", &arr[i]);

    int min = findMin(arr, 0, n-1);
    int max = findMax(arr, 0, n-1);

    printf("Max Element : %d, Min Element : %d\n", max, min);
    return 0;
}