#include <distribution_sort.h>

void count_sort(int arr[], int n) 
{
    // 找到最大元素
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    // 创建计数数组
    int count[] = new int[max + 1];
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }
    // 计算每个元素的计数
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    // 计算每个元素的正确位置
    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i]-- > 0) {
            arr[index++] = i;
        }
    }
    delete[] count;
}