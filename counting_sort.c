#include <stdio.h>
void countingSort(int a[], int n)
{
    int count[100] = {0};
    int i, j, k = 0;
    int max = a[0];
    for (i = 1; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }
    for (i = 0; i < n; i++)
        count[a[i]]++;
    for (i = 0; i <= max; i++)
    {
        while (count[i] > 0)
        {
            a[k] = i;
            k++;
            count[i]--;
        }
    }
}
int main()
{
    int a[100], n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
    scanf("%d", &a[i]);
    countingSort(a, n);
    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
    printf("%d ", a[i]);
    return 0;
}