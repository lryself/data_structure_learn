#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

typedef struct BiNode
{
	char data;
	struct BiNode *lchild;
	struct BiNode *rchild;
}BiNode, *BiTree;														/*二叉树*/
typedef struct QNode
{
	BiTree data;
	struct QNode *next;
}QNode, *QueueLink;														/*队列结点*/
typedef struct QLink
{
	QueueLink first;
	QueueLink last;
}QLink;																	/*队列*/
typedef struct Stack
{
	BiTree data;
	struct Stack *next;
}Stack, *StackLink;														/*栈*/
typedef struct renwushu
{
	BiTree data;
	int mes;
	struct renwushu *next;
}rws,*lrws;															/*任务书栈*/

FILE *TXT;																							/*文件*/

//菜单
int menu();
//二叉树的操作
void createBiTree(BiTree *t);																		/*先序创建二叉树*/
void pre(BiTree t);																					/*先根遍历*/
void layer(BiTree t);																				/*层次遍历*/
void creat_BiTree(BiTree *t);																		/*按边创建二叉树*/
void copy(BiTree t, BiTree *s);																		/*复制二叉树*/
void CrtBT(BiTree *t, char pre[], char min[], int ps, int is, int n);								/*根据先根和中根遍历序列创建二叉树*/
void Crtbt(BiTree *t, char m[], char l[], int is, int ls, int n);									/*根据中根和后根遍历序列创建二叉树*/
void initBiTree(BiTree *T);																			/*初始化二叉树*/
void createbd(BiTree *t);																			/*创建表达式二叉树*/
void inobd(BiTree t);																				/*中根输出表达式二叉树*/
void createbd1(BiTree *t);																			/*表达式二叉树中创建括号序列*/
void messionpre(BiTree t);																			/*任务书法先根遍历*/
void messionino(BiTree t);																			/*任务书法中根遍历*/
void messionpos(BiTree t);																			/*任务书法后根遍历*/
void roadpre(BiTree t);																				/*路径分析法先根遍历*/
void roadino(BiTree t);																				/*路径分析法中根遍历*/
void roadpos(BiTree t);																				/*路径分析法后根遍历*/
void everyroadpre1(BiTree t,StackLink s);															/*递归先根遍历每条路径*/
void everyroadpre2(BiTree t);																		/*非递归先根遍历每条路径*/
void destroyBiTree(BiTree T);																		/*销毁二叉树*/
int deleteBiTree(BiTree t,char a);																	/*删除二叉树结点*/
BiTree SearchBiTree(BiTree t,char a);																/*查找二叉树结点*/
int insertBiTree(BiTree t, char data, char parent);													/*插入二叉树结点*/
int depth(BiTree t);																				/*树的深度*/
int leafcount(BiTree t);																			/*树的叶子节点数*/
BiTree findparents(BiTree t, char e);																/*寻找父节点*/
//队列操作
void initQueue(QLink *q);																			/*初始化队列*/
void EnQueue(QLink *q, BiTree t);																	/*进队*/
BiTree DeQueue(QLink *q);																			/*出队*/
int ifemptyQueue(QLink q);																			/*判断队空*/
BiTree GetQueueHead(QLink q);																		/*得到队头*/
//栈操作
int initStack(StackLink *l);																		/*初始化栈*/
int push(StackLink l, BiTree x);																	/*进栈*/
BiTree pop(StackLink l);																			/*出栈*/
int ifemptyStack(StackLink l);																		/*判断栈空*/
void createrws(lrws *L);																			/*创建任务书栈*/
void pushrws(lrws l, BiTree t, int i);																/*进任务书栈*/
BiTree poprws(lrws l, int *x);																		/*出任务书栈*/
int ifemptyrws(lrws l);																				/*判断任务书栈空*/
void PrintStack(StackLink s);																		/*从栈底开始输出栈中的每一个元素*/

