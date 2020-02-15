#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

typedef struct tree
{
	char data;
	struct tree *lchild;
	struct tree *rchild;
}tree, *ltree;

typedef struct snode
{
	ltree data;
	struct snode *next;
}stack, *lstack;

int creates(lstack *l);
int push(lstack l, ltree x);
ltree pop(lstack l);
void initree(ltree *T);
void createbd(ltree *t);
void inobd(ltree t);
void createbd1(ltree *t);

FILE *IN;
int main()
{
	ltree t;
	printf("请在 输入.txt 中输入表达式，以#结束，注意：只能表达个位数或单个字母组成的表达式，使用英文字符，输入结束按回车继续\n");
	getchar();
	IN = fopen("输入.txt", "r");
	createbd(&t);
	inobd(t);
}

int creates(lstack *l)
{
	(*l) = (lstack)malloc(sizeof(stack));
	if (*l == NULL)
		return 0;
	(*l)->next = NULL;
	return 1;
}

int push(lstack l, ltree x)
{
	lstack s;
	creates(&s);
	if (s == NULL)
		return 0;
	s->next = l->next;
	l->next = s;
	s->data = x;
	return 1;
}

ltree pop(lstack l)
{
	lstack p;
	ltree x;
	x = l->next->data;
	p = l->next;
	l->next = p->next;
	free(p);
	return x;
}

int ifemptys(lstack l)
{
	if (l->next == NULL)
		return 1;
	else
		return 0;
}

void initree(ltree *T)
{
	(*T) = (ltree)malloc(sizeof(tree));
	(*T)->lchild = (*T)->rchild = NULL;
}

void createbd(ltree *t)
{
	ltree s, y, p;
	char x;
	lstack czf;

	initree(t);
	creates(&czf);

	x = fgetc(IN);
	if (x == '#')
		return;
	if (x == '(')
	{
		createbd1(&s);
		(*t)->lchild = s;
	}
	else
	{
		initree(&y);
		y->data = x;
		(*t)->lchild = y;
	}
	x = fgetc(IN);
	if (x == '#')
		return;
	while (x == '*' || x == '/')
	{
		initree(&s);
		s->data = x;
		x = fgetc(IN);
		if (x == '(')
		{
			createbd1(&s);
			s->rchild = s;
		}
		else
		{
			initree(&y);
			y->data = x;
			s->rchild = y;
		}
		s->lchild = (*t)->lchild;
		(*t)->lchild = s;
		x = fgetc(IN);
	}
	(*t)->data = x;
	x = fgetc(IN);
	if (x == '(')
	{
		createbd1(&s);
		(*t)->rchild = s;
	}
	else
	{
		initree(&y);
		y->data = x;
		(*t)->rchild = y;
	}
	p = (*t);
	x = fgetc(IN);
	while (x != '#')
	{
		if (x != '+'&&x != '-'&&x != '*'&&x != '/')
		{
			initree(&y);
			y->data = x;
			p->rchild = y;
		}
		else
		{
			switch (x)
			{
			case '+':
			case '-':
				if (!ifemptys(czf))
					p = pop(czf);
				initree(&s);
				s->data = x;
				s->lchild = p->rchild;
				p->rchild = s;
				p = s;
				break;
			case '*':
			case '/':
				initree(&s);
				s->data = x;
				s->lchild = p->rchild;
				p->rchild = s;
				if(ifemptys(czf))
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
		x = fgetc(IN);
	}
}

void createbd1(ltree *t)
{
	ltree s, y, p;
	char x;
	lstack czf;

	initree(t);
	creates(&czf);

	x = fgetc(IN);
	if (x == ')')
		return;
	if (x == '(')
	{
		createbd(&s);
		(*t)->lchild = s;
	}
	else
	{
		initree(&y);
		y->data = x;
		(*t)->lchild = y;
	}
	x = fgetc(IN);
	while (x == '*' || x == '/')
	{
		initree(&s);
		s->data = x;
		x = fgetc(IN);
		if (x == '(')
		{
			createbd1(&s);
			s->rchild = s;
		}
		else
		{
			initree(&y);
			y->data = x;
			s->rchild = y;
		}
		s->lchild = (*t)->lchild;
		(*t)->lchild = s;
		x = fgetc(IN);
	}
	if (x == ')')
		return;
	(*t)->data = x;
	x = fgetc(IN);
	if (x == '(')
	{
		createbd(&s);
		(*t)->rchild = s;
	}
	else
	{
		initree(&y);
		y->data = x;
		(*t)->rchild = y;
	}
	p = (*t);
	while (x != ')')
	{
		x = fgetc(IN);
		if (x != '+'&&x != '-'&&x != '*'&&x != '/')
		{
			initree(&y);
			y->data = x;
			p->rchild = y;
		}
		else
		{
			switch (x)
			{
			case '+':
			case '-':
				if (!ifemptys(czf))
					p = pop(czf);
				initree(&s);
				s->data = x;
				s->lchild = p->rchild;
				p->rchild = s;
				p = s;
				break;
			case '*':
			case '/':
				initree(&s);
				s->data = x;
				s->lchild = p->rchild;
				p->rchild = s;
				if (ifemptys(czf))
					push(czf, p);
				p = s;
				break;
			case '(':
				initree(&s);
				p->rchild = s;
				p = s;
				break;
			}
		}
	}
}

void inobd(ltree t)
{
	if (t != NULL)
	{
		printf("(");
		inobd(t->lchild);
		printf("%c",t->data);
		inobd(t->rchild);
		printf(")");
	}
}