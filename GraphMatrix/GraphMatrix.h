/******************************************************************************************
* Data Structures in C++ -- Graph ���ڽӾ���(adjacency matrix)ʵ��
* ���ϼ������ 2017/3/30 18:56
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "../vector/vector.h"
#include "Graph.h"
#include <climits>

// ����struct�������Ԫ��ȫ������

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
	Edge(Te const& d, int w) :data(d), weight(w), type(UNETERMINED) {  } // ����
};

template <typename Tv,typename Te> 
class GraphMatrix :public Graph<Tv, Te> // ����vectorһ�ڽӾ���ʽʵ�ֵ�ͼ
{
private:
	Vector<Vertex<Tv>> V; // ���㼯��������
	Vector<Vector<Edge<Te>*>> E; // �߼����ڽӾ���
public:
	GraphMatrix() { n = e = 0; }
	~GraphMatrix()
	{
		for (int j = 0;j < n;j++) // ���ж�̬�����ı߼�¼
			for (int k = 0;k < n;k++)
				delete E[j][k]; // �������
	}
	// ����Ļ�����������ѯ��i�����㣨0 <= n��
	virtual Tv& vertex(int i) { return V[i].data; } // ����
	virtual int inDegree(int i) { return V[i].inDegree; } // ���
	virtual int outDegree(int i) { return V[i].outDegree; } // ����
	virtual int firstNbr(int i) { return nextNbr(i, n); } // �׸��ڽӵ� ���Ӻ���ǰ�ƣ�
	virtual int nextNbr(int i,int j) // ����ڶ���j����һ�ڽӶ��㣨�����ڽӱ�����Ч�ʣ�
	{
		while ((-1 < j) && (!exists(i, --j)));
		return j; // ����������̽
	}
	virtual VStatus& status(int i) { return V[i].status; } // ״̬
	virtual int& dTime(int i) { return V[i].dTime; } // ʱ���ǩdTime
	virtual int& fTime(int i) { return V[i].fTime; } // ʱ���ǩfTime
	virtual int& parent(int i) { return V[i].parent; } // �ڱ������еĸ���
	virtual int& priority(int i) { return V[i].priority; } // �ڱ������е����ȼ���

//����Ķ�̬����
	virtual int insert(Tv const& vertex) // ���붥�㣬���ر��
	{
		for (int j = 0;j < n;j++)E[j].insert(nullptr);n++; // ������Ԥ��һ��Ǳ�ڵĹ�����
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*)nullptr)); // �����¶����Ӧ�ı�����
		return V.insert(Vertex<Tv>(vertex)); // ������������һ������
	}

	virtual Tv remove(int i) // ɾ����i�����㼰�������( 0 <= i < n )
	{
		for(int j = 0;j < n;j++)
			if (exists(i, j))
			{
				delete E[i][j];V[j].inDegree--;
			}
		E.remove(i);n--; // ɾ����i��
		Tv vBak = vertex(i);V.remove(i); // ɾ������i
		for(int j = 0;j < n;j++) // �������
			if(Edge<Te> * e = E[j].remove(i))
			{
				delete e;V[j].outDegree--; // ����ɾ��
			}
		return vBak; // ���ر�ɾ���������Ϣ
	}

// �ߵ�ȷ�ϲ���
	virtual bool exists(int i,int j) // �ߣ�i,j���Ƿ����
	{
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != nullptr;
	}

// �ߵĻ�����������ѯ����i��j֮�������( 0 <= i,j < n��exists(i,j)
	virtual EType& type(int i, int j) { return E[i][j]->type; } // ��(i,j)������
	virtual Te& edge(int i, int j) { return E[i][j]->data; } // ��(i,j)������
	virtual int& weight(int i, int j) { return E[i][j]->weight; } // ��(i,j)��Ȩ��

// �ߵĶ�̬����
	virtual void insert(Te const& edge,int w,int i,int j) // ����Ȩ��Ϊw�ı�e = (i,j)
	{
		if (exists(i, j)) // ȷ���ñ��в�����
			return;
		E[i][j] = new Edge<Te>(edge, w); // �����±�
		e++;V[i].outDegree++;V[j].inDegree++; // ���±߼������������Ķ���
	}
	virtual Te remove(int i,int j) // ɾ������i��j֮�������(exists(i,j))
	{
		Te eBak = edge(i, j);delete E[i][j];E[i][j] = nullptr; // ���ݺ�ɾ���߼�¼
		e--;V[i].outDegree--;V[j].inDegree--; // ���±߼������������Ķ���
		return eBak;
	}

};