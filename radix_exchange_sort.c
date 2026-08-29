#include <stdio.h>
void radixExchangeSort(int a[], int left, int right, int bit)
{
    int i, j, temp;
    if (left >= right || bit < 0)
    return;
    i = left;
    j = right;
    while (i <= j)
    {
        while (i <= right && ((a[i] >> bit) & 1) == 0)
            i++;
        while (j >= left && ((a[j] >> bit) & 1) == 1)
            j--;
        if (i < j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    radixExchangeSort(a, left, j, bit - 1);
    radixExchangeSort(a, i, right, bit - 1);
}
int main()
{
    int a[100], n, i;
    int max, bit = 0;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
    scanf("%d", &a[i]);
    max = a[0];
    for (i = 1; i < n; i++)
    {
        if (a[i] > max)
        max = a[i];
    }
    while ((max >> bit) > 1)
    bit++;
    radixExchangeSort(a, 0, n - 1, bit);
    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
    printf("%d ", a[i]);
    return 0;
}