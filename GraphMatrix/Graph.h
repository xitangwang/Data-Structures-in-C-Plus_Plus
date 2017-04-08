/******************************************************************************************
* Data Structures in C++ -- Graph ADT�ӿ�
* ���ϼ������� 2017/3/30 11:16
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "../stack/Stack@list.h"
#include "../Queue/Queue.h"
#include <climits>

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; // ����״̬
typedef enum { UNETERMINED, TREE, CROSS, FORWORD, BACKWORD } EType; // ���ڱ�����������������

template <typename Tv, typename Te> // �������͡�������
class Graph;

// ���ȼ�������

// ��С֧����
template <typename Tv, typename Te> struct PrimPU // ���Prim�㷨�����ȼ�������
{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
	{
		if (UNDISCOVERED == g->status(v)) // ����ukÿһ��δ���ֵ��ڽӶ���v
		{
			if (g->priority(v) > g->weight(uk, v)) // ��Prim�������ɳ�
			{
				g->priority(v) = g->weight(uk, v); //�������ȼ�
				g->parent(v) = uk; // ���¸��ڵ�
			}
		}
	}
};

// ���·��
template <typename Tv, typename Te> struct DijkstraPU // ���Dijkstra�㷨�����ȼ�������
{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
	{
		if (UNDISCOVERED == g->status(v)) // ���ukÿһ��δ���ֵ��ڽӶ���v����Dijkstra����
		{
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) // ���ɳ�
			{
				g->priority(v) = g->priority(uk) + g->weight(uk, v); // �������ȼ�
				g->parent(v) = uk; // ��ͬʱ���¸��ڵ�
			}
		}
	}
};
                                                                                                                                                                                                                                                                                  
// BFS�㷨
template <typename Tv,typename Te> struct BfsPU
{
	virtual void operator()(Graph<Tv,Te>* g,int uk,int v)
	{
		if (g->status(v) == UNDISCOVERED) // ����ukÿһ��δ���ֵ��ڽӶ���v
			if (g->priority(v) > g->priority(uk) + 1) // ���䵽���ľ�����Ϊ���ȼ���
			{
				g->priority(v) = g->priority(uk) + 1; // �������ȼ���
				g->parent(v) = uk; // ���¸��ڵ�
			} // ���Ч����ͬ�ڣ�������������
	}
};

// DFS�㷨
template <typename Tv,typename Te> struct DfsPU
{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
	{
		if (g->status() == UNDISCOVERED)
		{
			if(g->priority(v) > g->priority(uk) - 1) // ���붥��ԽԶ�����ȼ�Խ��
			{
				g->priority(v) = g->priority(uk) - 1;
				g->parent(v) = uk;
			}
			return; // ע�⣺��BfsPU()��ͬ������ֻҪ��һ���ڽӵ���Ը��£�������������
		}
	}
};

template <typename Tv, typename Te> // �������͡�������
class Graph
{
private:
	void reset() // ���ж��㡢�ߵĸ�����Ϣ��λ
	{
		for (int i = 0; i < n; ++i) // ���ж���
		{
			status(i) = UNDISCOVERED;dTime(i) = fTime(i) = -1; // ״̬��ʱ���ǩ
			parent(i) = -1;priority(i) = INT_MAX; // ���ڱ������еģ����ڵ㡢���ȼ���
			for (int j = 0;j < n;j++) // ���бߵ�
				if (exists(i, j)) type(i, j) = UNDISCOVERED; // ����
		}
	}

	void reset_1()
	{
		
	}

	// (��ͨ�򣩹�����������㷨
	int BFS(int v, int& clock)
	{
		// assert:0 <= v < n
		Queue<int> Q; // ���븨������
		status(v) = DISCOVERED;Q.enqueue(v); // ��ʼ�����
		while (!Q.empty())
		{
			int v = Q.dequeue();dTime(v) = ++clock; // ȡ�����׶���v
			for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u)) // ö��v�������ھ�u
			{
				if (UNDISCOVERED == status(u)) // ��δ�����֣���
				{
					status(u) == DISCOVERED;Q.enqueue(u); // ���ָö���
					type(v, u) = TREE;parent(u) = v; // ����������չ֧����
				}
				else // ����ѱ����ֻ򱻷���
				{
					type(v, u) = CROSS; // ��(v,u)��Ϊ���
				}
			}
			status(v) = VISITED; // ���ˣ���ǰ����������
		}
		return v;
	} // S: O(n + e) T: O(n + e)

	// ����ͨ��������������㷨--�ݹ��
	void DFS(int v, int& clock)
	{
		// assert:0 <= v < n
		dTime(v) = ++clock;status(v) = DISCOVERED; // ���ֵ�ǰ����v
		for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u)) // ö��v�������ھ�u
		{
			switch (status(u)) // ����״̬������
			{
			case UNDISCOVERED: // u��δ���֣���ζ��֧�������ڴ���չ
				type(v, u) = TREE;parent(u) = v;DFS(u, clock);break;
			case DISCOVERED: // u�ѱ����ֵ���δ���ʣ�Ӧ�������ָ�������
				type(v, u) = BACKWORD;break;
			default: // u�ѱ��������(VISITED,����ͼ)������̳й�ϵΪǰ��߻���
				type(v, u) = (dTime(v) < dTime(u)) ? FORWORD : CROSS;break;
			}
		}
		status(v) = VISITED;fTime(v) = ++clock; // ���ˣ���ǰ����v�������
	} // S: O(n + e) T: O(n + e)

	// ����ͨ��������������㷨--������
	void DFS_I(int v, int& clock)
	{
		// assert:0 <= v < n
		Stack<int> S;S.push(v); // ���ֵ�ǰ�ڵ㣬��ջ
		while (!S.empty())
		{
			v = S.top();dTime(v) = ++clock;status(v) = DISCOVERED;// ���ֵ�ǰ����v
			for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u))
			{
				switch (status(u))
				{
				case UNDISCOVERED: // u��δ���֣���ζ��֧�������ڴ���չ
					type(v, u) = TREE;parent(u) = v;S.push(u);break;
				case DISCOVERED: // u�ѱ����ֵ���δ���ʣ�Ӧ�������ָ�������
					type(v, u) = BACKWORD;break;
				default: // u�ѱ��������(VISITED,����ͼ)������̳й�ϵΪǰ��߻���
					type(v, u) = (dTime(v) < dTime(u)) ? FORWORD : CROSS;break;
				}
			}
			status(v) = VISITED;fTime(v) = ++clock;S.pop(); // ���ˣ���ǰ����v�������
		} // S: O(n + e) T: O(n + e)
	}

	// ����ͨ�򣩻���DFS��˫����ͨ�����ֽ��㷨
#define hca(x) (fTime(x)) // ����v������ͨ���������
	void BCC(int v, int& clock, Stack<int>& S)
	{
		// assert: 0 <= v < n
		hca(v) = dTime(v) = ++clock;status(v) = DISCOVERED;S.push(v); //v�����ֲ���ջ
		for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u)) //
		{
			switch (status(u))
			{
			case UNDISCOVERED:
				parent(u) = v;BCC(u, clock, S); // �Ӷ���u����
				if (hca(u) < dTime(v)) // �������غ�������u��ͨ������ߣ�����ָ��v��������
					hca(v) = min(hca(v), hca(u)); // ��v������
				else // ������vΪ�ؽڵ㣨u���¼���һ��BCC�������ж�����������ջS�Ķ�����
				{
					while (v != S.pop()); // ���ε�����ǰBCC�еĽڵ㣬���ת���������ṹ
					S.push(v); // ���һ�����㣨�ؽڵ㣩������ջ--��̯����һ��
				}
				break;
			case DISCOVERED:
				if (u != parent(v))hca(v) = min(hca(v), dTime(u)); // ����hca[v]
				break;
			default:
				break;
			}
		}
		status(v) = VISITED; // ��v�ķ��ʽ���
	}
#undef hca

	// �����ˣ�����DFS�����������㷨
	bool TSort(int v, Stack<Tv>* S)
	{
		// assert: 0 <= v < n
		status(v) = DISCOVERED; // ���ֶ���v
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
		{
			if(status(u) == UNDISCOVERED)
			{
				parent(u) = v;
				if (!TSort(u,  S))
					return false;
			}
		}
		status(v) = VISITED;S->push(vertex(v)); //
		return true;
	}

	bool TSort_1(int v, int& clock, Stack<Tv>* S)
	{
		for (int i = 0; i < n; ++i)
			if (inDegree(i) == 0)
				S->push(vertex(i));
		Queue<Tv> Q;
		while (!S->empty())
		{
			Q.enqueue(v = S->pop());
			for (int u = firstNbr(v);-1 < u;u = nextNbr(v,u))
			{
				if (inDegree(u) < 2)
					S->push(vertex(u));
			}
			remove(v);
		}
		return n == 0 ? true : false;
	}

	// (��ͨ�����ȼ��������
	template <typename PU>
	void PFS(int s,PU prioUpdater)
	{
		priority(s) = 0;status(s) = VISITED;parent(s) = -1; // ��ʼ�������s����PFS����
		while(true) // ����һ�ڵ�ͱ߼���PFS����
		{
			for (int w = firstNbr(s);-1 < w;w = nextNbr(s, w)) // ö��s�������ھ�
				prioUpdater(this, s, w); // ���¶���w�����ȼ����丸�ڵ�
			for(int shortest = INT_MAX,w = 0;w < n;w++) // ����ÿһ���ڵ�
				if(UNDISCOVERED == status(w)) // ����δ����������Ķ�����
					if(shortest > priority(w)) // ѡ����һ��
					{
						shortest = priority(w);s = w; // ���ȼ���ߵĶ���s
					} 
			if (VISITED == status(s))break; // ֱ�����ж�����Լ���
			status(s) = VISITED;type(parent(s), s) = TREE; // ��s���丸�ڵ�����߼��������
		}
	} // ͨ�������������ȼ����²���prioUpdater������ʵ�ֲ�ͬ���㷨����

public:
	virtual ~Graph() = default;
	// ����
	int n; // ��������
	virtual int insert(Tv const&) = 0; // ���붥�㣬���ر��
	virtual Tv remove(int) = 0; // ɾ�����㼰������ߣ����ض�����Ϣ
	virtual Tv& vertex(int) = 0; // ����v�����ݣ��ö����ȷ���ڣ�
	virtual int inDegree(int) = 0; // �������ȣ��ö����ȷ���ڣ�
	virtual int outDegree(int) = 0; // ����ĳ��ȣ��ö����ȷ���ڣ�
	virtual int firstNbr(int) = 0; // ����v���׸��ڽӶ���
	virtual int nextNbr(int, int) = 0; // ����v�ģ�����ڶ���j�ģ���һ���ڽӶ���
	virtual VStatus& status(int) = 0; // ����v��״̬
	virtual int& dTime(int) = 0; // ����v��ʱ���ǩdTime
	virtual int& fTime(int) = 0; // ����v��ʱ���ǩfTime
	virtual int& parent(int) = 0; // ����v�ڱ������еĸ���
	virtual int& priority(int) = 0; // ����v�ڱ������е����ȼ���
// �ߣ�����Լ��������߾�ת��Ϊ�������һ������ߣ��Ӷ�������ͼ��������ͼ������
	int e; // ������
	virtual bool exists(int, int) = 0; // ��(v,u)�Ƿ����
	virtual void insert(Te const&, int, int, int) = 0; // �ڶ���v��u֮�����Ȩ��Ϊw�ı�e
	virtual Te remove(int, int) = 0; // ɾ������v�Ͷ���u֮��ı�e�����ظñ���Ϣ
	virtual EType& type(int, int) = 0; // �ߣ�v��u��������
	virtual Te& edge(int, int) = 0; // �ߣ�v��u�������ݣ��ñ�ȷʵ���ڣ�
	virtual int& weight(int, int) = 0; // �ߣ�v��u����Ȩ��
// �㷨
	void bfs(int s) // ������������㷨(ȫͼ��
	{
		// assert:0 <= s < n
		reset();int clock = 0;int v = s; //��ʼ��
		do
			if (UNDISCOVERED == status(v)) // һ��������δ���ֵĶ���
				BFS(v, clock); // ���Ӹõ��������һ��BFS
		while (s != (v = (++v % n))); // ѭ��һ���ٵ�����ʱ����
	}
	void dfs(int s) // ������������㷨(ȫͼ��
	{
		// assert:0 <= s < n
		reset();int clock = 0;int v = s; //��ʼ��
		do
			if (UNDISCOVERED == status(v)) // һ��������δ���ֵĶ���
				DFS(v, clock); // ���Ӹõ��������һ��DFS
		while (s != (v = (++v % n))); // ѭ��һ���ٵ�����ʱ����
	}
	void bcc(int s) // ����DFS��˫��ͨ�����ֽ��㷨
	{
		reset();int clock = 0;int v = s;Stack<int> S; // ջS���Լ�¼���ʹ��Ķ���
		do
			if (UNDISCOVERED == status(v)) // һ�����ֻ�δ���ֵĵ㣨����ͨ������
			{
				BCC(v, clock, S); // ���Ӹö����������һ��BCC
				S.pop(); // �������غ󣬵���ջ�����һ������--��ǰ��ͨ������
			}
		while (s != (v = (++v % n)));
	}
	Stack<Tv>* tSort(int s) // ����DFS�����������㷨
	{
		// assert: 0 <= s < n
		reset();int clock = 0;int v = s;
		Stack<Tv> S = new Stack<Tv>; // ��ջ��¼���򶥵�
		do
		{
			if (UNDISCOVERED == status(v))
				if (!TSort(v, clock, S)) // clock���Ǳ���
				{
					while (!S.empty()) // ��һ��ͨ���༴��ͼ����DGA
						S.pop();break; // �򲻱ؼ�����ֱ�ӷ���
				}
		} while (s != (v = (++v % n)));
		return S;
	}
	void prim(int s) // ��С֧����prim�㷨
	{
		pfs<PrimPU>(s, PrimPU<Tv, Te>());
	}
	void dijkstra(int s) // ���·��Dijkstra�㷨
	{
		pfs<DijkstraPU>(s, DijkstraPU<Tv, Te>());
	}
	template <typename PU> void pfs(int s, PU prioUpdater) // ���ȼ��������
	{
		// assert: 0 <= s < n
		reset();int v = s; // ��ʼ��
		do
			if (UNDISCOVERED == status(v))
				PFS(v, prioUpdater);
		while (s != (v = (++v % n))); //
	}

// ͼ�������������㷨 ϰ��[6-10]

	Stack<int> DIA() // ֱ�����������Զ�����������ͨ·��
	{
		Stack<int> Dia;
		int clock = 0;
		int b;
		int v = b = BFS(0, clock);
		reset();
		v = BFS(v, clock);
		Dia.push(v);
		while (Dia.top() != b)
		{
			Dia.push(parent(Dia.top()));
		}
		return Dia;
	}

// ŷ����· ϰ��[6-11]

	bool eulerCircle(List<int> & euler,int v = 0)
	{
		status(v) = DISCOVERED; // ���ֵ�ǰ����v
		euler.insertAsLast(v);
		for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u)) // ö��v�������ھ�u
		{
			if (inDegree(u) != outDegree(u)) // һ�������������Ȳ���ȵĵ㣬��û��ŷ����·
				return false;
			if(status(u) == UNDISCOVERED) 
			{   // ��¼��;����
				euler.insertAsLast(u);
				remove(u, v); // ���漴ɾ��
				if (inDegree(u) || outDegree(u)) // һ���ж������Ϊ��
					remove(u);
				if (inDegree(v) || outDegree(v)) // ���漴����ɾ��
					remove(v);
			}
		}
		status(v) = VISITED; // ���ˣ���ǰ����v�������
	}

	bool EulerCircle(List<int> Euler)
	{
		int s;
		reset();int v = s  = 0; //��ʼ��
		do
		{
			if (UNDISCOVERED == status(v)) // һ��������δ���ֵĶ���
			{
				List<int> euler;
				if (!eulerCircle(euler, v))
					return false;
				ListNodePosi(int) p = Euler.find(euler.first()->data);
				if (p != nullptr)
				{
					for (int i = euler.size() - 1;i >= 0 ;--i)
					{
						Euler.insertBefore(p, euler[i]);
					}
				}
				else
				{
					for (int i = 0;i < euler.size();++i)
					{
						Euler.insertAsLast(euler[i]);
					}
				}
			}
		}while (s != (v = (++v % n))); // ѭ��һ���ٵ�����ʱ����
		return true;
	}
};
