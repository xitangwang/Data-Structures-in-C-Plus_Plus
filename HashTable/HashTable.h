/******************************************************************************************
* Data Structures in C++ -- ɢ�б�ADT�ӿ�
* ���ϼ������� 2017/9/8 10:00
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "../Dictionary/Dictionary.h"
#include "../Bitmap/Bitmap.h"
#include "../Entry/Entry.h"

#include <memory.h>
#include <cstring>

static size_t hashCode(char c) { return static_cast<size_t>(c); }
static size_t hashCode(int k) { return static_cast<size_t>(k); }
static size_t hashCode(long long i) { return static_cast<size_t>((i >> 32) + static_cast<int>(i)); }
static size_t hashCode(char s[])
{
	int h = 0;
	for(size_t n = strlen(s),i = 0;i < n;i++)
	{
		h = (h << 5) | (h >> 27); h += static_cast<int>(s[i]);
	}
	return static_cast<size_t>(h);
}

template <typename T>
static int hash(T key,int M)
{
	return hashCode(key) % M;
}

template <typename K,typename  V>
class HashTable : Dictionary<K,V>
{
private:
	Entry<K, V> **ht; // Ͱ���飬��Ŵ���ָ��
	int M; // ����
	int N; // ��ʵ��Ŀ
	Bitmap* lazyRemoval; // ����ɾ�����
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))
protected:
	int probe4Hit(const K& k); // �ز��������Ҵ�����Ӧ��Ͱ
	int probe4Free(const K& k); // �ز��������ҿ�Ͱ
	void rehash(); // ��ɢ�У�����������ά��װ������
	void initialize(int c);
public:
	HashTable(int c = 5);
	~HashTable();
	int size() const { return N; }
	bool put(K k, V v);
	V* get(K k);
	bool remove(K k);
};

template <typename K, typename V>
int HashTable<K, V>::probe4Hit(const K& k) // ������ֻ���ö���ɾ���Ĳ���
{
	int index = hash(k,M);
	while (ht[index])
	{
		if (ht[index]->key == k && !lazilyRemoved(index)) // ���������û�б�ɾ��
			break;
		index = hash(++index, M);
	}
	return index;
}

template <typename K, typename V>
int HashTable<K, V>::probe4Free(const K& k) // ������ֻ���ö���ɾ���Ĳ���
{
	int index = hash(k, M);
	while (ht[index] && !lazilyRemoved(index)) // Ҫ�ܶ���ɾ����־
		index = hash(++index, M);
	return index;
}

/******************************************************************************************
 * ��ɢ���㷨��װ�����ӹ���ʱ����ȡ����һȡ���ٲ��롱�����ز��ԣ���Ͱ��������
 * آ�ɼ򵥵أ�ͨ��memcpy()����ԭͰ���鸴�c�b��Ͱ���飨����ǰ�ˣ�����������������⣺
 * 1����̳�ԭ�г�ͻ��2������Ѱ�²������ں�˶��ѡ�������Ϊ��������Ͱک�����������־Ҳ�޼�ء��
 ******************************************************************************************/
template <typename K, typename V>
void HashTable<K, V>::rehash()
{
	int old_capacity = M; Entry<K, V>** old_ht = ht; Bitmap* old_lazyRemoval = lazyRemoval;
	initialize(M * 2);
	for (int i = 0; i < old_capacity; ++i)
	{
		if (old_ht[i] && !old_lazyRemoval->test(i))
			put(old_ht[i]->key, old_ht[i]->value);
	}
	release(old_ht);
}

template <typename K, typename V>
void HashTable<K, V>::initialize(int c)
{
	M = c;
	N = 0;
	ht = new Entry<K, V>*[M];
	memset(ht, 0, M * sizeof(Entry<K, V>*)); //  ��ʼ��Ͱ��Ԫ
	lazyRemoval = new Bitmap(M);
}

template <typename K, typename V>
HashTable<K, V>::HashTable(int c)
{
	initialize(c);
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
	for (int i = 0; i < M; ++i)
		if (ht[i]) 
			release(ht[i]);
	release(ht);
	release(lazyRemoval);
}

template <typename K, typename V>
bool HashTable<K, V>::put(K k, V v)
{
	int index = probe4Hit(k);
	if (ht[index]) return false; // ������ͬ
	index = probe4Free(k);
	ht[index] = new Entry<K,V>(k,v);
	++N;
	if (N * 2 > M) rehash();
	return true;
}

template <typename K, typename V>
V* HashTable<K, V>::get(K k)
{
	int index = probe4Hit(k);
	return ht[index] ? &ht[index]->value : NULL;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(K k)
{
	int index = probe4Hit(k);
	if (!ht[index])
		return false;
	markAsRemoved(index); // ����ɾ�����������ɾ��
	--N;
	return true;
}