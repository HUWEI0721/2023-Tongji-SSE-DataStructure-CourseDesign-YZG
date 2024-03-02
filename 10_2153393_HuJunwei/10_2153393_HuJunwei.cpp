#include<iostream>
#include<iomanip>
#include<time.h>
#include<cmath>
#include<climits>

using namespace std;

// 定义一个结构体来保存两个整数
struct TwoNumbers
{
	int firstNumber; // 第一个整数
	int secondNumber; // 第二个整数

	// 构造函数，用来初始化两个数
	TwoNumbers(int first, int second) : firstNumber(first), secondNumber(second) {}
};

// 堆的结构定义
struct Heap
{
	int* heapData; // 指向堆数据的指针
	int heapSize; // 堆中元素的数量
	bool (*compareFunction)(int, int); // 比较函数指针，用于比较堆中的元素
	int operationCount; // 记录操作次数的变量

	// 默认构造函数
	Heap() : heapData(nullptr), heapSize(0), operationCount(0) {}
	// 带参数的构造函数
	Heap(int* data, int size, bool (*compare)(int, int));
	// 析构函数
	~Heap();

	// 成员函数声明
	int ParentIndex(int index); // 获取父节点索引
	int LeftChildIndex(int index); // 获取左子节点索引
	int RightChildIndex(int index); // 获取右子节点索引

	void BuildHeap(int size); // 建立堆
	void Heapify(int index, int size); // 对堆进行调整
};

// 析构函数的实现
Heap::~Heap()
{
	delete[] heapData; // 释放堆数据所使用的内存
}

// 获取父节点索引的实现
int Heap::ParentIndex(int index)
{
	return (index - 1) / 2; // 根据子节点索引计算父节点索引
}

// 获取左子节点索引的实现
int Heap::LeftChildIndex(int index)
{
	return 2 * index + 1; // 根据父节点索引计算左子节点索引
}

// 获取右子节点索引的实现
int Heap::RightChildIndex(int index)
{
	return 2 * index + 2; // 根据父节点索引计算右子节点索引
}

// 建立堆的实现
void Heap::BuildHeap(int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		Heapify(i, size); // 从最后一个非叶子节点开始调整，直到根节点
	}
}

// 对堆进行调整的实现
void Heap::Heapify(int index, int size)
{
	int largestOrSmallest, leftIndex, rightIndex;

	while (LeftChildIndex(index) < size)
	{
		largestOrSmallest = leftIndex = LeftChildIndex(index);
		rightIndex = RightChildIndex(index);

		// 判断右子节点是否存在，并且是否满足比较条件
		if (rightIndex < size && compareFunction(heapData[rightIndex], heapData[leftIndex]))
		{
			largestOrSmallest = rightIndex;
		}

		// 调整当前节点与其子节点的位置，保持堆的性质
		if (!compareFunction(heapData[index], heapData[largestOrSmallest]))
		{
			swap(heapData[index], heapData[largestOrSmallest]); // 交换节点
			operationCount++; // 增加操作次数
			index = largestOrSmallest; // 更新当前节点索引，继续向下调整
		}
		else
		{
			break; // 如果满足堆性质，则退出循环
		}
	}
}

// 带参数的构造函数实现
Heap::Heap(int* data, int size, bool (*compare)(int, int))
{
	heapSize = size; // 设置堆大小
	heapData = new int[heapSize]; // 分配内存
	compareFunction = compare; // 设置比较函数
	operationCount = 0; // 操作次数初始化为0

	// 复制数据到堆中
	for (int i = 0; i < heapSize; i++)
	{
		heapData[i] = data[i];
	}

	BuildHeap(heapSize); // 建立堆
}

class mySort
{
private:
	int* originalData; // 原始数据
	int* currentData;  // 用于排序的数据副本
	int dataSize;      // 数据的大小
	int operationCount; // 操作计数

public:
	mySort(int n);
	~mySort();

	inline void swap(int& a, int& b);
	void reset();
	void output(const string& method);
	void log(); // for test 
	void print();

	void bubble_sort(bool(*compare_func)(int, int));
	void quick_sort(bool(*compare_func)(int, int));
	void quick_sort(bool(*compare_func)(int, int), int low, int high);
	void selection_sort(bool(*compare_func)(int, int));
	void heap_sort(bool(*compare_func)(int, int));
	void straight_insertion_sort(bool(*compare_func)(int, int));
	void shell_sort(bool(*compare_func)(int left, int right));
	void merge_sort(bool(*compare_func)(int left, int right));

	void radix_sort(bool(*compare_func)(int left, int right), int base = 10);
	void merge_sort(bool(*compare_func)(int left, int right), int start, int end);
	void merge(bool(*compare_func)(int left, int right), int start, int mid, int end);

