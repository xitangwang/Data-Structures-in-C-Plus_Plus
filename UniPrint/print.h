/******************************************************************************************
* Data Structures in C++ -- 数据元素、数据结构通用输出接口
* 丁酉鸡年正月 2017/2/26 10:20
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include<stdio.h>
#include <typeinfo>
#include "../BinTree/BinTree.h"

template <typename T> static void print(T* x) { x ? print(*x) : print(" <NULL>"); }
template <typename T> static void print(T & x) { UniPrint::p(x); }
template <typename T> static void print(const T& x) { UniPrint::p(x); } // for Stack
static void print(char * x) { printf(" %s", x ? x : "<NULL> "); }
static void print(const char* x) { printf("%s", x ? x : "<NULL>"); }

class UniPrint
{
public:
	static void p(int);
	static void p(float);
	static void p(double);
	static void p(char);


	template<typename T> static void p(T&); // 向量、列表等支持tracerse()遍历结构的线性结构
	template<typename T> static void p(T* s) // 所有指针
	{
		s ? p(*s) : print("<NULL>"); // 统一转为引用
	}
	template<typename T>static void p(BinNode<T> &);
	template<typename T>static void p(BinTree<T> & bt);
	/*
	template <typename T> static void p(BST<T>&); //BST
	template <typename T> static void p(AVL<T>&); //AVL
	template <typename T> static void p(RedBlack<T>&); //RedBlack
	template <typename T> static void p(Splay<T>&); //Splay
	template <typename T> static void p(Quadlist<T>&); //Quadlist
	template <typename K, typename V> static void p(Skiplist<K, V>&); //Skiplist
	template <typename K, typename V> static void p(Hashtable<K, V>&); //Hashtable
	template <typename T> static void p(PQ_List<T>&); //PQ_List
	template <typename T> static void p(PQ_ComplHeap<T>&); //PQ_ComplHeap
	template <typename T> static void p(PQ_LeftHeap<T>&); //PQ_LeftHeap
	template <typename Tv, typename Te> static void p(GraphMatrix<Tv, Te>&); //Graph
	*/
}; // UniPrint

inline void UniPrint::p(int e) { printf("%04d", e); }
inline void UniPrint::p(float e) { printf("%4.1f", e); }
inline void UniPrint::p(double e) { printf("%4.1f", e); }
inline void UniPrint::p(char e) { printf("%c", (31 < e) && (e < 128) ? e : '$'); }

template <typename T>
void UniPrint::p(T& s)
{
	printf("%s[%d]*%d:\n", typeid(s).name(), &s, s.size()); // 基本信息
	s.traverse(print);
	printf("\n");
}