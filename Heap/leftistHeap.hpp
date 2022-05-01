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

bool leftistHeap::isEmpty()
{
    return this->root==NULL;
}
leftistHeap::leftistHeap()
{
    this->size=0;
    this->root=NULL;
}

leftistHeap::Heap leftistHeap::MergeTwo(Heap H1, Heap H2)//the key part
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
        if(H1->left->npl < H1->right->npl)
            SwapChildren(H1);
        H1->npl=H1->right->npl+1;
    }
    return H1;
}

void leftistHeap::SwapChildren(Heap H)
{
    HeapNode* temp=H->left;
    H->left=H->right;
    H->right=temp;
}

void leftistHeap::Merge(leftistHeap H)
{  
    this->root=MergeTwo(this->root, H.root);
    this->size+=H.size;
}

void leftistHeap::Insert(ElementType val)
{  
    leftistHeap singleNodeHeap;
    singleNodeHeap.root=new HeapNode;
    singleNodeHeap.root->left=singleNodeHeap.root->right=NULL;
    singleNodeHeap.root->npl=0;
    singleNodeHeap.size=1;
    singleNodeHeap.root->val=val;

    this->Merge(singleNodeHeap);
}

leftistHeap::ElementType leftistHeap::DeleteMin()
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

int leftistHeap::get_size()
{
    return this->size;
}