#pragma once
#include<iostream>
using namespace std;
void MergeSort(int* a,int n);
void MSort(int* a, int* TempArr,int left, int right);
void Merge(int*a, int*TempArr, int Lpos, int Rpos, int RightEnd);