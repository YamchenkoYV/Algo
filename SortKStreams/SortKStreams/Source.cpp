//Дана последовательность целых чисел a[0..n-1] и натуральное число k, такое что для любых i, j: если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность. Последовательность может быть очень длинной. Время работы O(n * log(k)). Доп. память O(k).
//
//	Использовать слияние.
//!Можно сортировать и неупорядоченные массивы по частям

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring> //For memcpy() function
#include <assert.h>

using namespace std;

							////////////////////////////////Heap//////////////////////////////////
template<class T>
class MIndex{
public:
	int i;
	int j;

	MIndex(int mi = 0, int mj = 0) : i(mi), j(mj) {};
	T GetElem(T*, int, int);
};

template<class T> T MIndex<T>::GetElem(T* mas, int N, int k){
	if((i*k + j) >= N){
		cout << "Выход за границу массива"<<endl;
		exit(1);
	}
	return mas[i*k + j];

} 


template<class Q>
class MinHeap{
public:
	void SiftUp(int);
	void SiftDown(int);
	void BuildHeap();
	MIndex<Q> ExtractMin();
	void PrintHeap();
	void MinSort();
	void Add(MIndex<Q>);
	bool IsElementsLowerOrEqual(Q n);
	MinHeap(int, Q*, int, int);
	Q* bigMas; 
	int bMasSize;
	MIndex<Q> *mas; // Массив кучи
	int k; //Величина подмассива
	int length;
	int count;
};

template <class Q> 
MinHeap<Q>::MinHeap(int begSize = 20 , Q* bmas = NULL, int bMasSize = 0, int k = 0){
	mas = new MIndex<Q>[begSize];
	length = begSize;
	bigMas = bmas;
	this->k = k;
	this->bMasSize = bMasSize;
	int temp = bMasSize/k;
	assert((bMasSize % k) == 0);
	count = 0;
	for(int i =0; i < temp; i++)
		this->Add( MIndex<Q>(i,0));
//	PrintHeap();
}

template<class Q> void MinHeap<Q>::PrintHeap()
{
	cout << "Heap: ";
	for(int i=0; i< count;i++)
		cout<<mas[i].GetElem(bigMas, bMasSize,k)<<" ";
	cout << endl;
}

template<class Q> bool MinHeap<Q>::IsElementsLowerOrEqual(Q n){
	for(int i=0; i< count;i++)
		if(mas[i].GetElem(bigMas, bMasSize,k) > n)
			return false;
	return true;
}

template<class Q> MIndex<Q> MinHeap<Q>::ExtractMin(){
	assert(count != 0);
	//Запоминаем значение максимума
	MIndex<Q> result;
	result = mas[0];
	mas[0] = mas[count-1];
	if(result.j != (k-1)){
		mas[count-1] = MIndex<Q>(result.i, result.j + 1);
//		SiftUp(count-1);
	}
	else
		count-- ;
	if(count != 0)
		BuildHeap();
//		SiftDown(0);
	PrintHeap();
	return result;
}

template<class Q>void MinHeap<Q>::BuildHeap()
{
	for(int i = count/2 - 1; i >= 0; i--)
	{
		SiftDown(i);
	}
}

template<class Q> void MinHeap<Q>::Add(MIndex<Q> n)
{
	if(count == length){
		int newLength = length * 2;
		MIndex<Q> *newBuf = new MIndex<Q>[newLength];
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
		mas[count]=n;
	count++;
	BuildHeap();
//	PrintHeap();
}

template<class Q> void MinHeap<Q>::SiftDown(int i){
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	int smallest = i;
	if(left < count && mas[left].GetElem(bigMas, bMasSize,k) < mas[i].GetElem(bigMas, bMasSize,k))
		smallest = left;
	if(right < count && mas[right].GetElem(bigMas, bMasSize,k) < mas[smallest].GetElem(bigMas, bMasSize,k))
		smallest = right;

	if(smallest != i){
		std::swap(mas[i],mas[smallest]);
		SiftDown(smallest);
	}
}

template<class Q> void MinHeap<Q>::SiftUp(int i){
	while(i > 0){
		int parent = (i - 1)/2;
		if(mas[i].GetElem(bigMas, bMasSize, k) >= mas[parent].GetElem(bigMas, bMasSize,k))
			return;
		std::swap(mas[i],mas[parent]);
		i = parent;
	}
}

//Выводит отсортированный массив. Куча разрушается
template<class Q>void MinHeap<Q>::MinSort(){
	int size = this->bMasSize;
	for(int i = size - 1; i >= 0; i-- )
		cout << this->ExtractMin().GetElem(bigMas,this->bMasSize,k) << " ";
	cout << endl;
}
							////////////////////////////////Heap//////////////////////////////////

void Merge(const int* a, int aLen, const int* b, int bLen, int* c){
	int i = 0, j = 0;
	while( i < aLen && j < bLen )
	{
		if( a[i] <= b[j] ){
			c[i + j] = a[i];
			++i;
		}else {
			c[i + j] = b[j];
			++j;
		}
	}

	//Обработка остатка
	if( i == aLen){
		for(; j < bLen; ++j)
			c[i + j] = b[j];
	}else {
		for( ; i < aLen; ++i)
			c[i + j] = a[i];
	}

}

void MergeSort(int* a, int aLen)
{
	if(aLen <= 1)
		return;
	int firstLen = aLen/2;
	int secondLen = aLen - firstLen;
	MergeSort(a, firstLen);
	MergeSort(a + firstLen, secondLen);
	int* c = new int[aLen];
	Merge(a, firstLen, a + firstLen, secondLen, c);
	memcpy(a, c, sizeof(int) * aLen);
	delete[] c;
}

int main()
{
	int N, k;
	
	cin >> N;
	int* mas = new int[N];

	for(int i=0; i < N; i++)
		cin >> mas[i];

	cin >> k;
	for(int i=0; i < N; i+=k)
		MergeSort(&mas[i],k);
	try{
	MinHeap<int> heap(20, mas, N, k);
	heap.MinSort();
	}
	catch(...){
		cout << "Ошибка создания объекта HEAP!"<<endl;
	}
	
	while(true);
	return 0;
}