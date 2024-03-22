#include <stdio.h>

#define MAX_ITEMS 100

// Structure for items
struct Item {
    int value;
    int weight;
};

// Function to sort items based on value/weight ratio
void sortByRatio(struct Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            double ratio1 = (double)items[j].value / items[j].weight;
            double ratio2 = (double)items[j + 1].value / items[j + 1].weight;
            if (ratio1 < ratio2) {
                struct Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

// Function to solve knapsack using greedy approach
double knapsackGreedy(struct Item items[], int n, int capacity) {
    sortByRatio(items, n);

    int currentWeight = 0;
    double finalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            finalValue += items[i].value;
        } else {
            int remainingWeight = capacity - currentWeight;
            finalValue += items[i].value * ((double)remainingWeight / items[i].weight);
            break;
        }
    }

    return finalValue;
}

int main() {
    struct Item items[MAX_ITEMS];
    int n, capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    printf("Enter the value and weight of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d:\n", i + 1);
        printf("Value: ");
        scanf("%d", &items[i].value);
        printf("Weight: ");
        scanf("%d", &items[i].weight);
    }

    double maxValue = knapsackGreedy(items, n, capacity);
    printf("Maximum value that can be obtained: %.2f\n", maxValue);

    return 0;
}
