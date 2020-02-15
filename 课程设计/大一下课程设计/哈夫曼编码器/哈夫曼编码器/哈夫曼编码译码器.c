#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define M 100			/*哈夫曼树的最大节点数*/
#define MAX 100			/*输入字符数的最大个数*/

typedef struct huffman
{
	char data;						/*数据域*/
	float weight;					/*权重*/
	int parent;						/*父节点*/
	int rchild;						/*左子树*/
	int lchild;						/*右子树*/
}huffman;							/*哈夫曼结点*/
typedef huffman HufTree[M + 1];									/*哈夫曼树*/
typedef char **HufCode;											/*哈夫曼码*/

int menu();														/*菜单*/
void createHufTree(HufTree t, int n);							/*创建哈夫曼树*/
void select(HufTree t, int *s1, int *s2, int n);				/*从已有的哈夫曼结点中选择两个最小结点*/
void huf_code(HufCode * hcd, HufTree t, int n);					/*创建哈夫曼码*/
void encipher(int num);											/*进行哈夫曼码的编码*/
void decipher(HufTree t, int n);								/*进行哈夫曼码的译码*/

FILE *IN;														/*文件指针*/
FILE *OUT;
char huf[M / 2][2][MAX];										/*储存已有的哈夫曼码*/
void main()
{
	HufTree hf;
	HufCode hcd = NULL;
	int n=0, i;
	char ch;
	while (1)
	{
		n = 0;
		printf("已储存的哈夫曼编码为：\n");
		IN = fopen("哈夫曼编码.csv", "r");
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
		//sortchar(huf, n);	/*对所有结点按照所在哈夫曼树的深度由浅到深进行排序，以减少检索次数*/
							//输出已储存的哈夫曼码
		switch (menu())
		{
		case 0:		/*退出程序*/
			exit(1);
		case 1:		/*创建哈夫曼树*/
			printf("请输入您要输入的字符数（不能多于%d）:\n", M / 2);
			scanf("%d", &n);
			getchar();
			printf("请在“输入哈夫曼码.csv” 中输入您要输入的字符和对应权重,注意使用英文字符\n");
			printf("输入结束请保存，按回车继续\n");
			getchar();
			IN = fopen("输入哈夫曼码.csv", "r");			/*将输入的数据从文件导入程序中*/
			fseek(IN, 11L, 0);
			createHufTree(hf, n);							/*创建哈夫曼码*/
			printf("创建成功\n\n");
			fclose(IN);										/*关闭文件并储存*/
			huf_code(&hcd, hf, n);							/*创建哈夫曼码*/
			IN = fopen("哈夫曼编码.csv", "w");				/*将哈夫曼码写入文件中储存*/
			fprintf(IN, "字符,哈夫曼编码\n");
			for (i = 1; i <= n; i++)
			{
				fprintf(IN, "%c,%s\n", hf[i].data, hcd[i]);
			}
			fclose(IN);										/*关闭文件并储存*/
			printf("创建成功的哈夫曼编码已经输出到“哈夫曼编码.csv”中\n");
			break;
		case 2:
			OUT = fopen("编码完成.txt", "w");
			encipher(n);
			fclose(IN);
			fclose(OUT);
			break;
		case 3:
			OUT = fopen("译码完成.txt", "w");
			decipher(hf,n);
			fclose(IN);
			fclose(OUT);
			break;
		}
		printf("\n按回车键继续");
		getchar();
		system("cls");
	}
}

int menu()
{
	int n;
	printf("\n您要进行的操作是:\n");
	printf("0.退出\n");
	printf("1.创建新的哈夫曼树\n");
	printf("2.编码哈夫曼编码\n");
	printf("3.译码哈夫曼编码\n");
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
	}													/*初始化*/

	for (i = n + 1; i < 2 * n; i++)
	{
		select(t, &s1, &s2, i);							/*选择权重最小的两个为s1,s2*/
		t[i].weight = t[s1].weight + t[s2].weight;		/*将权重加和并赋给父节点的权重*/
		t[i].lchild = s1;								/*将父节点的左孩子赋给s1*/
		t[i].rchild = s2;								/*将父节点的右孩子赋给s2*/
		t[s1].parent = i;								/*将s1的父节点赋值*/
		t[s2].parent = i;								/*将s2的父节点赋值*/
	}
}

