/******************************************************************************************
* Data Structures in C++ -- BinTree 模板类
* 丁酉鸡年二月 2017/3/16 00:01
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "BinNode.h"
#include "../stack/Stack@list.h"
#include <stack>
#include "../Queue/Queue.h"

template <typename T> class BinTree
{
protected:
	int _size;
	BinNodePosi(T) _root;
	virtual int updateHeight(BinNodePosi(T) x);
	void updateHeightAbove(BinNodePosi(T) x);

public:
	BinTree() :_size(0), _root(nullptr) {  }
	~BinTree() { if (0 < _size) remove(_root); }
	int size() const { return _size; }
	bool empty() const { return !_root; }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const & e);
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const & e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const & e);
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S);
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S);
	int remove(BinNodePosi(T) x);
	//将子树x从当前树中移除
	BinTree<T>* secede(BinNodePosi(T) x);

	//树的遍历
	template <typename VST>
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }
	template <typename VST>
	void travPre(VST& visit) { if (_root) _root->travPre(visit); }
	template <typename VST>
	void travIn(VST& visit) { if (_root) _root->travIn(visit); }
	template <typename VST>
	void travPost(VST& visit) { if (_root) _root->travPost(visit); }

	//比较器、判等器
	bool operator<(BinTree<T> const& t) { return _root && t._root && lt(_root, t._root); }
	bool operator==(BinTree<T> const& t) { return _root && t._root && (_root == t._root); }

private:
};

template <typename T>
T max(T l, T r)
{
	if (l > r)
		return l;
	else
		return r;
}

//高度更新
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	int height = 0, lastHeight = 0;
	while (x)
	{
		lastHeight = updateHeight(x);
		if (height == lastHeight)
			break;
		height = lastHeight;
		x = x->parent;
	}
}
//O(depth(x))

//节点插入
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const & e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const & e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const & e)
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}

//子树接入
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>*& S)
{
	if ((x->lChild = S->_root))
		x->lChild->parent = x;
	_size += S->_size;updateHeightAbove(x);
	S->_root = nullptr;S->_size = 0;release(S);S = nullptr;
	return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNode<T>* x, BinTree<T>*& S)
{
	if ((x->lChild = S->_root))
		x->rChild->parent = x;
	_size += S->_size;updateHeightAbove(x);
	S->_root = nullptr;S->_size = 0;release(S);S = nullptr;
	return x;
}

//子树移除
template <typename T>
int BinTree<T>::remove(BinNode<T>* x)
{
	FromParentTo(*x) = nullptr;
	updateHeightAbove(x->parent);
	int n = removeAt(x);_size -= n;return n;
}

//O(release) * O(x->_size)
template<typename T>
static int  removeAt(BinNodePosi(T) x)
{
	if (!x) return 0;
	int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);
	release(x->data);release(x);return n;
}

//子树分离	O(depth(x))
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNode<T>* x)
{
	FromParentTo(*x) = nullptr;
	updateHeightAbove(x->parent);
	BinTree<T> * S = new BinTree<T>;S->_root = x;x->parent = nullptr;
	S->_size = x->size();_size -= S->_size;return S;
}

//递归遍历	T(n) = O(1) + T(a) + T(n - a -1) = O(n)但是递归方法空间复杂度较大会耗费大量资源，到一定运算量时就会到达瓶颈
template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit)
{
	if (!x)return;
	visit(x->data);
	travPre_R(x->lChild, visit);
	travPre_R(x->rChild, visit);
}

template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit)
{
	if (!x)return;
	travPost_R(x->lChild, visit);
	travPost_R(x->rChild, visit);
	visit(x->data);
}

template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit)
{
	if (!x)return;
	travIn_R(x->lChild, visit);
	visit(x->data);
	travIn_R(x->rChild, visit);
}

//迭代遍历	O(_size)
template <typename T, typename VST>
void travPre_L(BinNodePosi(T) x, VST& visit)
{
	if (!x)return;
	while (true)
	{
		Stack < BinNodePosi(T)> nodeStack;
		if (x)
			nodeStack.push(x);
		while (!nodeStack.empty())
		{
			x = nodeStack.pop();
			visit(x->data);
			if (HasRChild(*x))
				nodeStack.push(x->rChild);
			if (HasLChild(*x))
				nodeStack.push(x->rChild);
		}
	}
}

//遍历左节点的例程
template <typename T, typename VST>
void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)> & stack)
{
	while (x)
	{
		visit(x->data);
		stack.push(x->rChild);
		x = x->lChild;
	}
}

template <typename T, typename VST>
void travPre_L2(BinNodePosi(T) x, VST& visit)
{
	if (!x)return;
	Stack<BinNodePosi(T)> stack;stack.push(x);
	while (!stack.empty())
	{
		x = stack.pop();
		visitAlongLeftBranch(x, visit, stack);
	}
}

template <typename T, typename VST>
void goAlongLeftBranck(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)> stack)
{
	while (x)
	{
		stack.push(x);
		x = x->lChild;
	}
}

template <typename T, typename VST>
void travIn_L(BinNodePosi(T) x, VST& visit)
{
	if (!x)return;
	Stack<BinNodePosi(T)> stack;
	while (true)
	{
		goAlongLeftBranck(x, visit, stack);
		if (stack.empty())
			break;
		x = stack.pop();
		visit(x->data);
		x = x->rChild;
	}
}

template <typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST& visit) // 二叉树中序遍历（#迭代3，无需辅助栈）
{
	bool backtrack = false; // 前一步是否刚从右子树回溯——省去栈，仅O(1)辅助空间
	while (true)
	{
		if (!backtrack && HasLChild(*x))
		{
			x = x->lChild;
		}
		else
		{
			visit(x->data);
		}
		if (HasRChild(*x))
		{
			x = x->rChild;
			backtrack = false;
		}
		else
		{
			if (!(x = x->succ()))
				break;
			backtrack = true;
		}
	}
}

template <typename T, typename  VST>
void travLevel_L(BinNodePosi(T) x, VST& visit)
{
	if (!x)return;
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(x);
	while (!Q.empty())
	{
		x = Q.dequeue();visit(x->data);
		if (HasLChild(*x)) Q.enqueue(x->lChild);
		if (HasRChild(*x)) Q.enqueue(x->rChild);
	}
}