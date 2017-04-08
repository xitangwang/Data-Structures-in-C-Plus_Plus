/******************************************************************************************
* Data Structures in C++ -- 二叉搜索树ADT接口（binary serach tree)
* 丁酉鸡年三月 2017/4/7 23:03
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "../BinTree/BinTree.h"

template <typename K,typename V> struct Entry // 词条模板类
{
	K key;V value; // 关键码、数值
	Entry(K k = K(), V v = V()) :key(k), value(v) {}; // 默认构造函数
	Entry(Entry<K, V> const & e) :key(e.key), value(e.value) {}; // 克隆
// 比较器、判等器（从此，不必严格区分词条及其对应的关键码）
	bool operator< (Entry<K, V> const & e) { return key < e.key; } // 小于
	bool operator> (Entry<K, V> const & e) { return key > e.key; } // 大于
	bool operator==(Entry<K, V> const & e) { return key == e.key; } // 等于
	bool operator!=(Entry<K, V> const & e) { return key != e.key; } // 不等
};

template <typename T> class BST : public BinTree<T> // 由BinTree派生
{
public: // 以virtual修饰，以便派生类重写
	virtual BinNodePosi(T) & search(const T &); // 查找
	virtual BinNodePosi(T) insert(const T &); // 插入
	virtual bool remove(const T &); // 删除

protected:
	BinNodePosi(T) _hot; // 命中节点的父亲
	BinNodePosi(T) connect34( // 3 + 4 重构
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T)
	);
	BinNodePosi(T) rotateAt(BinNodePosi(T)); // 旋转调整
};