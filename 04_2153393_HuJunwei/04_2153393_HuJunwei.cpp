#include <iostream>
#include <climits>
using namespace std;
const int maxQueen = 15;
class NQueens 
{
private:
    int n;               // 皇后数量
    int** board;         // 棋盘数组
    int*** solutions;    // 存储解法的数组
    int solution_count;  // 解法计数
    // 检查在指定位置是否可以安全地放置皇后
    bool is_safe(int row, int col);
    // 打印一个解法
    void print_solution(int** solution);
    // 递归求解N皇后问题
    void solve_n_queens(int row);
public:
    // 构造函数，初始化N皇后问题的棋盘和解法计数器
    NQueens(int n);
    // 析构函数，释放动态分配的内存
    ~NQueens();
    // 解决N皇后问题的入口函数
    void solve();
    // 打印所有解法
    void print_solutions();
    // 获取解法的数量
    int get_solution_count();
};

// 构造函数，初始化N皇后问题的棋盘和解法计数器
NQueens::NQueens(int n) : n(n), board(nullptr), solutions(nullptr), solution_count(0) 
{
    // 动态分配棋盘数组并初始化为0
    board = new int* [n];
    for (int i = 0; i < n; i++) 
    {
        board[i] = new int[n];
        for (int j = 0; j < n; j++) 
            board[i][j] = 0;
    }
}
// 析构函数，释放动态分配的内存
NQueens::~NQueens() 
{
    // 释放棋盘的内存
    for (int i = 0; i < n; i++) 
        delete[] board[i];
    delete[] board;

    // 释放解决方案的内存
    if (solutions) 
    {
        for (int i = 0; i < solution_count; i++) 
        {
            for (int j = 0; j < n; j++)
                delete[] solutions[i][j];
            delete[] solutions[i];
        }
        delete[] solutions;
    }
}

// 解决N皇后问题的入口函数
void NQueens::solve() 
{
    solve_n_queens(0);
}

// 打印所有解法
void NQueens::print_solutions() 
{
    for (int i = 0; i < solution_count; i++) 
    {
        print_solution(solutions[i]);
        cout << endl;
    }
}

// 获取解法的数量
int NQueens::get_solution_count() 
{
    return solution_count;
}

// 检查在指定位置是否可以安全地放置皇后
bool NQueens::is_safe(int row, int col) 
{
    // 检查同一列
    for (int i = 0; i < row; i++) 
    {
        if (board[i][col] == 1)
            return false;
    }

    // 检查左上对角线
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) 
    {
        if (board[i][j] == 1)
            return false;
    }

    // 检查右上对角线
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) 
    {
        if (board[i][j] == 1)
            return false;
    }
    return true;
}

// 打印一个解法
void NQueens::print_solution(int** solution) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++)
        {
            if (solution[i][j] == 1)
                cout << "Q ";
            else
                cout << "x ";
        }
        cout << endl;
    }
}

// 递归求解N皇后问题
void NQueens::solve_n_queens(int row) 
{
    if (row == n) 
    {
        // 复制当前解法到新的存储数组中
        int*** new_solutions = new int** [solution_count + 1];
        for (int i = 0; i < solution_count; i++) 
        {
            new_solutions[i] = new int* [n];
            for (int j = 0; j < n; j++)
            {
                new_solutions[i][j] = new int[n];
                for (int k = 0; k < n; k++) 
                    new_solutions[i][j][k] = solutions[i][j][k];
            }
        }

        // 复制当前棋盘到新解法
        int** new_solution = new int* [n];
        for (int i = 0; i < n; i++) 
        {
            new_solution[i] = new int[n];
            for (int j = 0; j < n; j++) 
                new_solution[i][j] = board[i][j];
        }
        new_solutions[solution_count] = new_solution;
        // 释放旧的解法内存
        if (solutions)
        {
            for (int i = 0; i < solution_count; i++) 
            {
                for (int j = 0; j < n; j++)
                    delete[] solutions[i][j];
                delete[] solutions[i];
            }
            delete[] solutions;
        }

        // 更新解法数组和解法计数
        solutions = new_solutions;
        solution_count++;
    }

    // 尝试在当前行的不同列放置皇后
    for (int col = 0; col < n; col++) 
    {
        if (is_safe(row, col)) 
        {
            board[row][col] = 1;  // 放置皇后
            solve_n_queens(row + 1);
            board[row][col] = 0;  // 回溯
        }
    }
}

int main() 
{
    int n;
    while (1)
    {
        cout << "请输入皇后数量: ";
        cin >> n;
        if (cin.fail() || n > maxQueen || n < 1)
        {
            cout << "输入错误，请重新输入!" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        break;
    }
    NQueens nqueens(n);
    nqueens.solve();
    cout << "共有 " << nqueens.get_solution_count() << " 种解法" << endl;
    nqueens.print_solutions();

    return 0;
}
