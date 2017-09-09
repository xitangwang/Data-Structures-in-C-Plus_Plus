#include "vector.h"
#include<iostream>

using namespace std;

void main() 
{
	Vector<int> *v = new Vector<int>();
	v->insert(5);
	v->insert(4);
	v->insert(3);
	v->insert(2);
	v->insert(1);
	v->heapSort();

	for (int i = 0; i < v->size(); i++)
	{
		cout << v->operator[](i) << endl;
	}
}
