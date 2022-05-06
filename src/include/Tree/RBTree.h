//This header non-recursively implements an  Red-Black tree
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;


class RBTree
{
#define MAX_SIZE 1000   
private:
    typedef int ElementType;

    enum color{BLACK,RED};
    int max_ele(ElementType a, ElementType b)
    {
        return a>b?a:b;
    }
    struct _Node
    {
        ElementType val;//content value
        color col;
        _Node* left;//pointer to the left child
        _Node* right;//pointer to the right child
        _Node* parent;//NULL for the root
    };
    typedef struct _Node TreeNode;
    typedef TreeNode* Tree;

    Tree root;//root points to the root node of the AVL tree
    int NodesNum;//total nodes number
    //Rotations
    void RR_rotate(Tree& T);
    void LL_rotate(Tree& T);
    void RL_rotate(Tree& T);
    void LR_rotate(Tree& T);
    bool isBlack(TreeNode* Node);
    bool isRed(TreeNode* Node);
    void Adjust_Insert(TreeNode* focus);

public:
    RBTree();
    void Insert(ElementType val);
    //void Delete(ElementType val);
};