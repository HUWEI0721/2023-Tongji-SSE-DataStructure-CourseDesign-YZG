#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cstring>
#include <float.h>
#include <climits>
using namespace std;
const int DefaultSize = 32;
// 自定义String类
class String_hjw
{
	friend istream& operator>>(istream&, String_hjw& Str);
	friend ostream& operator<<(ostream&, const String_hjw& Str);

private:
	int present_Length;
	int max_Length;
	char* ch;

public:
	String_hjw(const int size = DefaultSize);
	String_hjw(const char* init);
	String_hjw(const String_hjw& obj);
	~String_hjw();
	int length();
	String_hjw operator()(int pos, int length);
	bool operator==(const String_hjw& obj);
	bool operator!=(const String_hjw& obj);
	String_hjw& operator=(const String_hjw& obj);
	String_hjw& operator=(const char* ch);
	String_hjw& operator+=(const String_hjw& obj);
	char operator[](int num);
	int QuickFind(String_hjw& pat, int pos);
};

/***************************************************************************
  函数名称：String_hjw::String_hjw(const int size)
  功    能：初始化一个空字符串
  输入参数：const int size
  返 回 值：构造函数无返回值
***************************************************************************/
String_hjw::String_hjw(const int size)
{
	max_Length = size;
	ch = new char[size + 1];
	if (ch == NULL)
		cerr << "空间分配错误!" << endl;
	present_Length = 0;
	ch[0] = '\0';
}

/***************************************************************************
  函数名称：String_hjw::String_hjw(const char* init)
  功    能：动态分配内存以容纳字符串，并将传入的字符数组复制到新分配的内存中
  输入参数：const char* init
  返 回 值：构造函数无返回值
***************************************************************************/
String_hjw::String_hjw(const char* init)
{
	int length = strlen(init);
	max_Length = length > DefaultSize ? length : DefaultSize;
	ch = new char[max_Length + 1];
	if (ch == NULL)
		cerr << "空间分配错误!" << endl;
	present_Length = length;
	strcpy(ch, init);
}

/***************************************************************************
  函数名称：String_hjw::String_hjw(const String_hjw& obj)
  功    能：拷贝构造函数，是对String_hjw类对象（obj）的内容的拷贝,
			它会动态分配内存，并复制来自原始对象的字符串内容
  输入参数：const String_hjw& obj
  返 回 值：构造函数无返回值
***************************************************************************/
String_hjw::String_hjw(const String_hjw& obj)
{
	int length = obj.present_Length;
	max_Length = length > DefaultSize ? length : DefaultSize;
	ch = new char[max_Length + 1];
	if (ch == NULL)
		cerr << "空间分配错误!" << endl;
	present_Length = length;
	strcpy(ch, obj.ch);
}

/***************************************************************************
函数名称：String_hjw::~String_hjw()
功    能：析构函数，用于释放String_hjw对象所分配的动态内存
输入参数：无
返 回 值：析构函数无返回值
***************************************************************************/
String_hjw::~String_hjw()
{
	delete[] ch;
}

/***************************************************************************
函数名称：int String_hjw::length()
功    能：返回当前String_hjw对象中存储的字符串的长度
输入参数：无
返 回 值：返回整数，表示当前字符串的长度
***************************************************************************/
int String_hjw::length()
{
	return present_Length;
}

/***************************************************************************
函数名称：String_hjw::operator()(int pos, int length)
功    能：返回一个新的String_hjw对象，包含原始字符串对象
		  中从位置pos开始的指定长度length的子串
输入参数：int pos - 子串的起始位置
		  int length - 子串的长度
返 回 值：返回新的String_hjw对象，包含指定位置和长度的子串
***************************************************************************/
String_hjw String_hjw::operator()(int pos, int length)
{
	String_hjw s;
	if (pos >= 0 && pos < present_Length && length > 0 && pos + length - 1 < present_Length)
	{
		for (int i = 0; i < length; i++)
		{
			s.ch[i] = ch[pos + i];
		}
		s.ch[length] = '\0';
	}
	return s;
}

