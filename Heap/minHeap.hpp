//This header implements a minHeap.
#pragma once
#include<cstdio>
#include<stdlib.h>
#include <iostream>
using namespace std;
#define H_MAX_SIZE 100000
class minHeap
{
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

int minHeap::get_len()
{
	return this->len;
}

minHeap::minHeap()
{
	this->len = 0;
}

void minHeap::Percolate_Up(int pos)
{
	if (pos >= len || pos < 0)
		cout << "Percolating up eroor!" << endl;
	while (pos!=0&&heapArr[(pos-1) / 2] > heapArr[pos])
	{
		int temp = heapArr[(pos-1) / 2];
		heapArr[(pos-1) / 2] = heapArr[pos];
		heapArr[pos] = temp;
		pos = (pos-1) / 2;
	}
}

void minHeap::Percolate_Down(int pos)
{
	int temp;
	while (2*pos+1<len)
	{
		if ((2 * pos + 2 >= len || heapArr[2 * pos + 1] <= heapArr[2 * pos + 2])&&heapArr[pos]>=heapArr[2*pos+1])
		{
			temp = heapArr[2 * pos + 1];
			heapArr[2 * pos + 1] = heapArr[pos];
			heapArr[pos] = temp;
			pos = 2 * pos + 1;
		}
		else if ((heapArr[2 * pos + 1] >= heapArr[2 * pos + 2])&&heapArr[pos]>=heapArr[2*pos+2])
		{
			temp = heapArr[2 * pos + 2];
			heapArr[2 * pos + 2] = heapArr[pos];
			heapArr[pos] = temp;
			pos = 2 * pos + 2;
		}
		else
			break;
	}
}

int minHeap::Remove(int pos)
{
	int temp = heapArr[pos];
	heapArr[pos] = heapArr[--len];
	if(pos<len)
		Percolate_Down(pos);
	return temp;
}

void minHeap::Insert(int val)
{
	len++;
	if (len > H_MAX_SIZE)
	{
		cout << "Space Overflow!" << endl;
		return;
	}
	heapArr[len - 1] = val;
	Percolate_Up(len - 1);
}

int minHeap::DeleteMin()
{
	int min_val = heapArr[0];
	heapArr[0] = heapArr[len-1];
	this->len--;
	Percolate_Down(0);
	return min_val;
}

void minHeap::ShowHeap()
{
	if (len == 0)
		cout << "An Empty Heap!" << endl;
	else
	{
		cout<<"Here is the heap:"<<endl;
		for (int i = 0; i < len; i++)
			cout << heapArr[i] << " ";
		cout << "\n";
	}
	return;
}

void heapSort(int n, int *a)
{
	minHeap mh;
	for(int i=0;i<n;i++)
		mh.Insert(a[i]);
	for(int i=0;i<n;i++)
	{
		mh.ShowHeap();
		a[i]=mh.DeleteMin();
	}
}