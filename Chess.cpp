#include<iostream>
#include<string>
#include<fstream>

using namespace std;
bool turn = true;
class Chess
{
public:
	string name;
	int player;
	int x1, x2;
	char y1, y2;
public:
	Chess()
	{
		name = " ";
		player = 0;
	}
	Chess(string s, int players)
	{
		name = s;
		player = players;
	}
	virtual void move(Chess *arr[][8], int y1, int x1, int y2, int x2) {};
	friend void printchessboard(Chess *arr[][8]);
	friend void LoadChessBoard(Chess *arr[][8]);
	friend void SaveChessBoard(Chess* arr[][8]);
	friend void NewChessBoard(Chess* arr[][8]);
	friend void WhitePromotion(Chess* arr[][8], int y1, int x1, int y2, int x2);
	friend void BlackPromotion(Chess* arr[][8], int y1, int x1, int y2, int x2);
};
class Pawn :public Chess
{
public:
	Pawn()
	{
		name = " ";
		player = 0;
	}
	Pawn(string s, int n)
	{
		name = s;
		player = n;
	}
	void move(Chess *arr[][8], int y1, int x1, int y2, int x2)
	{
		if (x1<8 && x1>-1 && y1<8 && y1>-1 && x2<8 && x2>-1 && y2<8 && y2>-1)
		{
			if (arr[x2][y2]->player != arr[x1][y1]->player)
			{
				if (arr[x1][y1]->player == 1)
				{
					if ((x2 == x1 - 1 && y2 == y1 && arr[x2][y2]->player == 0) || ((x2 == x1 - 2 && y2 == y1) && (x1 == 6) && (arr[x2 + 1][y2]->player == 0)) || (x2 == x1 - 1 && (y2 == y1 + 1 || y2 == y1 - 1) && arr[x2][y2]->player == 2))
					{
						if (x2 == 0)
						{
							WhitePromotion(arr, y1, x1, y2, x2);
							arr[x1][y1]->player = 0;
							arr[x1][y1]->name = " ";
							turn = false;
						}
						else
						{
							delete arr[x2][y2];
							arr[x2][y2] = new Pawn(arr[x1][y1]->name, arr[x1][y1]->player);
							arr[x1][y1]->player = 0;
							arr[x1][y1]->name = " ";
						}
					}
				}
				else if (arr[x1][y1]->player == 2)
				{
					if ((x2 == x1 + 1 && y2 == y1 && arr[x2][y2]->player == 0) || ((x2 == x1 + 2 && y2 == y1) && (arr[x2 - 1][y2]->player == 0) && x1 == 1) || (x2 == x1 + 1 && (y2 == y1 + 1 || y2 == y1 - 1) && arr[x2][y2]->player == 1))
					{
						if (x2 == 7)
						{
							BlackPromotion(arr, y1, x1, y2, x2);
							arr[x1][y1]->player = 0;
							arr[x1][y1]->name = " ";
							turn = true;
						}
						else
						{
							delete arr[x2][y2];
							arr[x2][y2] = new Pawn(arr[x1][y1]->name, arr[x1][y1]->player);
							arr[x1][y1]->player = 0;
							arr[x1][y1]->name = " ";
						}
					}
				}
			}
		}
	}
};

class Rook :public Chess
{
public:
	Rook()
	{
		name = " ";
		player = 0;
	}
	Rook(string s, int n)
	{
		name = s;
		player = n;
	}
	void move(Chess *arr[][8], int y1, int x1, int y2, int x2)
	{
		int inter = 0;
		if (x1<8 && x1>-1 && y1<8 && y1>-1 && x2<8 && x2>-1 && y2<8 && y2>-1)
		{
			if (arr[x2][y2]->player != arr[x1][y1]->player)
			{
				if ((x1 == x2 && (y2 > y1 || y2 < y1)) || (y1 == y2 && (x2<x1 || x2>x1)))
				{
					if (x1 == x2 && y2 > y1)
						for (int i = y1 + 1; i < y2; i++)
							if (arr[x1][i]->player != 0)
								inter = 1;
					if (x1 == x2 && y2 < y1)
						for (int i = y1 - 1; i > y2; i--)
							if (arr[x1][i]->player != 0)
								inter = 1;
					if (y1 == y2 && x2 < x1)
						for (int i = x1 - 1; i > x2; i--)
							if (arr[i][y1]->player != 0)
								inter = 1;
					if (y1 == y2 && x2 > x1)
						for (int i = x1 + 1; i < x2; i++)
							if (arr[i][y1]->player != 0)
								inter = 1;
					if (inter == 0)
					{
						delete arr[x2][y2];
						arr[x2][y2] = new Rook(arr[x1][y1]->name, arr[x1][y1]->player);
						arr[x1][y1]->player = 0;
						arr[x1][y1]->name = " ";
					}
				}
			}
		}
		inter = 0;
	}
};