/***************************************************************************
函数名称：bool String_hjw::operator==(const String_hjw& obj)
功    能：比较当前String_hjw对象和另一个String_hjw对象的内容是否相等
输入参数：const String_hjw& obj - 用于比较的另一个String_hjw对象
返 回 值：如果两个String_hjw对象的内容相等，返回true；否则返回false
***************************************************************************/
bool String_hjw::operator==(const String_hjw& obj)
{
	return strcmp(ch, obj.ch) == 0;
}

/***************************************************************************
函数名称：bool String_hjw::operator!=(const String_hjw& obj)
功    能：比较当前String_hjw对象和另一个String_hjw对象的内容是否不相等
输入参数：const String_hjw& obj - 用于比较的另一个String_hjw对象
返 回 值：如果两个String_hjw对象的内容不相等，返回true；否则返回false
***************************************************************************/
bool String_hjw::operator!=(const String_hjw& obj)
{
	return strcmp(ch, obj.ch) != 0;
}

/***************************************************************************
函数名称：String_hjw::operator=(const String_hjw& obj)
功    能：实现字符串对象之间的赋值操作，将一个
		  String_hjw对象的内容赋值给另一个String_hjw对象
输入参数：const String_hjw& obj - 要赋值的String_hjw对象
返 回 值：返回当前String_hjw对象的引用
***************************************************************************/
String_hjw& String_hjw::operator=(const String_hjw& obj)
{
	if (this != &obj)
	{
		delete[] ch;
		ch = new char[obj.max_Length + 1];
		if (ch == NULL)
			cerr << "空间分配错误!" << endl;
		max_Length = obj.max_Length;
		present_Length = obj.present_Length;
		strcpy(ch, obj.ch);
	}
	return *this;
}

/***************************************************************************
函数名称：String_hjw::operator=(const char* init)
功    能：将字符串对象初始化为传入的C字符串init
输入参数：const char* init - 要用于初始化的C字符串
返 回 值：返回当前String_hjw对象的引用
***************************************************************************/
String_hjw& String_hjw::operator=(const char* init)
{
	int length = strlen(init);
	max_Length = length > DefaultSize ? length : DefaultSize;
	ch = new char[max_Length + 1];
	if (ch == NULL)
		cerr << "空间分配错误!" << endl;
	present_Length = length;
	strcpy(ch, init);
	return *this;
}

/***************************************************************************
函数名称：String_hjw::operator+=(const String_hjw& obj)
功    能：将另一个String_hjw对象的内容添加到当前String_hjw对象的末尾
输入参数：const String_hjw& obj - 要添加到当前对象的String_hjw对象
返 回 值：返回当前String_hjw对象的引用
***************************************************************************/
String_hjw& String_hjw::operator+=(const String_hjw& obj)
{
	char* temp = ch;
	int length = present_Length + obj.present_Length;
	max_Length = max_Length > length ? max_Length : length;
	ch = new char[max_Length + 1];
	if (ch == NULL)
	{
		cerr << "空间分配错误!" << endl;
		exit(1);
	}
	strcpy(ch, temp);
	strcat(ch, obj.ch);
	present_Length = length;
	delete[] temp;
	return *this;
}

/***************************************************************************
函数名称：String_hjw::operator[](int num)
功    能：返回字符串中指定位置的字符
输入参数：int num - 要获取的字符的索引位置
返 回 值：返回字符串中指定位置的字符
***************************************************************************/
char String_hjw::operator[](int num)
{
	if (num < 0 || num >= present_Length)
	{
		cerr << "out of range!\n";
		exit(1);
	}
	return ch[num];
}

