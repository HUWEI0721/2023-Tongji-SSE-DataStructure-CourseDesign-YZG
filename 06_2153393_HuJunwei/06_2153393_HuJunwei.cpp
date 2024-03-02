#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <cstring>
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


// 自定义的家庭成员类
class FamilyMember
{
public:
	// 指向下一个兄弟的指针
	FamilyMember* nextSibling = nullptr;
	// 指向第一个孩子的指针
	FamilyMember* firstChild = nullptr;
	// 用于存储家庭成员的名字
	String_hjw memberName;
	// 默认构造函数
	FamilyMember() {};
	// 使用兄弟、孩子和名字作为参数的构造函数
	FamilyMember(FamilyMember* sibling, FamilyMember* child, String_hjw name)
		: nextSibling(sibling), firstChild(child), memberName(name) {};
	// 使用名字作为参数的构造函数
	FamilyMember(String_hjw name) : memberName(name) {};
};

// 家庭树类
class FamilyTree
{
public:
	// 指向树的根节点的指针
	FamilyMember* rootMember;
	// 默认构造函数
	FamilyTree() : rootMember(nullptr) {};
	// 初始化树的方法，获取根节点的名字
	void initializeTree();
	// 完善树的某个节点
	void updateTreeMember();
	// 根据名字递归地找到某个家庭成员并返回其地址
	FamilyMember* findMemberAddress(FamilyMember* currentMember, String_hjw name);
	// 根据名字递归地找到某个家庭成员的前一个成员并返回其地址
	FamilyMember* findPreviousMemberAddress(FamilyMember* currentMember, String_hjw name);
	// 为某个成员增加孩子
	void addChildToMember();
	// 解散局部家庭
	void dissolveSubTree();
	// 递归地删除某个家庭成员及其子孙
	void deleteSubTree(FamilyMember* memberRoot);
	// 为某个家庭成员改名
	void renameMember();
	// 打印家谱
	void printFamilyMember(FamilyMember* member, int indentLevel = 0);
	void printEntireFamilyTree();
};

// 初始化家族树的根节点
void FamilyTree::initializeTree()
{
	String_hjw ancestorName;
	cout << "首先建立一个家谱!" << endl;
	cout << "请输入祖先的姓名:";
	cin >> ancestorName;
	cout << "此家谱的祖先是:";
	cout << ancestorName << endl << endl;
	rootMember = new FamilyMember(ancestorName);
}

// 更新家族树的某个成员的子女信息
void FamilyTree::updateTreeMember()
{
	String_hjw memberName;
	int childrenCount;
	cout << "请输入要建立家庭的人的姓名:";
	cin >> memberName;
	auto targetMember = findMemberAddress(rootMember, memberName);

	if (!targetMember)
	{
		cerr << "家谱中找不到该成员。" << endl;
		return;
	}
	if (targetMember->firstChild)
	{
		cerr << "该成员已经有子女了" << endl;
		return;
	}
	cout << "请输入" << memberName << "的儿女人数:";
	cin >> childrenCount;
	if (childrenCount < 1)
	{
		cout << "子孙节点数太少，无需添加" << endl;
		return;
	}

	cout << "请依次输入" << memberName << "的儿女姓名:";
	cin >> memberName;
	auto newChild = new FamilyMember(memberName);
	targetMember->firstChild = newChild;
	auto currentChild = newChild;
	for (int i = 0; i < childrenCount - 1; i++)
	{
		cin >> memberName;
		auto nextChild = new FamilyMember(memberName);
		currentChild->nextSibling = nextChild;
		currentChild = nextChild;
	}
	currentChild = newChild;
	cout << targetMember->memberName << "的第一代子孙是:";
	while (currentChild)
	{
		cout << currentChild->memberName << '\t';
		currentChild = currentChild->nextSibling;
	}
	cout << endl;
}