class Bishop :public Chess
{
public:
	Bishop()
	{
		name = " ";
		player = 0;
	}
	Bishop(string s, int n)
	{
		name = s;
		player = n;
	}
	void move(Chess *arr[][8], int y1, int x1, int y2, int x2)
	{
		int abs1 = abs(x1 - x2), abs2 = abs(y1 - y2), inter = 0;
		if (x1<8 && x1>-1 && y1<8 && y1>-1 && x2<8 && x2>-1 && y2<8 && y2>-1)
		{
			if (arr[x2][y2]->player != arr[x1][y1]->player)
			{
				if (abs1 == abs2)
				{
					if (x1 < x2 && y1 < y2)
						for (int i = x1 + 1, j = y1 + 1; i < x2, j < y2; i++, j++)
							if (arr[i][j]->player != 0)
								inter = 1;
					if (x1 < x2 && y1 > y2)
						for (int i = x1 + 1, j = y1 - 1; i < x2, j>y2; i++, j--)
							if (arr[i][j]->player != 0)
								inter = 1;
					if (x1 > x2 && y1 < y2)
						for (int i = x1 - 1, j = y1 + 1; i > x2, j < y2; i--, j++)
							if (arr[i][j]->player != 0)
								inter = 1;
					if (x1 > x2 && y1 > y2)
						for (int i = x1 - 1, j = y1 - 1; i > x2, j > y2; i--, j--)
							if (arr[i][j]->player != 0)
								inter = 1;
					if (abs1 == 1 && abs2 == 1)
						inter = 0;
					if (inter == 0)
					{
						delete arr[x2][y2];
						arr[x2][y2] = new Bishop(arr[x1][y1]->name, arr[x1][y1]->player);
						arr[x1][y1]->player = 0;
						arr[x1][y1]->name = " ";
					}
				}
			}
			inter = 0;
		}
	}
};

class Knight :public Chess
{
public:
	Knight()
	{
		name = " ";
		player = 0;
	}
	Knight(string s, int n)
	{
		name = s;
		player = n;
	}
	void move(Chess *arr[][8], int y1, int x1, int y2, int x2)
	{
		int abs1 = abs(x1 - x2), abs2 = abs(y1 - y2);
		if (x1<8 && x1>-1 && y1<8 && y1>-1 && x2<8 && x2>-1 && y2<8 && y2>-1)
		{
			if (arr[x2][y2]->player != arr[x1][y1]->player)
			{
				if ((abs1 == 2 && abs2 == 1) || (abs1 == 1 && abs2 == 2))
				{
					delete arr[x2][y2];
					arr[x2][y2] = new Knight(arr[x1][y1]->name, arr[x1][y1]->player);
					arr[x1][y1]->player = 0;
					arr[x1][y1]->name = " ";
				}
			}
		}
	}
};