int main()
{
	BiTree tree = NULL;
	BiTree tree_2 = NULL;
	char p[100], m[100], l[100],ch,ch1;
	int ps = 0, is = 0, ls = 0, a;
	StackLink stack;
	while (1)
	{
		switch (menu())
		{
		case 1:
			printf("请在“输入树.txt”中输入要创建的二叉树序列（以先序形式,#代表空子树，注意使用英文字符）\n");
			printf("输完请请保存，按回车键继续\n");
			getchar();
			TXT = fopen("输入树.txt", "r");
			createBiTree(&tree);
			fclose(TXT);
			break;
		case 2:
			printf("请在“输入树.txt”中输入形如(#,A,0)的二叉树创建序列（注意使用英文字符）");
			printf("输完请请保存，按回车键继续\n");
			getchar();
			TXT = fopen("输入树.txt", "r");
			creat_BiTree(&tree);
			fclose(TXT);
			break;
		case 3:
			pre(tree);
			printf("\n");
			break;
		case 4:
			layer(tree);
			printf("\n");
			break;
		case 5:
			TXT = fopen("树的储存.txt", "w");
			copy(tree, &tree_2);
			printf("复制后的二叉树为:\n");
			layer(tree_2);
			printf("\n");
			break;
		case 6:
			printf("请在“输入树.txt”中输入中序和后序序列创建二叉树（注意使用英文字符）");
			printf("输完请请保存，按回车键继续\n");
			getchar();
			TXT = fopen("输入树.txt", "r");
			fscanf(TXT, "%tree_2%tree_2", &m, &l);
			a = strlen(l);
			ls = strlen(l) - 1;
			Crtbt(&tree, m, l, is, ls, a);
			fclose(TXT);
			break;
		case 7:
			printf("请在“输入树.txt”中输入前序序和中序序列创建二叉树（注意使用英文字符）");
			printf("输完请请保存，按回车键继续\n");
			getchar();
			TXT = fopen("输入树.txt", "r");
			fscanf(TXT, "%tree_2%tree_2", &p, &m);
			a = strlen(p);
			CrtBT(&tree, p, m, ps, is, a);
			fclose(TXT);
			break;
		case 8:
			printf("请在 输入树.txt 中输入表达式，以#结束，注意：只能表达个位数或单个字母组成的表达式，使用英文字符，输入结束请保存，按回车继续\n");
			getchar();
			TXT = fopen("输入树.txt", "r");
			createbd(&tree);
			printf("创建完成的树的为：\n");
			inobd(tree);
			printf("=");
			printf("%d", countbd(tree));
			printf("\n");
			fclose(TXT);
			break;
		case 9:
			messionpre(tree);
			printf("\n");
			break;
		case 10:
			messionino(tree);
			printf("\n");
			break;
		case 11:
			messionpos(tree);
			printf("\n");
			break;
		case 12:
			roadpre(tree);
			printf("\n");
			break;
		case 13:
			roadino(tree);
			printf("\n");
			break;
		case 14:
			roadpos(tree);
			printf("\n");
			break;
		case 15:
			initStack(&stack);
			everyroadpre1(tree, stack);
			free(stack);
			break;
		case 16:
			everyroadpre2(tree);
			printf("\n");
			break;
		case 17:
			destroyBiTree(tree);
			printf("销毁完成\n");
			break;
		case 18:
			printf("请输入您要查找的数据\n");
			scanf("%c", &ch);
			getchar();
			tree_2 = SearchBiTree(tree, ch);
			if (tree_2)
			{
				printf("该结点值为:%c\n", tree_2->data);
				if (tree_2->lchild)
					printf("该结点左子树值为:%c\n", tree_2->lchild->data);
				else
					printf("树中没有该结点的左子树\n");
				if (tree_2->rchild)
					printf("该结点右子树值为:%c\n", tree_2->rchild->data);
				else
					printf("树中没有该结点的有子树\n");
			}
			else
				printf("树中没有该结点\n");
			break;
		case 19:
			printf("请输入您要删除的树的根节点:\n");
			scanf("%c", &ch);
			getchar();
			if (deleteBiTree(tree, ch))
			{
				printf("删除完成\n");
			}
			else
				printf("删除失败，树中没有该结点\n");
			break;
		case 20:
			printf("请输入您要插入的结点的数据和您要插入的树的数据(用,隔开，注意使用英文符号)\n");
			scanf("%c,%c", &ch, &ch1);
			getchar();
			if (insertBiTree(tree, ch1, ch))
				printf("插入成功\n");
			else
				printf("插入失败，树中没有该结点或该结点有左右子树\n");
			break;
		case 21:
			printf("树的深度是:%d\n",depth(tree));
			break;
		case 22:
			printf("树的结点数是:%d\n",leafcount(tree));
			break;
		case 23:
			printf("请输入您要查找父节点的结点:\n");
			scanf("%c", &ch);
			getchar();
			if (findparents(tree, ch) == NULL)
				printf("该结点没有父节点\n");
			else
				printf("该结点的父节点是:%c\n", findparents(tree, ch)->data);
			break;
		case 0:
			exit(1);
		}
		printf("按回车键继续");
		getchar();
		system("cls");
	}
}

