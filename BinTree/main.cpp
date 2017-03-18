/******************************************************************************************
* Data Structures in C++ -- BinTree 测试用例
* 丁酉鸡年二月 2017/3/17 21:14
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"BinTree_test.h"
#include "../vector/vector.h"

int testID = 0;

// 随机生成期望高度为h的二叉树
template <typename T> bool randomBinTree(BinTree<T> & bt,BinNodePosi(T) x,int h)
{
	if (0 >= h) return false; //至多h层
	if (0 < dice(h)) //以1/h的概率终止当前分支的生长
		randomBinTree(bt, bt.insertAsLC(x, dice((T)h * h * h)), h - 1);
	if (0 < dice(h)) //以1/h的概率终止当前分支的生长
		randomBinTree(bt, bt.insertAsRC(x, dice((T)h * h * h)), h - 1);
	return true;
}

// 在二叉树中随机确定一个点的位置
template <typename T> BinNodePosi(T) randomPosiInBinTree(BinNodePosi(T) root)
{
	if (!HasChild(*root)) return root;
	if (!HasLChild(*root))
		return dice(6) ? randomPosiInBinTree(root->rChild) : root;
	if (!HasRChild(*root))
		return dice(6) ? randomPosiInBinTree(root->lChild) : root;
	return dice(2) ?
		randomPosiInBinTree(root->lChild) :
		randomPosiInBinTree(root->rChild) ;
}

template <typename T>void testBinTree(int h) // 测试二叉树
{
	printf("\n ==== Test %2d.Generate a binTree of height <= %d \n", testID++, h);
	BinTree<T> bt;print(bt);print(bt);
	bt.insertAsRoot(dice(static_cast<T>(h) * h * h));print(bt);
	randomBinTree(bt, bt.root(), h);print(bt);
	printf("\n ==== Test %2d.Double and insrease all nodes by traversal\n", testID++);
	bt.travPre(Double<T>());bt.travPre(Increase<T>());print(bt);
	bt.travIn(Double<T>());bt.travIn(Increase<T>());print(bt);
	bt.travPost(Double<T>());bt.travPost(Increase<T>());print(bt);
	bt.travLevel(Double<T>());bt.travLevel(Increase<T>());print(bt);
	Hailstone<T> he;bt.travIn(he);print(bt);
	printf("\n ==== Test %2d.Remove/release subtrees in the Tree\n",testID++);
	while (!bt.empty())
	{
		BinNodePosi(T) p = randomPosiInBinTree(bt.root());
		if(dice(2))
		{
			printf("removing ");print(p->data);printf("...\n");
			printf("%d node(s) removed\n", bt.remove(p));print(bt);
		}
		else
		{
			printf("releasing ");print(p->data);printf("...\n");
			BinTree<T>* S = bt.secede(p);print(S);
			printf("%d node(s) released\n", S->size());release(S);print(bt);
		}
	}
}

int main(int argc,char* argv[])
{
	if (2 > argc) { printf("Usage:%s <size of test>\a\a\n", argv[0]);return 1; }
	srand(static_cast<unsigned int>(time(nullptr)));
	testBinTree<int>(atoi(argv[1]));
	return 0;
}