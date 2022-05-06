//This header implements a disjoint set, maintaining an array
//This data structre is skillful at classification problems
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;

class djSet
{
#define MAX_SIZE 1000
private:
    int S[MAX_SIZE];
    int size;
public:
    djSet(int size);//initialize the array with zero
    int find(int x);
    void setUnion(int i, int j); 
    int comp_num();//get the number of components
    int get_size();
};