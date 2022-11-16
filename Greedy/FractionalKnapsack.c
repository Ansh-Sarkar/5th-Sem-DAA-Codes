#include <stdio.h>
#include <stdlib.h>

void swap(float *x, float *y) {
    float temp = *x;
    *x = *y;
    *y = temp;
}

void printArray(float *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%f ", arr[i]);
    printf("\n");
}

void sort(float *ratio, float *weights, float *profit, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (ratio[i] < ratio[j]) {
                swap(&ratio[i], &ratio[j]);
                swap(&weights[i], &weights[j]);
                swap(&profit[i], &profit[j]);
            }
}

int main() {
    int n; printf("Enter number of elements to be entered : "); scanf("%d", &n);

    float *weight = (float *)malloc(n * sizeof(n));
    float *profit = (float *)malloc(n * sizeof(n));
    float *ratio = (float *)malloc(n * sizeof(n));
    float W = 0;

    printf("Enter the weights of the elements : ");
    for (int i = 0; i < n; i++) scanf("%f", &weight[i]);

    printf("Enter the profit of the elements : ");
    for (int i = 0; i < n; i++) {
        scanf("%f", &profit[i]);
        ratio[i] = 1.0 * profit[i] / weight[i];
        printf("%d. Dividing %f by %f , ratio = %f\n", i + 1, profit[i], weight[i], ratio[i]);
    }
    printf("\n");

    printf("Enter KnapSack Capacity : ");
    scanf("%f", &W);
    float maxValue = 0, availableWeight = W;
    sort(ratio, weight, profit, n);
    printf("\n");

    printf("Sorted by price ratio : \n");
    printf("Weights : ");
    printArray(weight, n);
    printf("Price   : ");
    printArray(profit, n);
    printf("ratio : ");
    printArray(ratio, n);
    printf("\n");

    for (int i = 0; i < n; i++) {
        if (weight[i] <= availableWeight) {
            availableWeight -= weight[i];
            maxValue += profit[i];
            printf("Added %.2f units of element (%.2f, %f) worth : %.2f\n", weight[i], weight[i], profit[i], profit[i]);
        } else {
            maxValue += (ratio[i] * (availableWeight));
            printf("Added %.2f units of element (%.2f, %.2f) worth : %.2f\n", availableWeight, weight[i], profit[i], (ratio[i] * (availableWeight)));
            break;
        }
    }

    printf("Maximum possible value which can be taken is : %.2f", maxValue);
    return 0;
}