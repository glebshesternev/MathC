// MathC.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "hMath.h"
#include "stdlib.h"
#ifndef HMATH_H
#define HMATH_H

int main(int argc, char **argv)
{
	input(argv);
	math(memb[0], memb[1], op, &memb[2]);
	output(argv[2]);
}

void error(char *er)
{
	printf("%s", er);
	exit(0);
}

void errorf(char *path, char *er)
{
	if (path != NULL)
	{
		FILE *f; f = NULL;
		if (fopen_s(&f, path, "r"))
			error("Error<OutputFileOpen>");
		fprintf(f, "%s", er);
		fclose(f);
		exit(0);
	}
	else
	{
		error(er);
	}
}

void input(char **path)
{
	FILE *f; f = NULL;
	int n = 0;
	int start = 0;
	char curr; curr = NULL;
	char prev; prev = NULL;
	if (fopen_s(&f, path[1], "r"))
		errorf(path[2], "Error<InputFileOpen");
	while (curr != EOF && curr != '\n' && curr != ' ')
	{
		curr = getc(f);
		if ((curr > '9' || curr < '0') && curr != '*' && curr != '/' && curr != '+' && curr != '-' && curr != '(' && curr != ')' && curr != EOF && curr != '\n' && curr != '\0')
			errorf(path[1], "Error<UnknownSimbol>");
		if (curr <= '9' && curr >= '0' && (prev<'0' || prev>'9'))
		{
			memb[n].len = 0;
			memb[n].sign = 1;
			if (n == 1 && prev == '-' && op != NULL)
			{
				memb[n].sign = -1;
			}
			if (n == 0 && prev == '-')
			{
				memb[n].sign = -1;
			}
			start = 1;
		}
		if (prev <= '9' && prev >= '0' && (curr<'0' || curr>'9'))
		{
			n++;
			start = 0;
		}
		if (start)
		{
			memb[n].len++;
			memb[n].num = (int*)realloc(memb[n].num, memb[n].len * sizeof(int));
			memb[n].num[memb[n].len - 1] = curr - '0';
		}
		if ((prev == '-' || prev == '*' || prev == '/' || prev == '+') && n == 1 && op == NULL)
		{
			op = prev;
		}
		prev = curr;
	}
	for (int i = 0; i < memb[0].len / 2; i++)
	{
		n = memb[0].num[i];
		memb[0].num[i] = memb[0].num[memb[0].len - i - 1];
		memb[0].num[memb[0].len - i - 1] = n;
	}
	for (int i = 0; i < memb[1].len / 2; i++)
	{
		n = memb[1].num[i];
		memb[1].num[i] = memb[1].num[memb[1].len - i - 1];
		memb[1].num[memb[1].len - i - 1] = n;
	}
}

void output(char *path)
{
	if (path != NULL)
	{
		FILE *f;
		if (fopen_s(&f, path, "w"))
			ferror(path, "Error<OutputFileOpen>");
		if (memb[2].len == -1)
			ferror(path, "Error<Div0>");
		if (memb[2].sign == -1 && !(memb[2].len == 1 && memb[2].num[0] == 0))
			fprintf(f, "-");
		for (int i = memb[2].len; i > 0; i--)
			fprintf(f, "%d", memb[2].num[i - 1]);
	}
	else
	{
		if (memb[2].len == -1)
			error("Error<Div0>");
		if (memb[2].sign == -1 && !(memb[2].len == 1 && memb[2].num[0] == 0))
			printf("-");
		for (int i = memb[2].len; i > 0; i--)
			printf("%d", memb[2].num[i - 1]);
	}
//	free(memb);
}
#endif // !HMATH_H
