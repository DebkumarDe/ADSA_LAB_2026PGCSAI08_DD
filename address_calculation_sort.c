#include <stdio.h>
void addressCalculationSort(int a[], int n)
{
    int table[100] = {0};
    int i, j, k = 0;
    int max = a[0];
    for (i = 1; i < n; i++)
    {
        if (a[i] > max)
        max = a[i];
    }
    for (i = 0; i < n; i++)
    {
        table[a[i]]++;
    }
    for (i = 0; i <= max; i++)
    {
        for (j = 0; j < table[i]; j++)
        {
            a[k] = i;
            k++;
        }
    }
}
int main()
{
    int a[100], n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements (0-99):\n");
    for (i = 0; i < n; i++)
    scanf("%d", &a[i]);
    addressCalculationSort(a, n);
    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
    printf("%d ", a[i]);
    return 0;
}