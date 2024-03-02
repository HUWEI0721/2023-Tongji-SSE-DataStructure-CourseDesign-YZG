#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <climits>

using namespace std;
using namespace std::chrono;

// 函数声明
void generateRandomNumbers(vector<int>& nums, int n);
void bubbleSort(vector<int>& nums, long long& swaps, long long& comparisons);
void selectionSort(vector<int>& nums, long long& swaps, long long& comparisons);
void insertionSort(vector<int>& nums, long long& swaps, long long& comparisons);
void shellSort(vector<int>& nums, long long& swaps, long long& comparisons);
void quickSort(vector<int>& nums, int low, int high, long long& swaps, long long& comparisons);
int partition(vector<int>& nums, int low, int high, long long& swaps, long long& comparisons);
void heapSort(vector<int>& nums, long long& swaps, long long& comparisons);
void heapify(vector<int>& nums, int n, int i, long long& swaps, long long& comparisons);
void mergeSort(vector<int>& nums, int l, int r, long long& swaps, long long& comparisons);
void merge(vector<int>& nums, int l, int m, int r, long long& swaps, long long& comparisons);
void radixSort(vector<int>& nums, long long& swaps, long long& comparisons);
int getMax(vector<int>& nums);
void countSort(vector<int>& nums, int exp, long long& swaps, long long& comparisons);

// 主函数
int main() {

    cout << "=============================================" << endl;
    cout << "**             八种排序算法比较            **" << endl;
    cout << "=============================================" << endl;
    cout << "**             1---冒泡排序                **" << endl;
    cout << "**             2---选择排序                **" << endl;
    cout << "**             3---直接插入排序            **" << endl;
    cout << "**             4---希尔排序                **" << endl;
    cout << "**             5---快速排序                **" << endl;
    cout << "**             6---堆排序                  **" << endl;
    cout << "**             7---归并排序                **" << endl;
    cout << "**             8---基数排序                **" << endl;
    cout << "**             9---输出原始数据            **" << endl;
    cout << "**             0---退出程序                **" << endl;
    cout << "**   注意：基数排序目前仅支持从小到大排序  **" << endl;
    cout << "=============================================" << endl;

    cout << endl;

    int choice, n;
    cout << "请输入随机数的个数: ";
    cin >> n;

    while (true) {
        cout << "输入选择 (1-9): ";
        cin >> choice;

        if (choice == 9) break;
        if (cin.fail() || choice < 1 || choice>9)
        {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入错误，请重新输入!" << endl << endl;
            continue;
        }
        // 生成随机数
        vector<int> nums(n);
        generateRandomNumbers(nums, n);

        long long swaps = 0;
        long long comparisons = 0;
        auto start = high_resolution_clock::now();

        switch (choice) {
            case 1:
                bubbleSort(nums, swaps, comparisons);
                break;
            case 2:
                selectionSort(nums, swaps, comparisons);
                break;
            case 3:
                insertionSort(nums, swaps, comparisons);
                break;
            case 4:
                shellSort(nums, swaps, comparisons);
                break;
            case 5:
                quickSort(nums, 0, nums.size() - 1, swaps, comparisons);
                break;
            case 6:
                heapSort(nums, swaps, comparisons);
                break;
            case 7:
                mergeSort(nums, 0, nums.size() - 1, swaps, comparisons);
                break;
            case 8:
                radixSort(nums, swaps, comparisons);
                break;
            default:
                cout << "无效选择!" << endl;
                break;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "排序用时（微秒）: " << duration.count() << endl;
        cout << "交换次数: " << swaps << endl;
        cout << "比较次数: " << comparisons << endl << endl << endl;
    }

    return 0;
}

// 实现函数

void generateRandomNumbers(vector<int>& nums, int n) {
    srand((unsigned)time(0));
    for (int i = 0; i < n; ++i) {
        nums[i] = rand() % 100000;  // 生成0到99999之间的随机数
    }
}

void bubbleSort(vector<int>& nums, long long& swaps, long long& comparisons) {
    int n = nums.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (nums[j] > nums[j + 1]) {
                std::swap(nums[j], nums[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void selectionSort(vector<int>& nums, long long& swaps, long long& comparisons) {
    int n = nums.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (nums[j] < nums[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(nums[i], nums[min_idx]);
            swaps++;
        }
    }
}

void insertionSort(vector<int>& nums, long long& swaps, long long& comparisons) {
    int n = nums.size();
    for (int i = 1; i < n; i++) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key) {
            comparisons++; // 比较 nums[j] 和 key
            nums[j + 1] = nums[j];
            swaps++; // 这里的赋值操作也算作一种交换
            j--;
        }
        comparisons++; // 最后的失败比较
        nums[j + 1] = key;
    }
}

void shellSort(vector<int>& nums, long long& swaps, long long& comparisons) {
    int n = nums.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = nums[i];
            int j;
            for (j = i; j >= gap && nums[j - gap] > temp; j -= gap) {
                comparisons++; // 比较 nums[j - gap] 和 temp
                nums[j] = nums[j - gap];
                swaps++;
            }
            comparisons++; // 最后的失败比较
            nums[j] = temp;
            if (i != j) swaps++; // 如果发生了移动，则增加交换次数
        }
    }
}

int partition(vector<int>& nums, int low, int high, long long& swaps, long long& comparisons) {
    int pivot = nums[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (nums[j] < pivot) {
            i++;
            std::swap(nums[i], nums[j]);
            swaps++;
        }
    }
    std::swap(nums[i + 1], nums[high]);
    swaps++;
    return (i + 1);
}

void quickSort(vector<int>& nums, int low, int high, long long& swaps, long long& comparisons) {
    if (low < high) {
        int pi = partition(nums, low, high, swaps, comparisons);
        quickSort(nums, low, pi - 1, swaps, comparisons);
        quickSort(nums, pi + 1, high, swaps, comparisons);
    }
}

void heapify(vector<int>& nums, int n, int i, long long& swaps, long long& comparisons) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && nums[l] > nums[largest]) {
        comparisons++;
        largest = l;
    }

    if (r < n && nums[r] > nums[largest]) {
        comparisons++;
        largest = r;
    }

    if (largest != i) {
        std::swap(nums[i], nums[largest]);
        swaps++;
        heapify(nums, n, largest, swaps, comparisons);
    }
}

