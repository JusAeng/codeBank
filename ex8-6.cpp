#include <stdio.h>
int main()
{
	int l,i,j,numb[6];
	printf("enter 6 number : ");
	for (l=1;l<=6;l++)
	{
		scanf("%d",&numb[l-1]);
	}
	printf("Element\t\tValue\t\tHistogram\n");
	for(i=1;i<=6;i++)
	{
		printf("%4d%15d  ",i-1,numb[i-1]);
		for(j=1;j<=numb[i-1];j++)
		{
			printf("*");
		}
		printf("\n");
	}
}
