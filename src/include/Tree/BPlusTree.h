//This header implements a B+ tree
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include<cstdio>
#include<stdlib.h>
#include <iostream>
#include <vector>
#include<queue>
using namespace std;

class BPlusTree
{
#define MAX_SIZE 1000
#define DEGREE		3
#define NEGINF -999999
private:
	typedef int ElementType;

	struct _Node
	{
		vector<ElementType> keys;//key values
		vector<struct _Node*> childrens;//pointers to children.For leaves it's empty.For nonleaf nodes it's equal length to keys.
		struct _Node* parent;
		
		int num;//number of children
		bool isLeaf;
	};
	typedef struct _Node TreeNode;
	typedef TreeNode* Tree;

    Tree root;//root points to the root node of the B+ tree
	TreeNode* leafPointer;//point to the leftist leaf node.
	void Insert_nonleaf(TreeNode* p,TreeNode* newchild);

public:
    BPlusTree();
    void Insert(ElementType val);
	//void update_path(TreeNode* p);  
	void Print();
};