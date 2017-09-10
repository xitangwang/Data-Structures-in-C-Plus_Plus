#include"String.h"
#include<iostream>

using namespace std;

void main()
{
	char P[] = "CHINCHILLA";
	int* next = buildNext(P);
	for (size_t i = 0; i < strlen(P); i++)
	{
		cout << "[" << next[i] << "] ";
	}
	cin.get();
}