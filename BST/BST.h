/******************************************************************************************
* Data Structures in C++ -- ����������ADT�ӿڣ�binary serach tree)
* ���ϼ������� 2017/4/7 23:03
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "../BinTree/BinTree.h"

template <typename K,typename V> struct Entry // ����ģ����
{
	K key;V value; // �ؼ��롢��ֵ
	Entry(K k = K(), V v = V()) :key(k), value(v) {}; // Ĭ�Ϲ��캯��
	Entry(Entry<K, V> const & e) :key(e.key), value(e.value) {}; // ��¡
// �Ƚ������е������Ӵˣ������ϸ����ִ��������Ӧ�Ĺؼ��룩
	bool operator< (Entry<K, V> const & e) { return key < e.key; } // С��
	bool operator> (Entry<K, V> const & e) { return key > e.key; } // ����
	bool operator==(Entry<K, V> const & e) { return key == e.key; } // ����
	bool operator!=(Entry<K, V> const & e) { return key != e.key; } // ����
};

template <typename T> class BST : public BinTree<T> // ��BinTree����
{
public: // ��virtual���Σ��Ա���������д
	virtual BinNodePosi(T) & search(const T &); // ����
	virtual BinNodePosi(T) insert(const T &); // ����
	virtual bool remove(const T &); // ɾ��

protected:
	BinNodePosi(T) _hot; // ���нڵ�ĸ���
	BinNodePosi(T) connect34( // 3 + 4 �ع�
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T)
	);
	BinNodePosi(T) rotateAt(BinNodePosi(T)); // ��ת����
};