int menu()
{
	int n;
	printf("请选择你要进行的操作：\n");
	printf("1.递归创建\n");
	printf("2.按边创建\n");
	printf("3.先序遍历\n");
	printf("4.层次遍历\n");
	printf("5.二叉树的复制\n");
	printf("6.用中序和后序序列创建二叉树\n");
	printf("7.用先序和中序序列创建二叉树\n");
	printf("8.创建表达式二叉树\n");
	printf("9.任务书遍历(先序)\n");
	printf("10.任务书遍历(中序)\n");
	printf("11.任务书遍历(后序)\n");
	printf("12.路径分析法（先序）\n");
	printf("13.路径分析法（中序）\n");
	printf("14.路径分析法（后序）\n");
	printf("15.递归输出所有路径\n");
	printf("16.非递归输出所有路径\n");
	printf("17.销毁二叉树\n");
	printf("18.查找二叉树结点\n");
	printf("19.删除二叉树结点\n");
	printf("20.插入二叉树结点\n");
	printf("21.求树的深度\n");
	printf("22.求树的结点点数\n");
	printf("23.求树结点的父结点\n");
	printf("0.退出\n");
	scanf("%d", &n);
	getchar();
	system("cls");
	return n;
}

void createBiTree(BiTree *t)
{
	char ch;
	fscanf(TXT,"%c", &ch);
	if (ch == '#')
		*t = NULL;
	else
	{
		(*t) = (BiTree)malloc(sizeof(BiNode));
		(*t)->data = ch;
		createBiTree(&(*t)->lchild);
		createBiTree(&(*t)->rchild);
	}
}

void pre(BiTree t)
{
	if (t)
	{
		printf("%c", t->data);
		pre(t->lchild);
		pre(t->rchild);
	}
}

void ino(BiTree t)
{
	if (t)
	{
		ino(t->lchild);
		printf("%c", t->data);
		ino(t->rchild);
	}
}

void initQueue(QLink *q)
{
	(*q).first = (*q).last = (QueueLink)malloc(sizeof(QNode));
	(*q).first->next = NULL;
}

void EnQueue(QLink *q, BiTree t)
{
	QueueLink p;
	p = (QueueLink)malloc(sizeof(QNode));
	p->data = t;
	p->next = NULL;
	(*q).last->next = p;
	(*q).last = p;
}

BiTree DeQueue(QLink *q)
{
	QueueLink p;
	BiTree t;
	p = (*q).first->next;
	(*q).first->next = p->next;
	t = p->data;
	if (ifemptyQueue((*q)) == 0)
		(*q).last = (*q).first;
	free(p);
	return t;
}

int ifemptyQueue(QLink q)
{
	if (q.first->next == NULL)
		return 0;
	else
		return 1;
}

void layer(BiTree t)
{
	QLink q;
	BiTree p;
	initQueue(&q);
	if (t)
		EnQueue(&q, t);
	while (ifemptyQueue(q))
	{
		p = DeQueue(&q);
		printf("%c", p->data);
		if (p->lchild)
			EnQueue(&q, p->lchild);
		if (p->rchild)
			EnQueue(&q, p->rchild);
	}
}

BiTree GetQueueHead(QLink q)
{
	BiTree t;
	t = q.first->next->data;
	return t;
}

