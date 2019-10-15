#include <iostream>
#include "GenStack.h"

using namespace std;

template<typename t>
GenStack<t>::GenStack(){
  arr = new t[64];
  size = 64;
  top = -1;
}

template<typename t>
GenStack<t>::GenStack(int size){
  arr = new t[size];
  size = size;
  top = -1;
}

template<typename t>
GenStack<t>::~GenStack()
{
  delete[] arr;
}

template<typename t>
int GenStack<t>::getTop()
{
  return top;
}

template<typename t>
void GenStack<t>::push(t d)
{
  if(!(top<size-1)){ //grows if not enough space
    t *newArr = new t[size+64];
    for(int i = 0; i < size; ++i){
      newArr[i] = arr[i];
    }
    size = size+64;
    delete[] arr;
    arr = newArr;
  }
  arr[++top] = d;
}

template<typename t>
t GenStack<t>::pop()
{
  if(top==-1){
    std::cout << "The Stack is Empty! Nothing to remove" << std::endl;
  }else{
    return arr[top--];
  }
}

template<typename t>
t GenStack<t>::peek()
{
  return arr[top];
}

template<typename t>
void GenStack<t>::print()
{
  for(int i = 0; i <= top; ++i){
    cout << arr[i] << endl;
  }
}
