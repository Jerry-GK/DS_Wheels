//This header implements a queue<int>.
//Circular
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;


class myQueue
{
#define MAX_SIZE 100000
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