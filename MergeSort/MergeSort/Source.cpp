// На числовой прямой окрасили N отрезков. 
// 	Известны координаты левого и правого концов каждого отрезка (Li и Ri). 
// 	Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
// 	Для сортировки реализуйте сортировку слиянием.

#include <iostream>
#include <cstdio>
#include <cstring> //For memcpy() function

using namespace std;

int *mas;


int Lastmerge(const int* a, const int* b, int Len){
	int i = 0, j = 0, layer = 0;
	int summ = 0;
	int *c = new int[2*Len];

	while( i < Len && j < Len )
	{
		
		if( a[i] <= b[j] ){
			if(layer == 1)
				summ+=(a[i] - c[i+j-1]);
			c[i + j] = a[i];
			layer++;
			++i;
		}else {
			if(layer == 1)
				summ+=(b[j] - c[i+j-1]);
			c[i + j] = b[j];
			layer--;
			++j;
		}
	}
	int c1;
		for(; j < Len; ++j){
			c1 = c[i+j-1];
			if(layer == 1)
				summ+=(b[j] - c[i+j-1]);
			c[i + j] = b[j];
			layer--;
		}
	
// 		for(int i=0;i < 2*Len;i++)
// 				cout << c[i] << endl; 
// 		cout << endl;
	delete[] c;
	return summ;
}

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
	int N;
	
	cin >> N;

    mas = new int[N];
	int *sub_mas = new int[N];
	int *index = new int[N];

	for(int i=0; i < N; i++)
		cin >> mas[i] >> sub_mas[i];

	for(int i=0; i < N;i++)
		index[i] = i;

	MergeSort(mas,N);
	MergeSort(sub_mas,N);

// 	cout << endl;
// 	for(int i=0;i<N;i++)
// 		cout << mas[index[i]]<< " " << sub_mas[index[i]] << endl; 
// 	cout << endl;

// 	for(int i=0;i<N;i++)
// 		cout << index[i] << endl; 
// 	cout << endl;

	int result = Lastmerge(mas, sub_mas, N);

//	cout << "Result: ";
	cout << result << endl;
	while(true);
	return 0;
}