#include<iostream>
#include <ctime>

void Menu();
int win(char Map[11][17]);
void print(char Map[11][17], int rows, int col);
void Lgeneration(char Map[11][17], int &a, int &b, int power);
void Mgeneration(char Map[11][17], int &e, int &f, int lives);
void setup(char Map[11][17], int &r, int &c, int &x, int &y, int &a, int &b, int &e, int &f);
void logic(char Map[11][17], int &x, int &y, int &a, int &b, int &power, int r, int c, int &e, int &f, int &lives);
int score = 0, Pcount = 0, lives = 3;
using namespace std;

void setup(char Map[11][17], int &r, int &c, int &x, int &y, int &a, int &b, int &e, int &f) 
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (j == 0 || j == c - 1 || i == 0 || i == r - 1)
			{
				Map[i][j] = 'O';
			}
			else if ((i == 2 && j >= 1 && j <= 5 || j == 5 && i >= 2 && i <= 3) || (i == 2 && j >= 7 && j <= 11 || j == 11 && i >= 2 && i <= 5) || (i >= 2 && i <= 4 && j == 13 || i == 4 && j >= 14 && j <= 16) || (i == 5 && j >= 1 && j <= 4 || j == 4 && i >= 6 && i <= 8 || i == 8 && j == 3) || (i == 5 && j >= 6 && j <= 9 || j == 8 && i >= 6 && i <= 8 || i == 8 && j >= 6 && j <= 11 || i == 7 && j == 6 || i == 7 && j == 11) || (i == 6 && j >= 13 && j <= 16 || j == 13 && i >= 6 && i <= 8 || i == 8 && j == 14))
			{
				Map[i][j] = 'O';
			}
			else {
				Map[i][j] = '.';
			}

		}
	}
	Map[x][y] = 'P';
	Map[a][b] = 'L';
	Map[e][f] = 'M';
}
void Menu()
{
	system("clear");
	int choose;
	cout << endl;
	cout << " ---------------------------" << endl;
	cout << " | Press W : To Move UP.   | " << endl;
	cout << " | Press S : To Move DOWN. | " << endl;
	cout << " | Press D : To Move RIGHT.| " << endl;
	cout << " | Press A : To Move LEFT. | " << endl;
	cout << " ---------------------------" ;
	cout << endl;
}
void logic(char Map[11][17], int &x, int &y, int &a, int &b, int &power, int r, int c, int &e, int &f, int &lives) {

	char key;
	cin>>key;

	if (key == 'w' || key == 'W')
	{
		if (Map[x - 1][y] != 'O')
		{
			if (Map[x - 1][y] == '.')
			{
				score = score + 10;
			}
			else if (Map[x - 1][y] == 'L')
			{
				score = score + 20;
				Lgeneration(Map, a, b, power);
			}
			else if (Map[x - 1][y] == 'M')
			{
				lives = lives - 1;
				Mgeneration(Map, e, f, lives);
			}
			Map[x - 1][y] = 'P';
			Map[x][y] = ' ';
			x--;
		}

	}
	else if (key == 's' || key == 'S')
	{
		if (Map[x + 1][y] != 'O')
		{
			if (Map[x + 1][y] == '.')
			{
				score = score + 10;
			}
			else if (Map[x + 1][y] == 'L')
			{
				score = score + 20;
				Lgeneration(Map, a, b, power);
			}
			else if (Map[x + 1][y] == 'M')
			{
				lives = lives - 1;
				Mgeneration(Map, e, f, lives);
			}
			Map[x + 1][y] = 'P';
			Map[x][y] = ' ';
			x++;
		}
	}
	else if (key == 'a' || key == 'A')
	{
		if (Map[x][y - 1] != 'O')
		{
			if (Map[x][y - 1] == '.')
			{
				score = score + 10;
			}
			else if (Map[x][y - 1] == 'L')
			{
				score = score + 20;
				Lgeneration(Map, a, b, power);
			}
			else if (Map[x][y - 1] == 'M')
			{
				lives = lives - 1;
				Mgeneration(Map, e, f, lives);
			}
			Map[x][y - 1] = 'P';
			Map[x][y] = ' ';
			y--;
		}
	}
	else if (key == 'd' || key == 'D')
	{
		if (Map[x][y + 1] != 'O')
		{
			if (Map[x][y + 1] == '.')
			{
				score = score + 10;
			}
			else if (Map[x][y + 1] == 'L')
			{
				score = score + 20;
				Lgeneration(Map, a, b, power);
			}
			else if (Map[x][y + 1] == 'M')
			{
				lives = lives - 1;
				Mgeneration(Map, e, f, lives);
			}
			Map[x][y + 1] = 'P';
			Map[x][y] = ' ';
			y++;
		}
	}

}
void Lgeneration(char Map[11][17], int &a, int &b, int power)
{
	int m = 0;
	if (Pcount < power&&win(Map) != 0)
	{
		do
		{
			a = rand() % 11 + 1;
			b = rand() % 17 + 1;

			if (Map[a][b] == '.')
			{

				Map[a][b] = 'L';
				m = 0;
			}
			else
			{
				m = 1;
			}
		} while (m == 1);
	}
	Pcount++;
}
void Mgeneration(char Map[11][17], int &e, int &f, int lives)
{
	int m = 0;
	if (Pcount <= lives && win(Map) != 0)
	{
		do
		{
			e = rand() % 11 + 1;
			f = rand() % 17 + 1;

			if (Map[e][f] == '.')
			{

				Map[e][f] = 'M';
				m = 0;
			}
			else
			{
				m = 1;
			}
		} while (m == 1);
	}
	lives--;
}

int win(char Map[11][17])
{
	if (lives == 0)
	{
		system("clear");
		cout << endl << endl << "\t" << "You lose !!! " << endl << endl;
		cout << "Your Score is : " << score << endl;
		return 0;
	}
	else
	{
		int count = 0;
		int x = 0;
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				if (Map[i][j] == '.' || Map[i][j] == 'L')
				{
					count++;
				}

				if (i == 10 && j == 16)
				{
					if (count == 0)
					{
						system("clear");
						cout << endl << endl << "\t" << "You Win !!! " << endl << endl;
						cout << "Your Score is : " << score << endl;
						return 0;
					}
					else
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
void print(char Map[11][17], int r, int c)
{
	cout << endl << endl;
	cout << "     Score : " << score << "               Lives : " << lives << endl;
	cout << "     -------------------------------------------------" << endl;
	for (int i = 0; i < r; i++)
	{
		cout << "     ";
		for (int j = 0; j < c; j++)
		{

			cout << Map[i][j];
			cout << "  ";
		}
		cout << endl << endl;
	}
}
