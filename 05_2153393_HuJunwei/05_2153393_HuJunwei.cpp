#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cctype>
#include<climits>

using namespace std;

// 自定义字符串类
class String_hjw 
{
public:
    char* str; // 动态分配的字符数组
    int length; // 字符串的长度

    // 构造函数
    String_hjw() : str(nullptr), length(0) {}

    // 从C字符串构造String_hjw
    String_hjw(const char* s) 
    {
        length = cstrlen(s);
        str = new char[length + 1];
        cstrcpy(str, s);
    }

    // 析构函数
    ~String_hjw() 
    {
        delete[] str;
    }

    // 复制构造函数
    String_hjw(const String_hjw& other) 
    {
        length = other.length;
        str = new char[length + 1];
        cstrcpy(str, other.str);
    }

    // 赋值运算符
    String_hjw& operator=(const String_hjw& other)
    {
        if (this != &other) 
        {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            cstrcpy(str, other.str);
        }
        return *this;
    }

    // C字符串长度
    static int cstrlen(const char* s)
    {
        int i = 0;
        while (s[i]) ++i;
        return i;
    }

    // C字符串复制
    static void cstrcpy(char* dest, const char* src) 
    {
        while ((*dest++ = *src++));
    }

    // 转换为小写
    void toLower()
    {
        for (int i = 0; i < length; ++i)
            str[i] = tolower(str[i]);
    }
};

// 字典树节点
struct TrieNode
{
    int wordNum; // 单词频数
    TrieNode* next[26]; // 子节点

    // 构造函数
    TrieNode() : wordNum(0)
    {
        for (int i = 0; i < 26; ++i) next[i] = nullptr;
    }

    // 析构函数
    ~TrieNode()
    {
        for (int i = 0; i < 26; ++i) delete next[i];
    }
};

// 字典树
class Trie 
{
public:
    TrieNode* root; // 根节点

    // 构造函数
    Trie() : root(new TrieNode()) {}

    // 析构函数
    ~Trie()
    {
        delete root;
    }

    // 插入字符串
    void insert(const String_hjw& word) 
    {
        TrieNode* current = root;
        for (int i = 0; i < word.length; ++i)
        {
            int index = word.str[i] - 'a';
            if (!current->next[index])
                current->next[index] = new TrieNode();
            current = current->next[index];
        }
        current->wordNum++;
    }

    // 搜索字符串
    int search(const String_hjw& word)
    {
        TrieNode* current = root;
        for (int i = 0; i < word.length; ++i) 
        {
            int index = word.str[i] - 'a';
            if (!current->next[index]) 
                return 0;
            current = current->next[index];
        }
        return current->wordNum;
    }
};

int main()
{
    cout << "文件检索系统" << endl;

    // 获取文件名
    char fileName[1024];
    cout << "请输入文件名：";
    cin.getline(fileName, 1024);

    // 打开文件用于写入
    FILE* fp = fopen(fileName, "w");
    if (fp == nullptr) 
    {
        cout << "文件打开失败" << endl;
        system("pause");
        exit(-1);
    }

    // 获取文件内容
    char fileContent[1024];
    cout << "请输入一段英文：" << endl;
    cin.getline(fileContent, 1024);

    // 写入文件内容
    fputs(fileContent, fp);
    cout << "本段文本已经保存在文本文件 \"" << fileName << "\" 中。" << endl;

    // 关闭文件
    fclose(fp);

    // 重新打开文件用于读取
    fp = fopen(fileName, "r");
    if (fp == nullptr) 
    {
        cout << "文件打开失败" << endl;
        system("pause");
        exit(-1);
    }

    // 读取文件并显示内容
    cout << endl << "显示源文件 \"" << fileName << "\"：" << endl;
    while (fgets(fileContent, 1024, fp)) 
    {
        cout << fileContent;
    }

    // 关闭文件
    fclose(fp);

    // 获取用户输入的关键字
    char keyWord[100]; // 假定关键词长度不超过100
    cout << "\n请输入要检索的关键字：";
    cin >> keyWord;
    if (getchar() == ' ')
        cout << "检测到空格，只查询空格前的单词!" << endl;
    String_hjw searchWord(keyWord);
    searchWord.toLower();

    // 重新打开文件进行搜索
    fp = fopen(fileName, "r");
    if (fp == nullptr)
    {
        cout << "文件打开失败" << endl;
        system("pause");
        exit(-1);
    }

    // 字典树
    Trie trie;
    while (fgets(fileContent, 1024, fp))
    {
        int i = 0;
        while (fileContent[i] != '\0') 
        {
            if (!isalpha(fileContent[i]))
            {
                i++;
                continue;
            }
            char currentWord[100];
            int wordLen = 0;
            while (isalpha(fileContent[i]))
                currentWord[wordLen++] = tolower(fileContent[i++]);
            currentWord[wordLen] = '\0';
            String_hjw current(currentWord);
            trie.insert(current);
        }
    }

    // 关闭文件
    fclose(fp);

    // 搜索关键字并输出结果
    cout << endl << "在源文件 \"" << fileName << "\" 中共检索到 " << trie.search(searchWord) << " 个 \"" << keyWord << "\"" << endl;

    system("pause");
    return 0;
}
