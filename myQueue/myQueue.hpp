//This header implements a queue<int>.
//Circular
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;
#define MAX_SIZE 1000
class myQueue
{
public:
    myQueue();
    bool isEmpty();
    void enqueue(int val);
    int dequeue();
    void dispose();
    int *get_front();
    int *get_rear();
    int get_size();

private:
    int* front;
    int* rear;
    int size;
    int* begin;
    int* end;
    int* next_pos(int* p);
};

int *myQueue::get_front()
{
    return this->front; 
}
int *myQueue::get_rear()
{
    return this->rear; 
}
int myQueue::get_size()
{
    return this->size; 
}

myQueue::myQueue()
{
    rear=new int[MAX_SIZE];
    front=rear;
    begin=rear;
    end=rear+MAX_SIZE-1;
    size=0;
}

bool myQueue::isEmpty()
{
    return size==0;
}
void myQueue::enqueue(int val)
{
    if(++size>MAX_SIZE)
    {
        cout<<"Error:Queue Up Overflow!"<<endl;
        return;
    }
    *front=val;
    front=next_pos(front);
}

int myQueue::dequeue()
{
    if(--size<0)
    {
        cout<<"Error:Stack Down Overflow!"<<endl;
        return -1;
    }
    int ret = *rear;
    rear=next_pos(rear);
    return ret;
}

int* myQueue::next_pos(int *p)
{
    return p==end?begin:p+1;
}