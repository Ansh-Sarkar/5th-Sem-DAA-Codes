#include <stdio.h>
#include <stdlib.h>

struct Activity {
    int id, start, end, selected;
};

void swap(struct Activity *x, struct Activity *y) {
    struct Activity temp = *x;
    *x = *y;
    *y = temp;
}

void sortActivities(struct Activity *activities, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (activities[j].end > activities[j + 1].end)
                swap(&activities[j], &activities[j + 1]);
}

void fillActivityData(struct Activity *activity) {
    printf("Enter Activity ID : ");
    scanf("%d", &activity->id);
    printf("Enter start time : ");
    scanf("%d", &activity->start);
    printf("Enter end time : ");
    scanf("%d", &activity->end);
    printf("\n");
    activity->selected = 0;
}

void printActivity(struct Activity *activity) {
    printf("Activity ID : %d\n", activity->id);
    printf("Activity St : %d\n", activity->start);
    printf("Activity En : %d\n", activity->end);
}

int main() {
    int n;
    printf("Enter the number of activities : ");
    scanf("%d", &n);

    struct Activity *activities = (struct Activity *)malloc(n * sizeof(struct Activity));

    printf("\nEnter Activity Details : ");
    printf("\n--------------------------\n");
    for (int i = 0; i < n; i++)
        fillActivityData(&activities[i]);

    sortActivities(activities, n);

    int next = 0;
    for(int i = 0 ; i < n ; i++) {
        if(next <= activities[i].start) {
            // this activity gets selected
            activities[i].selected = 1;
            next = activities[i].end;
        }
    }

    printf("Selected Activities : ");
    for(int i = 0 ; i < n ; i++) {
        if(activities[i].selected) {
            printf("%d ", activities[i].id);
        }
    }
    
    return 0;
}