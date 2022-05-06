#include "..\include\myStack\myStack.h"

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