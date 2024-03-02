#include<iostream>
#include<iomanip>
#include<climits>
using namespace std;

const int MAX_SIZE = 11;

template<class T>
class Stack_hjw
{
public:
    Stack_hjw(int initialSize = 2);  // 构造函数，初始化堆栈大小，默认大小为2
    ~Stack_hjw();                    // 析构函数，释放堆栈占用的内存
    void push(const T& val);         // 将一个元素推入堆栈顶部
    void showElements() const;       // 显示堆栈中的所有元素
    bool isEmpty() const;            // 检查堆栈是否为空
    void makeEmpty();                // 清空堆栈
    T pop();                         // 弹出堆栈顶部的元素，并返回它
    T top() const;                   // 返回堆栈顶部的元素，但不弹出
    int getSize() const;             // 返回堆栈中的元素数量
    void elem_copy();                // 拷贝堆栈元素
private:
    void resize(int newSize);        // 调整堆栈的大小
    int m_top_copy;                  // 拷贝索引最大值
    int m_top;                       // 堆栈的顶部索引，-1表示堆栈为空
    int m_maxSize;                   // 堆栈的当前最大容量
    T* m_elements;                   // 存储堆栈元素的动态数组
    T* m_elements_copy;              // 拷贝堆栈元素的动态数组方便打印路径
};

template<class T>
Stack_hjw<T>::Stack_hjw(int initialSize) : m_maxSize(initialSize), m_top(-1)
{
    m_elements = new T[m_maxSize]; // 动态分配数组
}

template<class T>
Stack_hjw<T>::~Stack_hjw()
{
    delete[] m_elements; // 释放数组内存
    delete[] m_elements_copy;
}

template<class T>
void Stack_hjw<T>::push(const T& val)
{
    if (m_top + 1 == m_maxSize) // 堆栈已满，需要扩容
        resize(m_maxSize * 2);  // 扩大两倍
    m_elements[++m_top] = val;  // 推入新元素
}

template<class T>
void Stack_hjw<T>::showElements() const
{
    for (int i = 0; i <= m_top_copy; i++)
    {
        cout << m_elements_copy[i];
        if (i < m_top_copy) 
            cout << " ---> ";
    }
    cout << endl;
}

template<class T>
bool Stack_hjw<T>::isEmpty() const
{
    return m_top == -1; // 如果m_top为-1，则堆栈为空
}

template<class T>
void Stack_hjw<T>::makeEmpty()
{
    m_top = -1; // 将顶部设置为-1，即清空堆栈
}

template<class T>
T Stack_hjw<T>::pop()
{
    if (isEmpty())
    {
        cerr << "空栈，没有可以弹出的元素！" << endl;
        return T(); // 返回T的默认值
    }
    return m_elements[m_top--]; // 返回顶部元素，并减小m_top
}

template<class T>
T Stack_hjw<T>::top() const
{
    if (isEmpty())
    {
        cerr << "空栈，顶部没有元素！" << endl;
        return T(); // 返回T的默认值
    }
    return m_elements[m_top]; // 返回顶部元素
}

template<class T>
int Stack_hjw<T>::getSize() const
{
    return m_top + 1; // 由于m_top是0-based，所以加1得到实际大小
}

template<class T>
void Stack_hjw<T>::elem_copy()
{
    m_elements_copy = new T[m_maxSize];
    m_top_copy = m_top;
    for (int i = 0; i <= m_top; i++)
        m_elements_copy[i] = m_elements[i];
    return;
}

template<class T>
void Stack_hjw<T>::resize(int newSize)
{
    T* newElements = new T[newSize]; // 分配新的数组
    for (int i = 0; i <= m_top; i++)
        newElements[i] = m_elements[i]; // 复制旧数组的内容
    delete[] m_elements; // 释放旧数组内存
    m_elements = newElements; // 使m_elements指向新数组
    m_maxSize = newSize; // 更新最大容量
}

// 定义一个Pair_hjw模板类，其中T1和T2是该对的两个元素的类型
template<class T1, class T2>
class Pair_hjw
{
public:
    T1 first;
    T2 second;// Pair中的两个公有成员，分别代表Pair的第一个和第二个元素


    // 默认构造函数，初始化成员为其类型的默认值
    Pair_hjw() : first(T1()), second(T2()) {}
    // 带有两个参数的构造函数，用于初始化Pair的两个成员
    Pair_hjw(const T1& a, const T2& b) : first(a), second(b) {}     
    // 重载"=="运算符，比较两个Pair对象是否相等  
    bool operator ==(const Pair_hjw<T1, T2>& other) const            
    {
        return first == other.first && second == other.second;
    }  
    // 重载"+"运算符，使得可以将两个Pair对象相加
    Pair_hjw operator +(const Pair_hjw<T1, T2>& other) const        
    {
        return Pair_hjw(first + other.first, second + other.second);
    }
    // 重载输出流操作符，使得可以直接将Pair对象输出到ostream对象
    friend ostream& operator<<(ostream& output, const Pair_hjw<T1, T2>& p)     
    {
        output << "<" << p.first << "," << p.second << ">";
        return output;
    }
};

