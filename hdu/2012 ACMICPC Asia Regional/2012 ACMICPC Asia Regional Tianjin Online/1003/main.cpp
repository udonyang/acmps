/*
   This Problem beat me completely.
   Beat my template completely.
   Beat my funtion comletely.
   Waste my time comletely.

   It's a naked maximum-stream problem.
   The main point is your template.

   It make me realize that my SAP template is a sh*t!
   
   ....To make my SAP faster, I have done three kinds of optimization.
   1. Record the adjacency node which has minimum distance;
   2. Initailize the distance by using BFS;
   3. As I got a Stack-Overflow, I simulate the DFS by using stack in STL;

   Then I got AC in 2s+.

   Of course, the problem is also correspond to the Minimum-Cut in Dual-Graph.
   Hence, Dijkstra with minimum heap is optimal algorithm.
   */
//Header
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;
//Macro
//STL-Alias
#define UN(c, a) unique(c, a)
#define MS(c, a) memset(c, a, sizeof c)
#define FLC(c, a ,b) fill(c, c + a, b)
#define LOS(c, a, b) lower_bound(c, a, b)
#define UPS(c, a, b) upper_bound(c, a, b)
//Syntax-Alias
#define Rep(c, a, b) for (int c = (a); c < (b); c++)
#define Nre(c, a, b) for (int c = (a); c > (b); c--)
//DEBUG
#define FK puts("Fu*k here!")
#define PA(s, c, a, b, p, f){\
	printf(s);\
	Rep(c, a, b) printf(p, (f));\
	puts("");}
//Constant
#define INFL (0x7fffffffffffffffLL)
#define INFI (0x7fffffff)
#define MOD ()
#define MAXN (100005)
//Type-Alias
typedef long long LL;
typedef long double LD;
typedef int AI[MAXN];
typedef bool AB[MAXN];
typedef double AD[MAXN];
typedef LL ALL[MAXN];
typedef LD ALD[MAXN];

//Linking list Graph
//include: vector
struct LLG {
    struct Edge {
        //Externs should be defined here
        int w;
        //Basic
        int v,       //Adjust node v
            next;    //Index of the next node v
    };
	const static int n = MAXN;
	const static int m = MAXN << 2;
	Edge E[m];    //Aarry in which Edges store
	int  L[n],    //Head of linking list of nodes
		 El,         //Total of Edges
		 V;          //Total of nodes
    //Init
    //usage: obj.Init(int TotalOfNode)
    void Init(int _V = 0) {
        V = _V;
		El = 0;
		memset(L, -1, sizeof(L));
    }
    //AddEdge 
    //usage: obj.AddEdge(From, To, Extern)
    void AddEdge(int u, int v, int w) {
        Edge t =  {w, v, L[u]}; //rule: Node t = {Extern, Basic}
        E[L[u] = El++] = t;
    }
    //FlowAddEdge 
    //usage: obj.FlowAddEdge(From, To, Extern)
    void FlowAddEdge(int u, int v, int w) {
        AddEdge(u, v, w);
        AddEdge(v, u, 0);
    }
};
//SAP  
//include: LLG
int SAP(int src, int snk, LLG &G){
    const int n = MAXN;
    const int inf = ;
    typedef int AI[n];
    static AI dis, gap, _L, se, Q;
    int u = src, mxf = 0, te = 0, Qf = 0, Qt = 0, 
		V = G.V, *L = G.L;
    LLG::Edge *E = G.E;
    memcpy(_L, L, sizeof L);
    memset(dis, -1, sizeof(dis));
    memset(gap, 0, sizeof(gap));
    gap[dis[snk] = 0] = 1;  
    Q[Qt++] = snk;
	while (Qf != Qt) {
		int u = Q[Qf++];
		for (int i = L[u]; i != -1; i = E[i].next) {
			if (E[i].w && dis[E[i].v] < 0){  
				gap[dis[E[i].v] = dis[u] + 1]++;
				Q[Qt++] = E[i].v;  
			}  
		}
	}
	while (dis[src] < V) {
		for (int &i = _L[u]; i != -1; i = E[i].next) {
			if (E[i].w && dis[u] == dis[E[i].v] + 1) {
				break;  
			}
		}
		if (_L[u] != -1) {  
			u = E[se[te++] = _L[u]].v;  
			if (u == snk) {  
				int _i = 0, mf = inf;  
				for (int i = 0; i < te; i++) {
					if (E[se[i]].w < mf){  
						mf = E[se[i]].w;
						_i = i;  
					}
				}  
				for (int i = 0; i < te; i++) { 
					E[se[i]].w -= mf;
					E[se[i] ^ 1].w += mf;  
				}  
				mxf += mf;
				te = _i;  
				u = E[se[_i] ^ 1].v;  
			}  
			continue;  
		}
		int md = V;
		for (int i = L[u]; i != -1; i = E[i].next) {
			if (E[i].w && dis[E[i].v] < md){  
				md = dis[E[i].v];
				_L[u] = i;  
			}  
		}
		if (!--gap[dis[u]]) {
			break;  
		}
		gap[dis[u] = md + 1]++;  
		if (u != src) {
			u = E[se[te-- - 1] ^ 1].v;  
		}
	}  
    return mxf;  
}

struct Isl
{
	int x, y;
	void inp()
	{
		scanf("%d%d", &x, &y);
	}
} I[MAXN];
LLG G;
int n, m;

int main()
{
#if 1
	freopen("test.txt", "r", stdin);
	//freopen("test.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while (T--)
	{
		//Initialize
		scanf("%d%d", &n, &m);
		I[0].inp();
		int src = 0, snk = 0;
		Rep(i, 1, n)
		{
			I[i].inp();
			if (I[i].x < I[src].x) src = i;
			if (I[i].x > I[snk].x) snk = i;
		}
		G.Init(n);
		while (m--)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			u--;
			v--;
			G.AddEdge(u, v, w);
			G.AddEdge(v, u, w);
		}
		//Solve
		printf("%d\n", ISAP(src, snk, G));
	}
	return 0;
}