// 根据姓名递归地查找某个家庭成员并返回其地址
FamilyMember* FamilyTree::findMemberAddress(FamilyMember* currentMember, String_hjw name)
{
	if (!currentMember)
		return nullptr;
	if (currentMember->memberName == name)
		return currentMember;

	FamilyMember* siblingAddress = findMemberAddress(currentMember->nextSibling, name);
	if (siblingAddress)
		return siblingAddress;

	FamilyMember* childAddress = findMemberAddress(currentMember->firstChild, name);
	if (childAddress)
		return childAddress;

	return nullptr;
}

// 根据姓名递归地找到某个家庭成员的前一个成员并返回其地址
FamilyMember* FamilyTree::findPreviousMemberAddress(FamilyMember* currentMember, String_hjw name)
{
	if (!currentMember)
		return nullptr;

	FamilyMember* siblingResult = nullptr;
	FamilyMember* childResult = nullptr;

	if (currentMember->nextSibling && currentMember->nextSibling->memberName == name)
		return currentMember;

	siblingResult = findPreviousMemberAddress(currentMember->nextSibling, name);

	if (currentMember->firstChild && currentMember->firstChild->memberName == name)
		return currentMember;

	childResult = findPreviousMemberAddress(currentMember->firstChild, name);

	return siblingResult ? siblingResult : childResult;
}

// 为家庭成员添加子女
void FamilyTree::addChildToMember()
{
	cout << "请输入要添加子女的人的姓名:";
	String_hjw parentName, memberName;
	cin >> parentName;
	auto targetMember = findMemberAddress(rootMember, parentName);
	if (!targetMember)
	{
		cerr << "家庭中没有该成员" << endl;
		return;
	}
	auto currentChild = targetMember->firstChild;
	if (!currentChild)
	{
		//没有子女
		cout << "请输入" << parentName << "新添加的子女的姓名:";
		cin >> memberName;
		targetMember->firstChild = new FamilyMember(memberName);
		cout << parentName << "的第一代子孙是：" << memberName << endl;
		return;
	}
	while (currentChild->nextSibling)
		currentChild = currentChild->nextSibling;

	cout << "请输入" << parentName << "新添加的子女的姓名:";
	cin >> memberName;
	currentChild->nextSibling = new FamilyMember(memberName);
	cout << parentName << "的第一代子孙是：" << memberName << endl;
}


// 解散家族树的某个子树
void FamilyTree::dissolveSubTree()
{
	cout << "请输入要解散家庭的人的姓名:";
	String_hjw memberName;
	cin >> memberName;

	auto previousMember = findPreviousMemberAddress(rootMember, memberName);

	if (!previousMember)
	{
		cout << "不存在这样的家庭" << endl;
		return;
	}

	FamilyMember* targetSubTree = nullptr;

	if (previousMember->firstChild && previousMember->firstChild->memberName == memberName)
	{
		targetSubTree = previousMember->firstChild;
		previousMember->firstChild = targetSubTree->nextSibling;
	}
	else
	{
		targetSubTree = previousMember->nextSibling;
		previousMember->nextSibling = targetSubTree->nextSibling;
	}

	auto currentChild = targetSubTree->firstChild;

	if (!currentChild)
	{
		cout << memberName << "没有子孙" << endl;
		cout << "正在删除: " << targetSubTree->memberName << endl;  // 显示正在删除的家庭成员的姓名
		deleteSubTree(targetSubTree);
		return;
	}
	cout << "要解散的家庭的人是:" << memberName << endl;
	cout << memberName << "的第一代子孙是:";
	while (currentChild)
	{
		cout << currentChild->memberName << '\t';
		currentChild = currentChild->nextSibling;
	}
	cout << endl;
	cout << "正在删除家庭：" << memberName << " 及其所有子孙..." << endl;  // 显示正在删除的家庭及其所有子孙的通知

	deleteSubTree(targetSubTree);
}


