# 排序的相关概念

**排序**：所谓排序，就是使一串记录，按照其中的某个或某些关键字的大小，递增或递减的排列起来的操作。
**稳定性**：**假定在待排序的记录序列中，存在多个具有相同的关键字的记录，若经过排序，这些记录的相对次序保持不变，即在原序列中，r[i]=r[j]，且r[i]在r[j]之前，而在排序后的序列中，r[i]仍在r[j]之前，则称这种排序算法是稳定的；否则称为不稳定的。**
**内部排序**：数据元素全部放在内存中的排序。
**外部排序**：数据元素太多不能同时放在内存中，根据排序过程的要求不能在内外存之间移动数据的排序。

# 插入排序

## 直接插入排序

往一个有序序列里（每次）插入一个数，使得这个有序序列仍保持有序。

```cpp
void insert_sort(int arr[], int len) 
{
    for (int i = 1; i < len; i++) {
        int key = arr[i];
        //直觉上从后往前遍历效率似乎更高，但理论上复杂度仍然是O(n^2)
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}
```

## 希尔排序

希尔排序是对**插入排序的优化**，主要思想即是利用多组**预排序**（本质就是多组预排序，只是每次不是将后面有序区间后面的一个数开始，而是从有序区间后的gap个位置开始），将序列变为接近有序的序列，然后再对该接近有序的序列进行排序。

```cpp
void shell_sort(int arr[], int len) {
    int gap = len;
    while (gap > 1) {
        gap /= 2;
        for (int i = 0; i < gap; i++) {
            insert_sort(arr + i, len - i);
        }
    }
    insert_sort(arr, len);
}
```

`gap` 是一个称为**增量**的概念。希尔排序通过使用不同的增量，逐步将原始数组分割成更小的子数组进行插入排序，最终达到排序整个数组的目的。

这里使用的是**希尔增量**，具体来说：

- 初始时，`gap` 的值通常被设为数组长度的一半（`len / 2`），即将整个数组分成两部分。[希尔增量：$len \over 2^k$，k是迭代次数]
- 在每一轮迭代中，通过逐渐减小 `gap` 的值来分割数组，并对分割后的子数组进行插入排序。
- 随着迭代的进行，`gap` 的值会逐渐减小，直到最后 `gap` 变为 1，此时相当于对整个数组进行了一次插入排序。

通过希尔排序中的这种增量序列，可以在一定程度上提高插入排序的效率，因为通过提前部分排序，可以使得较小的元素尽早地移动到合适的位置，从而减少了后续元素的移动次数。

# 选择排序

## 传统选择

遍历整个序列未排序的部分，每次都找到序列中最小的值，然后将其与序列最左端的值进行交换。**是效率最低下的排序之一**

```cpp
#include <algorithm>
void select_sort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        //确保已排序序列中所有元素都分别是待排序序列中的最小值。 
        std::swap(arr[i], arr[min_index]);  
    }
}
```

## 堆排序

本质思想是选择排序，不过选数的方式有所改变，不再是遍历整个数组选数，而是通过**数据结构中的堆**来进行选数

大根堆代码：

```c++
#include <algorithm>

void heapify(int arr[], int n, int i) {
    // 在根结点和子结点中查找最大
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果根不是最大的，则交换并继续堆化
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    // 建立大根堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    // 堆排序
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

# 交换排序

## 冒泡排序

最无脑的排序算法。从第一个数开始，往后每两个数进行两两比较，若比其大，则进行交换。依次进行，最大的值沉底，最小的值冒到前面。

```cpp
#include <algorithm>
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) 
        for (int j = 0; j < n - i - 1; j++) 
            if (arr[j] > arr[j + 1]) 
                std::swap(arr[j], arr[j + 1]);
}
```

## 快速排序

整体思想是采用了分治算法的思想。

首先选出一个基准值（key），一般默认都是序列最左端的那个数，然后每次进行快排后，这个基准值都被放到了正确位置（该基准值左侧都比其本身小，基准值右侧都比其本身大）。

那么以基准值为轴，则将原序列分为了左序列与右序列，再分别在左序列和右序列中选出一个基准值，进行快排过程，完成后依旧是基准值左侧都是比其本身小，右侧都比其本身大。

一直周而复始下去，将序列分至只有一个数时，则说明该序列已经有序。

```cpp
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//分区操作(快排算法的核心)
int partition(int arr[], int low, int high) {
    int mid = arr[high]; 
    int i = low - 1; 
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < mid) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}
```

# 归并排序

首先，`merge` 函数用于合并两个已排序的子数组。然后，`mergeSort` 函数对数组进行递归地分割和排序。

```cpp
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
```



# 分布排序

## 计数排序

```cpp
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
```

