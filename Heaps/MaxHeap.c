#include<stdio.h>
#include<stdlib.h>

int size = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *arr, int size, int i) {
    if(size == 1) { printf("Single Element in Heap. Already a Heap !"); return; }
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if(l < size && arr[l] > arr[largest]) largest = l;
    if(r < size && arr[r] > arr[largest]) largest = r;
    if(largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, size, largest);
    }
}

void insert(int *arr, int val) {
    if(size == 0) {
        arr[0] = val;
        size += 1;
        return;
    }
    arr[size] = val;
    size += 1;
    for(int i = size / 2 - 1; i >= 0 ; i--) heapify(arr, size, i);
}

void deleteRoot(int *arr, int val) {
    int i;
    for(i = 0; i < size ; i++) if(arr[i] == val) break;
    swap(&arr[i], &arr[size - 1]);
    size -= 1;
    for(int i = size / 2 - 1 ; i >= 0 ; i--) heapify(arr, size, i);
}

void printArray(int *arr, int size) {
    for(int i = 0 ; i < size ; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n; printf("Enter the number of nodes to be entered : "); scanf("%d", &n);
    int *arr = (int *) malloc(n * sizeof(int));

    int val;
    for(int i = 0 ; i < n ; i++) {
        printf("Enter next value to be inserted in the heap : ");
        scanf("%d", &val); insert(arr, val);
    }

    printf("Max Heap : ");
    printArray(arr, size);

    // deleting the root element
    deleteRoot(arr, arr[0]);
    printArray(arr, size);

    return 0;
}