void select(HufTree t, int *s1, int *s2, int n)
{
	int i, j;
	float min;
	for (i = 1, min = pow(2, 30); i < n; i++)							/*初始化min为int的最大值*/
	{
		if (t[i].weight < min&&t[i].parent == 0)						/*找到权重最小且没有根的第一个叶子节点（父节点为0）*/
		{
			min = t[i].weight;
			(*s1) = i;
		}
	}
	for (i = 1, min = pow(2, 30); i < n; i++)							/*找到权重最小且没有根的第二个叶子节点（父节点为0）*/
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
	(*hcd) = (HufCode)malloc((n + 1) * sizeof(char*));							/*申请字符串hcd的数组储存空间*/
	cd = (char*)malloc(n * sizeof(char));										/*申请字符的数组储存空间*/
	for (i = 1; i <= n; i++)
	{
		cd[n - 1] = '\0';														/*最后一位为\0使字符串有意义*/
		start = n - 1;															/*倒序输入*/
		c = i;																	/*从第一个字符开始检索检索*/
		f = t[c].parent;														/*找到该字符的父节点*/
		while (f)
		{
			if (t[f].lchild == c)
				cd[--start] = '0';												/*左孩子为0*/
			else
				cd[--start] = '1';												/*右孩子为1*/
			c = f;
			f = t[f].parent;
		}
		(*hcd)[i] = (char*)malloc((n - start) * sizeof(char));					/*为hcd的成员申请空间*/
		strcpy((*hcd)[i], &cd[start]);											/*将完成的编码存入hcd中*/
	}
}

void encipher(int num)
{
	char ch;
	char temp[2];
	int j , r=0;
	printf("请将您要进行编码的字符序列输入到“待编码.txt”中，注意：只能编码已存入系统中的哈夫曼编码\n");
	printf("输入结束请保存，按回车键继续\n");
	getchar();
	IN = fopen("待编码.txt", "r");
	printf("编码后的序列为:\n");
	while((ch=fgetc(IN))!=EOF)									/*从文件中读取一个字符放入ch中*/
	{
		temp[0] = ch;										/*将ch中的值赋给temp的末尾*/
		temp[1] = '\0';										/*将temp最后一位赋值为\0使字符串有意义*/
		for (j = 0; j<num; j++)
		{
			if (strcmp(huf[j][0], temp) == 0)					/*若huf中储存的字符与temp中字符相同，则输出对应的哈夫曼码*/
			{
				printf("%s", huf[j][1]);						/*将结果显示在屏幕上*/
				fprintf(OUT, "%s", huf[j][1]);					/*将结果储存在文件中*/
				break;
			}
		}
	}
	printf("\n编码完成的序列同时储存在“编码完成.txt”中\n");
}

void decipher(HufTree t, int n)
{
	int p;
	char ch;
	printf("请将您要进行译码的字符序列输入到“待译码.txt”中，注意：只能译码已存入系统中的哈夫曼编码\n");
	printf("输入结束请保存，按回车键继续\n");
	getchar();
	IN = fopen("待译码.txt", "r");
	printf("译码后的序列为:\n");
	p = 2*n-1;								/*从根子树开始检索*/
	if ((ch = fgetc(IN)) == EOF)			/*从文件中读入一位*/
		return;
	while (1)
	{
		if (ch == '0')						/*若为0则转向左子树*/
		{
			if (t[p].lchild)	
				p = t[p].lchild;			/*若p的左子树存在则指向p的左子树*/
			else
			{
				printf("%c", t[p].data);	/*输出*/
				fprintf(OUT, "%c", t[p].data);
				p = 2*n - 1;				/*将p重新指向根结点*/
				continue;
			}
		}
		else
		{
			if (ch == '1')					/*若为1则转向右子树*/
			{
				if (t[p].rchild)
					p = t[p].rchild;		/*若p的右子树存在则指向p的右子树*/
				else
				{
					printf("%c", t[p].data);/*输出*/
					fprintf(OUT, "%c", t[p].data);
					p = 2*n - 1;			/*将p重新指向根结点*/
					continue;
				}
			}
			else
			{
				printf("输入有误，请重新输入\n");/*容错性*/
				break;
			}
		}
		if ((ch = fgetc(IN)) == EOF)				/*读入下一位*/
		{
			printf("%c", t[p].data);				/*输出最后一位结点*/
			fprintf(OUT, "%c", t[p].data);
			printf("\n译码完成的序列同时储存在“译码完成.txt”中\n");
			break;
		}
	}
}