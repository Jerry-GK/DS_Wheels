//This header implements a skew minHeap.
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;

class SkewHeap
{
typedef int ElementType;
struct _HeapNode
{
    ElementType val;                
    _HeapNode *left;    
    _HeapNode *right;    
};
typedef struct _HeapNode HeapNode;
typedef HeapNode* Heap;

private:
    Heap root;
	int size;
    Heap MergeTwo(Heap H1, Heap H2);
    void SwapChildren(Heap H);

public:
	SkewHeap();//initilazation
    bool isEmpty();
	void Merge(SkewHeap H);//merge with another skew heap H
    void Insert(ElementType val);
    ElementType DeleteMin();
    int get_size();
};