#include "..\include\myQueue\myQueue.h"

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