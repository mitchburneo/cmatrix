/*////////////////////////////////
Module Name: Burn_LAB11	      ////
Author: Smirnov D.S., A-06    ////
*///////////////////////////////// 
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdio>
#include <stdio.h>
#include <windows.h>

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

using namespace std;

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

struct Elm
{
	int value = 0;
	Elm * right = NULL;
	Elm * down = NULL;
};

struct Matrix
{
	Elm * top = NULL;
	Elm * cur = top;

	int line = 0;
	int col = 0;
};

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