class Queen :public Chess
{
public:
	Queen()
	{
		name = " ";
		player = 0;
	}
	Queen(string s, int n)
	{
		name = s;
		player = n;
	}
	void move(Chess *arr[][8], int y1, int x1, int y2, int x2)
	{
		int abs1 = abs(x1 - x2), abs2 = abs(y1 - y2), inter = 0;
		if (x1<8 && x1>-1 && y1<8 && y1>-1 && x2<8 && x2>-1 && y2<8 && y2>-1)
		{
			if (arr[x2][y2]->player != arr[x1][y1]->player)
			{
				if ((x1 == x2 && (y2 > y1 || y2 < y1)) || (y1 == y2 && (x2<x1 || x2>x1)))
				{
					if (x1 == x2 && y2 > y1)
						for (int i = y1 + 1; i < y2; i++)
							if (arr[x1][i]->player != 0)
								inter = 1;
					if (x1 == x2 && y2 < y1)
						for (int i = y1 - 1; i > y2; i--)
							if (arr[x1][i]->player != 0)
								inter = 1;
					if (y1 == y2 && x2 < x1)
						for (int i = x1 - 1; i > x2; i--)
							if (arr[i][y1]->player != 0)
								inter = 1;
					if (y1 == y2 && x2 > x1)
						for (int i = x1 + 1; i < x2; i++)
							if (arr[i][y1]->player != 0)
								inter = 1;
					if (inter == 0)
					{
						delete arr[x2][y2];
						arr[x2][y2] = new Queen(arr[x1][y1]->name, arr[x1][y1]->player);
						arr[x1][y1]->player = 0;
						arr[x1][y1]->name = " ";
						inter = 0;
					}
				}
				if (abs1 == abs2)
				{
					if (x1 < x2 && y1 < y2)
						for (int i = x1 + 1, j = y1 + 1; i < x2, j < y2; i++, j++)
							if (arr[i][j]->player != 0)
								inter = 1;
					if (x1 < x2 && y1 > y2)
						for (int i = x1 + 1, j = y1 - 1; i < x2, j>y2; i++, j--)
							if (arr[i][j]->player != 0)
								inter = 1;
					if (x1 > x2 && y1 < y2)
						for (int i = x1 - 1, j = y1 + 1; i > x2, j < y2; i--, j++)
							if (arr[i][j]->player != 0)
								inter = 1;
					if (x1 > x2 && y1 > y2)
						for (int i = x1 - 1, j = y1 - 1; i > x2, j > y2; i--, j--)
							if (arr[i][j]->player != 0)
								inter = 1;
					if (abs1 == 1 && abs2 == 1)
						inter = 0;
					if (inter == 0)
					{
						delete arr[x2][y2];
						arr[x2][y2] = new Queen(arr[x1][y1]->name, arr[x1][y1]->player);
						arr[x1][y1]->player = 0;
						arr[x1][y1]->name = " ";
						inter = 0;
					}
				}
			}
		}
	}
};

class King :public Chess
{
public:
	King()
	{
		name = " ";
		player = 0;
	}
	King(string s, int n)
	{
		name = s;
		player = n;
	}
	void move(Chess *arr[][8], int y1, int x1, int y2, int x2)
	{
		if (x1<8 && x1>-1 && y1<8 && y1>-1 && x2<8 && x2>-1 && y2<8 && y2>-1)
		{
			if (arr[x1][y1]->player != arr[x1][y1]->player)
			{
				if ((x1 == x2 && (y2 == y1 + 1 || y2 == y1 - 1)) || (y1 == y2 && (x2 == x1 + 1 || x2 == x1 - 1)) || (x2 == x1 + 1 && y2 == y1 - 1) || (x2 == x1 + 1 && y2 == y1 + 1) || (x2 == x1 - 1 && y2 == y1 - 1) || (x2 == x1 - 1 && y2 == y1 + 1))
				{
					delete arr[x2][y2];
					arr[x2][y2] = new King(arr[x1][y1]->name, arr[x1][y1]->player);
					arr[x1][y1]->player = 0;
					arr[x1][y1]->name = " ";
				}
			}
		}
	}
};

