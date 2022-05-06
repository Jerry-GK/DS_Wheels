#include "..\include\Tree\RBTree.h"

RBTree::RBTree()
{
    this->root=NULL;
    NodesNum=0;
}

void RBTree::Insert(ElementType newval)
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
    (*temp)->col=RED;//depth of a leaf is 0
    (*temp)->left=(*temp)->right=NULL;
    
    this->Adjust_Insert(*temp);
    NodesNum++;
    cout<<"successfully insert "<<newval<<endl;
}

//single rotation
void RBTree::RR_rotate(Tree& T)
{
    TreeNode** p=&T;
    if(T==NULL||T->right==NULL)
    {
        cout<<"Error:RR Rotation problem"<<endl;
        return;
    }

    //reconstruct the lower part
    Tree rightNode=(*p)->right;
    (*p)->right=rightNode->left;
    rightNode->left=*p;
    (*p)=rightNode;//T is now the new root

    //update parent message
    (*p)->parent=(*p)->left->parent;
    (*p)->left->parent=(*p);
    if((*p)->left->right!=NULL)
        (*p)->left->right->parent=(*p)->left;
    
    //outer link
    if((*p)->parent==NULL)
    {
        this->root=(*p);
    }
    else if((*p)->parent->left==(*p)->left)
    {
        (*p)->parent->left=(*p);
    }
    else if((*p)->parent->right==(*p)->left)
    {
        (*p)->parent->right=(*p);
    }
}

void RBTree::LL_rotate(Tree& T)
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
void RBTree::RL_rotate(Tree& T)
{
    LL_rotate(T->right);
    return RR_rotate(T);
}

void RBTree::LR_rotate(Tree& T)
{
    RR_rotate(T->left);
    return LL_rotate(T);
}

bool RBTree::isBlack(TreeNode* Node)
{
    return Node==NULL || Node->col==BLACK;
}
bool RBTree::isRed(TreeNode* Node)
{
    return !isBlack(Node);
}

void RBTree::Adjust_Insert(TreeNode* focus)
{
    if(isBlack(focus->parent))//Case 0
    {
        if(focus->parent==NULL)
            focus->col=BLACK;
        return;
    }
    else
    {
        if(focus->val<focus->parent->parent->val)
        {
            if(isRed(focus->parent->parent->right))//Case 1, recolor
            {
                focus->parent->col=BLACK;
                focus->parent->parent->col=RED;
                focus->parent->parent->right->col=BLACK;
                focus=focus->parent->parent;
                if(isBlack(focus->parent))
                    return;
            }
            if(focus->val>focus->parent->val)//Case2, RR to case 3
            {
                RR_rotate(focus->parent);
                focus=focus->left;
            }
            if(focus->val<focus->parent->val)
            {
                LL_rotate(focus->parent->parent);
                focus->parent->col=BLACK;
                focus->parent->right->col=RED;
                return;
            }
        }
        else
        {
            if(isRed(focus->parent->parent->left))//Case 1, recolor
            {
                focus->parent->col=BLACK;
                focus->parent->parent->col=RED;
                focus->parent->parent->left->col=BLACK;
                focus=focus->parent->parent;
                if(isBlack(focus->parent))
                    return;
            }
            if(focus->val<focus->parent->val)//Case2, RR to case 3
            {
                LL_rotate(focus->parent);
                focus=focus->right;
            }
            if(focus->val>focus->parent->val)
            {
                RR_rotate(focus->parent->parent);
                focus->parent->col=BLACK;
                focus->parent->left->col=RED;
                return;
            }
        }
    }
}