/***************************************************************************
函数名称：String_hjw::QuickFind(String_hjw& pat, int pos)
功    能：在当前字符串中查找指定子串pat，从指定位置pos开始搜索
输入参数：String_hjw& pat - 要查找的子串
		  int pos - 开始搜索的位置
返 回 值：如果找到子串pat，则返回子串首次出现的位置；如果未找到，则返回-1
***************************************************************************/
int String_hjw::QuickFind(String_hjw& pat, int pos)
{
	int pLength = pat.length();
	int* next = new int[pLength];
	next[0] = -1;
	int j = 0, k = -1;
	while (j < pLength - 1)
	{
		if (k == -1 || ch[j] == ch[k])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
	int tPos = 0;
	int pPos = 0;
	while (tPos < present_Length && pPos < pLength)
	{
		if (pPos == -1 || ch[tPos] == ch[pPos])
		{
			tPos++;
			pPos++;
		}
		else
		{
			pPos = next[pPos];
		}
	}
	delete[] next;
	if (pPos < pLength)
	{
		return -1;
	}
	else
	{
		return tPos - pLength;
	}
}

/***************************************************************************
函数名称：istream& operator>>(istream& cin, String_hjw& Str)
功    能：从输入流中读取数据，并将其存储到String_hjw对象中
输入参数：istream& cin - 输入流对象
		 String_hjw& Str - 要存储数据的String_hjw对象
返 回 值：返回输入流对象istream的引用
***************************************************************************/
istream& operator>>(istream& cin, String_hjw& Str)
{
	cin >> Str.ch;
	return cin;
}

/***************************************************************************
函数名称：ostream& operator<<(ostream& cout, const String_hjw& Str)
功    能：将String_hjw对象的内容输出到输出流
输入参数：ostream& cout - 输出流对象
		 const String_hjw& Str - 要输出内容的String_hjw对象（const引用）
返 回 值：返回输出流对象ostream的引用
***************************************************************************/
ostream& operator<<(ostream& cout, const String_hjw& Str)
{
	cout << Str.ch;
	return cout;
}

// 得到一个[ minNum，maxNum ]的数字，进行了输入错误处理，保证健壮性
int GetInput(const int minNum = INT_MIN, const int maxNum = INT_MAX, const String_hjw errorInfo = "")
{
	int retNum = INT_MIN;
	while (1)
	{
		cin >> retNum;
		if (cin.fail() || retNum < minNum || retNum > maxNum) // 若输入变量类型不同或数字不在要求范围内
		{
			cin.clear();
			cin.ignore(1024, '\n');                           // 清除缓存区
			cout << errorInfo;                                // 给出错误输入的提示
			continue;
		}
		break;
	}
	return retNum;
}


// 边
struct Edge
{
	Edge()
	{
		src = dst = -1;
		value = 0;
	}
	int src;          // 起始点编号  
	int dst;          // 目标点序号
	double value;     // 边长度权重
	bool operator<(const Edge& other) { return value < other.value; };// 重载小于比较运算符
	bool operator>(const Edge& other) { return value > other.value; };// 重载大于比较运算符
};

// 点
struct Vertex
{
	Vertex()
	{
		name = "";
		ancestor = -1;
	}
	String_hjw name;
	int ancestor;          // 记录在并查集中的祖先
};

// 类模板实现优化后的快速排序，排序区间为[begin,end]
template<typename T>
void QuickSort(T a[], int begin, int end)
{
	if (begin > end)
		return;
	T mid = a[(begin + end) / 2];      // 取中间元素
	int i = begin, j = end;
	while (i < j)
	{
		while (a[i] < mid) i++;  // 查找左半部分比中间数大的数
		while (a[j] > mid) j--;  // 查找右半部分比中间数小的数
		if (i <= j)              // 如果有一组不满足排序条件（左小右大）的数
		{
			swap(a[i], a[j]);    // 交换
			i++;
			j--;
		}
	}
	if (begin < j) QuickSort(a, begin, j);// 递归排序左半部分
	if (i < end) QuickSort(a, i, end);// 递归排序右半部分
}

class Graph
{
	template<typename T>
	friend void QuickSort(T a[], int l, int r);
public:
	// 构造函数
	Graph(int n = 0, int m = 0) :vertexNumber(n), edgeNumber(m)
	{
		vertexs = NULL, edges = NULL;
		MST = NULL;
		vertexs = new Vertex[n]; edges = new Edge[m];
	}

	// 析构函数
	~Graph()
	{
		// 分别释放最小生成树、边数组和顶点数组内存，避免内存泄露
		delete[]edges;
		delete[]vertexs;
		delete MST;
	}

	bool Prim()
	{
		delete MST;
		MST = NULL;
		MST = new Graph(vertexNumber, vertexNumber - 1);

		double** adjMatrix = CreateAdjMatrix();
		double* distance = new double[vertexNumber];
		bool* visited = new bool[vertexNumber];
		int* parent = new int[vertexNumber];

		for (int i = 0; i < vertexNumber; i++)
			distance[i] = DBL_MAX, visited[i] = false, parent[i] = -1;

		distance[0] = 0;
		for (int count = 0; count < vertexNumber - 1; count++)
		{
			int u = MinDistance(distance, visited);
			visited[u] = true;
			for (int v = 0; v < vertexNumber; v++)
				if (!visited[v] && adjMatrix[u][v] && distance[v] > adjMatrix[u][v])
					parent[v] = u, distance[v] = adjMatrix[u][v];
		}

		for (int i = 1; i < vertexNumber; i++)
		{
			MST->edges[i - 1].src = parent[i];
			MST->edges[i - 1].dst = i;
			MST->edges[i - 1].value = adjMatrix[i][parent[i]];
		}

		for (int i = 0; i < vertexNumber; i++)
			delete[] adjMatrix[i];
		delete[] adjMatrix;
		delete[] distance;
		delete[] visited;
		delete[] parent;

		return true;
	}


	// 初始化顶点信息
	void InitVertex()
	{
		// 将图重置
		initGraph();

		// 初始化顶点数量
		cout << "请输入顶点的个数：";
		vertexNumber = GetInput(1, 1024, "顶点必须是1-1024的数字，请重新输入：");
		vertexs = new Vertex[vertexNumber];

		// 设置顶点名称
		cout << "请依次输入各顶点的名称：" << endl;
		for (int i = 0; i < vertexNumber; ++i)
		{
			String_hjw vertexName;
			cin >> vertexName;
			// 判断姓名是否已存在
			if (SearchVertex(vertexName) != -1)
			{
				// 若已经存在，请重新输入
				cout << "顶点" << vertexName << "已存在！请重新输入：";
				i--;
			}
			// 初始化并查集祖先为自己
			else
			{
				vertexs[i].name = vertexName;
				vertexs[i].ancestor = i;
			}
		}
	}

	// 初始化边信息
	void InitEdge()
	{
		// 删除原来的边集信息
		delete[]edges;

		cin.clear();
		cin.ignore(1024, '\n'); // 清除缓存区

		// 根据题目信息，边最多有 n*(n-1)/2 条
		cout << "请输入边的数目：";
		edgeNumber = GetInput(1, vertexNumber * (vertexNumber - 1) / 2, "根据题目信息，边最多有 n*(n-1)/2 条，请重新输入：");
		edges = new Edge[edgeNumber];

		cout << "请依次输入" << edgeNumber << "条边的起点、终点、权重：" << endl;

		for (int i = 0; i < edgeNumber; i++)
		{
			// 设置起点终点
			cout << "请输入第" << i + 1 << "条边的信息：";
			String_hjw src, dst;
			double value;
			cin >> src >> dst;
			edges[i].src = SearchVertex(src);
			edges[i].dst = SearchVertex(dst);
			// 信息异常处理
			if (edges[i].src == -1 || edges[i].dst == -1)
			{
				cout << "点信息输入错误，请重新输入：" << endl;
				cin.clear();
				cin.ignore(1024, '\n');                           // 清除缓存区
				i--;
				continue;
			}

			// 设置边权
			cin >> value;
			// 信息异常处理
			if (cin.fail() || value <= 0)
			{
				cout << "点信息输入错误，请重新输入：" << endl;
				cin.clear();
				cin.ignore(1024, '\n');                           // 清除缓存区
				i--;
				continue;
			}
			edges[i].value = value;
		}
	}

	// 打印最小生成树
	void printMST()
	{
		// 未生成成功
		if (MST == NULL)
		{
			cout << "未生成最小生成树，请先生成！" << endl << endl;
			return;
		}


		// 生成成功
		cout << "最小生成树信息如下：" << endl;
		// 输出MST中的信息
		for (int i = 0; i < MST->edgeNumber; i++)
			cout << "选边信息：起点<" << vertexs[MST->edges[i].src].name << ">  终点<" << vertexs[MST->edges[i].dst].name << ">  权值：" << MST->edges[i].value << endl;

		cout << endl;

	}


private:
	int MinDistance(const double distance[], const bool visited[])
	{
		double min = DBL_MAX;
		int min_index;

		for (int v = 0; v < vertexNumber; v++)
			if (!visited[v] && distance[v] < min)
				min = distance[v], min_index = v;

		return min_index;
	}

	double** CreateAdjMatrix()
	{
		double** matrix = new double* [vertexNumber];
		for (int i = 0; i < vertexNumber; i++)
		{
			matrix[i] = new double[vertexNumber];
			for (int j = 0; j < vertexNumber; j++)
				matrix[i][j] = (i == j ? 0 : DBL_MAX);
		}

		for (int i = 0; i < edgeNumber; i++)
		{
			int src = edges[i].src;
			int dst = edges[i].dst;
			double val = edges[i].value;
			matrix[src][dst] = val;
			matrix[dst][src] = val; // Assuming undirected graph
		}

		return matrix;
	}


	// 将图重置
	void initGraph()
	{
		vertexNumber = 0, edgeNumber = 0;
		if (edges != NULL)	delete[]edges;
		if (vertexs != NULL)delete[]vertexs;
		edges = NULL, vertexs = NULL;
	}

	// 寻找在图中是否有名字为s的顶点
	int SearchVertex(const String_hjw& s)
	{
		for (int i = 0; i < vertexNumber; i++)
		{
			// 如果有，返回下标
			if (vertexs[i].name == s)
				return i;
		}
		// 如果没有，返回-1
		return -1;
	}

	// 并查集寻父节点，采用记忆化搜索，进行路径压缩优化
	int FindAncestor(int i)
	{
		if (i == vertexs[i].ancestor) return i;
		return vertexs[i].ancestor = FindAncestor(vertexs[i].ancestor);
	}

	Graph* MST;					  // 最小生成树
	int vertexNumber, edgeNumber; // 记录顶点数、边数
	Edge* edges;                  // 顶点数组
	Vertex* vertexs;              // 边数组
};

// 得到A-E的字符，进行了错误输入处理
char Choice()
{
	cout << endl << "请选择操作：";
	char ret = '\0';

	while (1)
	{
		cin >> ret;
		if (cin.fail() || ret < 'A' || ret > 'E') // 若输入变量类型不同或数字不在要求范围内
		{
			cin.clear();
			cin.ignore(1024, '\n');                           // 清除缓存区
			cout << "输入错误，请重新输入：";                 // 给出错误输入的提示
			continue;
		}
		break;
	}
	return ret;
}

int main()
{
	cout << "**                       电网造价模拟系统                       **" << endl;
	cout << "==================================================================" << endl;
	cout << "**                       A---创建电网顶点                       **" << endl;
	cout << "**                       B---添加电网的边                       **" << endl;
	cout << "**                       C---构建最小生成树                     **" << endl;
	cout << "**                       D---显示最小生成树                     **" << endl;
	cout << "**                       E---退出程序                           **" << endl;
	cout << "==================================================================" << endl;

	Graph graph;
	while (1)
	{
		char ch = Choice();
		switch (ch)
		{
			case 'A':
				graph.InitVertex();
				break;
			case 'B':
				graph.InitEdge();
				break;
			case 'C':
				if (graph.Prim()) cout << "Prime最小生成树生成完毕！" << endl;
				else cout << "无法生成最小生成树！";
				break;
			case 'D':
				graph.printMST();
				break;
			case 'E':
				system("pause");
				return 0;
		}
	}
}
