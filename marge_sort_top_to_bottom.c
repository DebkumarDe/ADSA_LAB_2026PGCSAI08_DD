//using stack
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
struct Stack {
    int left;
    int right;
};
void merge(int a[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = 0;
    int temp[MAX];
    while (i <= mid && j <= right)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= right)
        temp[k++] = a[j++];
    for (i = left, k = 0; i <= right; i++, k++)
        a[i] = temp[k];
}
void mergeSort(int a[], int n)
{
    struct Stack stack[MAX];
    int top = -1;
    int left, right, mid;
    stack[++top].left = 0;
    stack[top].right = n - 1;
    while (top >= 0)
    {
        left = stack[top].left;
        right = stack[top].right;
        top--;
        if (left < right)
        {
            mid = (left + right) / 2;
            stack[++top].left = mid + 1;
            stack[top].right = right;
            stack[++top].left = left;
            stack[top].right = mid;
        }
    }
    int size;
    for (size = 1; size < n; size = size * 2)
    {
        for (left = 0; left < n - size; left += 2 * size)
        {
            mid = left + size - 1;
            right = left + 2 * size - 1;
            if (right >= n)
            right = n - 1;
            merge(a, left, mid, right);
        }
    }
}
int main()
{
    int a[MAX];
    int n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    mergeSort(a, n);
    printf("Sorted array:\n");
    for (i = 0; i < n; i++)
    printf("%d ", a[i]);
    return 0;
}
