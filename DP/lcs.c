#include<stdio.h>
#include<string.h>

int max(int a, int b) { return (a > b) ? a : b; }

void lcs(char* X, char* Y, int m, int n) {
    int L[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1]) L[i][j] = L[i - 1][j - 1] + 1;
            else L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    int index = L[m][n];
    char lcs[index + 1];
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];  
            i--; j--; index--; 
        }
        else if (L[i - 1][j] > L[i][j - 1]) i--;
        else j--;
    }
    printf("LCS is %s", lcs);
}
 
/* Driver program to test above function */
int main() {
    FILE *input1, *input2;
    input1 = fopen("input1.txt", "r");
    input2 = fopen("input2.txt", "r");

    if(input1 == NULL || input2 == NULL) {
        printf("Could not open one of the files");
        return 0;
    }

    char X[100], Y[100];
    fgets(X, 100, input1);
    fgets(Y, 100, input2);

    int m = strlen(X);
    int n = strlen(Y);

    lcs(X, Y, m, n);
    return  0;
}