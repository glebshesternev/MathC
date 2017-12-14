#include "stdafx.h"
#include "hMath.h"

void math(struct Memb a, struct Memb b, char op, struct Memb *res)
{
	switch (op)
	{
	case '+':
	{
		for (int i = 0; i < b.len; i++)
			b.num[i] *= b.sign;
		for (int i = 0; i < a.len; i++)
			a.num[i] *= a.sign;
		if (a.len > b.len)
			sum(a, b, res);
		else sum(b, a, res);
		break;
	}
	case '-':
	{
		for (int i = 0; i < b.len; i++)
			b.num[i] *= (b.sign*(-1));
		for (int i = 0; i < a.len; i++)
			a.num[i] *= a.sign;
		if (a.len > b.len)
			sum(a, b, res);
		else sum(b, a, res);
		break;
	}
	case '*':
	{
		res->sign = a.sign*b.sign;
		if (a.len > b.len)
			mult(a, b, res);
		else mult(b, a, res);
		break;
	}
	case '/':
	{
		if (b.len == 1 && b.num[0] == 0)
		{
			res->len = -1;
			break;
		}
		res->sign = a.sign*b.sign;
		divv(a, b, res);
		break;
	}
	default:
		break;
	}
}

int compare(struct Memb a, struct Memb b)
{
	if (a.len > b.len)
		return 1;
	else if (b.len > a.len)
		return 0;
	else for (int i = a.len - 1; i >= 0; i--)
		if (a.num[i] > b.num[i])
			return 1;
		else if (b.num[i] > a.num[i])
			return 0;
	return 2;
}

void sum(struct Memb a, struct Memb b, struct Memb *res)
{
	res->len = a.len + 1;
	res->num = (int*)malloc((res->len + 1) * sizeof(int));
	res->sign = 1;
	memset(res->num, 0, res->len * sizeof(int));
	for (int i = 0; i < b.len; i++)
	{
		res->num[i] = a.num[i] + b.num[i];
		if (res->num[i] < 0)
		{
			res->num[i] += 10;
			res->num[i + 1]--;
		}
		if (res->num[i] > 9)
		{
			res->num[i] -= 10;
			res->num[i + 1]++;
		}
	}
	for (int i = b.len; i < a.len; i++)
	{
		res->num[i] = a.num[i];
		if (res->num[i] < 0)
		{
			res->num[i] += 10;
			res->num[i + 1]--;
		}
		if (res->num[i] > 9)
		{
			res->num[i] -= 10;
			res->num[i + 1]++;
		}
	}
	if (res->num[res->len - 1] < 0)
	{
		if (res->num[res->len - 1] == -1)
		{
			res->len--;
			res->num[res->len] = 0;
		}
		else
		{
			res->num[res->len - 1] += 10;
		}
		res->sign = -1;
		res->num[0] = 10 - res->num[0];
		for (int i = 1; i < res->len; i++)
		{
			res->num[i] = 9 - res->num[i];
		}
		int i = 0;
		while (res->num[i] == 10)
		{
			i++;
			res->num[i - 1] = 0;
			res->num[i]++;
		}
		if (res->num[res->len] != 0)
			res->len++;
	}
	while (res->num[res->len - 1] == 0 && res->len > 1)
		res->len--;
}

void mult(struct Memb a, struct Memb b, struct Memb *res)
{
	res->len = a.len + b.len;
	res->num = (int*)malloc(res->len * sizeof(int));
	memset(res->num, 0, res->len * sizeof(int));
	for (int i = 1; i <= b.len; i++)
		for (int j = 1; j <= a.len; j++)
		{
			res->num[i + j - 2] += (a.num[j - 1] * b.num[i - 1]);
		}
	for (int i = 0; i < res->len; i++)
	{
		res->num[i + 1] += (res->num[i] / 10);
		res->num[i] %= 10;
	}
	while (res->num[res->len - 1] == 0 && res->len > 1)
		res->len--;
}

void divv(struct Memb a, struct Memb b, struct Memb *res)
{
	struct Memb c;
	struct Memb t;
	res->len = a.len - b.len + 1;
	res->len = res->len < 1 ? 1 : res->len;
	res->num = (int*)malloc(res->len * sizeof(int));
	memset(res->num, 0, res->len * sizeof(int));
	if (compare(b, a))
	{
		res->len = 1;
		if (res->sign == -1 && (a.len != 1 || a.num[0] != 0))
			res->num[0] = 1;
		return;
	}
	else
	{
		for (int i = a.len - b.len; i >= 0; i--)
		{
			c.len = a.len - i;
			c.num = &a.num[i];
			if (compare(c, b))
			{
				t.len = c.len + 1;
				t.num = (int*)malloc(t.len * sizeof(int));
				memset(t.num, 0, t.len * sizeof(int));
				t.len = 1;
				int j = 0;
				while (compare(c, t))
				{
					j++;
					if (t.len > b.len)
						sum(t, b, &t);
					else
						sum(b, t, &t);
				}
				j--;
				res->num[i] = j;
				memset(t.num, 0, t.len * sizeof(int));
				t.len = 1;
				for (int g = 0; g < j; g++)
					if (t.len > b.len)
						sum(t, b, &t);
					else
						sum(b, t, &t);
				for (int g = 0; g < t.len; g++)
					t.num[g] *= -1;
				sum(c, t, &c);
				for (int g = i; g < a.len; g++)
					a.num[g] = c.num[g - i];
				while (a.num[a.len - 1] == 0 && a.len > 1)
					a.len--;
			}
		}
		if (res->sign == -1 && (a.len != 1 || a.num[0] != 0))
		{
			int i = 0;
			res->num[0]++;
			while (res->num[i++] > 9)
			{
				res->num[i - 1] %= 10;
				res->num[i]++;
			}
		}
		while (res->num[res->len - 1] == 0 && res->len > 1)
			res->len--;
	}

}
