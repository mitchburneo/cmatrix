#include "list.h"

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

bool isempty(Matrix * A)
{
	return (A->top == NULL);
}

void crt_matrix(Matrix * A, int n, int m)
{
	A->line = n;
	A->col = m;
	
	for (int i(0); i < A->line; i++)
	{
		Node * U = new Node;
		if (isempty(A))
		{
			A->top = U;
		}
		else
		{
			U->down = A->top->down;
			A->top->down = U;
		}
	}
	
	for (int j(0); j < A->col - 1; j++)
	{
		Node * GoLn = A->top, *GoCol = A->top;

		for (int burn(0); burn < j + 1; burn++)
		{
			GoCol = GoCol->right;
		}

		for (int i(0); i < A->line; i++)
		{

			Node * U = new Node;
			if (i == 0)
			{
				GoLn = A->top;
				for (int burn(0); burn < j; burn++)
				{
					GoLn = GoLn->right;
				}
				GoCol = U;
				GoLn->right = U;
			}
			else
			{
				GoLn = A->top;

				for (int burn(0); burn < j; burn++)
				{
					GoLn = GoLn->right;
				}

				for (int vlademar(0); vlademar < A->line - i; vlademar++)
				{
					GoLn = GoLn->down;
				}
				U->down = GoCol->down;
				GoCol->down = U;
				GoLn->right = U;
			}
		}
	}
	return;
}

void go_toline(Matrix * A, int i)
{
	A->cur = A->top;
	for (int vlademar(0); vlademar < i; vlademar++) A->cur = A->cur->down;
	return;
}

void go_tocol(Matrix * A, int j)
{
	A->cur = A->top;
	for (int burn(0); burn < j; burn++) A->cur = A->cur->right;
	return;
}

void write_value(Matrix * A, int c)
{
	A->cur->value = c;
	return;
}

void next_inline(Matrix * A)
{
	A->cur = A->cur->right;
	return;
}

int read_cur(Matrix * A)
{
	return A->cur->value;
}

int read_byindex(Matrix * A, int i, int j)
{
	go_toline(A, i - 1);
	for (int shesh(0); shesh < j - 1; shesh++)
		next_inline(A);

	return read_cur(A);
}

void write_cur(Matrix * A, int c)
{
	A->cur->value = c;
	return;
}

void write_byindex(Matrix * A, int c, int i, int j)
{
	if ((i < 1) || (i >(A->line)))
	{
		cout << "Incorrect line" << endl;
		return;
	}

	if ((j < 1) || (j >(A->col)))
	{
		cout << "Incorrect column" << endl;
		return;
	}
	cout << "Element " << read_byindex(A, i, j) << " (" << i << ", " << j << ")" << " replaced with new value ";
	go_toline(A, i - 1);
	for (int shesh(0); shesh < j - 1; shesh++)
		next_inline(A);
	write_cur(A, c);
	cout << read_byindex(A, i, j) << endl;
	return;
}

void add_col(Matrix * A)
{
	go_toline(A, 0);
	for (int j(0); j < A->col - 1; j++)
		next_inline(A);

	Node * GoLn = A->cur, *GoCol = A->cur;

	GoCol = GoCol->right;

	for (int i(0); i < A->line; i++)
	{

		Node * U = new Node;
		if (i == 0)
		{
			GoCol = U;
			GoLn->right = U;
		}
		else
		{
			GoLn = A->cur;

			for (int vlademar(0); vlademar < A->line - i; vlademar++)
			{
				GoLn = GoLn->down;
			}
			U->down = GoCol->down;
			GoCol->down = U;
			GoLn->right = U;
		}
	}
	A->col++;
	cout << "Column have been added, new dimention is " << A->line << " x " << A->col << endl;
	return;
}

void add_line(Matrix * A)
{
	go_toline(A, A->line - 1);

	Node * GoLn = A->cur, *GoCol = A->cur;
	GoLn = GoLn->down;

	for (int j(0); j < A->col; j++)
	{

		Node * U = new Node;
		if (j == 0)
		{
			GoLn = U;
			GoCol->down = U;
		}
		else
		{
			GoCol = A->cur;

			for (int vlademar(0); vlademar < A->col - j; vlademar++)
			{
				GoCol = GoCol->right;
			}
			U->right = GoLn->right;

			GoLn->right = U;

			GoCol->down = U;
		}
	}
	A->line++;
	cout << "Column have been added, new dimention is " << A->line << " x " << A->col << endl;
	return;
}

void free_mem(Matrix * A)
{
	Node * B;
	for (int i(0); i < A->line; i++)
	{
		A->cur = A->top;
		next_inline(A);
		for (int j(0); j < (A->col - 1); j++)
		{
			B = A->cur;
			next_inline(A);
			delete B;
		}

		B = A->top;
		A->top = A->top->down;
		delete B;
	}
	A->line = 0;
	A->col = 0;
	A->cur = A->top;
	return;
}

void write_tolog(Matrix * A)
{
	FILE *log = fopen(LOGFILENAME, "a+");

	if (log == NULL)
	{
		cout << "Error occuring creating log file" << endl;
		return;
	}

	for (int i(0); i < A->line; i++)
	{
		go_toline(A, i);
		for (int j(0); j < A->col; j++)
		{
			fprintf(log, "%4d", read_cur(A));
			next_inline(A);
		}
		putc('\n', log);
	}
	putc('\n', log);

	fclose(log);

	return;
}



void solution(Matrix * A)
{
	FILE *log = fopen(LOGFILENAME, "a+");

	if (log == NULL)
	{
		cout << "Error occuring creating log file" << endl;
		return;
	}

	bool check = false;
	int min = 0, line_index = 0, col_index = 0;
	for (int i(0); i < A->line; i++)
	{
		go_toline(A, i);
		for (int j(0); j < A->col; j++)
		{
			if (!check)
			{
				if (read_cur(A) == 0) check = 1;
			}
			else
			{
				if ((read_cur(A) > 0) && (min == 0))
				{
					min = read_cur(A);
					line_index = i + 1;
					col_index = j + 1;
				}
				else
				{
					if ((read_cur(A) > 0) && (read_cur(A) < min))
					{
						min = read_cur(A);
						line_index = i + 1;
						col_index = j + 1;
					}
				}
			}
			next_inline(A);
		}
	}
	fprintf(log, "======================================================\n");
	if (!check)
	{
		cout << "There\'s no zeros" << endl;
		fprintf(log, "There\'s no zeros\n");
	}
	else
	{
		if (min == 0) 
		{
			cout << "There\'s no positive after first zero" << endl;
			fprintf(log, "There\'s no positive after first zero\n"); 
		}
		else
		{
			cout << "Minimal element is " << min << "\nIts index is " << line_index << " line & " << col_index << " column" << endl;
			fprintf(log, "Minimal element is %i\nIts index is %i line & %i column\n", min, line_index, col_index);
		}
	}
	fprintf(log, "======================================================\n");
	putc('\n', log);
	fclose(log);
	return;
}

void print_value(Matrix * A)
{
	for (int i(0); i < A->line; i++)
	{
		go_toline(A, i);
		for (int j(0); j < A->col; j++)
		{
			printf("%4d", A->cur->value);
			next_inline(A);
		}
		cout << '\n';
	}
}