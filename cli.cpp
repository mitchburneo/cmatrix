/*//////////////////////////////////
Program Name: cmatrix_cli	////
Author: Smirnov D.S., A-06-15	////
Date: 	May, 2016		////
*///////////////////////////////////

#include <iostream>
#include <fstream>
#include <cstdio>

// #include "utils/list.h"
#include "utils/binfile.h" // TO USE binfile DATATYPE - UNCOMMENT binfile.h & COMMENT list.h

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

using namespace std;

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

#define ERROR_DATATYPE -1;
#define ERROR_ARGS -5;
#define ERROR_IO -10;

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

int main(int argc, char* argv[])
{
	ofstream fout;
	ifstream fin;

	/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

	char button;

	Matrix * Neo = new Matrix;

	/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

	if (argc < 2) {
		cout << "USAGE: " << argv[0] << " [PATH/TO/DATA_FILE]" << endl;
		return ERROR_ARGS;
	}

	/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
	// Read data: dimN, dimM and elements of matrix
	fin.open(argv[1]);
	if (!fin.is_open())
	{
		cout << "Error occuring opening data file" << endl;
		return ERROR_IO;
	}

	/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

	do
	{
		// Print menu
		cout << "=====================================================================" << endl;
		cout << 
		"N - create new matrix N x M\n" << 
		"P - print\n" << "F - free memory\n" << 
		"C - change single element by index\n" << 
		"I - change dimention by adding line/column of zeros\n" << 
		"S - solution\n" << 
		"E - exit\n" << 
		endl;
		// Read choice
		cout << "Your choice --> ";
		(cin >> button).get();
		cout << "=====================================================================" << endl;
		fflush(stdin);
		button = toupper(button);
		switch (button) 
		{
			case 'N':
			{
				if (!isempty(Neo))
				{
					char yn;
					cout << "Firstly, you should clear the memory\nDo you wanna clear now? (y/n) -> "; 
					(cin >> yn).get();
					yn = toupper(yn);
					if (yn == 'Y')
					{
						free_mem(Neo);
						cout << "Memory has been cleared" << endl;
					}
					else
						if (yn != 'N') cout << "There\'s no such a command" << endl;
					break;
				}

				fin.seekg(0);

				int n, m;

				fin >> n >> m;
				if ((n < 0) || (m < 0))
				{
					cout << "Incorrect dimentions\n";
					break;
				}
				crt_matrix(Neo, n, m);
				for (int i(0); i < n; i++)
				{
					int c = 0;
					go_toline(Neo, i);
					for (int j(0); j < m; j++)
					{
						fin >> c;
						write_value(Neo, c);
						next_inline(Neo);
					}
				}
				cout << "Matrix " << n << " x " << m << " has been created" << endl;
				write_tolog(Neo);
				break;
			}

		/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

			case 'P':
			{
				if (isempty(Neo))
				{
					cout << "Matrix is empty" << endl;
					break;
				}
				print_value(Neo);
				break;
			}

		/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

			case 'F':
			{
				if (!isempty(Neo))
				{
					free_mem(Neo);
					cout << "Memory has been cleared" << endl;
					break;
				}
				else
				{
					cout << "Matrix is empty" << endl;
					break;
				}
			}

		/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

			case 'C':
			{
				if (isempty(Neo))
				{
					cout << "Matrix is empty\nFirstly you should alloc memory" << endl;
					break;
				}
				cout << "Enter index of element (line and column)" << endl;

				int line, col;

				cout << "Line \t-> ";
				cin >> line;

				cout << "Column \t-> ";
				cin >> col;

				int c = 0;

				cout << "Enter value -> ";
				cin >> c;

				write_byindex(Neo, c, line, col);

				write_tolog(Neo);
				break;
			}

		/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

			case 'I':
			{
				if (isempty(Neo))
				{
					cout << "Matrix is empty\nFirstly you should alloc memory" << endl;
					break;
				}
				char w = 0;
				cout << "Add line (1) or add column (2)?" << endl;
				cout << "1 or 2 -> "; 
				(cin >> w).get();
				switch (w)
				{
					case '1':
					{

						add_line(Neo);
						write_tolog(Neo);
					break;
					}
					case '2':
					{
						add_col(Neo);
						write_tolog(Neo);
						break;
					}
					default: 
						cout << "There\'s no such command" << endl;
				}
				break;
			}

		/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

			case 'S':
			{
				if (isempty(Neo))
				{
					cout << "Matrix is empty" << endl;
					break;
				}
				write_tolog(Neo);
				solution(Neo);
				break;
			}

		/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

			case 'E':
			{
				if (!isempty(Neo)) free_mem(Neo);
				return 0;
			}

		/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

			default:
				cout << "There\'s no such command" << endl;
		}
	} while (button != 'E');

	// Clear memory
	free_mem(Neo);
	// Close data file
	fin.close();
	// Successful termination
	cout << "Follow the white rabbit..." << endl;
	return 0;
}
