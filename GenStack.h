#include <iostream>

using namespace std;

template<typename t>
class GenStack
{
  public:
    int size;
    int top;
    t *arr;

    GenStack();
    GenStack(int maxSize);
    ~GenStack();

    int getTop();
    void push(t d);
    t pop();
    t peek();
    void print();
};
