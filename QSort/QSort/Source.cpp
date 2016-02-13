#include <iostream>
#include <cstdio>

using namespace std;

template<class T>
void VstavSort(T* mas, int size)
{
	if (size > 1)
	{
		for(int i = 1; i < size; i++)
		{
			T vstavka = mas[i];
			int j = 0;

			//Обычный вариант 

			for( j = i - 1; j >= 0 && mas[j] >= vstavka; j--)
				mas[j+1] = mas[j];

			mas[j+1] = vstavka; 

		}
	}
}

template<class T>
void PrintHeap(T* mas, int size)
{
	for(int i=0; i < size; i+=1){
//		cout.setf(ios::fixed);
		cout << mas[i] << " ";
	}
	cout << endl;
}

template<class T>
int Partition(T* a, int n)
{
	if( n <= 1){
		return 0;
	}
	const T& pivot = a[n - 1];
	int i = 0, j = n - 2;
	while( i < j){
		//Не проверяем что i < n - 1, т.к. a[n - 1] == pivot
		for( ; a[i] < pivot ; ++i){}
		for( ; j >= 0 && !( a[j] < pivot ); --j){}
		if(i < j){
			swap( a[i++], a[j--]);
//			cout << "Swaping: " << a[i-1] <<" " << a[j+1] << endl;
		}
	}
	swap( a[i], a[n - 1]);
	return i;
}

template<class T>
void QuickSort(T* a, int n)
{
	int part = Partition(a, n);
	if(n > 40){        //Остальную часть отсортируем вставками, должно быть быстрее
//		cout << "Part: ";
//		PrintHeap(a, n);
		if( part > 0) QuickSort(a, part);
		if( part + 1 < n) QuickSort(a + part + 1, n - (part + 1));
	}else
		VstavSort(a, n);
}




int main(){
	char c;
	int bufsize = 30;
	char* buf = new char[bufsize]; 
	double* mas = new double[1000000];

	int mas_count = 0;
	int temp ;
//	scanf("%d", &temp);
//	cout << temp;


	while((scanf("%d", &temp)) && mas_count <= 1000000)
		mas[mas_count++] = temp;

//	c = getchar();
//
//	int mas_count = 0;
//	int buf_count = 0;
// 	while( (c ==' ' || c=='-' || c=='.' || (c <= '9' && c >= '0')) && mas_count <= 1000000  )
// 	{
// 		while((c <= '9' && c >= '0') || c == '-' || c == '.')
// 		{
// 			buf[buf_count++] = c;
// 			c = getchar();
// 		}
// 		if(buf_count != 0){
// 			double temp = atof(buf);
// 			if(temp <= 1000000000 && temp > 0)
// 				mas[mas_count++] = temp;
// 		}
// 		buf_count = 0;
// 		for(int i =0 ; i < bufsize;i++)
// 			buf[i] = 0;
// 		if(c !=' ' && c!='-' && c!='.' )
// 			break;
// 
// 		c = getchar();

//		cin >> mas[mas_count++];
//	}

	QuickSort(mas, mas_count);

	PrintHeap(mas, mas_count);

 	while(true);
	return 0;
}