void NewChessBoard(Chess *arr[][8])
{
	ifstream fin;
	fin.open("newchess.txt");
	if (!fin)
	{
		cout << "File not Found!" << endl;
	}
	else
	{
		char c;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++)
			{
				fin >> c;
				if (c == 'r')
					arr[i][j] = new Rook("r", 1);
				if (c == 'n')
					arr[i][j] = new Knight("n", 1);
				if (c == 'b')
					arr[i][j] = new Bishop("b", 1);
				if (c == 'q')
					arr[i][j] = new Queen("q", 1);
				if (c == 'k')
					arr[i][j] = new King("k", 1);
				if (c == 'R')
					arr[i][j] = new Rook("R", 2);
				if (c == 'N')
					arr[i][j] = new Knight("N", 2);
				if (c == 'B')
					arr[i][j] = new Bishop("B", 2);
				if (c == 'Q')
					arr[i][j] = new Queen("Q", 2);
				if (c == 'K')
					arr[i][j] = new King("K", 2);
				if (c == 'P')
					arr[i][j] = new Pawn("P", 2);
				if (c == 'p')
					arr[i][j] = new Pawn("p", 1);
				if (c == '.')
					arr[i][j] = new Chess(" ", 0);
			}
		}
	}
}
void printchessboard(Chess *arr[][8])
{
	for (int i = 0; i < 8; i++) {
		cout << i << " " << " |";
		for (int j = 0; j < 8; j++) {
			cout << "__" << arr[i][j]->name << "__" << "|";
		}
		cout << endl << endl;
	}
	cout << "     a" << "     b" << "     c" << "     d" << "     e" << "     f" << "     g" << "     h" << endl << endl << endl;
}
void LoadChessBoard(Chess *arr[][8])
{
	ifstream fin;
	fin.open("loadchess.txt");
	char c;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			fin >> c;
			if (c == 'r')
				arr[i][j] = new Rook("r", 1);
			if (c == 'n')
				arr[i][j] = new Knight("n", 1);
			if (c == 'b')
				arr[i][j] = new Bishop("b", 1);
			if (c == 'q')
				arr[i][j] = new Queen("q", 1);
			if (c == 'k')
				arr[i][j] = new King("k", 1);
			if (c == 'R')
				arr[i][j] = new Rook("R", 2);
			if (c == 'N')
				arr[i][j] = new Knight("N", 2);
			if (c == 'B')
				arr[i][j] = new Bishop("B", 2);
			if (c == 'Q')
				arr[i][j] = new Queen("Q", 2);
			if (c == 'K')
				arr[i][j] = new King("K", 2);
			if (c == 'P')
				arr[i][j] = new Pawn("P", 2);
			if (c == 'p')
				arr[i][j] = new Pawn("p", 1);
			if (c == '.')
				arr[i][j] = new Chess(" ", 0);
		}
	}
}
void SaveChessBoard(Chess *arr[][8])
{
	ofstream fout("loadchess.txt");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[i][j]->name == " ") {
				fout << ".";
			}
			else {
				fout << arr[i][j]->name;
			}
		}
		fout << endl;
	}
}
void WhitePromotion(Chess *arr[][8], int y1, int x1, int y2, int x2)
{
	char promo;
	cout << "Please Select Promotion Q)Queen R)Rook K)Knight B)Bishop : ";
	cin >> promo;
	if (promo == 'Q' || promo == 'q')
	{
		delete arr[x2][y2];
		arr[x2][y2] = new Queen("q", 1);
	}
	if (promo == 'R' || promo == 'r')
	{
		delete arr[x2][y2];
		arr[x2][y2] = new Rook("r", 1);
	}
	if (promo == 'K' || promo == 'k')
	{
		delete arr[x2][y2];
		arr[x2][y2] = new Knight("k", 1);
	}
	if (promo == 'B' || promo == 'b')
	{
		delete arr[x2][y2];
		arr[x2][y2] = new Bishop("b", 1);
	}
}
void BlackPromotion(Chess* arr[][8], int y1, int x1, int y2, int x2)
{
	char promo;
	cout << "Please Select Promotion Q)Queen R)Rook K)Knight B)Bishop : ";
	cin >> promo;
	if (promo == 'Q' || promo == 'q')
	{
		delete arr[x2][y2];
		arr[x2][y2] = new Queen("Q", 2);
	}
	if (promo == 'R' || promo == 'r')
	{
		delete arr[x2][y2];
		arr[x2][y2] = new Rook("R", 2);
	}
	if (promo == 'K' || promo == 'k')
	{
		delete arr[x2][y2];
		arr[x2][y2] = new Knight("N", 2);
	}
	if (promo == 'B' || promo == 'b')
	{
		delete arr[x2][y2];
		arr[x2][y2] = new Bishop("B", 2);
	}
}

