#include<iostream>
#include <iomanip>
#include<array>

struct State
{
    // static const int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // static const int a = 10;

    static constexpr int move[8][2] = {{-2, 1},
                                      {-1, 2},
                                      {1, 2},
                                      {2, 1},
                                      {2, -1},
                                      {1, -2},
                                      {-1, -2},
                                      {-2, -1}};
    int x, y, move_idx;
    State(){};
    State(int x, int y, int move_idx):x(x), y(y), move_idx(move_idx){};
};

template <class T>
class Stack
{
private:
    T *data;
    int top;
    int capacity;
public:
    Stack(int capacity);
    void push(const T &item);
    void pop();
    bool is_empty();
    int get_top();
    T &top_data();
};

template <class T>
Stack<T>::Stack(int capacity)
:top(-1), capacity(capacity)
{
    data = new T[capacity];
    for (int i = 0; i < capacity; i++) {
        data[i] = T();
    }
}

template <class T>
void Stack<T>::push(const T &item)
{
    if (top == capacity-1)
    {
        throw "Stack full";
    }
    data[++top] = item;

    // for (int i = 0; i < top; i++)
    // {
    //     std::cout << data[i].y
    //                 << data[i].x
    //                 << data[i].move_idx;
    //     std::cout << std::endl;
    // }

}

template <class T>
void Stack<T>::pop()
{
    if (is_empty())
    {
        throw "Stack is empty";
    }
    data[top].~T();
    top--;
}

template <class T>
bool Stack<T>::is_empty()
{
    if (top == -1)
    {
        return true;
    }
    return false;
}

template <class T>
int Stack<T>::get_top()
{
    return top;
}

template <class T>
T &Stack<T>::top_data()
{
    return data[top];
}

int main(int argc, char const *argv[])
{
    // State a(1,2,3);
    // std::cout << a.x << a.y << a.move << std::endl;
    // Stack<State> s(10);
    // std::cout << s.is_empty() << std::endl;
    // s.push(State(1,2,3));
    // std::cout << s.is_empty() << std::endl;
    // s.pop();
    // std::cout << s.is_empty() << std::endl;

    int n = 6;
    int board[n][n];
    Stack<State> stack(n*n);

    // initialize board to all zero
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            board[i][j] = 0;
        }
        std::cout << std::endl;
    }

    // put 1 to top-left corner
    stack.push({0,0,-1});
    board[0][0] = stack.get_top() + 1;

    while (stack.get_top() >= 0 && stack.get_top() < n*n -1)
    {
        State &current = stack.top_data();
        // std::cout << current.y << current.x << current.move_idx << std::endl;
        for (int &i = ++current.move_idx; i < 8; i++)
        {
            State new_state(current.x + State::move[i][1], current.y + State::move[i][0], -1);
            if ((new_state.y < 0) || (new_state.x < 0) || (new_state.y >= n) || (new_state.x >= n))
            {
                continue;
            }

            if (board[new_state.y][new_state.x] > 0)
            {
                continue;
            }
            stack.push(new_state);
            board[new_state.y][new_state.x] = stack.get_top() + 1;
            break;
        }

        if (current.move_idx == 8)
        {
            board[current.y][current.x] = 0;

            stack.pop();
        }

        // print board
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                std::cout << std::setw(2) << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }



    return 0;
}
