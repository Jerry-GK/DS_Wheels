//This header implements a minHeap.
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;

class minHeap
{
#define H_MAX_SIZE 100000
private:
	int len;//length of the current heap
	int heapArr[H_MAX_SIZE];//store the element of the heap in an array

public:
	minHeap();//initilazation
	void Percolate_Up(int pos);//percolate up the element in heapArr[pos]
	void Percolate_Down(int pos);//percolate down the element in heapArr[pos]
	int Remove(int pos);
	void Insert(int val);
	void ShowHeap();
	int DeleteMin();
	int get_len();
};