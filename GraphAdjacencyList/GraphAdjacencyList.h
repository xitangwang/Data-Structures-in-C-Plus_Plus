/******************************************************************************************
* Data Structures in C++ -- Graph ���ڽӱ�(adjacency matrix)ʵ��
* ���ϼ������� 2017/4/5 0��00
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "../vector/vector.h"
#include "../GraphMatrix/Graph.h"

/*
template <typename Tv> struct Vertex // �������Ϊ���������δ�ϸ��װ��
{
	Tv data;int inDegree, outDegree, VStatus, status; // ���ݣ����������״̬
	int dTime, fTime; // ʱ���ǩ
	int parent;int priority; // �ڱ������еĸ��ڵ㣬���ȼ���
	Vertex(Tv const& d = (Tv)0) :
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {	} // �ݲ�����Ȩ�����
};

template <typename Te> struct Edge // �߶���Ϊ���������δ�ϸ��װ��
{
	Te data;int weight;EType type; // ���ݣ�Ȩ�أ�����
	int v; // ��������
	Edge(Te const& d, int w,int v) :data(d), weight(w), type(UNETERMINED),v(v) {  } // ����
};

*/

template <typename Tv,typename Te> // �������͡�������
class GraphAdjacencyList : public Graph<Tv,Te>
{
private:
	Vector<Vertex<Tv>> V; // ���㼯��������
	Vector<List<Edge<Te>*>> E; // �߼����ڽӱ�

public:
	GraphAdjacencyList() { n = e = 0; }
	~GraphAdjacencyList()
	{
		
	}

// ����Ļ�����������ѯ��i������(0 <= n)
	virtual Tv& vertex(int i) { return V[i].data; } 
	virtual int inDegree(int i) { return V[i].inDegree; }
	virtual int outDegree(int i) { return V[i].outDegree; }
	virtual int firstNbr(int i) { return E[i][0].v;}
	virtual int nextNbr(int i,int j)
	{
		return E[i][++j].v;
	} // �ı�����һ���ھӵĽӿڣ����������㷨����Ҫ�ı�һ��
	virtual VStatus& status(int i) { return V[i].status; } // ״̬
	virtual int& dTime(int i) { return V[i].dTime; } // ʱ���ǩdTime
	virtual int& fTime(int i) { return V[i].fTime; } // ʱ���ǩfTime
	virtual int& parent(int i) { return V[i].parent; } // �ڱ������еĸ���
	virtual int& priority(int i) { return V[i].priority; } // �ڱ������е����ȼ���

// ����Ķ�̬����
	virtual int insert(Tv const& vertex) // 
	{
		E.insert(List<Edge<Te>*>()); // ����һ���ڽӱ�
		return V.insert(Vertex<Tv>(vertex));
	}

	virtual Tv remove(int i) // ɾ����i�����㼰�������( 0 <= i < n )
	{
		for(int j = 0;j < E[i].size();++j)
		{
			Edge<Te>* e = E[i].remove(j);
			delete e;V[i].inDegree--;--j;
		}
		for(int m = 0;m < E.size();++m)
		{
			for(int n = 0;n < E[m].size();++n)
			{
				if (E[m][n].v > i)
					E[m][n].v--;
				else if(E[m][n].v == i)
				{
					Edge<Te>* e = E[m].remove(n);
					delete e;V[m].inDegree--;--n;
				}
			}
		}
		Tv vBak = vertex(i);V.remove(i); // ɾ������i
		return vBak;
	}
// �ߵ�ȷ�ϲ���
	virtual bool exists(int i,int j) // 
	{
		for(int n = 0;i < E[i].size();++n)
		{
			if (E[i][n].v == j)
				return true;
		}
		return false;
	}

// �ߵĻ�����������ѯ����i��j֮�������( 0 <= i,j < n��exists(i,j)
	virtual EType& type(int i, int j) { return E[i][j]->type; } // ��(i,j)������
	virtual Te& edge(int i, int j) { return E[i][j]->data; } // ��(i,j)������
	virtual int& weight(int i, int j) { return E[i][j]->weight; } // ��(i,j)��Ȩ��

//�ߵĶ�̬����
	virtual void insert(Te const& edge,int w,int i,int j) // ����Ȩ��Ϊw�ı�e = (i,j)
	{
		if (exists(i, j))
			return;
		E[i].insert(new Edge<Te>(edge, w,j));
		e++;V[i].outDegree++;V[j].inDegree++;
	}

	virtual Te remove(int i,int j) // ɾ������i�ĵ�j������(exists(i,j))
	{
		Te eBak = edge(i, j);E[i].remove(j);
		e--;V[i].outDegree--;V[eBak.v].inDegree--;
		return eBak;
	}
};
