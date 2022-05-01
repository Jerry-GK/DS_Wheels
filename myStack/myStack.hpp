//This header implements a stack<int>.
//Dynamic allocated, upside down
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;
#define MAX_SIZE 1000
class myStack
{
private:
    int* base;
    int* top;
    int size;

public:
    myStack();
    bool isEmpty();
    void push(int val);
    int pop();
    void dispose();
    int* GetTop();
    int get_size();
};
int myStack::get_size()
{
    return this->size;
}
myStack::myStack()
{
    base=new int[MAX_SIZE+1];
    top=base;
    size=0;
}

bool myStack::isEmpty()
{
    return size==0;
}
void myStack::push(int val)
{
    if(++size>MAX_SIZE)
    {
        cout<<"Error:Stack Up Overflow!"<<endl;
        return;
    }
    top++;
    *top=val;
}

int myStack::pop()
{
    if(--size<0)
    {
        cout<<"Error:Stack Down Overflow!"<<endl;
        return -1;
    }
    int ret = *top;
    top--;
    return ret;
}

int* myStack::GetTop()
{
    return top;
}