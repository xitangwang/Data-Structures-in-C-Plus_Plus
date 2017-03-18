
#include<iostream>

const int N = 64;

using namespace std;

//普通递归版本
__int64 fib_01(__int64 n)
{
	return (n <= 2) ? 1 : (fib_01(n - 1) + fib_01(n - 2));
}

//迭代版本
__int64 fib_02(__int64 n)
{
	__int64 one = 1,tow = 0;
	while (0 < n--)
	{
		tow += one;
		one = tow - one;
	}
	return tow;
}

int main()
{
	cout << "********************迭代版本*********************" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << "fib(" << i << ") = " << fib_02(i) << endl;
	}
	cout << "********************递归版本*********************" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << "fib(" << i << ") = " << fib_01(i) << endl;
	}

	system("pause");
}

