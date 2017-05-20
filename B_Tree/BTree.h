/******************************************************************************************
* Data Structures in C++ -- BTree ADT�ӿ�
* ���ϼ������� 2017/5/20 : 16:56
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"../vector/vector.h"
#include "../_share/release.h"

#define BTNodePosi(T) BTNode<T>*

template <typename T> struct BTNode
{
	BTNodePosi(T) parent; // ���ڵ�
	Vector<T> key; // �ؼ�������
	Vector<BTNodePosi(T)> child; // �����������䳤���ܱ�key ��һ�㣩
	// ���캯����ע�⣺BTNodeֻ����Ϊ���ڵ㴴�������ҳ�ʼ��ʱ��0���ؼ����1���պ���ָ�룩
	BTNode() { parent = nullptr;child.insert(0, nullptr); }
	BTNode(T e,BTNodePosi(T) lc = nullptr,BTNodePosi(T) rc = nullptr)
	{
		parent = nullptr; // ��Ϊ���ڵ㣬���ҳ�ʼʱ
		key.insert(0, e); // ֻ��һ���ؼ��룬�Լ�
		child.insert(0, lc);child.insert(1, rc); // ��������
		if (lc) lc->parent = this;if (rc) rc->parent = this;
	}
};

template <typename T> 
class BTree // BTreeģ����
{
protected:
	int _size; // ��Źؼ�������
	int _order; // B-���Ľ״Σ�����Ϊ��--����ʱָ��
	BTNodePosi(T) _root; // ���ڵ�
	BTNodePosi(T) _hot; // BTree::search()�����ʵķǿգ��������գ��Ľڵ�λ��
	void solveOVerflow(BTNodePosi(T) ); // ����������֮��ķ��Ѵ���
	void solveUnderflow(BTNodePosi(T)); // ��ɾ��������֮��ĺϲ�����
public:
	BTree(int order = 3):_order(order),_size(0)
	{
		_root = new BTNode<T>();
	}

	~BTree()
	{
		if (_root)
			release(_root);
	}

	int const order() { return _order; } // �״�

	int const size() { return _size; } // ��ģ

	BTNodePosi(T) & root() { return _root; } // ����
	
	bool empty() const { return !_root; } // �п�

	BTNodePosi(T) search(const T & e); // ����

	bool insert(const T & e); // ����

	bool remove(const T & e); // ɾ��
}; // BTree
