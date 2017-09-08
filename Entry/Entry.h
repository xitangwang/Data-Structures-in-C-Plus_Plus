/******************************************************************************************
* Data Structures in C++ -- Entry 
* ���ϼ��������� 2017/8/12 7:59
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

template <typename K,typename V>
struct Entry
{
	K key;V value;
	Entry(K k = K(), V v = V()) : key(k), value(v) {};
	Entry(Entry<K, V> const& e) : ley(e.key), value(e.value) {};
	bool operator< (Entry<K, V> const& e) {return key < e.key;}
	bool operator> (Entry<K, V> const& e) {return key > e.key;}
	bool operator== (Entry<K, V> const& e) {return key == e.key;}
	bool operator!= (Entry<K, V> const& e) {return key != e.key;}
}; // �����ڱȽ������е������Ӵ����󣬲����ϸ����ִ��������Ӧ�Ĺؼ���

