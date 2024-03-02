#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
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

// 学生对象类
class Student
{
private:
	// 准考证号，姓名，性别，年龄，报考类别
	int Id;
	String_hjw Name;
	String_hjw Gender;
	int Age;
	String_hjw Category;

public:
	Student()
	{
		Id = 0;
		Name = "0";
		Gender = "0";
		Age = 0;
		Category = "0";
	}
	Student(int id, String_hjw name, String_hjw gender, int age, String_hjw category)
	{
		Id = id;
		Name = name;
		Gender = gender;
		Age = age;
		Category = category;
	}
	~Student() {};
	int getStuId() { return this->Id; }
	String_hjw getStuName() { return this->Name; }
	String_hjw getStuGender() { return this->Gender; }
	int getStuAge() { return this->Age; }
	String_hjw getStuCategory() { return this->Category; }
};

// 存放考生数据和下个结点地址的结点类
class Node
{
	friend class Linklist;

private:
	Student Stu;
	Node* next;
	Node* last;
	Node()
	{
		Stu = Student();
		next = NULL;
		last = NULL;
	};
	~Node() {}; // 析构函数，自动释放空间
};

// 链表类
class Linklist
{
	int size;	// 链表长度
	Node* head; // 链表头地址
public:
	// 构造函数(存在表头结点)
	Linklist();
	// 析构函数，自动释放空间
	~Linklist();
	// 输入考生信息
	void Input();
	// 输出全部考生信息
	void Output();
	// 查询考生信息
	bool Search();
	// 添加考生信息
	bool Append();
	// 修改考生信息
	bool Modify();
	// 删除考生信息
	bool Delete();
	// 操作选择函数
	void selection_Operation();
};

Linklist::Linklist()
{
	head = new Node; // 分配空间
	size = 1;
	head->last = NULL;
	head->next = NULL;
}

Linklist::~Linklist()
{
	Node* temp = this->head;
	while (temp != NULL && temp->next != NULL)
	{
		temp = temp->next;
		delete temp->last;
	}
	delete temp;
};

