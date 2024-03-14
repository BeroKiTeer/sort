#include <select_sort.h>
#include <algorithm>

void select_sort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        std::swap(arr[i], arr[min_index]);  //确保已排序序列中所有元素都分别是待排序序列中的最小值。 
    }
}