// 递归地删除家族树的某个子树
void FamilyTree::deleteSubTree(FamilyMember* currentRoot)
{
	if (!currentRoot)
		return;

	FamilyMember* sibling = currentRoot->nextSibling;
	FamilyMember* child = currentRoot->firstChild;

	deleteSubTree(sibling);
	deleteSubTree(child);

	delete currentRoot;
}

// 修改家族树的某个成员的名字
void FamilyTree::renameMember()
{
	cout << "请输入要修改的成员目前的姓名:";
	String_hjw currentName;
	cin >> currentName;

	auto targetMember = findMemberAddress(rootMember, currentName);

	if (!targetMember)
	{
		cout << "此人不存在" << endl;
		return;
	}

	cout << "请输入更改后的姓名:";
	String_hjw newName;
	cin >> newName;

	targetMember->memberName = newName;
	cout << currentName << "已更名为" << newName << endl;
}
void FamilyTree::printFamilyMember(FamilyMember* member, int indentLevel)
{
	if (!member)
		return;

	// 打印缩进以显示层级
	for (int i = 0; i < indentLevel; i++)
		cout << "  ";

	cout << member->memberName << endl;

	// 打印子孙
	FamilyMember* child = member->firstChild;
	while (child)
	{
		printFamilyMember(child, indentLevel + 1);
		child = child->nextSibling;
	}
}
void FamilyTree::printEntireFamilyTree()
{
	cout << "家谱成员：" << endl;
	printFamilyMember(rootMember);  // 
}


class FamilyTreeManager
{
public:
	void displayMenu();
	void handleUserInput();
	FamilyTree familyTree;
};

void FamilyTreeManager::displayMenu()
{
	cout << "**             家谱管理系统                **" << endl;
	cout << "=============================================" << endl;
	cout << "**           请选择要执行的操作            **" << endl;
	cout << "**            A --- 完善家谱               **" << endl;
	cout << "**            B --- 添加家庭成员           **" << endl;
	cout << "**            C --- 解散局部家庭           **" << endl;
	cout << "**            D --- 更改家庭成员姓名       **" << endl;
	cout << "**            E --- 查找家庭成员           **" << endl;
	cout << "**            F --- 打印所有家庭成员       **" << endl;
	cout << "**            G --- 退出程序               **" << endl;
	cout << "=============================================" << endl;
}

void FamilyTreeManager::handleUserInput()
{
	familyTree.initializeTree();
	char userOption;

	while (true)
	{
		cout << "请输入要执行的操作:";
		cin >> userOption;

		switch (userOption)
		{
			case 'A':
				familyTree.updateTreeMember();
				break;
			case 'B':
				familyTree.addChildToMember();
				break;
			case 'C':
				familyTree.dissolveSubTree();
				break;
			case 'D':
				familyTree.renameMember();
				break;
			case 'E':
			{
				String_hjw memberName;
				cout << "请输入要查找的家庭成员姓名:";
				cin >> memberName;

				auto memberAddress = familyTree.findMemberAddress(familyTree.rootMember, memberName);
				if (!memberAddress)
				{
					cout << "未找到该成员" << endl;
					break;
				}

				auto currentChild = memberAddress->firstChild;
				if (!currentChild)
				{
					cout << memberName << "没有子孙" << endl;
					break;
				}
				cout << memberName << "的第一代子孙是:";
				while (currentChild)
				{
					cout << currentChild->memberName << '\t';
					currentChild = currentChild->nextSibling;
				}
				cout << endl;
				break;
			}
			case 'F':
				cout << "家谱成员：" << endl;
				familyTree.printFamilyMember(familyTree.rootMember);
				break;
			case 'G':
				return;
			default:
				cerr << "请输入正确的操作码" << endl;
				break;
		}
		cout << endl;
	}
}

int main()
{
	FamilyTreeManager familyManager;
	familyManager.displayMenu();
	familyManager.handleUserInput();
	return 0;
}
