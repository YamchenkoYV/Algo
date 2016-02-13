// Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся незамкнутую ломаную, 
// проходящую через все эти точки. 
// 	Стройте ломаную в порядке возрастания x-координаты. 
// Если имеются две точки с одинаковой x-координатой, то расположите раньше ту точку, у которой y-координата меньше.
// 	Для сортировки точек реализуйте пирамидальную сортировку.


#include <iostream>
//#include "C:\Users\Юрий\Documents\Visual Studio 2012\Projects\Stepic\Mylib\Heap.h"
#include <assert.h>
#include <stdlib.h>
#include <cstdio>
using namespace std;

class MaxHeap{
public:
	void SiftUp(int);
	void SiftDown(int);
	void BuildHeap();
	double* ExtractMax();
	void PrintHeap();
	void MaxSort();
	void Add(double);
	void Add(double , double );
	bool IsElementsLowerOrEqual(double n);
	MaxHeap(int begSize = 20);
	double *mas;
	double *sub_mas;
	int length;
	int count;
};

MaxHeap::MaxHeap(int begSize){
	mas = new double[begSize];
	sub_mas = new double[begSize];
	length = begSize;
	count = 0;
}

void MaxHeap::PrintHeap()
{
	for(int i=0; i< count;i++)
		cout<<mas[i]<<" ";
	cout << endl;
}

bool MaxHeap::IsElementsLowerOrEqual(double n){
	for(int i=0; i< count;i++)
		if(mas[i] > n)
			return false;
	return true;
}

double* MaxHeap::ExtractMax(){
	assert(count != 0);
	//Запоминаем значение максимума
	double* result = new double[2];
	result[0] = mas[0];
	result[1] = sub_mas[0];
	mas[0] = mas[count-1];
	sub_mas[0] = sub_mas[count -1];
	count-- ;
	if(count != 0)
		SiftDown(0);
	return result;
}

void MaxHeap::BuildHeap()
{
	for(int i = count/2 - 1; i >= 0; i--)
	{
		SiftDown(i);
	}
}

void MaxHeap::Add(double n)
{
	if(count == length){
		int newLength = length * 2;
		double *newBuf = new double[newLength];
		if( newBuf != NULL ){
			for(int i=0; i< length;i++)
			{
				newBuf[i] = mas[i];
			}
			newBuf[length]=n;
			length = newLength;
			delete[] mas;
			mas = newBuf;
		}else
		{
			clog<<"Ошибка выделения памяти"<<endl;
			exit(0);
		}
	}
	else
	{
		mas[count]=n;
	}
	count++;
	BuildHeap();
}

void MaxHeap::Add(double n, double m)
{
	if(count == length){
		int newLength = length * 2;
		double *newBuf = new double[newLength];
		double *sub_newBuf = new double[newLength];
		if( newBuf != NULL && sub_newBuf != NULL){
			for(int i=0; i< length;i++)
			{
				newBuf[i] = mas[i];
				sub_newBuf[i] = sub_mas[i];
			}
			newBuf[length]= n;
			sub_newBuf[length] = m;
			length = newLength;

			//Исключение на наборе(-0.1 0.1 \ -0.1 0.2 \ -0.1 -0.1)
			delete[] sub_mas;
			delete[] mas;

			mas = newBuf;
			sub_mas = sub_newBuf;
		}else
		{
			clog<<"Ошибка выделения памяти"<<endl;
			exit(0);
		}
	}
	else
	{
		mas[count] = n;
		sub_mas[count] = m;
	}
	count++;
	BuildHeap();
}


void MaxHeap::SiftDown(int i){
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	int largest = i;
	if(left < count && mas[left] > mas[i])
		largest = left;
	if(left < count && mas[right] > mas[largest])
		largest = right;

	if(largest != i){
		std::swap(mas[i],mas[largest]);
		std::swap(sub_mas[i],sub_mas[largest]);
		SiftDown(largest);
	}
}

void MaxHeap::SiftUp(int i){
	while(i > 0){
		int parent = (i - 1)/2;
		if(mas[i] <= mas[parent])
			return;
		std::swap(mas[i],mas[parent]);
		std::swap(sub_mas[i],sub_mas[parent]);
		i = parent;
	}
}

//Выводит отсортированный массив. Куча разрушается
void MaxHeap::MaxSort(){
	double* extr = new double[1];
	int heapSize = count;
	for(int i = count - 1; i >= 0; i-- )
	{
		extr = this->ExtractMax();
		mas[i] = extr[0];
		sub_mas[i] = extr[1];
		int j = i;
		while(mas[j] == mas[j+1] && j < (heapSize - 1) )
		{
			if(sub_mas[j] > sub_mas[j+1])
				std::swap(sub_mas[j], sub_mas[j + 1]);
			j++;
		}
	}

	//Print

	for(int i = 0; i < heapSize; i++)
		cout << mas[i] << " " << sub_mas[i] << endl;
}


int main()
{
	int N;
	double tn,tm;
	cin >> N;
	MaxHeap heap(2);
	int temp;

	for(int i=0; i < N; i++)
	{
		cin >> tn >> tm;
//		cout << "Input: " << tn << tm<< endl;
		heap.Add(tn,tm);
	}

	heap.MaxSort();
	while(true)
		;
	return 0;
}