//This header non-recursively implements an Splay tree
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;
#define _SPLAY_MAX_SIZE 1000

class SplayTree
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
        _Node* left;//pointer to the left child
        _Node* right;//pointer to the right child
        _Node* parent;//NULL for the root
    };
    typedef struct _Node TreeNode;
    typedef TreeNode* Tree;

    Tree root;//root points to the root node of the Splay tree
    int NodesNum;//total nodes number

    //Rotations
    void RR_rotate(Tree& T);
    void LL_rotate(Tree& T);
    void RL_rotate(Tree& T);
    void LR_rotate(Tree& T);
    void Update_depth_Insert(TreeNode* start);//depth-update and single-rotation-control function for insertion

public:
    SplayTree();
    void Insert(ElementType val);//insert into the tree, find the first unblanced node(finder) and do only one rotation
    void Delete(ElementType val);//delete a node from the tree, backtrack from the parent of the deleted node
                                 //and rebalance the tree by (maybe multiple) rotations along the way to the root (complicated)
    int get_node_sum();
};

int SplayTree::get_node_sum()
{
    return this->NodesNum;
}

SplayTree::SplayTree()
{
    this->root=NULL;
    NodesNum=0;
}

void SplayTree::Insert(ElementType newval)
{
    TreeNode* myParent=NULL;
    TreeNode** temp=&root;
    //find the correct position to insert
    while(*temp!=NULL)
    {
        myParent = *temp;
        if(newval>(*temp)->val)
        {
            temp=&((*temp)->right);
        }
        else
        {
            temp=&((*temp)->left);
        }
    }
    //allocate space for the new node
    *temp = new TreeNode;
    if(*temp==NULL)
    {
        cout<<"Error: Malloc Space Overflow!"<<endl;
        return;
    }
    (*temp)->val=newval;
    (*temp)->parent = myParent;
    (*temp)->left=(*temp)->right=NULL;

    this->Update_depth_Insert(*temp);//find the unblanced node(if exist) caused by insertion and rotate once to correct

    NodesNum++;
    //cout<<"successfully insert "<<newval<<",height = "<<this->root->depth<<endl;
}


void SplayTree::Update_depth_Insert(TreeNode* start)//update the depth of nodes from root to start->parent  
{
    while(start!=NULL)
    {
        if(start==this->root)
            return;
        else if(start->parent==this->root)
        {   
            if(start->parent->val>start->val)
                LL_rotate(start->parent);
            else
                RR_rotate(start->parent);
            return;
        }
        else
        {
            //zig-zag
            if(start->val>start->parent->val&&start->parent->val<start->parent->parent->val)
                this->LR_rotate(start->parent->parent);
            else if(start->val<start->parent->val&&start->parent->val>start->parent->parent->val)
                this->RL_rotate(start->parent->parent);
            //zig-zig
            else if(start->val<start->parent->val&&start->parent->val<start->parent->parent->val)
                this->LL_rotate(start->parent->parent);
            else if(start->val>start->parent->val&&start->parent->val>start->parent->parent->val)
                this->RR_rotate(start->parent->parent);
            else
                cout<<"Error:Unknown condition"<<endl;//this should never happen    
            start=start->parent;//continue go up
        }
    }
}


//single rotation
void SplayTree::RR_rotate(Tree& T)
{
    if(T==NULL||T->right==NULL)
    {
        cout<<"Error:RR Rotation problem"<<endl;
        return;
    }

    //reconstruct the lower part
    Tree rightNode=T->right;
    T->right=rightNode->left;
    rightNode->left=T;
    T=rightNode;//T is now the new root

    //update parent message
    T->parent=T->left->parent;
    T->left->parent=T;
    if(T->left->right!=NULL)
        T->left->right->parent=T->left;
    
    //outer link
    if(T->parent==NULL)
    {
        this->root=T;
    }
    else if(T->parent->left==T->left)
    {
        T->parent->left=T;
    }
    else if(T->parent->right==T->left)
    {
        T->parent->right=T;
    }
}

void SplayTree::LL_rotate(Tree& T)
{
    if(T==NULL||T->left==NULL)
    {
        cout<<"Error:LL Rotation problem"<<endl;
        return;
    }

    //reconstruct the lower part
    Tree leftNode=T->left;
    T->left=leftNode->right;
    leftNode->right=T;
    T=leftNode;//T is now the new root

    //update parent message
    T->parent=T->right->parent;
    T->right->parent=T;
    if(T->right->left!=NULL)
        T->right->left->parent=T->right;

    //outer link
    if(T->parent==NULL)
    {
        this->root=T;
    }
    else if(T->parent->left==T->right)
    {
        T->parent->left=T;
    }
    else if(T->parent->right==T->right)
    {
        T->parent->right=T;
    }
}

//double rotation
void SplayTree::RL_rotate(Tree& T)
{
    LL_rotate(T->right);
    return RR_rotate(T);
}

void SplayTree::LR_rotate(Tree& T)
{
    RR_rotate(T->left);
    return LL_rotate(T);
}