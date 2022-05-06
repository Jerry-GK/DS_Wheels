//This header implements a binary searching tree
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>

using namespace std;

class BSTree
{
#define MAX_SIZE 1000
private:
    struct _Node
    {
        int val;
        _Node* left;
        _Node* right;
    };
    typedef struct _Node TreeNode;
    typedef TreeNode* Tree;

    Tree root;
    int NodesNum;
    
public:
    BSTree();
    void Insert(int val);
    void Delete(int val);
    int get_node_sum();
};