void creat_BiTree(BiTree *t)
{
	QLink Q;
	BiTree p, s;
	char fa, ch;
	int lrflag;
	initQueue(&Q);
	*t = NULL;
	fscanf(TXT,"(%c,%c,%d)", &fa, &ch, &lrflag);
	while (ch != '#')
	{
		p = (BiTree)malloc(sizeof(BiNode));
		p->data = ch;
		p->lchild = p->rchild = NULL;
		EnQueue(&Q, p);
		if (fa == '#')
			*t = p;
		else
		{
			s = GetQueueHead(Q);
			while (s->data != fa)
			{
				DeQueue(&Q);
				s = GetQueueHead(Q);
			}
			if (lrflag == 0)
				s->lchild = p;
			else
				s->rchild = p;
		}
		getchar();
		fscanf(TXT,"(%c,%c,%d)", &fa, &ch, &lrflag);
	}
}

void copy(BiTree t, BiTree *S)
{
	if (t)
	{
		(*S)->data = t->data;
		copy(t->lchild, &(*S)->lchild);
		copy(t->rchild, &(*S)->rchild);
	}
}

void CrtBT(BiTree *t, char p[], char m[], int ps, int is, int n)
{
	int k = -1;
	int i;
	if (n == 0)
		*t = NULL;
	else
	{
		for (i = 0; i < strlen(m); i++)
		{
			if (m[i] == p[ps])
			{
				k = i;
				break;
			}
		}
		if (k == -1)
			*t = NULL;
		else {
			(*t) = (BiTree)malloc(sizeof(BiNode));
			(*t)->data = p[ps];
			if (k == is)
				(*t)->lchild = NULL;
			else
				CrtBT(&(*t)->lchild, p, m, ps + 1, is, k - is);
			if (k == (is + n - 1))
				(*t)->rchild = NULL;
			else
				CrtBT(&(*t)->rchild, p, m, ps + 1+k - is, k+1 , n - (k - is) - 1);
		}
	}
}

void Crtbt(BiTree *t, char m[], char l[], int is, int ls, int n)
{
	int k = -1;
	int i;
	if (n == 0)
		*t = NULL;
	else
	{
		for (i = 0; i < strlen(m); i++)
		{
			if (m[i] == l[ls])
			{
				k = i;
				break;
			}
		}
		if (k == -1)
			*t = NULL;
		else {
			(*t) = (BiTree)malloc(sizeof(BiNode));
			(*t)->data = l[ls];
			if (k == is)
				(*t)->lchild = NULL;
			else
				Crtbt(&(*t)->lchild, m, l, is , ls-(n-k), k);
			if (k == (is + n - 1))
				(*t)->rchild = NULL;
			else
				Crtbt(&(*t)->rchild, m, l, k+1, ls-1, n - (k - is) - 1);
		}
	}
}

int initStack(StackLink *l)
{
	(*l) = (StackLink)malloc(sizeof(Stack));
	if (*l == NULL)
		return 0;
	(*l)->next = NULL;
	return 1;
}

int push(StackLink l, BiTree x)
{
	StackLink s;
	initStack(&s);
	if (s == NULL)
		return 0;
	s->next = l->next;
	l->next = s;
	s->data = x;
	return 1;
}

BiTree pop(StackLink l)
{
	StackLink p;
	BiTree x;
	x = l->next->data;
	p = l->next;
	l->next = p->next;
	free(p);
	return x;
}

int ifemptyStack(StackLink l)
{
	if (l->next == NULL)
		return 1;
	else
		return 0;
}

void initBiTree(BiTree *T)
{
	(*T) = (BiTree)malloc(sizeof(BiNode));
	(*T)->lchild = (*T)->rchild = NULL;
}

