#include "..\include\DisjointSet\DisjointSet.h"

int djSet::get_size()
{
    return this->size;
}
djSet::djSet(int size)
{
    this->size=size;
    if(size<0)
        cout<<"Unavailable Size!"<<endl;
    for(int i=0;i<size;i++)
        this->S[i]=-1;
}

int djSet:: find(int x)
{
    int root,trail,lead;
    for(root=x;S[root]>=0;root=S[root]);

    for(trail=x;trail!=root;trail=lead)
    {
        lead=S[trail];
        S[trail]=root;//Path compression
    }
    return root;
}

void djSet:: setUnion(int i, int j)//union by size
{
    if(find(i)==find(j))//if the two elements have been in the same set, do nothing
        return;
    if(S[find(j)]<S[find(i)])
    {
        S[find(j)]=find(i);
        S[find(i)]--;
    }
    else
    {
        S[find(i)]=find(j);
        S[find(j)]--;
    }
}

int djSet::comp_num()
 {
     int comp=0;
     for(int i=0;i<this->size;i++)
     {
         if(S[i]<0)
         {
             comp++;
         }
     }
     return comp;
 }