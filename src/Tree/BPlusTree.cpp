#include "..\include\Tree\BPlusTree.h"

BPlusTree::BPlusTree()
{
    this->root=NULL;
	this->leafPointer=NULL;
}


void BPlusTree::Insert_nonleaf(TreeNode* p, TreeNode* newchild)
{
	// if(p==NULL)
	// {
	// 	cout<<"Error:Insert into NULL"<<endl;
	// 	return;
	// }
	if(p->num==0)//insert into an initially empty nonleaf node
	{
		p->keys.push_back(newchild->keys[0]);
		p->childrens.push_back(newchild);
		p->num++;
		return;
	}
	vector<TreeNode*>::iterator itc=p->childrens.begin();
	for(vector<ElementType>::iterator itk=p->keys.begin();;itk++)
	{
		if(itk==p->keys.end()||newchild->keys[0]<*itk)
		{
			//cout<<"insert "<<newval<<"\n";
			p->keys.insert(itk,newchild->keys[0]);
			p->childrens.insert(itc,newchild);
			p->num++;
			break;		
		}
		itc++;
	}
	if(p->num>DEGREE)//after insertion the leaf node has DEGREE+1 keys
	{
		//split the nonleaf node
		TreeNode* right_half_node=new TreeNode;
		right_half_node->num=DEGREE+1-(DEGREE+1)/2;
		right_half_node->parent=p->parent;
		right_half_node->isLeaf=p->isLeaf;
		//reallocate pointers and keys
		right_half_node->keys.assign(p->keys.begin()+(DEGREE+1)/2, p->keys.end());
		right_half_node->childrens.assign(p->childrens.begin()+(DEGREE+1)/2, p->childrens.end());
		for(vector<TreeNode*>::iterator it=right_half_node->childrens.begin();it!=right_half_node->childrens.end();it++)
		{
			(*it)->parent=right_half_node;
		}
		p->num=(DEGREE+1)/2;
		p->keys.erase(p->keys.begin()+(DEGREE+1)/2,  p->keys.end());
		p->childrens.erase(p->childrens.begin()+(DEGREE+1)/2,  p->childrens.end());

		if(p->parent==NULL)
		{
			TreeNode* CommonParent=new TreeNode;
			p->parent=CommonParent;
			right_half_node->parent=CommonParent;
			CommonParent->parent=NULL;
			CommonParent->isLeaf=false;
			CommonParent->num=0;
			//CommonParent->childrens.push_back(p);
			//CommonParent->childrens.push_back(right_half_node);

			this->root=CommonParent;
			this->Insert_nonleaf(CommonParent,p);
			this->Insert_nonleaf(CommonParent,right_half_node);
		}
		else
		{
			this->Insert_nonleaf(p->parent,right_half_node);
		}
	}
}

void BPlusTree::Insert(ElementType newval)
{
	if(this->leafPointer==NULL)//empty tree
	{
		leafPointer=new TreeNode;
		leafPointer->num=0;
		leafPointer->keys.push_back(newval);
		leafPointer->isLeaf=true;
		leafPointer->num++;
		leafPointer->parent=NULL;
		this->root=leafPointer;
		//cout<<"insert "<<newval<<"\n";
		return;
	}
	
	//insert into nonempty tree
	TreeNode *temp=root;
	if(newval<=leafPointer->keys[0])//insert a minimum element
	{
		temp=leafPointer;//directly jump to the leftist leaf
	}
	while(!temp->isLeaf)//find the leaf node to insert
	{
		for(int i=0;i<temp->num;i++)
		{
			if(temp->keys[i]<newval&&(i==temp->num-1||newval<temp->keys[i+1]))
			{
				temp=temp->childrens[i];
				break;
			}
		}
	}
	//temp is now the inserted leaf node,directly insert into the leaf node
	for(vector<ElementType>::iterator it=temp->keys.begin();;it++)
	{
		if(it==temp->keys.end()||newval<=*it)
		{
			//cout<<"insert "<<newval<<"\n";
			if(it!=temp->keys.end()&&newval==*it)
			{
				cout<<"Key "<<newval<<" is duplicated"<<endl;
				return;
			}
			temp->keys.insert(it,newval);
			if(it==temp->keys.begin())
			{
				//update the "left edge" of the tree to the newly inserted minimum value
				TreeNode* leftist=temp->parent;
				while(leftist!=NULL)
				{
					leftist->keys[0]=newval;
					leftist=leftist->parent;
				} 
			}
			temp->num++;
			break;		
		}
	}
	if(temp->num>DEGREE)//after insertion the leaf node has DEGREE+1 keys
	{
		//split the leaf node
		TreeNode* right_half_leaf=new TreeNode;
		right_half_leaf->num=DEGREE+1-(DEGREE+1)/2;
		right_half_leaf->parent=temp->parent;
		right_half_leaf->isLeaf=temp->isLeaf;
		right_half_leaf->keys.assign(temp->keys.begin()+(DEGREE+1)/2, temp->keys.end());

		temp->keys.erase(temp->keys.begin()+(DEGREE+1)/2,  temp->keys.end());

		temp->num=(DEGREE+1)/2;
		if(temp->parent==NULL)
		{
			TreeNode* CommonParent=new TreeNode;
			temp->parent=CommonParent;
			right_half_leaf->parent=CommonParent;
			CommonParent->parent=NULL;
			CommonParent->isLeaf=false;
			CommonParent->num=0;
			this->root=CommonParent;
			this->Insert_nonleaf(CommonParent,temp);
			this->Insert_nonleaf(CommonParent,right_half_leaf);
		}
		else
		{
			right_half_leaf->parent=temp->parent;
			this->Insert_nonleaf(temp->parent,right_half_leaf);
		}
	}
}

void BPlusTree::Print()
{
	if(this->root==NULL)
		return;
	TreeNode* temp=root;
	queue<TreeNode*> q;
	q.push(root);
	while(!q.empty())
	{
		int levelSize=q.size();
		while(levelSize--)
		{
			temp=q.front();
			q.pop();
			putchar('[');
			for(vector<ElementType>::iterator it=temp->keys.begin();it!=temp->keys.end();it++)
			{
				if(!(!temp->isLeaf&&it==temp->keys.begin()))
				{
					printf("%d",*it);
					if(it+1!=temp->keys.end())
						putchar(',');
				}
			}
			putchar(']');
			for(vector<TreeNode*>::iterator it=temp->childrens.begin();it!=temp->childrens.end();it++)
			{
				q.push(*it);
			}
		}	
		putchar('\n');	
	}
}