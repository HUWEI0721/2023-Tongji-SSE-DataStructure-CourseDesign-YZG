#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<climits>

using namespace std;

// 定义二叉搜索树节点结构体
struct BinarySearchTreeNode 
{
    double value; // 节点储存的数据
    BinarySearchTreeNode* left;  // 指向左子节点的指针
    BinarySearchTreeNode* right; // 指向右子节点的指针

    // 节点构造函数
    BinarySearchTreeNode(double val = 0.0) : value(val), left(nullptr), right(nullptr) {}
};

// 重载输出运算符，方便打印节点值
ostream& operator<<(ostream& os, const BinarySearchTreeNode& node)
{
    os << node.value << "->";
    return os;
}

// 二叉搜索树类
class BinarySearchTree
{
private:
    BinarySearchTreeNode* root; // 根节点指针

    // 递归释放节点内存
    void FreeMemory(BinarySearchTreeNode* node) 
    {
        if (node == nullptr) return;
        FreeMemory(node->left);
        FreeMemory(node->right);
        delete node;
    }

    // 内部插入函数
    void InsertInternal(BinarySearchTreeNode*& node, double key)
    {
        if (node == nullptr)
        {
            node = new BinarySearchTreeNode(key);
            if (node == nullptr)
            {
                cerr << "内存分配错误！" << endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (key < node->value)
            InsertInternal(node->left, key);
        else if (key > node->value)
            InsertInternal(node->right, key);
    }

    // 内部搜索函数
    BinarySearchTreeNode* SearchInternal(BinarySearchTreeNode* node, double key) const
    {
        if (node == nullptr || node->value == key) 
            return node;
        if (key < node->value)
            return SearchInternal(node->left, key);
        return SearchInternal(node->right, key);
    }

    // 中序遍历
    void InOrderTraversal(BinarySearchTreeNode* node) const 
    {
        if (node == nullptr) return;
        InOrderTraversal(node->left);
        cout << *node;
        InOrderTraversal(node->right);
    }

public:
    // 构造函数
    BinarySearchTree() : root(nullptr) {}

    // 析构函数
    ~BinarySearchTree() 
    {
        FreeMemory(root);
    }

    // 插入新节点
    bool Insert(double key) 
    {
        if (root == nullptr)
        {
            root = new BinarySearchTreeNode(key);
            return true;
        }
        if (SearchInternal(root, key) == nullptr) 
        {
            InsertInternal(root, key);
            return true;
        }
        else
        {
            cout << "节点" << key << "已经存在于二叉搜索树中" << endl;
            return false;
        }
    }

    // 搜索值为key的节点
    BinarySearchTreeNode* Search(double key) const
    {
        return SearchInternal(root, key);
    }

    // 打印树的中序遍历
    void PrintInOrder() const
    {
        InOrderTraversal(root);
        cout << endl;
    }

    // 获取根节点指针
    BinarySearchTreeNode* GetRoot() const
    {
        return root;
    }

    // 清空二叉搜索树
    void Clear() 
    {
        FreeMemory(root);
        root = nullptr;
    }
};

// 用户操作选择函数
char GetUserChoice() 
{
    char choice = '\0';
    cout << "请选择操作：";
    while (!(cin >> choice) || choice < '1' || choice > '4')
    {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "输入错误，请重新输入：" << endl;
    }
    return choice;
}

int main() 
{
    cout << "**             二叉排序树操作菜单             **" << endl;
    cout << "================================================" << endl;
    cout << "**             1 -- 建立二叉排序树            **" << endl;
    cout << "**             2 -- 插入元素                  **" << endl;
    cout << "**             3 -- 查询元素                  **" << endl;
    cout << "**             4 -- 退出程序                  **" << endl;
    cout << "================================================" << endl;

    BinarySearchTree bst;
    double key;

    while (true) 
    {
        char ch = GetUserChoice();
        switch (ch) {
            case '1':
                bst.Clear();
                cout << "请输入元素值，以0结束：" << endl;
                while (cin >> key && key != 0.0) 
                    bst.Insert(key);
                cout << "二叉排序树元素：" << endl;
                bst.PrintInOrder();
                break;

            case '2':
                if (bst.GetRoot() == nullptr) 
                    cout << "请先建立二叉搜索树！" << endl;
                else 
                {
                    cout << "请输入要插入的元素：" << endl;
                    cin >> key;
                    bst.Insert(key);
                    bst.PrintInOrder();
                }
                break;

            case '3':
                if (bst.GetRoot() == nullptr) 
                    cout << "请先建立二叉搜索树！" << endl;
                else
                {
                    cout << "请输入要查询的元素：" << endl;
                    cin >> key;
                    if (bst.Search(key))
                        cout << key << "存在于二叉搜索树中！" << endl;
                    else
                        cout << key << "不存在于二叉搜索树中！" << endl;
                }
                break;

            case '4':
                cout << "程序退出。" << endl;
                return 0;
        }
    }
    return 0;
}