// 定义一个迷宫类
class Maze
{
public:
    Maze();                                 // 默认构造函数
    void getMazeData();                     // 从用户处获取迷宫数据
    bool isInRange(Pair_hjw<int, int> p);   // 检查给定的坐标是否在迷宫范围内
    void dfsTrace();                        // 使用深度优先搜索找到从起点到终点的路径
    void showTrace();                       // 显示找到的路径
    void setMazeData(int predefinedMaze[][7], int rows, int cols, Pair_hjw<int, int> start, Pair_hjw<int, int> end);// 设置迷宫的预定义数据
private:
    // 迷宫属性
    int m_rows;
    int m_cols;
    Pair_hjw<int, int> m_start;
    Pair_hjw<int, int> m_end;
    int m_map[MAX_SIZE][MAX_SIZE];
    int m_visited[MAX_SIZE][MAX_SIZE];
    Pair_hjw<int, int> dirs[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
    Stack_hjw<Pair_hjw<int, int>> m_traceStack;
    int m_fFindWay;
    void initArrays();                                          // 初始化地图和访问数组
    void readCoordinates(const char* msg, Pair_hjw<int, int>& coord); // 从用户处读取坐标
    void readMaze();                                                  // 从用户处读取迷宫数据

};

// Maze的默认构造函数。当创建Maze对象时，此函数将被调用。
Maze::Maze()
{
    initArrays();   // 初始化迷宫和访问数组
    m_fFindWay = 0;       // 设置找到路径的标志为0（未找到）
}

// 用于初始化迷宫和访问数组的函数
void Maze::initArrays() 
{
    for (int i = 0; i < MAX_SIZE; i++) 
    {
        for (int j = 0; j < MAX_SIZE; j++) 
        {
            m_map[i][j] = 0;         // 初始化迷宫数组为0（表示没有墙）
            m_visited[i][j] = 0;     // 初始化访问数组为0（表示未访问）
        }
    }
}

// 获取用户输入的迷宫数据，包括大小、起始和结束位置
void Maze::getMazeData() 
{
    // 获取迷宫的行数
    cout << "输入迷宫的行数，最大为10：";
    cin >> m_rows;
    while (m_rows >= MAX_SIZE || m_rows <= 0||cin.fail()) 
    {
        
        cerr << "行数非法，请重新输入合法的行数";
        cin.clear();
        cin.ignore(1024, '\n');
        cin >> m_rows;
    }

    // 获取迷宫的列数
    cout << "输入迷宫的列数，最大为10：";
    cin >> m_cols;
    while (m_cols >= MAX_SIZE || m_cols <= 0 || cin.fail())
    {
        cerr << "列数非法，请重新输入合法的列数:";
        cin.clear();
        cin.ignore(1024, '\n');
        cin >> m_cols;
    }

    // 读取入口坐标
    readCoordinates("请输入迷宫的入口坐标(x, y均从0开始)：", m_start);
    // 读取出口坐标
    readCoordinates("请输入迷宫的出口坐标:", m_end);
    // 读取实际的迷宫数据
    readMaze();

    // 将起点坐标压入路径栈
    m_traceStack.push(m_start);
}

// 读取一个坐标对并确保它们在迷宫的有效范围内
void Maze::readCoordinates(const char* msg, Pair_hjw<int, int>& coord) 
{
    cout << msg;
    cin >> coord.first >> coord.second;
    while (!isInRange(coord)) 
    {
        cerr << "坐标非法，请重新输入合法的坐标:";
        cin >> coord.first >> coord.second;
    }
}

// 从用户那里读取迷宫的实际数据
void Maze::readMaze() 
{
    cout << "请输入迷宫，1表示墙，0表示路：" << endl;
    int errFlag;
    do 
    {
        errFlag = 0;
        for (int i = 0; i < m_rows; i++) 
        {
            for (int j = 0; j < m_cols; j++) 
            {
                cin >> m_map[i][j];
                if (m_map[i][j] != 0 && m_map[i][j] != 1)
                    errFlag = 1;
            }
        }
        if (errFlag) 
            cerr << "迷宫有非法数据，请重新输入。" << endl;
    } while (errFlag);
}

// 检查给定的坐标是否在迷宫的有效范围内
bool Maze::isInRange(Pair_hjw<int, int> p)
{
    return p.first >= 0 && p.first < m_rows && p.second >= 0 && p.second < m_cols;
}

// 使用深度优先搜索算法在迷宫中查找路径
void Maze::dfsTrace() 
{
    if (!m_traceStack.getSize())                                    // 如果路径栈为空，直接返回
        return; 
    if (!isInRange(m_traceStack.top()))                             // 如果栈顶坐标不在范围内，返回
        return; 
    if (m_map[m_traceStack.top().first][m_traceStack.top().second]  // 如果栈顶坐标是墙或已经访问过
        || m_visited[m_traceStack.top().first][m_traceStack.top().second]) 
        return;
    if (m_fFindWay)                                                 // 如果已经找到路径，返回
        return;
    if (m_traceStack.top() == m_end)                                // 如果栈顶坐标是终点，设置找到路径标志为true
    {  
        m_fFindWay = 1;
        return;
    }
    m_visited[m_traceStack.top().first][m_traceStack.top().second] = 1;  // 设置当前坐标为已访问
    // 遍历当前坐标的四个方向
    for (int i = 0; i < 4; i++) 
    {
        m_traceStack.push(m_traceStack.top() + dirs[i]);  // 将新坐标压入栈中
        dfsTrace();                                       // 递归地调用dfsTrace
        if (m_fFindWay) return;                           // 如果找到路径，直接返回
        m_traceStack.pop();                               // 如果当前方向没有找到路径，从栈中弹出坐标
    }
}

// 显示找到的路径，并提供一个可视化表示
void Maze::showTrace() 
{
    // 如果没有找到路径，输出提示
    if (!m_fFindWay) 
    {
        cout << "没有合理解" << endl;  
        return;
    }             
    // 将路径栈元素拷贝
    m_traceStack.elem_copy();

    // 将路径栈中的坐标在迷宫中标记为2
    while (m_traceStack.getSize()) 
    {
        auto t = m_traceStack.pop();
        m_map[t.first][t.second] = 2;
    }
    cout << endl;
    // 输出迷宫，其中路径用*表示
    cout << "详细路径，用'*'表示：" << endl;
    for (int i = 0; i < m_rows; i++) 
    {
        cout << endl;
        for (int j = 0; j < m_cols; j++)
        {
            if (m_map[i][j] == 2)
                cout << setw(5) << "*";
            else
                cout << setw(5) << m_map[i][j];
        }
    }
    cout << endl << endl << endl;

    cout << "可行路径为：" << endl;
    // 输出路径栈中的所有坐标
    m_traceStack.showElements();
}

// 使用给定的预定义迷宫数据设置迷宫的属性
void Maze::setMazeData(int predefinedMaze[][7], int rows, int cols, Pair_hjw<int, int> start, Pair_hjw<int, int> end) 
{
    m_rows = rows;      // 设置迷宫的行数
    m_cols = cols;      // 设置迷宫的列数
    m_start = start;    // 设置起点坐标
    m_end = end;        // 设置终点坐标

    // 将预定义的迷宫数据复制到m_map数组中
    for (int i = 0; i < m_rows; i++) 
    {
        for (int j = 0; j < m_cols; j++) 
            m_map[i][j] = predefinedMaze[i][j];
    }
    // 将起点坐标压入路径栈
    m_traceStack.push(m_start);
}

int main()
{
    // 用户的选择
    int choice;
    // 创建迷宫对象
    Maze probMaze;
    // 显示菜单和获取用户选择
    cout << "菜单:" << endl;
    cout << "1: 使用默认迷宫" << endl;
    cout << "2: 输入自定义迷宫" << endl;
    cout << "0: 退出程序" << endl;
    cout << endl << endl;
    cout << "请输入您的选择:";
    cin >> choice;

    switch (choice) 
    {
        // 使用默认迷宫
        case 1: 
        {
            int predefinedMaze[7][7] = 
            {
                {1, 1, 1, 1, 1, 1, 1},
                {1, 0, 1, 0, 0, 0, 1},
                {1, 0, 1, 0, 1, 1, 1},
                {1, 0, 0, 0, 1, 0, 1},
                {1, 0, 1, 0, 0, 0, 1},
                {1, 0, 1, 0, 1, 0, 1},
                {1, 1, 1, 1, 1, 1, 1}
            };
            probMaze.setMazeData(predefinedMaze, 7, 7, { 1, 1 }, { 5, 5 });
        }
        break;
        // 输入自定义迷宫
        case 2: 
            probMaze.getMazeData();
            break;
        // 退出程序
        case 0:
            return 0;
        default:
            cerr << "无效的选择" << endl;
            return -1;
    }

    // 使用DFS查找路径
    probMaze.dfsTrace();
    // 显示找到的路径
    probMaze.showTrace();

    return 0;
}
