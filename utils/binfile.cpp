#include "binfile.h"

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

bool isempty(Matrix * A)
{
	if (A->bin == NULL)
	{
		return 1;
	}

	rewind(A->bin);

	if (sizeof(A->bin) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void crt_matrix(Matrix * A, int n, int m)
{
	if (remove(A->name) == 0) cout << "File have been removed" << endl;
	A->bin = fopen(A->name, "w+b");
	if (A->bin == NULL)
	{
		cout << "Error occuring creating file" << endl;
		return;
	}

	A->line = n;
	A->col = m;

	for (int i(0); i < (A->line)*(A->col); i++)
	{
		A->value = 0;
		fwrite(&A->value, sizeof(A->value), 1, A->bin);
	}
	return;
}

void go_toline(Matrix * A, int i)
{
	rewind(A->bin);
	for (int u(0); u < ((i)*A->col); u++)
	{
		fseek(A->bin, sizeof(A->value), SEEK_CUR);
	}

	return;
}

void go_tocol(Matrix * A, int j)
{
	rewind(A->bin);
	for (int u(0); u < (j); u++)
	{
		fseek(A->bin, sizeof(A->value), SEEK_CUR);
	}

	return;
}

void write_value(Matrix * A, int c)
{
	A->value = c;
	fwrite(&A->value, sizeof(A->value), 1, A->bin);
	fseek(A->bin, 0 - sizeof(A->value), SEEK_CUR);
	return;
}

void next_inline(Matrix * A)
{
	fseek(A->bin, sizeof(A->value), SEEK_CUR);
}

int read_cur(Matrix * A)
{	
	fread(&A->value, sizeof(A->value), 1, A->bin);
	fseek(A->bin, 0 - sizeof(A->value), SEEK_CUR);
	return A->value;
}

int read_byindex(Matrix * A, int i, int j)
{
	go_toline(A, i-1);

	for (int shesh(0); shesh < j-1; shesh++)
		next_inline(A);

	return read_cur(A);
}

void write_cur(Matrix * A, int c)
{
	A->value = c;
	fwrite(&A->value, sizeof(A->value), 1, A->bin);
	fseek(A->bin, 0 - sizeof(A->value), SEEK_CUR);
	return;
}

void write_byindex(Matrix * A, int c, int i, int j)
{
	
	if ((i < 1) || (i >(A->line)))
	{
		cout << "\nIncorrect line" << endl;;

		return;
	}

	if ((j < 1) || (j >(A->col)))
	{
		cout << "\nIncorrect column" << endl;
	
		return;
	}
	cout << "Element " << read_byindex(A, i, j) << " (" << i << ", " << j << ")" << " replaced with new value ";
	go_toline(A, i - 1);
	for (int shesh(0); shesh < j - 1; shesh++)
	{
		next_inline(A);
	}
	write_cur(A, c);
	cout << read_byindex(A, i, j) << endl;
	return;
}

void add_col(Matrix * A)
{
	fpos_t position;
	short int jump = 0;
	rewind(A->bin);
	for (int i(0); i < A->line; i++)
	{
		go_toline(A, i);
		for (int don(0); don < A->col + jump; don++)
			fseek(A->bin, sizeof(A->value), SEEK_CUR);
		for (int j(0); j < (A->line*A->col - (i + 1)*A->col) + 1; j++)
		{
			fgetpos(A->bin, &position);
			for (int shesh(0); shesh < (A->line*A->col - (i + 1)*A->col) - j; shesh++)
				{

					fseek(A->bin, sizeof(A->value), SEEK_CUR);

				}

			A->value = read_cur(A);
			next_inline(A);
			fwrite(&A->value, sizeof(A->value), 1, A->bin);
			fsetpos(A->bin, &position);
		}
		write_cur(A, 0);
		jump++;
	}
	A->col++;
	cout << "Column have been added, new dimention is " << A->line << " x " << A->col << endl;
	return;
}

void add_line(Matrix * A)
{
	rewind(A->bin);
	for (int shesh(0); shesh < A->line*A->col; shesh++)
		fseek(A->bin, sizeof(A->value), SEEK_CUR);
	for (int valdemar(0); valdemar < A->col; valdemar++)
	{
		write_value(A, 0);
		next_inline(A);
	}

	A->line++;
	cout << "Column have been added, new dimention is " << A->line << " x " << A->col << endl;

	return;
}

void free_mem(Matrix * A)
{
	fclose(A->bin);
	A->bin = NULL;
	A->line = 0;
	A->col = 0;

	remove(A->name);
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
	rewind(A->bin);

	for (int i(0); i < A->line; i++)
	{
		go_toline(A, i);
		for (int j(0); j < A->col; j++)
		{
			printf("%4d", read_cur(A));
			next_inline(A);
		}
		cout << '\n';
	}
	return;
}