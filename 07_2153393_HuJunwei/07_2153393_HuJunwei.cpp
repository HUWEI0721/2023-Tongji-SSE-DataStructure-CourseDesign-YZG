#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cstring>
#include<climits>
using namespace std;

class String_hjw
{
private:
    char* data;
    size_t len;

public:
    String_hjw() : data(new char[1]), len(0)
    {
        data[0] = '\0'; // ����Ϊ���ַ���
    }

    String_hjw(const char* str)
    {
        len = strlen(str);
        data = new char[len + 1];
        strcpy(data, str);
    }

    // ��Ӹ��ƹ��캯��
    String_hjw(const String_hjw& other)
    {
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
    }

    // ��Ӹ�ֵ����������
    String_hjw& operator=(const String_hjw& other)
    {
        if (this != &other)
        {
            delete[] data; // ɾ����ǰ�ַ������ڴ�
            len = other.len;
            data = new char[len + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    ~String_hjw()
    {
        delete[] data;
        data = nullptr; // ����Ϊ nullptr �Ա����ظ�ɾ��
    }

    char operator[](size_t index) const
    {
        return data[index];
    }

    size_t size() const
    {
        return len;
    }

    // Ϊ�˼򻯣������resize��������С�����
    void resize(size_t newSize)
    {
        char* newData = new char[newSize + 1];
        if (data)
        {
            strncpy(newData, data, len);
            delete[] data;
        }
        data = newData;
        len = newSize;
        data[len] = '\0';
    }

    void append(char c)
    {
        resize(len + 1);
        data[len - 1] = c;
    }

    friend std::istream& operator>>(std::istream& in, String_hjw& str);
};

std::istream& operator>>(std::istream& in, String_hjw& str)
{
    char c;
    while (in.get(c) && c != '\n' && !isspace(c))
    {
        str.append(c);
    }
    return in;
}

// �Զ���Stack_hjw��
template<typename T>
class Stack_hjw
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node(T val) : data(val), next(NULL) {}
    };

    Node* topNode = NULL;

public:
    void push(const T& val)
    {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop()
    {
        if (topNode)
        {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    T top() const
    {
        if (topNode) return topNode->data;
        throw std::runtime_error("Stack is empty!");
    }

    bool empty() const
    {
        return topNode == NULL;
    }
};

struct TreeNode 
{
    char val;
    bool hasLeftBracket;  // ��ʾ�ڵ�ǰ�Ƿ���������
    bool hasRightBracket; // ��ʾ�ڵ���Ƿ���������
    TreeNode* left;
    TreeNode* right;

    TreeNode(char x) : val(x), left(NULL), right(NULL), hasLeftBracket(false), hasRightBracket(false) {}
};


class ExpressionTree
{
private:
    int precedence(char op)
    {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    TreeNode* buildTree(String_hjw s)
    {
        Stack_hjw<TreeNode*> nodes;
        Stack_hjw<char> ops;
        bool nextHasLeftBracket = false;

        for (int i = 0; i < s.size(); i++)
        {
            if (isdigit(s[i]))
            {
                TreeNode* node = new TreeNode(s[i]);
                node->hasLeftBracket = nextHasLeftBracket;
                nextHasLeftBracket = false;
                nodes.push(node);
            }
            else if (s[i] == '(')
            {
                nextHasLeftBracket = true;
                ops.push(s[i]);
            }
            else if (s[i] == ')')
            {
                while (ops.top() != '(')
                {
                    createSubTree(ops, nodes);
                }
                ops.pop();
                if (!nodes.empty())
                {
                    nodes.top()->hasRightBracket = true;
                }
            }
            else
            {
                while (!ops.empty() && precedence(ops.top()) >= precedence(s[i]))
                {
                    createSubTree(ops, nodes);
                }
                ops.push(s[i]);
            }
        }
        while (!ops.empty())
        {
            createSubTree(ops, nodes);
        }
        return nodes.top();
    }

    void createSubTree(Stack_hjw<char>& ops, Stack_hjw<TreeNode*>& nodes)
    {
        char op = ops.top();
        ops.pop();
        TreeNode* right = nodes.top();
        nodes.pop();
        TreeNode* left = nodes.top();
        nodes.pop();
        TreeNode* curr = new TreeNode(op);
        curr->left = left;
        curr->right = right;
        nodes.push(curr);
    }

    void preorder(TreeNode* node)
    {
        if (!node) return;

        if (node->hasLeftBracket) cout << "(";
        cout << node->val << " ";
        preorder(node->left);
        preorder(node->right);
        if (node->hasRightBracket) cout << ")";
    }

    void inorder(TreeNode* node)
    {
        if (!node)
            return;

        if (node->hasLeftBracket) cout << "(";

        if (node->left)
            inorder(node->left);

        cout << node->val << " ";

        if (node->right)
            inorder(node->right);

        if (node->hasRightBracket) cout << ")";
    }


    void postorder(TreeNode* node)
    {
        if (!node) return;

        if (node->hasLeftBracket) cout << "(";
        postorder(node->left);
        postorder(node->right);
        cout << node->val << " ";
        if (node->hasRightBracket) cout << ")";
    }

    TreeNode* root;

public:
    ExpressionTree(String_hjw s)
    {
        root = buildTree(s);
    }

    void printPreorder()
    {
        cout << "�������ʽ  :";
        preorder(root);
        cout << endl;
    }

    void printInorder()
    {
        cout << "��׺���ʽ  :";
        inorder(root);
        cout << endl;
    }

    void printPostorder()
    {
        cout << "�沨�����ʽ:";
        postorder(root);
        cout << endl;
    }
};


int main()
{
    String_hjw expression;
    cout << "������ʽ:";
    cin >> expression;

    ExpressionTree et(expression);
    et.printPreorder();
    et.printInorder();
    et.printPostorder();

    return 0;
}
