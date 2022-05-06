#include "..\include\Tree\AVLTree.h"

int AVLTree::get_node_sum()
{
    return this->NodesNum;
}

AVLTree::AVLTree()
{
    this->root=NULL;
    NodesNum=0;
}

int AVLTree::getBF(Tree T)
{
    if(T==NULL)
        return 0;//bf value of NULL is defined to be 0
    else
    {
        int leftDepth=T->left==NULL?-1:T->left->depth;
        int rightDepth=T->right==NULL?-1:T->right->depth;
        return leftDepth-rightDepth;
    }
}

void AVLTree::Insert(ElementType newval)
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
    (*temp)->depth=0;//depth of a leaf is 0
    (*temp)->left=(*temp)->right=NULL;

    this->Update_depth_Insert(*temp);//find the unblanced node(if exist) caused by insertion and rotate once to correct

    NodesNum++;
    //cout<<"successfully insert "<<newval<<",height = "<<this->root->depth<<endl;
}

void AVLTree::Delete(ElementType delval)
{
    TreeNode** temp=&root;
    if(*temp==NULL)
    {
        cout<<"Error:Empty tree!"<<endl;
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
            cout<<"Error:No such value to delete!"<<endl;
            return;
        }
    }
    //*temp points to the node that should be deleted
    if((*temp)->left==NULL)//no left subtree
    {
        TreeNode* ttemp=*temp;
        TreeNode* start = (*temp)==NULL?NULL:(*temp)->parent;//the parent of the deleted node (update depth down from it)

        if(((*temp)->right)!=NULL)
            (*temp)->right->parent=(*temp)->parent;
        *temp=(*temp)->right;
        delete ttemp;

        this->Update_depth_Delete(start);
    }
    else//left subtree exists
    {
        //replace the deleted node with the maximum node in the left subtree 
        TreeNode *del_temp=*temp;
        temp=&((*temp)->left);
        while((*temp)->right!=NULL)//find the maximum node in the left subtree
        {
            temp=&((*temp)->right);
        }
        del_temp->val=(*temp)->val;

        TreeNode *ttemp=*temp;
        TreeNode* start = (*temp)==NULL?NULL:(*temp)->parent;//the parent of the deleted node (update depth down from it)
        if(((*temp)->left)!=NULL)
            (*temp)->left->parent=(*temp)->parent;
        *temp=(*temp)->left;

        this->Update_depth_Delete(start);//go from <start> to the root, do rotation when needed and update depth

        delete ttemp;
    }
    //cout<<"successfully delete "<<delval<<endl;
    NodesNum--;
}

void AVLTree::Update_depth_Insert(TreeNode* start)//update the depth of nodes from root to start->parent  
{
    int maker;//trouble maker value(inserted value)
    if(start!=NULL)
    {
        maker=start->val;
        start=start->parent;
    }
    while(start!=NULL)
    {
        int leftDepth = (start->left)==NULL?-1:start->left->depth;
        int rightDepth = (start->right)==NULL?-1:start->right->depth;
        int finder=start->val;
        int BF=leftDepth-rightDepth;
        if(abs(BF)>1)
        {
            //do rotation according to the relationship of the position of root, root's children and the inserted node
            if(maker<finder&&maker<start->left->val)
                this->LL_rotate(start);
            else if(maker<finder&&maker>start->left->val)
                this->LR_rotate(start);
            else if(maker>finder&&maker<start->right->val)
                this->RL_rotate(start);
            else if(maker>finder&&maker>start->right->val)
                this->RR_rotate(start);
            else
            {
                cout<<"Error:Unknown condition"<<endl;//this should never happen
            }
        }
        else
            //if rotation happens, depth of relative nodes will be updated in the rotation function
            start->depth=max_ele(leftDepth+1,rightDepth+1);
        start=start->parent;//continue go up to check balance
    }
}

void AVLTree::Update_depth_Delete(TreeNode* start)//update the depth of nodes from root to start->parent  
{
    //CORRECTION AFTER DELETION IS THE MOST COMPLICATED PART OF AVL TREE 
    if(start==NULL)//NULL will be passed in only if the deleted node has no left subtree and is the root
        return;
    while(start!=NULL)
    {
        int leftDepth = (start->left)==NULL?-1:start->left->depth;
        int rightDepth = (start->right)==NULL?-1:start->right->depth;

        int BF=leftDepth-rightDepth;   
        int newDepth=max_ele(leftDepth+1,rightDepth+1);

        if(abs(BF)<=1&&start->depth==newDepth)//the depth of current node did not change, don't need to go up to check balance
        {    
            break; 
        }
        else if(abs(BF)<=1&&start->depth>newDepth)//taller subtree of the current node is shorted, go up to check
        {
            start->depth=newDepth;//update depth
            start=start->parent;
        }
        else if(abs(BF)>1)//the shorter subtree of the cuurent node is shorted, unbalance happens at this node 
        {
            //LOGIC IN THIS PART(WHY ROTATE IN THIS WAY) IS NOT THAT EASY TO QUICKLY UNDERSTAND
            start->depth=newDepth;//update depth
            
            if(leftDepth < rightDepth)//Deletion happens in left subtree
            {
                if(getBF(start->right)==0)//the right subtree is balanced
                {
                    RR_rotate(start);
                    break;
                }
                else if(getBF(start->left)==getBF(start->right))//BF values of left and right subtrees are the same
                {
                    RR_rotate(start);
                    start=start->parent;
                }
                else if(getBF(start->left)!=getBF(start->right))//BF values of left and right subtrees are not the same
                {
                    LL_rotate(start->right);
                    RR_rotate(start);
                    start=start->parent;
                }
            }
            if(rightDepth < leftDepth)//Deletion happens in right subtree
            {
                if(getBF(start->left)==0)//the left subtree is balanced
                {
                    LL_rotate(start);
                    break;
                }
                else if(getBF(start->right)==getBF(start->left))//BF values of left and right subtrees are the same
                {
                    LL_rotate(start);
                    start=start->parent;
                }
                else if(getBF(start->right)!=getBF(start->left))//BF values of left and right subtrees are not the same
                {
                    RR_rotate(start->left);
                    LL_rotate(start);
                    start=start->parent;
                }
            }
        }
    }
}

//single rotation
void AVLTree::RR_rotate(Tree& T)
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

    //update depth
    int lld = (T->left->left)==NULL?-1:T->left->left->depth;
    int lrd = (T->left->right)==NULL?-1:T->left->right->depth;
    int rd = (T->right)==NULL?-1:T->right->depth;
    T->left->depth=max_ele(lld+1,lrd+1);
    T->depth=max_ele(T->left->depth+1,rd+1);
  
    //Update_depth(T);
}

void AVLTree::LL_rotate(Tree& T)
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

    //update depth
    int rrd = (T->right->right)==NULL?-1:T->right->right->depth;
    int rld = (T->right->left)==NULL?-1:T->right->left->depth;
    int ld = (T->left)==NULL?-1:T->left->depth;
    T->right->depth=max_ele(rrd+1,rld+1);
    T->depth=max_ele(T->right->depth+1,ld+1);

    //Update_depth(T);
}

//double rotation
void AVLTree::RL_rotate(Tree& T)
{
    LL_rotate(T->right);
    return RR_rotate(T);
}

void AVLTree::LR_rotate(Tree& T)
{
    RR_rotate(T->left);
    return LL_rotate(T);
}