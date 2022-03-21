#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <pthread.h>
#ifndef COLORS
#define COLORS
#define KRED "\x1B[31m"
#endif
#include "MinesweeperNewTerminal.cpp"
using namespace std;

void Reveal(int, int);
void Mine_Position();
void Cell(int i, int j);
void Board();
void Open_Cell();
void Game();
void Display(char arr[10][10]);
char board[10][10];
char mine_position[10][10];
char i;
int Flag_Counter = 0;
int Mines_Counter = 0;
bool Loose_Game = false;

void Cell(int i, int j)
{
	if (i >= 0 && i < 10 && j >= 0 && j < 10 && mine_position[i][j] != 'X')
	{
		mine_position[i][j]++;
	}
}

void Mine_Position()
{
	int c = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			mine_position[i][j] = '0';

	while (c < 10)
	{
		int i = rand() % 10;
		int j = rand() % 10;
		if (mine_position[i][j] == '0')
		{
			mine_position[i][j] = 'X';

			Cell(i - 1, j);
			Cell(i + 1, j);
			Cell(i, j - 1);
			Cell(i, j + 1);
			Cell(i - 1, j - 1);
			Cell(i - 1, j + 1);
			Cell(i + 1, j - 1);
			Cell(i + 1, j + 1);
			c++;
		}
	}
}

void Board()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			board[i][j] = '*';
		}
	}
}

void Display(char arr[10][10])
{
	cout << "    ";
	for (int i = 0; i < 10; i++)
		cout << setw(3) << i;

	cout << endl
		 << "  ";
	for (int i = 0; i < 32; i++)
		cout << "_";
	cout << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << setw(3) << i << "|";
		for (int j = 0; j < 10; j++)
			cout << setw(3) << arr[i][j];
		cout << endl;
	}
}

void Open_Cell()
{
	int i, j;
	do
	{
		cout << "Enter the value of i and j to Open Cell: " << endl;
		cin >> i >> j;
	} while (i < 0 || i > 9 || j < 0 || j > 9);

	if (mine_position[i][j] == 'X')
	{
		board[i][j] = 'X';
		Loose_Game = true;

		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (mine_position[i][j] == 'X')
					board[i][j] = 'X';
	}
	else
	{
		Reveal(i, j);
	}
}

void Place_OR_Remove_Flag()
{
	int i, j;
	do
	{
		cout << "Enter the value of i and j to Place or Remove Flag: " << endl;
		cin >> i >> j;
	} while (i < 0 || i > 9 || j < 0 || j > 9);

	if (board[i][j] == '*')
	{
		board[i][j] = 'F';
		Flag_Counter++;

		if (mine_position[i][j] == 'X')
			Mines_Counter++;
	}

	else if (board[i][j] == 'F')
	{
		board[i][j] = '*';
		Flag_Counter--;
		if (mine_position[i][j] == 'X')
			Mines_Counter--;
	}
}

void Input()
{
	cin >> i;
	switch (i)
	{
	case 's':
		Open_Cell();
		break;
	case 'f':
		Place_OR_Remove_Flag();
		break;
	default:
		Input();
	}
}

void Reveal(int i, int j)
{
	if (board[i][j] == '*' && mine_position[i][j] != 'X' && i >= 0 && i < 10 && j >= 0 && j < 10)
	{
		board[i][j] = mine_position[i][j];

		if (mine_position[i][j] == '0')
		{
			Reveal(i, j - 1);
			Reveal(i, j + 1);
			Reveal(i - 1, j - 1);
			Reveal(i + 1, j - 1);
			Reveal(i + 1, j + 1);
			Reveal(i - 1, j + 1);
			Reveal(i - 1, j);
			Reveal(i + 1, j);
		}
	}
}

bool Win_Check()
{
	if (Flag_Counter == 10 && Mines_Counter == 10)
		return 1;
	else
		return 0;
}

void Game()
{
	Board();
	Mine_Position();

	while (!Loose_Game && !Win_Check())
	{

		Display(board);
		cout << endl
			 << "Flags: " << Flag_Counter << endl;
		Input();
	}

	if (Loose_Game)
	{
		Display(board);
		cout << endl
			 << "Game Over" << endl;
		cout << endl
			 << "You Loose -_-" << endl;
	}

	else if (Win_Check())
	{
		cout << endl
			 << "You Win." << endl;
	}
}

void *Minesweeper(void *m)
{
	cout << KRED << "If you want to Run any other Process then press 1\e[0m" << endl;
	int n;
	cin >> n;
	if (n == 1)
	{
		system("g++ link.cpp -o mylinknew -lpthread");
		system("gnome-terminal -- \"./mylinknew\"");
	}
	cout << "Instructions:" << endl;
	cout << "Enter => s to Start the Game." << endl;
	cout << "Enter => f to Place or Remove Flag." << endl
		 << endl;
	Game();
	return NULL;
}
