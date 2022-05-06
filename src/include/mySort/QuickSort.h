#pragma once
#define SORT_EDGE 7 //do insertion sort if length of array is less or equal than this value
#include "SimpleSort.h"

void swap_Quick(int*x,int*y);
void MyQsort(int *a, int left, int right);//qsort a[left:right]
int getMid(int *a,int left,int right);//return the mid value of a[left],a[right] and a[(left+right)/2], and swap it with a[right-1]