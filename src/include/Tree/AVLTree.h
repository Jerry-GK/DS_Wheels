//This header non-recursively implements an AVL tree
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;
#define _AVL_MAX_SIZE 1000

class AVLTree
{
private:
    typedef int ElementType;
    int max_ele(ElementType a, ElementType b)
    {
        return a>b?a:b;
    }
    struct _Node
    {
        ElementType val;//content value
        int depth;//depth of a node. 0 for leaves, -1 for NULL(also represents the height of a tree whose root is this node)
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
    int getBF(Tree T);//get the BF value (height of left subtree - height of right subtree)
    void Update_depth_Insert(TreeNode* start);//depth-update and single-rotation-control function for insertion
    void Update_depth_Delete(TreeNode* start);//depth-update multiple-rotation-control function for deletion

public:
    AVLTree();
    void Insert(ElementType val);//insert into the tree, find the first unblanced node(finder) and do only one rotation
    void Delete(ElementType val);//delete a node from the tree, backtrack from the parent of the deleted node
                                 //and rebalance the tree by (maybe multiple) rotations along the way to the root (complicated)
    int get_node_sum();
};