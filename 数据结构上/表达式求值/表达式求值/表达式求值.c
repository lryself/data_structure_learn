#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
	char ysf;
	int number;
}member;

typedef struct node
{
	 member data;
	 struct node *next;
}stack,*lstack;

void create(lstack *l);
member pop(lstack l);
int push(lstack l, member x);

FILE *IN;
int main()
{
	int i, j, n,b,c;
	char a[100],op;
	int y1, y2;
	char *p;
	member x;
	stack s;
	lstack l1,l2;
	create(&l1);
	create(&l2);
	printf("请输入算式，以#结束\n");
	fopen("Text.txt", "r");
	fscanf(IN,"%s", &a);
	for (i = 0; a[i] != '#';)
	{
		if (a[i] >= '0'&&a[i] <= '9')
		{
			b = 0;
			while (a[i] >= '0'&&a[i] <= '9')
			{
				b = b * 10;
				c = ((int)a[i] - 48);
				b = b + c;
				i++;
			}
			x.number = c;
			push(l1, x);
			continue;
		}
		else
		{
			x.ysf = a[i];
			switch (a[i])
			{
				case '+':
					push(l2, x);
					break;
				case '-':
					push(l2, x);
					break;
				case '*':
					push(l2, x);
					i++;
					if (a[i] == '(')
					{
						x.ysf = a[i];
						push(l2, x);
						break;
					}
					pop(l2);
					y2 = a[i];
					x = pop(l1);
					y1 = x.number;
					x.number=y1*y2;
					push(l1, x);
					break;
				case '/':
					push(l2, x);
					i++;
					if (a[i] == '(')
					{
						x.ysf = a[i];
						push(l2, x);
						break;
					}
					pop(l2);
					y2 = a[i];
					x = pop(l1);
					y1 = x.number;
					x.number=y1/y2;
					push(l1, x);
					break;
				case '(':
					push(l2, x);
					break;
				case ')':
					while (l2->next->data.ysf != '(')
					{
						x = pop(l2);
						op = x.ysf;
						x = pop(l1);
						y2 = x.number;
						x = pop(l1);
						y1 = x.number;
						if (op == '+')
						{
							x.number = y1 + y2;
							push(l1, x);
						}
						if (op == '-')
						{
							x.number = y1 - y2;
							push(l1, x);
						}
					}
					pop(l2);
					while (l2->next->data.ysf == '*'||l2->next->data.ysf=='/')
					{
						x=pop(l2);
						op = x.ysf;
						x = pop(l1);
						y2 = x.number;
						x = pop(l1);
						y1 = x.number;
						if(op=='*')
							x.number = y1 * y2;
						if (op == '/')
							x.number = y1 / y2;
						push(l1, x);
						break;
					}
					break;
			}
		}
		i++;
	}
	while (l1->next->next != NULL)
	{
		x = pop(l2);
		op = x.ysf;
		x = pop(l1);
		y2 = x.number;
		x = pop(l1);
		y1 = x.number;
		if (op == '+')
		{
			x.number = y1 + y2;
			push(l1, x);
		}
		if (op == '-')
		{
			x.number = y1 - y2;
			push(l1, x);
		}
	}
	x = pop(l1);
	printf("%d", x.number);
}

void create(lstack *l)
{
	(*l) = (lstack)malloc(sizeof(stack));
	(*l)->next = NULL;
}

int push(lstack l,member x)
{
	lstack s;
	s = (lstack)malloc(sizeof(stack));
	if (s == NULL)
		return 0;
	s->next = l->next;
	l->next = s;
	s->data = x;
	return 1;
}

member pop(lstack l)
{
	member x;
	lstack p;
	p = l->next;
	x = p->data;
	l->next = p->next;
	free(p);
	return x;
}