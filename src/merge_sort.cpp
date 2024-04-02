#include <merge_sort.h>

void merge(int arr[], int begin, int mid, int end)
{
    int i, j, k;
    int n1 = mid - begin + 1;
    int n2 = end - mid;

    //搓个临时数组
    int* L = new int[n1];
    int* R = new int[n2];

    //分别存储左右两块排序好的子数组
    for (i = 0; i < n1; i++)  L[i] = arr[begin + i];
    for (j = 0; j < n2; j++)  R[j] = arr[mid + 1 + j];
    
    //将两个已排序的子数组合并为一个排序好的数组
    i = 0; j = 0 ; k = begin;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //填到原来那个数组
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
    //析构释放内存
    delete[] L;
    delete[] R;
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r) {
        // 找第一个中点
        int m = l + (r - l) / 2;

        // 两部分分别排序
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        // 合并
        merge(arr, l, m, r);
    }
}