	int getDigit();

	TwoNumbers partitionDutchFlag(bool(*compare_func)(int, int), int low, int high, int pivotIndex);
};

mySort::mySort(int n)
{
	originalData = new int[n];
	currentData = new int[n];
	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < n; i++) {
		originalData[i] = currentData[i] = rand();
	}
	operationCount = 0;
	dataSize = n;
}

mySort::~mySort()
{
	delete[] currentData;
	delete[] originalData;
}

void mySort::swap(int& a, int& b)
{
	if (a == b) return;

	int temp = a;
	a = b;
	b = temp;
}

void mySort::reset()
{
	operationCount = 0;
	for (int i = 0; i < dataSize; i++) {
		currentData[i] = originalData[i];
	}
}

void mySort::output(const string& method)
{
	cout << setw(20) << left << method + "的次数" << operationCount << endl;
}

void mySort::log()
{
	for (int i = 0; i < dataSize; i++) {
		cout << currentData[i] << " ";
	}
	cout << endl;
}

void mySort::print()
{
	for (int i = 0; i < dataSize; i++) {
		cout << originalData[i] << " ";
	}
	cout << endl;
}

void mySort::bubble_sort(bool(*compare_func)(int left, int right))
	{
		for (int i = 0; i < dataSize; i++)
		{
			for (int j = 0; j < dataSize - i - 1; j++)
			{
				if (compare_func(currentData[j], currentData[j + 1]))
					swap(currentData[j], currentData[j + 1]);
				operationCount++;
			}
		}
		output("冒泡排序");
		reset();
	}

void mySort::quick_sort(bool(*compare_func)(int left, int right))
{
	quick_sort(compare_func, 0, dataSize - 1);
	output("快速排序");
	reset();
}

void mySort::quick_sort(bool(*compare_func)(int left, int right), int low, int high)
{
	if (low < high)
	{
		int random = low + rand() % (high - low + 1);
		TwoNumbers result = partitionDutchFlag(compare_func, low, high, random);
		quick_sort(compare_func, low, result.firstNumber - 1);
		quick_sort(compare_func, result.secondNumber + 1, high);
	}
}

void mySort::selection_sort(bool(*compare_func)(int left, int right))
{
	for (int i = 0; i < dataSize; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < dataSize; j++)
		{
			if (compare_func(currentData[minIndex], currentData[j]))
				minIndex = j;
			operationCount++;
		}
		swap(currentData[minIndex], currentData[i]);
	}
	output("选择排序");
	reset();
}

void mySort::heap_sort(bool(*compare_func)(int left, int right))
{
	Heap heap(currentData, dataSize, compare_func); // 初始化堆
	heap.BuildHeap(dataSize); // 构建堆

	for (int i = dataSize - 1; i > 0; i--)
	{
		swap(heap.heapData[0], heap.heapData[i]); // 将最大元素放到数组末尾
		heap.Heapify(0, i); // 对剩余的堆进行调整
		heap.operationCount++; // 更新操作次数
	}

	cout << setw(20) << left << "堆排序的次数" << heap.operationCount << endl;
}

void mySort::straight_insertion_sort(bool(*compare_func)(int left, int right))
{
	for (int i = 1; i < dataSize; i++)
	{
		int temp = currentData[i], j = i;
		while (j > 0 && !compare_func(currentData[j - 1], temp))
		{
			currentData[j] = currentData[j - 1];
			operationCount++;
			j--;
		}
		currentData[j] = temp;
	}
	output("直接插入排序");
	reset();
}

void mySort::shell_sort(bool(*compare_func)(int left, int right))
{
	for (int gap = dataSize / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < dataSize; i += 1)
		{
			int temp = currentData[i];
			int j;
			for (j = i; j >= gap && compare_func(currentData[j - gap], temp); j -= gap)
			{
				currentData[j] = currentData[j - gap];
				operationCount++;
			}
			currentData[j] = temp;
		}
	}
	output("希尔排序");
	reset();
}

void mySort::merge_sort(bool(*compare_func)(int left, int right))
{
	int partSize, startIndex, midIndex, endIndex;
	for (partSize = 1; partSize < dataSize; partSize *= 2) {
		for (startIndex = 0; startIndex < dataSize; startIndex += (2 * partSize)) {
			midIndex = min(startIndex + partSize - 1, dataSize - 1); //闭区间
			endIndex = min(startIndex + 2 * partSize - 1, dataSize - 1);
			merge(compare_func, startIndex, midIndex, endIndex);
		}
	}

	output("归并排序");
	reset();
}

