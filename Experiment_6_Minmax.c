#include <stdio.h>

typedef struct
{
    int min;
    int max;
} MinMax;

MinMax findMaxMin(int arr[], int low, int high)
{
    MinMax minMax, mml, mmr;
    int mid;

    if (low == high)
    { // If there is only one element
        minMax.max = arr[low];
        minMax.min = arr[low];
        return minMax;
    }

    if (high == low + 1)
    { // If there are two elements
        if (arr[low] > arr[high])
        {
            minMax.max = arr[low];
            minMax.min = arr[high];
        }
        else
        {
            minMax.max = arr[high];
            minMax.min = arr[low];
        }
        return minMax;
    }

    mid = (low + high) / 2; // If there are more than 2 elements
    mml = findMaxMin(arr, low, mid);
    mmr = findMaxMin(arr, mid + 1, high);

    minMax.min = (mml.min < mmr.min) ? mml.min : mmr.min;
    minMax.max = (mml.max > mmr.max) ? mml.max : mmr.max;

    return minMax;
}

int main()
{
    int arr[] = {1000, 11, 445, 1, 330, 3000};
    int arr_size = 6;

    MinMax minMax = findMaxMin(arr, 0, arr_size - 1);
    printf("Minimum element is %d\n", minMax.min);
    printf("Maximum element is %d\n", minMax.max);

    return 0;
}
