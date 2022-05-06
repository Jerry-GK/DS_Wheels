#pragma once
#include<iostream>
using namespace std;

//heap sort without extra space
void HeapSort(int*a, int n);
void PercDown(int*H, int pos, int size);
void swap_Heap(int*x, int*y);