//This header implements a stack<int>
//Dynamic allocated, upside down
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
#define MAX_SIZE 1000
using namespace std;

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