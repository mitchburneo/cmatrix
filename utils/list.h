/*//////////////////////////////////
Module Name: list.h		////
Author: Smirnov D.S., A-06-15	////
Date: 	May, 2016		////
*///////////////////////////////////
#pragma once

#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

using namespace std;

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

#ifndef LOGFILENAME
	#define LOGFILENAME "logs"
#endif

struct Node
{
	int value = 0;
	Node * right = NULL;
	Node * down = NULL;
};

struct Matrix
{
	Node * top = NULL;
	Node * cur = top;

	int line = 0;
	int col = 0;
};

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

bool isempty(Matrix * A);

void crt_matrix(Matrix * A, int n, int m);

void go_toline(Matrix * A, int i);

void go_tocol(Matrix * A, int j);

void write_value(Matrix * A, int c);

void next_inline(Matrix * A);

int read_cur(Matrix * A);

int read_byindex(Matrix * A, int i, int j);

void write_cur(Matrix * A, int c);

void write_byindex(Matrix * A, int c, int i, int j);

void add_col(Matrix * A);

void add_line(Matrix * A);

void free_mem(Matrix * A);

void write_tolog(Matrix * A);

void solution(Matrix * A);

void print_value(Matrix * A);
