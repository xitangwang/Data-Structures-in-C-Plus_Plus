/******************************************************************************************
* Data Structures in C++ -- StackShuffle
* 丙申猴年腊月廿八 2017/1/25 17:56
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"Stack@list.h"
#include "../_share/rand.h"

template<typename T>
int shuffle(Stack<T>& A,Stack<T>& S)
{
	Stack<T> B;
	int num = 0;
	while(!(A.empty() && B.empty()))
	{
		if (!A.empty() && (90 < dice(100)))
			B.push(A.pop());
		else if (!B.empty())
			S.push(B.pop());
		++num;
	}
	return num;
}