void createbd(BiTree *t)
{
	BiTree s, y, p;
	char x;
	StackLink czf;

	initBiTree(t);
	initStack(&czf);

	x = fgetc(TXT);
	if (x == '#')
		return;
	if (x == '(')
	{
		createbd1(&s);
		(*t)->lchild = s;
	}
	else
	{
		initBiTree(&y);
		y->data = x;
		(*t)->lchild = y;
	}
	x = fgetc(TXT);
	if (x == '#')
		return;
	while (x == '*' || x == '/')
	{
		initBiTree(&s);
		s->data = x;
		x = fgetc(TXT);
		if (x == '(')
		{
			createbd1(&s);
			s->rchild = s;
		}
		else
		{
			initBiTree(&y);
			y->data = x;
			s->rchild = y;
		}
		s->lchild = (*t)->lchild;
		(*t)->lchild = s;
		x = fgetc(TXT);
	}
	(*t)->data = x;
	x = fgetc(TXT);
	if (x == '(')
	{
		createbd1(&s);
		(*t)->rchild = s;
	}
	else
	{
		initBiTree(&y);
		y->data = x;
		(*t)->rchild = y;
	}
	p = (*t);
	x = fgetc(TXT);
	while (x != '#')
	{
		if (x != '+'&&x != '-'&&x != '*'&&x != '/'&&x!='('&&x!=')')
		{
			initBiTree(&y);
			y->data = x;
			p->rchild = y;
		}
		else
		{
			switch (x)
			{
			case '+':
			case '-':
				if (!ifemptyStack(czf))
					p = pop(czf);
				initBiTree(&s);
				s->data = x;
				s->lchild = p->rchild;
				p->rchild = s;
				p = s;
				break;
			case '*':
			case '/':
				initBiTree(&s);
				s->data = x;
				s->lchild = p->rchild;
				p->rchild = s;
				if (ifemptyStack(czf))
					push(czf, p);
				p = s;
				break;
			case '(':
				createbd1(&s);
				p->rchild = s;
				p = s;
				break;
			}
		}
		x = fgetc(TXT);
	}
}

void createbd1(BiTree *t)
{
	BiTree s, y, p;
	char x;
	StackLink czf;

	initBiTree(t);
	initStack(&czf);

	x = fgetc(TXT);
	if (x == ')')
		return;
	if (x == '(')
	{
		createbd(&s);
		(*t)->lchild = s;
	}
	else
	{
		initBiTree(&y);
		y->data = x;
		(*t)->lchild = y;
	}
	x = fgetc(TXT);
	while (x == '*' || x == '/')
	{
		initBiTree(&s);
		s->data = x;
		x = fgetc(TXT);
		if (x == '(')
		{
			createbd1(&s);
			s->rchild = s;
		}
		else
		{
			initBiTree(&y);
			y->data = x;
			s->rchild = y;
		}
		s->lchild = (*t)->lchild;
		(*t)->lchild = s;
		x = fgetc(TXT);
	}
	if (x == ')')
		return;
	(*t)->data = x;
	x = fgetc(TXT);
	if (x == '(')
	{
		createbd(&s);
		(*t)->rchild = s;
	}
	else
	{
		initBiTree(&y);
		y->data = x;
		(*t)->rchild = y;
	}
	p = (*t);
	while (x != ')')
	{
		x = fgetc(TXT);
		if (x != '+'&&x != '-'&&x != '*'&&x != '/'&&x != '('&&x != ')')
		{
			initBiTree(&y);
			y->data = x;
			p->rchild = y;
		}
		else
		{
			switch (x)
			{
			case '+':
			case '-':
				if (!ifemptyStack(czf))
					p = pop(czf);
				initBiTree(&s);
				s->data = x;
				s->lchild = p->rchild;
				p->rchild = s;
				p = s;
				break;
			case '*':
			case '/':
				initBiTree(&s);
				s->data = x;
				s->lchild = p->rchild;
				p->rchild = s;
				if (ifemptyStack(czf))
					push(czf, p);
				p = s;
				break;
			case '(':
				initBiTree(&s);
				p->rchild = s;
				p = s;
				break;
			}
		}
	}
}

void inobd(BiTree t)
{
	if (t != NULL)
	{
		printf("(");
		inobd(t->lchild);
		printf("%c", t->data);
		inobd(t->rchild);
		printf(")");
	}
}

int countbd(BiTree t)
{
	char x=t->data;
	int y, z,r;
	if (x >= '0'&&x <= '9')
	{
		y = (int)(x - 48);
		return y;
	}
	y = countbd(t->lchild);
	z = countbd(t->rchild);
	switch (x)
	{
	case '+':
		r = y + z;
		break;
	case '-':
		r = y - z;
		break;
	case '*':
		r = y * z;
		break;
	case '/':
		r = y / z;
		break;
	}
	return r;
}

