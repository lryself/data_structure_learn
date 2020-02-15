#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

typedef struct BiNode
{
	char data;
	struct BiNode *lchild;
	struct BiNode *rchild;
}BiNode, *BiTree;														/*������*/
typedef struct QNode
{
	BiTree data;
	struct QNode *next;
}QNode, *QueueLink;														/*���н��*/
typedef struct QLink
{
	QueueLink first;
	QueueLink last;
}QLink;																	/*����*/
typedef struct Stack
{
	BiTree data;
	struct Stack *next;
}Stack, *StackLink;														/*ջ*/
typedef struct renwushu
{
	BiTree data;
	int mes;
	struct renwushu *next;
}rws,*lrws;															/*������ջ*/

FILE *TXT;																							/*�ļ�*/

//�˵�
int menu();
//�������Ĳ���
void createBiTree(BiTree *t);																		/*���򴴽�������*/
void pre(BiTree t);																					/*�ȸ�����*/
void layer(BiTree t);																				/*��α���*/
void creat_BiTree(BiTree *t);																		/*���ߴ���������*/
void copy(BiTree t, BiTree *s);																		/*���ƶ�����*/
void CrtBT(BiTree *t, char pre[], char min[], int ps, int is, int n);								/*�����ȸ����и��������д���������*/
void Crtbt(BiTree *t, char m[], char l[], int is, int ls, int n);									/*�����и��ͺ���������д���������*/
void initBiTree(BiTree *T);																			/*��ʼ��������*/
void createbd(BiTree *t);																			/*�������ʽ������*/
void inobd(BiTree t);																				/*�и�������ʽ������*/
void createbd1(BiTree *t);																			/*���ʽ�������д�����������*/
void messionpre(BiTree t);																			/*�����鷨�ȸ�����*/
void messionino(BiTree t);																			/*�����鷨�и�����*/
void messionpos(BiTree t);																			/*�����鷨�������*/
void roadpre(BiTree t);																				/*·���������ȸ�����*/
void roadino(BiTree t);																				/*·���������и�����*/
void roadpos(BiTree t);																				/*·���������������*/
void everyroadpre1(BiTree t,StackLink s);															/*�ݹ��ȸ�����ÿ��·��*/
void everyroadpre2(BiTree t);																		/*�ǵݹ��ȸ�����ÿ��·��*/
void destroyBiTree(BiTree T);																		/*���ٶ�����*/
int deleteBiTree(BiTree t,char a);																	/*ɾ�����������*/
BiTree SearchBiTree(BiTree t,char a);																/*���Ҷ��������*/
int insertBiTree(BiTree t, char data, char parent);													/*������������*/
int depth(BiTree t);																				/*�������*/
int leafcount(BiTree t);																			/*����Ҷ�ӽڵ���*/
BiTree findparents(BiTree t, char e);																/*Ѱ�Ҹ��ڵ�*/
//���в���
void initQueue(QLink *q);																			/*��ʼ������*/
void EnQueue(QLink *q, BiTree t);																	/*����*/
BiTree DeQueue(QLink *q);																			/*����*/
int ifemptyQueue(QLink q);																			/*�ж϶ӿ�*/
BiTree GetQueueHead(QLink q);																		/*�õ���ͷ*/
//ջ����
int initStack(StackLink *l);																		/*��ʼ��ջ*/
int push(StackLink l, BiTree x);																	/*��ջ*/
BiTree pop(StackLink l);																			/*��ջ*/
int ifemptyStack(StackLink l);																		/*�ж�ջ��*/
void createrws(lrws *L);																			/*����������ջ*/
void pushrws(lrws l, BiTree t, int i);																/*��������ջ*/
BiTree poprws(lrws l, int *x);																		/*��������ջ*/
int ifemptyrws(lrws l);																				/*�ж�������ջ��*/
void PrintStack(StackLink s);																		/*��ջ�׿�ʼ���ջ�е�ÿһ��Ԫ��*/

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
			printf("���ڡ�������.txt��������Ҫ�����Ķ��������У���������ʽ,#�����������ע��ʹ��Ӣ���ַ���\n");
			printf("�������뱣�棬���س�������\n");
			getchar();
			TXT = fopen("������.txt", "r");
			createBiTree(&tree);
			fclose(TXT);
			break;
		case 2:
			printf("���ڡ�������.txt������������(#,A,0)�Ķ������������У�ע��ʹ��Ӣ���ַ���");
			printf("�������뱣�棬���س�������\n");
			getchar();
			TXT = fopen("������.txt", "r");
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
			TXT = fopen("���Ĵ���.txt", "w");
			copy(tree, &tree_2);
			printf("���ƺ�Ķ�����Ϊ:\n");
			layer(tree_2);
			printf("\n");
			break;
		case 6:
			printf("���ڡ�������.txt������������ͺ������д�����������ע��ʹ��Ӣ���ַ���");
			printf("�������뱣�棬���س�������\n");
			getchar();
			TXT = fopen("������.txt", "r");
			fscanf(TXT, "%tree_2%tree_2", &m, &l);
			a = strlen(l);
			ls = strlen(l) - 1;
			Crtbt(&tree, m, l, is, ls, a);
			fclose(TXT);
			break;
		case 7:
			printf("���ڡ�������.txt��������ǰ������������д�����������ע��ʹ��Ӣ���ַ���");
			printf("�������뱣�棬���س�������\n");
			getchar();
			TXT = fopen("������.txt", "r");
			fscanf(TXT, "%tree_2%tree_2", &p, &m);
			a = strlen(p);
			CrtBT(&tree, p, m, ps, is, a);
			fclose(TXT);
			break;
		case 8:
			printf("���� ������.txt ��������ʽ����#������ע�⣺ֻ�ܱ���λ���򵥸���ĸ��ɵı��ʽ��ʹ��Ӣ���ַ�����������뱣�棬���س�����\n");
			getchar();
			TXT = fopen("������.txt", "r");
			createbd(&tree);
			printf("������ɵ�����Ϊ��\n");
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
			printf("�������\n");
			break;
		case 18:
			printf("��������Ҫ���ҵ�����\n");
			scanf("%c", &ch);
			getchar();
			tree_2 = SearchBiTree(tree, ch);
			if (tree_2)
			{
				printf("�ý��ֵΪ:%c\n", tree_2->data);
				if (tree_2->lchild)
					printf("�ý��������ֵΪ:%c\n", tree_2->lchild->data);
				else
					printf("����û�иý���������\n");
				if (tree_2->rchild)
					printf("�ý��������ֵΪ:%c\n", tree_2->rchild->data);
				else
					printf("����û�иý���������\n");
			}
			else
				printf("����û�иý��\n");
			break;
		case 19:
			printf("��������Ҫɾ�������ĸ��ڵ�:\n");
			scanf("%c", &ch);
			getchar();
			if (deleteBiTree(tree, ch))
			{
				printf("ɾ�����\n");
			}
			else
				printf("ɾ��ʧ�ܣ�����û�иý��\n");
			break;
		case 20:
			printf("��������Ҫ����Ľ������ݺ���Ҫ�������������(��,������ע��ʹ��Ӣ�ķ���)\n");
			scanf("%c,%c", &ch, &ch1);
			getchar();
			if (insertBiTree(tree, ch1, ch))
				printf("����ɹ�\n");
			else
				printf("����ʧ�ܣ�����û�иý���ý������������\n");
			break;
		case 21:
			printf("���������:%d\n",depth(tree));
			break;
		case 22:
			printf("���Ľ������:%d\n",leafcount(tree));
			break;
		case 23:
			printf("��������Ҫ���Ҹ��ڵ�Ľ��:\n");
			scanf("%c", &ch);
			getchar();
			if (findparents(tree, ch) == NULL)
				printf("�ý��û�и��ڵ�\n");
			else
				printf("�ý��ĸ��ڵ���:%c\n", findparents(tree, ch)->data);
			break;
		case 0:
			exit(1);
		}
		printf("���س�������");
		getchar();
		system("cls");
	}
}

int menu()
{
	int n;
	printf("��ѡ����Ҫ���еĲ�����\n");
	printf("1.�ݹ鴴��\n");
	printf("2.���ߴ���\n");
	printf("3.�������\n");
	printf("4.��α���\n");
	printf("5.�������ĸ���\n");
	printf("6.������ͺ������д���������\n");
	printf("7.��������������д���������\n");
	printf("8.�������ʽ������\n");
	printf("9.���������(����)\n");
	printf("10.���������(����)\n");
	printf("11.���������(����)\n");
	printf("12.·��������������\n");
	printf("13.·��������������\n");
	printf("14.·��������������\n");
	printf("15.�ݹ��������·��\n");
	printf("16.�ǵݹ��������·��\n");
	printf("17.���ٶ�����\n");
	printf("18.���Ҷ��������\n");
	printf("19.ɾ�����������\n");
	printf("20.������������\n");
	printf("21.���������\n");
	printf("22.�����Ľ�����\n");
	printf("23.�������ĸ����\n");
	printf("0.�˳�\n");
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