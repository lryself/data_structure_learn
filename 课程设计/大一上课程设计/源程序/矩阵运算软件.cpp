#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define X 100
#define Y 100

int jiafa(int a[X][Y],int b[X][Y],int d,int e);
int jianfa(int a[X][Y],int b[X][Y],int d,int e);
int chengfa(int a[X][Y],int b[X][Y],int d,int e);
int zhuanzhi(int a[X][Y],int d,int e);

void main()
{
	int i=0,j=0,x=0,y=0,n=0;
	int a[X][Y];
	int b[X][Y];

	printf("�������ʲô���㣿����������4��ѡ����ѡ���������������Ŀ�����ֱ�ţ�\n");
	printf("1.�ӷ�\n");
	printf("2.����\n");
	printf("3.�˷�\n");
	printf("4.ת��\n");
	scanf("%d",&n);

	printf("����������������(1-100)\n");
	scanf("%d",&x);
	printf("����������������(1-100)\n");	
	scanf("%d",&y);

	printf("�������һ������\n");
	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			printf("�������һ������ĵ�%d�е�%d�е����֣�\n",i+1,j+1);
			scanf("%d",&a[i][j]);
		}
	}

	if(n!=4)
	{
		printf("������ڶ�������\n");
		for(i=0;i<x;i++)
		{
			for(j=0;j<y;j++)
			{
				printf("������ڶ�������ĵ�%d�е�%d�е����֣�\n",i+1,j+1);
				scanf("%d",&b[i][j]);
			}
		}
	}


	switch(n)
	{
		case 1:jiafa(a,b,x,y);break;
		case 2:jianfa(a,b,x,y);break;
		case 3:chengfa(a,b,x,y);break;
		case 4:zhuanzhi(a,x,y);break;
	}

	scanf("%d",i);
}

int jiafa(int a[X][Y],int b[X][Y],int d,int e)
{
	int i,j;
	int c[X][Y];
	for(i=0;i<d;i++)
	{	
		for(j=0;j<e;j++)
		{
			c[i][j]=a[i][j]+b[i][j];
		}
	}

	printf("����ǣ�\n");
	for(i=0;i<d;i++)
	{
		for(j=0;j<e;j++)
		{
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int jianfa(int a[X][Y],int b[X][Y],int d,int e)
{
	int i,j;
	int c[X][Y];
	for(i=0;i<d;i++)
	{
		for(j=0;j<e;j++)
		{
			c[i][j]=a[i][j]-b[i][j];
		}
	}

	printf("����ǣ�\n");
	for(i=0;i<d;i++)
	{
		for(j=0;j<e;j++)
		{
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int chengfa(int a[X][Y],int b[X][Y],int d,int e)
{
	int i,j,s,m;
	int c[X][Y];
	for(i=0;i<d;i++)
	{
		for(j=0;j<e;j++)
		{
			s=0;
			for(m=0;m<d;m++)
			{
				s=a[i][m]*b[m][i]+s;
			}
			c[i][j]=s;
		}
	}

	printf("����ǣ�\n");
	for(i=0;i<d;i++)
	{
		for(j=0;j<e;j++)
		{
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int zhuanzhi(int a[X][Y],int d,int e)
{
	int i,j;
	int c[X][Y];
	for(i=0;i<d;i++)
	{
		for(j=0;j<e;j++)
		{
			c[i][j]=a[j][i];
		}
	}

	printf("����ǣ�\n");
	for(i=0;i<d;i++)
	{
		for(j=0;j<e;j++)
		{
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}
	return 0;
}
