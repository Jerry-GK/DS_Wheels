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

bool SkewHeap::isEmpty()
{
    return this->root==NULL;
}
SkewHeap::SkewHeap()
{
    this->size=0;
    this->root=NULL;
}

SkewHeap::Heap SkewHeap::MergeTwo(Heap H1, Heap H2)
{
    if(H1==NULL)
        return H2;
    if(H2==NULL)
        return H1;
    if(H1->val>H2->val)
    {
        //swap H1,H2
        Heap temp=H1;
        H1=H2;
        H2=temp;
    }

    if(H1->left==NULL)
        H1->left=H2;
    else
    {
        H1->right=MergeTwo(H1->right, H2);
        //unconditionally swap! regardless of NPL
        SwapChildren(H1);
    }
    return H1;
}

void SkewHeap::SwapChildren(Heap H)
{
    HeapNode* temp=H->left;
    H->left=H->right;
    H->right=temp;
}

void SkewHeap::Merge(SkewHeap H)
{  
    this->root=MergeTwo(this->root, H.root);
    this->size+=H.size;
}

void SkewHeap::Insert(ElementType val)
{  
    SkewHeap singleNodeHeap;
    singleNodeHeap.root=new HeapNode;
    singleNodeHeap.root->left=singleNodeHeap.root->right=NULL;
    singleNodeHeap.size=1;
    singleNodeHeap.root->val=val;

    this->Merge(singleNodeHeap);
}

SkewHeap::ElementType SkewHeap::DeleteMin()
{
    if(this->isEmpty())
    {
        cout<<"The Heap isAlready Empty!"<<endl;
        return 0;
    }
    ElementType temp=this->root->val;
    HeapNode* p=this->root;

    this->root=MergeTwo(this->root->left, this->root->right);
    this->size--;
    delete p;
    return temp;
}

int SkewHeap::get_size()
{
    return this->size;
}