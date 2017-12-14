#pragma once

char op;
void input(char **argv);
void output(char *path);
void errorf(char *path, char *er);
void math(struct Memb a, struct Memb b, char op, struct Memb *res);
void sum(struct Memb a, struct Memb b, struct Memb *res);
void mult(struct Memb a, struct Memb b, struct Memb *res);
void divv(struct Memb a, struct Memb b, struct Memb *res);

struct Memb
{
	int len;
	int sign;
	int *num;

}memb[3];