void messionpre(BiTree t)
{
	lrws l;
	BiTree s;
	int x;
	initBiTree(&s);
	createrws(&l);
	pushrws(l, t, 1);
	while (!ifemptyrws(l))
	{
		s=poprws(l,&x);
		if (x == 1)
		{
			if(s->rchild)
				pushrws(l, s->rchild, 1);
			if(s->lchild)
				pushrws(l, s->lchild, 1);
			pushrws(l, s, 0);
		}
		if (x == 0)
		{
			printf("%c", s->data);
		}
	}
}

void messionino(BiTree t)
{
	lrws l;
	BiTree s;
	int x;
	initBiTree(&s);
	createrws(&l);
	pushrws(l, t, 1);
	while (!ifemptyrws(l))
	{
		s=poprws(l,&x);
		if (x == 1)
		{
			if(s->rchild)
				pushrws(l, s->rchild, 1);
			pushrws(l, s, 0);
			if(s->lchild)
				pushrws(l, s->lchild, 1);
		}
		if (x == 0)
		{
			printf("%c", s->data);
		}
	}
}

void messionpos(BiTree t)
{
	lrws l;
	BiTree s;
	int x;
	initBiTree(&s);
	createrws(&l);
	pushrws(l, t, 1);
	while (!ifemptyrws(l))
	{
		s=poprws(l,&x);
		if (x == 1)
		{
			pushrws(l, s, 0);
			if(s->rchild)
				pushrws(l, s->rchild, 1);
			if(s->lchild)
				pushrws(l, s->lchild, 1);
		}
		if (x == 0)
		{
			printf("%c", s->data);
		}
	}
}

void createrws(lrws *L)
{
	(*L) = (lrws)malloc(sizeof(rws));
	(*L)->next = NULL;
}

void pushrws(lrws l,BiTree t,int i)
{
	lrws s;
	createrws(&s);
	s->data = t;
	s->mes = i;
	s->next = l->next;
	l->next = s;
}

BiTree poprws(lrws l,int *x)
{
	BiTree t;
	lrws p;
	p = l->next;
	t = p->data;
	(*x) = l->next->mes;
	l->next = p->next;
	free(p);
	return t;
}

int ifemptyrws(lrws l)
{
	if (l->next)
		return 0;
	return 1;
}

void roadpre(BiTree t)
{
	int yn=1;
	StackLink l;
	initStack(&l);
	while (yn)
	{
		printf("%c", t->data);
		push(l,t->rchild);
		if (t->lchild)
		{
			t = t->lchild;
		}
		else
		{
			while (!(t = pop(l)))
			{
				if (ifemptyStack(l))
				{
					yn = 0;
					break;
				}
			}

		}
	}
}

void roadino(BiTree t)
{
	int yn = 1;
	StackLink l;
	initStack(&l);
	while (yn)
	{
		push(l, t);
		if (t != NULL&&t->lchild!=NULL)
		{
			t = t->lchild;
		}
		else
		{
			while (!(t = pop(l)))
			{
				if (ifemptyStack(l))
				{
					yn = 0;
					break;
				}
			}
			if (yn == 0)
				break;
			printf("%c", t->data);
			t = t->rchild;
		}
	}
}

void roadpos(BiTree t)
{
	int yn = 1;
	StackLink l;
	BiTree s;
	initBiTree(&s);
	initStack(&l);
	while (yn)
	{
		if (t&&t->rchild!=s)
		{
			push(l, t);
			push(l, t->rchild);
			push(l, t->lchild);
		}
		else
		{
			if(!t)
				while (!(t = pop(l)))
				{
					if (ifemptyStack(l))
					{
						yn = 0;
						break;
					}
				}
			if (yn==0)
			{
				break;
			}
			printf("%c", t->data);
			s = t;
		}
		if (ifemptyStack(l))
		{
			yn = 0;
			break;
		}
		t = pop(l);
	}
}

void everyroadpre1(BiTree t, StackLink s)
{
	push(s, t);
	if (t->lchild)
	{
		everyroadpre1(t->lchild, s);
		pop(s);
	}
	if (t->rchild)
	{
		everyroadpre1(t->rchild, s);
		pop(s);
	}
	if (!t->lchild && !t->rchild)
	{
		PrintStack(s);
		printf("\n");
	}
}

