#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <vector>
using namespace std::chrono;
using namespace std;

int Days(int day, int month, int year)
{
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	year -= month < 3;
	return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}

string Months(int Month_Number)
{
	string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	return (months[Month_Number]);
}

int No_Of_Days(int Month_Number, int year)
{
	if (Month_Number == 0)
		return (31);
	if (Month_Number == 1)
	{
		if (year % 400 == 0 ||
			(year % 4 == 0 && year % 100 != 0))
			return (29);
		else
			return (28);
	}
	if (Month_Number == 2)
		return (31);

	if (Month_Number == 3)
		return (30);

	if (Month_Number == 4)
		return (31);

	if (Month_Number == 5)
		return (30);

	if (Month_Number == 6)
		return (31);

	if (Month_Number == 7)
		return (31);

	if (Month_Number == 8)
		return (30);

	if (Month_Number == 9)
		return (31);

	if (Month_Number == 10)
		return (30);

	if (Month_Number == 11)
		return (31);
	return 0;
}

void *Display(void *x)
{
	int year;
	cout << "Enter the Year: ";
	cin >> year;
	cout << " Calendar " << year;
	int days;
	int current = Days(1, 1, year);

	for (int i = 0; i < 12; i++)
	{
		days = No_Of_Days(i, year);
		printf("\n  ------------%s-------------\n", Months(i).c_str());
		cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
		int k;
		for (k = 0; k < current; k++)
			cout << "     ";

		for (int j = 1; j <= days; j++)
		{
			printf("%5d", j);

			if (++k > 6)
			{
				k = 0;
				cout << endl;
			}
		}
		if (k)
			cout << endl;

		current = k;
	}
	return NULL;
}

void *Timer(void *t)
{
	//TIME
	vector<int> values(10000);
	auto f = []() -> int
	{ return rand() % 10000; };
	generate(values.begin(), values.end(), f);
	auto start = high_resolution_clock::now();
	sort(values.begin(), values.end());
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by this Process = " << duration.count() << " MicroSeconds" << endl;
	return NULL;
}

void *Scheduling_Algorithm(void *s)
{
	float BT[20], WT[20], TAT[20], Avg_WT = 0, Avg_TAT = 0;
	int n, i, j;
	cout << "Enter the Number of Processes: ";
	cin >> n;
	cout << endl
		 << "Enter the Burst Time" << endl;
	for (i = 0; i < n; i++)
	{
		cout << "P[" << i + 1 << "]: ";
		cin >> BT[i];
	}
	WT[0] = 0;

	for (i = 1; i < n; i++)
	{
		WT[i] = 0;
		for (j = 0; j < i; j++)
			WT[i] += BT[j];
	}
	cout << endl
		 << "Process  Burst-Time  Waiting-Time  Turnaround-Time" << endl;

	for (i = 0; i < n; i++)
	{
		TAT[i] = BT[i] + WT[i];
		Avg_WT += WT[i];
		Avg_TAT += TAT[i];
		cout << "  P[" << i + 1 << "] " << setw(8) << BT[i] << setw(14) << WT[i] << setw(14) << TAT[i] << endl;
	}

	Avg_WT /= i;
	Avg_TAT /= i;
	cout << endl;
	cout << "Average Waiting Time = " << Avg_WT << endl;
	cout << "Average Turnaround Time = " << Avg_TAT << endl;
	return NULL;
}
