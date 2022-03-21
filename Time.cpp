#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<time.h>
#include <ctime>
#include<pthread.h>

using namespace std;
void * Time(void *x)
{
	time_t t1 = time(0);
	char* t2 = ctime(&t1);
	cout << "Current Date and Time: " << t2 << endl;
	tm *gmt_time = gmtime(&t1);
	return NULL;
}
