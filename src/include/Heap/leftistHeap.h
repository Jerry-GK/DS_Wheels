//This header implements a leftist minHeap.
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;

class leftistHeap
{
typedef int ElementType;
struct _HeapNode
{
    ElementType val;       
    int npl;            
    _HeapNode *left;    
    _HeapNode *right;    
};
typedef struct _HeapNode HeapNode;
typedef HeapNode* Heap;

private:
    Heap root;
	int size;
    Heap MergeTwo(Heap H1, Heap H2);//merge two heaps
    void SwapChildren(Heap H);

public:
	leftistHeap();//initilazation
    bool isEmpty();
	void Merge(leftistHeap H);//merge with another lefist heap H
    void Insert(ElementType val);
    ElementType DeleteMin();
    int get_size();
};