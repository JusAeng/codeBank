#include <stdio.h>
#include <conio.h>
#define SIZE 4
int main()
{
	int a[SIZE]={2,1,6,37};
	int i,pass,hold;
	printf("Data items in original order\n");
	for(i=0;i<=SIZE-1;i++)
	{
		printf("%4d",a[i]);
	}
	for(pass=0;pass<=SIZE-2;pass++)
	{
		for(i=0;i<=SIZE-pass-2;i++)
		{
			if (a[i]>a[i+1])
				{
					hold=a[i];
					a[i]=a[i+1];
					a[i+1]=hold;
				}
		}
	}
	printf("\nData items in ascending order\n");
	for(i=0;i<=SIZE-1;i++)
	{
		printf("%4d",a[i]);
	}
	printf("\n");
	return 0;
}
