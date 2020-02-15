#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define M 100			/*�������������ڵ���*/
#define MAX 100			/*�����ַ�����������*/

typedef struct huffman
{
	char data;						/*������*/
	float weight;					/*Ȩ��*/
	int parent;						/*���ڵ�*/
	int rchild;						/*������*/
	int lchild;						/*������*/
}huffman;							/*���������*/
typedef huffman HufTree[M + 1];									/*��������*/
typedef char **HufCode;											/*��������*/

int menu();														/*�˵�*/
void createHufTree(HufTree t, int n);							/*������������*/
void select(HufTree t, int *s1, int *s2, int n);				/*�����еĹ����������ѡ��������С���*/
void huf_code(HufCode * hcd, HufTree t, int n);					/*������������*/
void encipher(int num);											/*���й�������ı���*/
void decipher(HufTree t, int n);								/*���й������������*/

FILE *IN;														/*�ļ�ָ��*/
FILE *OUT;
char huf[M / 2][2][MAX];										/*�������еĹ�������*/
void main()
{
	HufTree hf;
	HufCode hcd = NULL;
	int n=0, i;
	char ch;
	while (1)
	{
		n = 0;
		printf("�Ѵ���Ĺ���������Ϊ��\n");
		IN = fopen("����������.csv", "r");
		fseek(IN, 17L, 0);
		for (i = 0; i < M / 2; i++)
		{
			if ((huf[i][0][0] = fgetc(IN)) == EOF)
				break;
			else
				huf[i][0][1] = '\0';
			fseek(IN, 1L, 1);
			if(fscanf(IN,"%s", huf[i][1])==EOF)
				break;
			printf("%s:%s\n", huf[i][0], huf[i][1]);
			n++;
			if(fgetc(IN)==EOF)
				break;
		}
		fclose(IN);
		//sortchar(huf, n);	/*�����н�㰴�����ڹ��������������ǳ������������Լ��ټ�������*/
							//����Ѵ���Ĺ�������
		switch (menu())
		{
		case 0:		/*�˳�����*/
			exit(1);
		case 1:		/*������������*/
			printf("��������Ҫ������ַ��������ܶ���%d��:\n", M / 2);
			scanf("%d", &n);
			getchar();
			printf("���ڡ������������.csv�� ��������Ҫ������ַ��Ͷ�ӦȨ��,ע��ʹ��Ӣ���ַ�\n");
			printf("��������뱣�棬���س�����\n");
			getchar();
			IN = fopen("�����������.csv", "r");			/*����������ݴ��ļ����������*/
			fseek(IN, 11L, 0);
			createHufTree(hf, n);							/*������������*/
			printf("�����ɹ�\n\n");
			fclose(IN);										/*�ر��ļ�������*/
			huf_code(&hcd, hf, n);							/*������������*/
			IN = fopen("����������.csv", "w");				/*����������д���ļ��д���*/
			fprintf(IN, "�ַ�,����������\n");
			for (i = 1; i <= n; i++)
			{
				fprintf(IN, "%c,%s\n", hf[i].data, hcd[i]);
			}
			fclose(IN);										/*�ر��ļ�������*/
			printf("�����ɹ��Ĺ����������Ѿ������������������.csv����\n");
			break;
		case 2:
			OUT = fopen("�������.txt", "w");
			encipher(n);
			fclose(IN);
			fclose(OUT);
			break;
		case 3:
			OUT = fopen("�������.txt", "w");
			decipher(hf,n);
			fclose(IN);
			fclose(OUT);
			break;
		}
		printf("\n���س�������");
		getchar();
		system("cls");
	}
}

int menu()
{
	int n;
	printf("\n��Ҫ���еĲ�����:\n");
	printf("0.�˳�\n");
	printf("1.�����µĹ�������\n");
	printf("2.�������������\n");
	printf("3.�������������\n");
	scanf("%d", &n);
	getchar();
	return n;
}

void createHufTree(HufTree t, int n)
{
	int s1, s2, i, j;
	for (i = 1; i < 2 * n; i++)
	{
		if (i >= 1 && i <= n)
		{
			t[i].data=fgetc(IN);
			fgetc(IN);
			fscanf(IN, "%f\n", &t[i].weight);
		}
		else
			t[i].weight = 0;
		t[i].parent = 0;
		t[i].lchild = 0;
		t[i].rchild = 0;
	}													/*��ʼ��*/

	for (i = n + 1; i < 2 * n; i++)
	{
		select(t, &s1, &s2, i);							/*ѡ��Ȩ����С������Ϊs1,s2*/
		t[i].weight = t[s1].weight + t[s2].weight;		/*��Ȩ�ؼӺͲ��������ڵ��Ȩ��*/
		t[i].lchild = s1;								/*�����ڵ�����Ӹ���s1*/
		t[i].rchild = s2;								/*�����ڵ���Һ��Ӹ���s2*/
		t[s1].parent = i;								/*��s1�ĸ��ڵ㸳ֵ*/
		t[s2].parent = i;								/*��s2�ĸ��ڵ㸳ֵ*/
	}
}

