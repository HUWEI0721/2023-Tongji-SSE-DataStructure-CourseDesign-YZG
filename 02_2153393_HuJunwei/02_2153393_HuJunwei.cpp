#include<iostream>
#include<iomanip>
#include<climits>
using namespace std;

// 定义一个结构来表示链表节点
struct LinkNode
{
	int ID;        // 节点的ID
	bool is_Dead;  // 标志，表示节点是否"死亡"
	LinkNode* next; // 指向链表中下一个节点的指针

	// 默认构造函数，初始化节点的默认值
	LinkNode()
	{
		ID = 0;
		next = nullptr;
		is_Dead = false;
	}

	// 带有参数的构造函数，用于设置节点的ID
	LinkNode(int x)
	{
		ID = x;
		next = nullptr;
		is_Dead = false;
	}
};

// 类用于实现约瑟夫问题
class Joseph_Round
{
private:
	LinkNode* head; // 指向链表头部的指针
	int N, S, M, K; // N是总人数，S是起始位置，M是步进数，K是幸存者人数

public:
	Joseph_Round(int N, int S, int M, int K);
	~Joseph_Round();
	void implement();
};

// 构造函数初始化链表
Joseph_Round::Joseph_Round(int N, int S, int M, int K) :N(N), S(S), M(M), K(K), head(nullptr)
{
	head = new LinkNode(1);
	LinkNode* point = head;

	// 创建链表节点，连接成循环链表
	for (int i = 2; i <= N; i++)
	{
		LinkNode* passenger = new LinkNode(i);
		point->next = passenger;
		point = point->next;
	}
	point->next = head;
}

// 析构函数用于释放链表节点内存
Joseph_Round::~Joseph_Round()
{
	LinkNode* point = head;
	while (point->next != head)
	{
		LinkNode* temp = point;
		point = point->next;
		delete temp;
	}
}

// 执行约瑟夫问题的计算
void Joseph_Round::implement()
{
	// 到达起始报数位置
	LinkNode* point = head;
	while (point->ID != S)
		point = point->next;

	// 计算每个死者的位置
	int count = 0;
	for (int i = 1; i <= (N - K); i++)
	{
		while (true)
		{
			if (!point->is_Dead)
			{
				count++;
				if (count == M)
				{
					cout << "第" << setw(4) << i << "个死者的位置是：" << point->ID << endl;
					point->is_Dead = true;
					count = 0;
					break;
				}
			}
			point = point->next;
		}
	}

	// 输出幸存者
	cout << "剩余  " << K << "  个生存者 其序号分别为（开始为1）：" << endl;
	point = head;
	while (1)
	{
		if (!point->is_Dead)
			cout << point->ID << "   ";
		if (point->next == head)
			break;
		else
			point = point->next;
	}
	cout << endl;
	return;
}

bool InputData(int& k)
{
	bool b = 1;
	while (b)
	{
		cin >> k;
		if (cin.fail())
		{
			cerr << "输入数据有误！请重新输入该数据：";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else
			b = 0;
	}
	return true;
}

int main()
{
	int	N, S, M, K;
	bool tag = 1;
	while (1)
	{
		N = S = M = K = 0;
		cout << "约瑟夫生死环问题" << endl;
		cout << "现有N人围成一圈，从第S个人开始依次报数" << endl;
		cout << "报M的人出局，再由下一个人开始报数" << endl;
		cout << "如此循环直至剩下K个人为止" << endl;
		cout << "N为0表示退出" << endl;

		cout << "请输入生死游戏总人数N：";
		tag = InputData(N);
		if (N == 0)
			break;
		cout << "请输入游戏开始的位置S：";
		tag = InputData(S);
		cout << "请输入死亡数字M：";
		tag = InputData(M);
		cout << "请输入剩余的生者人数K：";
		tag = InputData(K);

		Joseph_Round joseph_ring(N, S, M, K);
		joseph_ring.implement();
		
		system("pause");
		system("cls");
	}

	return 0;
}
