/******************************************************************************************
* Data Structures in C++ -- Skiplist ADTģ��
* ���ϼ��������� 2017/8/12 8:06
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/


#pragma once

#include "../List/List.h"
#include "../Entry/Entry.h"
#include "Quadlist.h" 
#include "../Dictionary/Dictionary.h"

template <typename K,typename V> 
class Skiplist : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*>
{
protected:
	bool skipSearch(ListNode<Quadlist<Entry<K, V>>*>* &qlist,
		QuadlistNode<Entry<K, V>>* &p,
		K & k);

public:
	int size() const { return empty() ? 0 : last()->data->size(); } // �ײ�Quadlist�Ĺ�ģ
	int level() { return List<Quadlist<Entry<K, V>>*>::size(); }
	bool put(K, V);
	V* get(K k);
	bool remove(K k);
};

template<typename K, typename V>
inline bool Skiplist<K, V>::put(K k, V v)
{
	Entry<K, V> e = Entry<K, V>(k, v);
	if (empty()) insertAsFirst(new Quadlist<Entry<K, V>>); // �����׸�Entry
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();
	QuadlistNode<Entry<K, V>>* p = qlist->data->first();
	if (skipSearch(qlist, p, k))
		while (p->below) p = p->below;
	qlist = last();
	QuadlistNode<Entry<K, V>>* b = qlist->data->insertAfterAbove(e, p);
	while (rand() & 1) //��Ͷ��Ӳ�ң���ȷ��������Ҫ�ٳ���һ�֣���
	{
		while (qlist->data->valid(p) && !p->above) p = p->pred;
		if (!qlist->data->valid(p))
		{
			if (qlist == first())
				insertAsFirst(new Quadlist<Entry<K, V>>);
			p = qlist->pred->data->first()->pred;
		}
		else
		{
			p = p->above;
		}
		qlist = qlist->pred;
		b = qlist->data->insertAfterAbove(e, p, b);
	} 
	return true; // Dictionary�����ظ�Ԫ�أ��ʲ���سɹ���������Hashtable��Map�Ĳ��Բ�ͬ
}



template<typename K, typename V>
inline V * Skiplist<K, V>::get(K k)
{
	if (empty()) return nullptr;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();
	QuadlistNode<Entry<K, V>>* p = qlist->data->first();
	return skipSearch(qlist, p, k) ? (p->entry.value) : nullptr; //���Ҳ�����
} // �ж������ʱ��������

template <typename K, typename V> bool Skiplist<K, V>::skipSearch(
	ListNode<Quadlist<Entry<K, V>>*>* &qlist, // 
	QuadlistNode<Entry<K, V>>* &p,
	K& k) 
{
	while (true) // ��ÿһ��
	{
		while (p->succ && (p->entry.key <= k)) //��ǰ������,ֱ�����ָ����key�������trailer
			p = p->succ;
		p = p->pred;
		if (p->pred && (k == p->entry.key))
			return true;// ����
		qlist = qlist->succ; // ����ת����һ��
		if (!qlist->succ)
			return false; // �����ײ㣬��ʧ��
		p = (p->pred) ? p->below : qlist->data->first();
	}
}

template <typename K, typename V>
bool Skiplist<K, V>::remove(K k)
{
	if (empty()) return false;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first();
	QuadlistNode<Entry<K, V>>* p = qlist->data->first();
	if (!skipSearch(qlist, p, k)) return false;
	do
	{
		QuadlistNode< Entry<K, V >>* lower = p->below;
		qlist->data->remove(p);
		p = lower; qlist = qlist->succ;
	} while (qlist->succ);
	while (!empty() && first()->data->empty())
		List<Quadlist<Entry<K, V>>*>::remove(first());
	return true;
}             