// 输入考生信息
void Linklist::Input()
{
	cout << "首先请建立考生信息系统！" << endl;
	int student_num = 0, id = 0, age = 0;
	String_hjw name, gender, category;
	while (1)
	{
		cout << "请输入考生人数：";
		cin >> student_num;
		if (cin.fail() || student_num < 0)
		{
			cout << "考生人数输入错误，请重新输入！" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		else
			break;
	}
	cin.get();
	this->size = student_num;
	if (student_num == 0)
		return;
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别:" << endl;
	Node* current = this->head, * tempnode;
	for (int i = 0; i < student_num; i++)
	{
		// 开辟空间
		tempnode = current;
		current->next = new Node;
		current = current->next;
		current->last = tempnode;
		// 输入数据
		cin >> id >> name >> gender >> age >> category;
		current->Stu = Student(id, name, gender, age, category);
	}
	cout << endl;
}

// 输出考生信息
void Linklist::Output()
{
	Node* temp = this->head->next;
	if (temp == NULL)
		cout << "无任何考生信息" << endl;
	else
	{
		cout << setiosflags(ios::left);
		cout << setw(10) << "考号" << setw(10) << "姓名" << setw(10)
			<< "性别" << setw(10) << "年龄" << setw(10) << "报考类别" << endl;
		while (temp != NULL)
		{
			cout << setw(10) << temp->Stu.getStuId()
				<< setw(10) << temp->Stu.getStuName()
				<< setw(10) << temp->Stu.getStuGender()
				<< setw(10) << temp->Stu.getStuAge()
				<< setw(10) << temp->Stu.getStuCategory()
				<< endl;
			temp = temp->next;
		}
	}
	cout << endl;
}

// 查询考生信息
bool Linklist::Search()
{
	int num = 0;
	cout << "请输入要查找的考生考号：";
	cin >> num;
	Node* temp = this->head->next;
	while (temp != NULL)
	{
		if (temp->Stu.getStuId() == num)
		{
			cout << setiosflags(ios::left);
			cout << setw(10) << "考号" << setw(10) << "姓名" << setw(10) << "性别"
				<< setw(10) << "年龄" << setw(10) << "报考类别" << endl;
			cout << setw(10) << temp->Stu.getStuId()
				<< setw(10) << temp->Stu.getStuName()
				<< setw(10) << temp->Stu.getStuGender()
				<< setw(10) << temp->Stu.getStuAge()
				<< setw(10) << temp->Stu.getStuCategory()
				<< endl;
			cout << endl;
			return true;
		}
		else if (temp->Stu.getStuId() != num)
			temp = temp->next;
	}
	cout << "此考号不存在,请重新选择操作" << endl << endl;
	return false;
}

// 添加考生信息
bool Linklist::Append()
{
	int num = 0;
	cout << "请输入要插入的考生位置：";
	cin >> num;
	cin.get();
	if (num <= 0 || num > this->size + 1)
	{
		cout << "输入位置有误，请重新选择操作" << endl;
		cout << endl;
		return false;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别：" << endl;
	int id = 0;
	String_hjw name;
	String_hjw gender;
	int age = 0;
	String_hjw category;
	cin >> id >> name >> gender >> age >> category;
	// 检测是否有重复
	Node* temp = this->head->next;
	while (temp != NULL)
	{
		if (temp->Stu.getStuId() == id)
		{
			cout << "考生考号重复，请重新选择操作" << endl;
			cout << endl;
			return false;
		}
		else if (temp->Stu.getStuId() != id)
			temp = temp->next;
	}
	// 插入
	temp = this->head;
	while (num != 1)
	{
		temp = temp->next;
		num--;
	}
	if (temp->next == NULL)
	{
		temp->next = new Node;
		temp->next->Stu = Student(id, name, gender, age, category);
		temp->next->last = temp;
		temp->next->next = NULL;
		this->size++;
		cout << "操作成功！" << endl
			<< endl;
	}
	else if (temp->next != NULL)
	{
		Node* extra = new Node;
		extra->Stu = Student(id, name, gender, age, category);
		extra->next = temp->next;
		extra->last = temp;
		temp->next = extra;
		extra->next->last = extra;
		this->size++;
		cout << "操作成功！" << endl
			<< endl;
	}
	return true;
}

// 修改考生信息
bool Linklist::Modify()
{
	int num = 0;
	cout << "请输入要修改的考生考号：";
	cin >> num;
	Node* temp = this->head->next;
	while (temp != NULL)
	{
		if (temp->Stu.getStuId() == num)
		{
			cout << "请依次输入修改后考生的考号，姓名，性别，年龄及报考类别！" << endl;
			int id = 0, age = 0; String_hjw name, gender, category;
			cin >> id >> name >> gender >> age >> category;
			// 检测是否有重复
			Node* temppp = this->head->next;
			while (temppp != NULL)
			{
				if (temppp->Stu.getStuId() == id && temppp != temp)
				{
					cout << "考生考号重复，请重新选择操作" << endl << endl;
					return false;
				}
				else
					temppp = temppp->next;
			}
			// 进行修改
			temp->Stu = Student(id, name, gender, age, category);
			cout << "操作成功！" << endl << endl;
			return true;
		}
		else if (temp->Stu.getStuId() != num)
			temp = temp->next;
	}
	cout << "此考号不存在,请重新选择操作" << endl << endl;
	return false;
}

// 删除考生信息
bool Linklist::Delete()
{
	int num = 0;
	cout << "请输入要删除的考生考号：";
	cin >> num;
	Node* temp = this->head->next;
	while (temp != NULL)
	{
		if (temp->Stu.getStuId() == num)
		{
			cout << "你删除的考生信息是：";
			cout << setiosflags(ios::left);
			cout << setw(10) << temp->Stu.getStuId()
				<< setw(10) << temp->Stu.getStuName()
				<< setw(10) << temp->Stu.getStuGender()
				<< setw(10) << temp->Stu.getStuAge()
				<< setw(10) << temp->Stu.getStuCategory() << endl;
			if (temp->next == NULL)
			{
				temp->last->next = NULL; delete temp;
			}
			else if (temp->next != NULL)
			{
				temp->next->last = temp->last;
				temp->last->next = temp->next;
				delete temp;
			}
			cout << "操作成功！" << endl; this->size--;
			return true;
		}
		else if (temp->Stu.getStuId() != num)
			temp = temp->next;
	}
	cout << "此考号不存在,请重新选择操作" << endl << endl;
	return false;
}

void Linklist::selection_Operation()
{
	int operation = 5;
	while (operation != 0)
	{
		switch (operation)
		{
			case 1:
				this->Append();
				break;
			case 2:
				this->Delete();
				break;
			case 3:
				this->Search();
				break;
			case 4:
				this->Modify();
				break;
			case 5:
				this->Output();
				break;
			default:
				cout << "错误输入，请重新选择操作" << endl;
				break;
		}
		cout << "请选择您要进行的操作(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)" << endl;
		cout << "请选择您要进行的操作：";
		cin >> operation;
	}
	cout << "操作结束" << endl;
}
// 主函数入口
int main()
{
	Linklist studentExamSystem;
	studentExamSystem.Input();
	studentExamSystem.selection_Operation();
	cout << endl;
	cout << "按回车键结束";
	getchar();
	getchar();
	return 0;
}
