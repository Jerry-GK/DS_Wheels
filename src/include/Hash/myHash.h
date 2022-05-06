#pragma once
#include<iostream>
using namespace std;

class HashTable//hash function: H(val) = val % TableSize
{
#define MAXSIZE 1000
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