void mySort::merge_sort(bool(*compare_func)(int left, int right), int start, int end) 
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		merge_sort(compare_func, start, mid);
		merge_sort(compare_func, mid + 1, end);
		merge(compare_func, start, mid, end);
	}
}

void mySort::merge(bool(*compare_func)(int left, int right), int start, int mid, int end)
{
	int leftIndex = start, rightIndex = mid + 1, * tempData = new int[end - start + 1], tempIndex = 0;
	while (leftIndex <= mid && rightIndex <= end) 
	{
		operationCount++;
		if (compare_func(currentData[rightIndex], currentData[leftIndex]))
			tempData[tempIndex++] = currentData[leftIndex++];
		else
			tempData[tempIndex++] = currentData[rightIndex++];
	}

	while (leftIndex <= mid) 
	{
		tempData[tempIndex++] = currentData[leftIndex++];
		operationCount++;
	}

	while (rightIndex <= end) 
	{
		tempData[tempIndex++] = currentData[rightIndex++];
		operationCount++;
	}

	for (int i = start; i <= end; i++)
		currentData[i] = tempData[i - start];

	delete[]tempData;
}

void mySort::radix_sort(bool(*compare_func)(int left, int right), int base)
{
	int digit = getDigit(), radix = 1;
	int* nums = new int[base], * tempData = new int[dataSize];
	for (int i = 0; i < digit; i++, radix *= 10)
	{
		for (int j = 0; j < base; j++) // 清零
			nums[j] = 0;

		for (int j = 0; j < dataSize; j++)
		{
			operationCount++;
			(nums[currentData[j] / radix % 10])++;
		}

		for (int j = 1; j < base; j++)
			nums[j] += nums[j - 1];

		for (int j = dataSize - 1; j >= 0; j--) //应从尾部开始 不然后面数字的权重不符
			tempData[--(nums[currentData[j] / radix % 10])] = currentData[j];

		for (int j = 0; j < dataSize; j++)
			currentData[j] = tempData[j];
	}

	delete[] tempData;
	delete[] nums;

	output("基排序");
	reset();
}

int mySort::getDigit()
{
	int result = 1, maxNum = originalData[0];

	for (int i = 0; i < dataSize; i++)
		if (originalData[i] > maxNum)
			maxNum = originalData[i];

	while (maxNum /= 10)
		result++;

	return result;
}

TwoNumbers mySort::partitionDutchFlag(bool(*compare_func)(int left, int right), int low, int high, int pivotIndex)
{
	int smaller = low, equal = low, larger = high, pivot = currentData[pivotIndex];
	while (equal <= larger)
	{
		operationCount++;
		if (compare_func(currentData[equal], pivot))
		{
			swap(currentData[equal], currentData[larger]);
			larger--;
		}
		else if (currentData[equal] == pivot)
			equal++;
		else
		{
			swap(currentData[smaller], currentData[equal]);
			equal++;
			smaller++;
		}
	}

	return TwoNumbers(smaller, larger);
}

int main()
{
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
	int size;
	cout << "请输入要产生的随机数的个数: ";
	cin >> size;
	mySort sort(size);
	cout << endl;
	cout << "请选择从大到小排序还是从小到大排序(输入 N/n 代表从小到大排序,输入其他为默认从大到小排序):" << endl;
	bool(*compare_func)(int left, int right) = [](int left, int right) -> bool {return left < right; };
	char input;
	cin >> input;
	if (input == 'n' || input == 'N')
		compare_func = [](int left, int right) -> bool {return left > right; };

	int choice = -1;
	while (true)
	{
		while (true)
		{
			cout << "请输入你选择的排序算法:";
			cin >> choice;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else if (choice < 0 || choice>9)
				cout << "输入存在错误！请重新输入\n";
			else
				break;
		}

		if (!choice)
			break;
		auto timeStart = clock();
		switch (choice)
		{
			case 1:
				sort.bubble_sort(compare_func);
				break;
			case 2:
				sort.selection_sort(compare_func);
				break;
			case 3:
				sort.straight_insertion_sort(compare_func);
				break;
			case 4:
				sort.shell_sort(compare_func);
				break;
			case 5:
				sort.quick_sort(compare_func);
				break;
			case 6:
				sort.heap_sort(compare_func);
				break;
			case 7:
				sort.merge_sort(compare_func);
				break;
			case 8:
				sort.radix_sort(compare_func);
				break;
			case 9:
				sort.print();
				break;
		}
		auto timeEnd = clock();
		cout << setw(20) << "花费时间为:" << double((timeEnd - timeStart)) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
		cout << endl << endl;
	}
	return 0;
}