void select(HufTree t, int *s1, int *s2, int n)
{
	int i, j;
	float min;
	for (i = 1, min = pow(2, 30); i < n; i++)							/*��ʼ��minΪint�����ֵ*/
	{
		if (t[i].weight < min&&t[i].parent == 0)						/*�ҵ�Ȩ����С��û�и��ĵ�һ��Ҷ�ӽڵ㣨���ڵ�Ϊ0��*/
		{
			min = t[i].weight;
			(*s1) = i;
		}
	}
	for (i = 1, min = pow(2, 30); i < n; i++)							/*�ҵ�Ȩ����С��û�и��ĵڶ���Ҷ�ӽڵ㣨���ڵ�Ϊ0��*/
	{
		if (t[i].weight < min&&t[i].parent == 0 && i != (*s1))
		{
			min = t[i].weight;
			(*s2) = i;
		}
	}
}

void huf_code(HufCode *hcd, HufTree t, int n)
{
	char *cd;
	int i, start, c, f;
	(*hcd) = (HufCode)malloc((n + 1) * sizeof(char*));							/*�����ַ���hcd�����鴢��ռ�*/
	cd = (char*)malloc(n * sizeof(char));										/*�����ַ������鴢��ռ�*/
	for (i = 1; i <= n; i++)
	{
		cd[n - 1] = '\0';														/*���һλΪ\0ʹ�ַ���������*/
		start = n - 1;															/*��������*/
		c = i;																	/*�ӵ�һ���ַ���ʼ��������*/
		f = t[c].parent;														/*�ҵ����ַ��ĸ��ڵ�*/
		while (f)
		{
			if (t[f].lchild == c)
				cd[--start] = '0';												/*����Ϊ0*/
			else
				cd[--start] = '1';												/*�Һ���Ϊ1*/
			c = f;
			f = t[f].parent;
		}
		(*hcd)[i] = (char*)malloc((n - start) * sizeof(char));					/*Ϊhcd�ĳ�Ա����ռ�*/
		strcpy((*hcd)[i], &cd[start]);											/*����ɵı������hcd��*/
	}
}

void encipher(int num)
{
	char ch;
	char temp[2];
	int j , r=0;
	printf("�뽫��Ҫ���б�����ַ��������뵽��������.txt���У�ע�⣺ֻ�ܱ����Ѵ���ϵͳ�еĹ���������\n");
	printf("��������뱣�棬���س�������\n");
	getchar();
	IN = fopen("������.txt", "r");
	printf("����������Ϊ:\n");
	while((ch=fgetc(IN))!=EOF)									/*���ļ��ж�ȡһ���ַ�����ch��*/
	{
		temp[0] = ch;										/*��ch�е�ֵ����temp��ĩβ*/
		temp[1] = '\0';										/*��temp���һλ��ֵΪ\0ʹ�ַ���������*/
		for (j = 0; j<num; j++)
		{
			if (strcmp(huf[j][0], temp) == 0)					/*��huf�д�����ַ���temp���ַ���ͬ���������Ӧ�Ĺ�������*/
			{
				printf("%s", huf[j][1]);						/*�������ʾ����Ļ��*/
				fprintf(OUT, "%s", huf[j][1]);					/*������������ļ���*/
				break;
			}
		}
	}
	printf("\n������ɵ�����ͬʱ�����ڡ��������.txt����\n");
}

void decipher(HufTree t, int n)
{
	int p;
	char ch;
	printf("�뽫��Ҫ����������ַ��������뵽��������.txt���У�ע�⣺ֻ�������Ѵ���ϵͳ�еĹ���������\n");
	printf("��������뱣�棬���س�������\n");
	getchar();
	IN = fopen("������.txt", "r");
	printf("����������Ϊ:\n");
	p = 2*n-1;								/*�Ӹ�������ʼ����*/
	if ((ch = fgetc(IN)) == EOF)			/*���ļ��ж���һλ*/
		return;
	while (1)
	{
		if (ch == '0')						/*��Ϊ0��ת��������*/
		{
			if (t[p].lchild)	
				p = t[p].lchild;			/*��p��������������ָ��p��������*/
			else
			{
				printf("%c", t[p].data);	/*���*/
				fprintf(OUT, "%c", t[p].data);
				p = 2*n - 1;				/*��p����ָ������*/
				continue;
			}
		}
		else
		{
			if (ch == '1')					/*��Ϊ1��ת��������*/
			{
				if (t[p].rchild)
					p = t[p].rchild;		/*��p��������������ָ��p��������*/
				else
				{
					printf("%c", t[p].data);/*���*/
					fprintf(OUT, "%c", t[p].data);
					p = 2*n - 1;			/*��p����ָ������*/
					continue;
				}
			}
			else
			{
				printf("������������������\n");/*�ݴ���*/
				break;
			}
		}
		if ((ch = fgetc(IN)) == EOF)				/*������һλ*/
		{
			printf("%c", t[p].data);				/*������һλ���*/
			fprintf(OUT, "%c", t[p].data);
			printf("\n������ɵ�����ͬʱ�����ڡ��������.txt����\n");
			break;
		}
	}
}