void heapSort(vector<int>& nums, long long& swaps, long long& comparisons) {
    int n = nums.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(nums, n, i, swaps, comparisons);
    for (int i = n - 1; i > 0; i--) {
        std::swap(nums[0], nums[i]);
        swaps++;
        heapify(nums, i, 0, swaps, comparisons);
    }
}

void merge(vector<int>& nums, int l, int m, int r, long long& swaps, long long& comparisons) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = nums[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = nums[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            nums[k] = L[i];
            i++;
        }
        else {
            nums[k] = R[j];
            j++;
        }
        swaps++;
        k++;
    }

    while (i < n1) {
        nums[k] = L[i];
        i++;
        k++;
        swaps++;
    }

    while (j < n2) {
        nums[k] = R[j];
        j++;
        k++;
        swaps++;
    }
}

void mergeSort(vector<int>& nums, int l, int r, long long& swaps, long long& comparisons) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(nums, l, m, swaps, comparisons);
    mergeSort(nums, m + 1, r, swaps, comparisons);
    merge(nums, l, m, r, swaps, comparisons);
}

int getMax(vector<int>& nums) {
    int mx = nums[0];
    for (int i = 1; i < nums.size(); i++)
        if (nums[i] > mx)
            mx = nums[i];
    return mx;
}

void countSort(vector<int>& nums, int exp, long long& swaps, long long& comparisons) {
    int n = nums.size();
    vector<int> output(n);
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++)
        count[(nums[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(nums[i] / exp) % 10] - 1] = nums[i];
        count[(nums[i] / exp) % 10]--;
        swaps++;
    }

    for (i = 0; i < n; i++)
        nums[i] = output[i];
}

void radixSort(vector<int>& nums, long long& swaps, long long& comparisons) {
    int m = getMax(nums);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(nums, exp, swaps, comparisons);
}
