/******************************************************************************************
* Data Structures in C++ -- 散列表ADT接口
* 丁酉鸡年七月 2017/9/8 10:00
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
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
	Entry<K, V> **ht; // 桶数组，存放词条指针
	int M; // 容量
	int N; // 真实数目
	Bitmap* lazyRemoval; // 惰性删除标记
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))
protected:
	int probe4Hit(const K& k); // 沿查找链查找词条对应的桶
	int probe4Free(const K& k); // 沿查找链查找空桶
	void rehash(); // 再散列，扩充容量，维持装填因子
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
int HashTable<K, V>::probe4Hit(const K& k) // 现在是只采用惰性删除的策略
{
	int index = hash(k,M);
	while (ht[index])
	{
		if (ht[index]->key == k && !lazilyRemoved(index)) // 如果命中且没有被删除
			break;
		index = hash(++index, M);
	}
	return index;
}

template <typename K, typename V>
int HashTable<K, V>::probe4Free(const K& k) // 现在是只采用惰性删除的策略
{
	int index = hash(k, M);
	while (ht[index] && !lazilyRemoved(index)) // 要管惰性删除标志
		index = hash(++index, M);
	return index;
}

/******************************************************************************************
 * 重散列算法：装填因子过大时，采取“逐一取出再插入”的朴素策略，对桶数组扩容
 * 丌可简单地（通过memcpy()）将原桶数组复刢刡新桶数组（比如前端），否则存在两个问题：
 * 1）会继承原有冲突；2）可能寻致查找链在后端断裂——即便为所有扩充桶讴置懒惰初除标志也无济亍事
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
	memset(ht, 0, M * sizeof(Entry<K, V>*)); //  初始化桶单元
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
	if (ht[index]) return false; // 不能雷同
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
	markAsRemoved(index); // 惰性删除，不是真的删除
	--N;
	return true;
}