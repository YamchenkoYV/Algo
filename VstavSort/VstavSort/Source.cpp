#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void Sort(int* mas, int size)
{
	if (size > 1)
	{
		for(int i = 1; i < size; i++)
		{
			int vstavka = mas[i];
			int j = 0;

			//Обычный вариант 

			for( j = i - 1; j >= 0 && mas[j] >= vstavka; j--)
				mas[j+1] = mas[j];

			mas[j+1] = vstavka; 



			//Бинарный поиск
// 			int first = 0;
// 			int last = size - 1;
// 
// 			while(first != last)
// 			{
// 				int mid = (first + last)/2;
// 				if(mas[mid] > vstavka)
// 					last = mid;
// 				else if(mas[mid] < vstavka)
// 					first = mid + 1;
// 				else 
// 				{
// 					last = mid;
// 					break;
// 				}
// 			}
// 
// 			if(mas[last] <= vstavka){
// 				memmove(mas + last + 2,mas + last + 1,size - last - 2);
// 				mas[last+1] = vstavka;
// 			}else
// 			{
// 				memmove(mas + last + 1,mas + last,size - last - 1);
// 				mas[last] = vstavka;
// 			}

		}
	}
}

int main()
{
	char c;
	int bufsize = 30;
    char* buf = new char[bufsize]; 
	int* mas = new int[10000];
	c = getchar();

	int mas_count = 0;
	int buf_count = 0;
	while( c != '\n' || c != '\0' )
	{
		while(c <= '9' && c >= '0')
		{
			buf[buf_count++] = c;
			c = getchar();
		}
		if(buf_count != 0)
			mas[mas_count++] = atoi(buf);
		buf_count = 0;
		for(int i =0 ; i < bufsize;i++)
			buf[i] = 0;
		if(c == '\n')
			break;

		c = getchar();

	}
	
// 	for(int i=0; i < mas_count; i++)
// 		cout << mas[i]<<" ";
// 	cout << endl;

	Sort(mas,mas_count);

	for(int i=0; i < mas_count; i++)
		cout << mas[i]<<" ";
	cout << endl;

	while (true)
		;
 return 0;
}