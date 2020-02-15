#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

typedef struct BiNode
{
	char data;
	struct BiNode *lchild;
	struct BiNode *rchild;
}BiNode, *BiTree;														/*������*/
typedef struct Stack
{
	BiTree data;
	struct Stack *next;
}Stack, *StackLink;														/*ջ*/
typedef struct linklist
{
	char letter;
	float number;
	struct linklist *next;
}linklist,*Linklist;													/*����*/

FILE *TXT;

int menu();
int initStack(StackLink * l);
int push(StackLink l, BiTree x);
BiTree pop(StackLink l);
int ifemptyStack(StackLink l);
void initBiTree(BiTree * T);
void createbd(BiTree * t);
void createbd1(BiTree * t);
float countbd(BiTree t,Linklist l);
void leafcount(BiTree t, Linklist l);
void initlinklist(Linklist * l);
void insert(Linklist l, char x, float y);
float search(Linklist l, char x);

void main()
{
	char ch;
	BiTree tree=NULL;
	Linklist l;
	while (1)
	{
		char ��ʽ[MAX];
		switch (menu())
		{
		case 0:
			exit(1);
		case 1:
			printf("��������Ҫ����Ĺ�ʽ��\n");
			scanf("%s", &��ʽ);
			getchar();
			TXT=fopen("��ʽ.txt", "w");
			fprintf(TXT,"%s", ��ʽ);
			fprintf(TXT, "#");
			fclose(TXT);
			printf("��ʽ�Ѵ���\n");
			break;
		case 2:
			TXT = fopen("��ʽ.txt", "r");
			createbd(&tree);
			fclose(TXT);
			printf("���ʽ�������Ѵ���\n");
			printf("��ʽΪ:");
			TXT = fopen("��ʽ.txt", "r");
			while((ch=fgetc(TXT))!='#')
				printf("%c",ch);
			fclose(TXT);
			printf("\n");
			initlinklist(&l);
			printf("��������Ҫ���������ݣ�\n");
			leafcount(tree, l);
			printf("���ս��Ϊ��%f\n",countbd(tree,l));
		}
		printf("���س�������\n");
		getchar();
		system("cls");
	}
}

int menu()
{
	int n;
	printf("��������Ҫ���еĲ���\n");
	printf("1.���벢���湫ʽ���ļ�\n");
	printf("2.����ʽ���뵽������������������ľ���ֵ��������\n");
	printf("0.�˳�\n");
	scanf("%d", &n);
	getchar();
	return n;
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
	BiTree s, y, p,q;
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
			initBiTree(&q);
			createbd1(&q);
			s->rchild = q;
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
	BiTree s, y, p,q;
	char x;
	StackLink czf;

	initBiTree(t);
	initStack(&czf);

	x = fgetc(TXT);
	if (x == ')')
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
	while (x == '*' || x == '/')
	{
		initBiTree(&s);
		s->data = x;
		x = fgetc(TXT);
		if (x == '(')
		{
			initBiTree(&q);
			createbd1(&q);
			s->rchild = q;
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

float countbd(BiTree t,Linklist l)
{
	float y, z, r;
	char x = t->data;
	if (x >= 'a'&&x <= 'z'||x>='A'&&x<='Z')
	{
		y = search(l,x);
		return y;
	}
	if(t->lchild)
		y = countbd(t->lchild,l);
	if(t->rchild)
		z = countbd(t->rchild,l);
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

void leafcount(BiTree t,Linklist l)
{
	int n = 0;
	float temp;
	StackLink s;
	initStack(&s);
	if (!t)
		return 0;
	while (1)
	{
		if (t->lchild == NULL && t->rchild == NULL)
		{
			printf("%c:", t->data);
			scanf("%f", &temp);
			getchar();
			printf("\n");
			insert(l, t->data, temp);
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
				return;
			t = pop(s);
		}
	}
}

void initlinklist(Linklist *l)
{
	(*l) = (Linklist)malloc(sizeof(linklist));
	(*l)->next = NULL;
}

void insert(Linklist l,char x,float y)
{
	Linklist p;
	initlinklist(&p);
	p->letter = x;
	p->number = y;
	p->next = l->next;
	l->next = p;
}

float search(Linklist l, char x)
{
	while (l != NULL)
	{
		if (l->letter == x)
			return l->number;
		l = l->next;
	}
}