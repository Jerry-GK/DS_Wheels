#include "..\include\Tree\BSTree.h"

int BSTree::get_node_sum()
{
    return this->NodesNum;
}

BSTree::BSTree()
{
    this->root=NULL;
    NodesNum=0;
}

void BSTree::Insert(int newval)
{
    TreeNode** temp=&root;
    while(*temp!=NULL)
    {
        if(newval>(*temp)->val)
        {
            temp=&((*temp)->right);
        }
        else
        {
            temp=&((*temp)->left);
        }
    }
    *temp = new TreeNode;
    if(*temp==NULL)
    {
        cout<<"Error: Malloc Space Overflow!"<<endl;
        return;
    }
    (*temp)->val=newval;
    cout<<"successfully insert "<<newval<<endl;
    (*temp)->left=(*temp)->right=NULL;
    NodesNum++;
}

void BSTree::Delete(int delval)
{
    TreeNode** temp=&root;
    if(*temp==NULL)
    {
        cout<<"Errot:No such value to delete!"<<endl;
        return;
    }
    while((*temp)->val!=delval)
    {
        if(delval>(*temp)->val)
        {
            temp=&((*temp)->right);
        }
        else
        {
            temp=&((*temp)->left);
        }
        if(*temp==NULL)
        {
            cout<<"Errot:No such value to delete!"<<endl;
            return;
        }
    }
    if((*temp)->left==NULL)
    {
        TreeNode* ttemp=*temp;
        *temp=(*temp)->right;
        delete ttemp;
    }
    else
    {
        TreeNode *del_temp=*temp;
        temp=&((*temp)->left);
        while((*temp)->right!=NULL)
        {
            temp=&((*temp)->right);
        }
        del_temp->val=(*temp)->val;

        TreeNode *ttemp=*temp;
        *temp=(*temp)->left;
        delete ttemp;
    }
    cout<<"successfully delete "<<delval<<endl;
}