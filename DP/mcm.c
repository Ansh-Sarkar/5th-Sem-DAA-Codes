#include <stdio.h>
#include <limits.h>

#define INF 999999999
long int cost_matrix[20][20];
int s[20][20], p[20], i, j, n;

void printOrder(int i, int j) {
    if (i == j) printf("A%d", i);
    else {
        printf("("); printOrder(i, s[i][j]);
        printOrder(s[i][j] + 1, j); printf(")");
    }
}

void matmultiply() {
    long int q; int k;
    for (i = n; i > 0; i--) {
        for (j = i; j <= n; j++) {
            if (i == j) cost_matrix[i][j] = 0;
            else {
                for (k = i; k < j; k++) {
                    q = cost_matrix[i][k] + cost_matrix[k + 1][j] + p[i - 1] * p[k] * p[j];
                    if (q < cost_matrix[i][j]) {
                        cost_matrix[i][j] = q;
                        s[i][j] = k;
                    }
                }
            }
        }
    }
}

int MatrixChainOrder(int p[], int i, int j) {
    if (i == j) return 0;
    int k, count, min = INT_MAX;
    for (k = i; k < j; k++) {
        count = MatrixChainOrder(p, i, k) + MatrixChainOrder(p, k + 1, j) + p[i - 1] * p[k] * p[j];
        if (count < min) min = count;
    } return min;
}

int main() {
    int k; printf("Enter the no. of elements in the dimensions array (no. of matrices) : "); 
    scanf("%d", &n);
    
    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            cost_matrix[i][i] = 0;
            cost_matrix[i][j] = INF;
            s[i][j] = 0;
        }
    }

    printf("\nEnter the dimensions: \n");
    for (k = 0; k <= n; k++) {
        printf("Dim [%d]: ", k);
        scanf("%d", &p[k]);
    }

    matmultiply();

    i = 1, j = n;

    printf("\nMultiplication Order : ");
    printOrder(i, j);
    printf("\nMinimum number of multiplications is : %d ", MatrixChainOrder(p, 1, n));

    printf("\n");
    return 0;
}