void everyroadpre2(BiTree t)
{
	BiTree p;
	StackLink s1,s2;
	initStack(&s1);
	initStack(&s2);
	while (1)
	{
		push(s1, t);
		if (t->rchild)
		{
			push(s2, t);
		}
		if (t->lchild)
		{
			push(s1, t->lchild);
			t = pop(s1);
		}
		else
		{
			if (!t->rchild)
			{
				PrintStack(s1);
				printf("\n");
				if (!ifemptyStack(s2))
				{
					t = pop(s2);
					while (t != (p = pop(s1)));
					push(s1, p);
					t = t->rchild;
				}
				else
					break;
			}
		}
	}

}

void destroyBiTree(BiTree T)
{
	if (T->lchild)
		destroyBiTree(T->lchild);
	if (T->rchild)
		destroyBiTree(T->rchild);
	free(T);
	T = NULL;
}

int deleteBiTree(BiTree t,char a)
{
	lrws l;
	BiTree p;
	int x;
	createrws(&l);
	pushrws(l, t, 1);
	while (!ifemptyrws(l))
	{
		t = poprws(l, &x);
		if (x == 1)
		{
			pushrws(l, t, 0);
			if (t->rchild)
				pushrws(l, t->rchild, 1);
			if (t->lchild)
				pushrws(l, t->lchild, 1);
		}
		if (x == 0)
		{
			if (t->data == a)
			{
				do
				{
					p = poprws(l, &x);
				} while (x != 0);
				if (p->lchild == t)
				{
					destroyBiTree(t);
					p->lchild = NULL;
				}
				if (p->rchild == t)
				{
					destroyBiTree(t);
					p->rchild = NULL;
				}
				return 1;
			}
		}
	}
	return 0;
}

BiTree SearchBiTree(BiTree t,char a)
{
	StackLink s;
	initStack(&s);
	while (1)
	{
		if (t->data == a)
			return t;
		else
		{
			if (t->rchild)
				push(s, t->rchild);
			if (t->lchild)
				t = t->lchild;
			else
			{
				if (!ifemptyStack(s))
					t = pop(s);
				else
					return NULL;
			}
		}
	}
}

int insertBiTree(BiTree t, char data, char parent)
{
	BiTree s;
	initBiTree(&s);
	s->data=data;
	t = SearchBiTree(t, parent);
	if(!t)
		return 0;
	if (!t->lchild)
		t->lchild = s;
	else
		if (!t->rchild)
			t->rchild = s;
		else
			return 0;
	return 1;
}

void PrintStack(StackLink s)
{
	BiTree q;
	StackLink p;
	initStack(&p);
	while (!ifemptyStack(s))
		push(p, pop(s));
	while(!ifemptyStack(p))
	{
		q = pop(p);
		printf("%c", q->data);
		push(s, q);
	}
}

int depth(BiTree t)
{
	int depl, depr;
	if (t == NULL)
		return 0;
	else
	{
		depl = depth(t->lchild);
		depr = depth(t->rchild);
		if (depl > depr)
			return depl + 1;
		else
			return depr + 1;
	}
}

int leafcount(BiTree t)
{
	int n = 0;
	StackLink s;
	initStack(&s);
	if (!t)
		return 0;
	while (1)
	{
		if (t->lchild == NULL && t->rchild == NULL)
		{
			n++;
		}
		if (t->rchild)
		{
			push(s, t->rchild);
		}
		if (t->lchild)
		{
			t = t->lchild;
		}
		else
		{
			if (ifemptyStack(s))
				return n;
			t = pop(s);
		}
	}
}

BiTree findparents(BiTree t, char e)
{
	StackLink s;
	initStack(&s);
	while (1)
	{
		if (t->data == e)
			return NULL;
		if (t->rchild)
		{
			push(s, t->rchild);
			if (t->rchild->data==e)
			{
				return t;
			}
		}
		if (t->lchild)
		{
			if (t->lchild->data==e)
			{
				return t;
			}
			t = t->lchild;
		}
		else
		{
			if (ifemptyStack(s))
				return NULL;
			t = pop(s);
		}
	}
}