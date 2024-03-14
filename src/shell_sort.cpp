#include <insert_sort.h>

void shell_sort(int arr[], int len) {
    int gap = len;
    while (gap > 1) {
        gap = gap / 2;
        for (int i = 0; i < gap; i++) {
            insert_sort(arr + i, len - i);
        }
    }
    insert_sort(arr, len);
}