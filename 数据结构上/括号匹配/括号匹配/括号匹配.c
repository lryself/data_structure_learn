#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
	char data;
	struct node *next;
}stack, *lstack;

int create(lstack *l);
int push(lstack l, char x);
char gettop(lstack l);
int pop(lstack l);

int main()
{
	int i, j;
	char x = 0, y;
	lstack l;
	create(&l);
	printf("请输入一个表达式（请使用英文符号）\n");
	while (x != '\n')
	{
		x = getchar();
		switch (x)
		{
		case '(':
		case '[':
		case '{':
			push(l, x);
			break;
		case ')':
		case ']':
		case '}':
			y = gettop(l);
			switch (y)
			{
			case '(':
				if (x == ')')
					pop(l);
				else
					push(l, x);
				break;
			case '[':
				if (x == ']')
					pop(l);
				else
					push(l, x);
				break;
			case '{':
				if (x == '}')
					pop(l);
				else
					push(l, x);
				break;
			}
		}
	}
	if (l->next == NULL)
		printf("括号匹配！\n");
	else
		printf("括号不匹配！\n");
	return 0;
}

int create(lstack *l)
{
	(*l) = (lstack)malloc(sizeof(stack));
	if (*l == NULL)
		return 0;
	(*l)->next = NULL;
	return 1;
}

int push(lstack l, char x)
{
	lstack s;
	create(&s);
	if (s == NULL)
		return 0;
	s->next = l->next;
	l->next = s;
	s->data = x;
	return 1;
}

char gettop(lstack l)
{
	char x;
	x = l->next->data;
	return x;
}

int pop(lstack l)
{
	lstack p;
	p = l->next;
	l->next = p->next;
	free(p);
	return 1;
}