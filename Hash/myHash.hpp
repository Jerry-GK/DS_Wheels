#pragma once
#include<iostream>
#define MAXSIZE 1000
using namespace std;
class HashTable//hash function: H(val) = val % TableSize
{
private:
    int table[MAXSIZE];
    int TableSize;
    string probe;
    int HashFunc(int key);

public:
    HashTable(int TableSize, string probe);
    int Insert(int key);
    int Find(int key);
    void Show();
    int get_size();
};

int HashTable::get_size()
{
    return this->TableSize;
}
HashTable::HashTable(int TableSize, string probe)
{
    if(TableSize<=MAXSIZE)
        this->TableSize=TableSize;
    else
        cout<<"Error: Hash table is too big!"<<endl;
    if(probe=="L"||probe=="Q")
        this->probe=probe;
    else
        cout<<"Error: No such probing stategy!"<<endl;       
    for(int i=0;i<this->TableSize;i++)
        this->table[i]=-1;
}

int HashTable::HashFunc(int key)
{
    return key % this->TableSize;
}

int HashTable::Insert(int key)
{
    int maxloop=this->TableSize;
    int i=0;
    int pos=HashFunc(key);
    while(i<maxloop)
    {
        if(table[pos]!=-1)
        {
            if(probe=="L")
                pos++;
            else if(probe=="Q")
                pos+=2*i+1;
            if(pos>=this->TableSize)
                pos-=this->TableSize;
        }
        else
        {
            table[pos]=key;
            return 1;
        }
        i++;
    }
    cout<<"Error: Unsolved collison!"<<endl;
    return 0;
}

int HashTable::Find(int key)
{
    int maxloop=this->TableSize;
    int i=0;
    int pos=HashFunc(key);
    while(i<maxloop)
    {
        if(table[pos]!=key)
        {
            if(probe=="L")
                pos++;
            else if(probe=="Q")
                pos+=2*i+1;
            if(pos>=this->TableSize)
                pos-=this->TableSize;
        }
        else
        {
            return pos;
        }
        i++;
    }
    return -1;
}

void HashTable::Show()
{
    for(int i=0;i<this->TableSize;i++)
    {
        cout<<"table["<<i<<"] = "<<this->table[i]<<endl;
    }
    return;
}   