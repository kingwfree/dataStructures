#include <stdio.h>
#include <malloc.h>

#define MAX 20
#define MAXDATA 1000  /* 该值应根据具体情况定义为大于堆中所有可能元素的值 */
#define MINDATA -1	  /* 该值应根据具体情况定义为小于堆中所有可能元素的值 */

typedef int VertexType;
typedef int Vertex;
typedef int WeightType;
typedef int ElementType;

//堆
typedef struct{
	ElementType* data; //从1开始存储，0存放哨兵
	int count;
	int len;
}HNode,*PHeap;
typedef PHeap MaxHeap;
typedef PHeap MinHeap;


//图
typedef struct{
	Vertex V1,V2;
	WeightType Weight;
}ENode,*PENode;
//邻接表
typedef struct AdjNode* PArc;
typedef struct AdjNode{
	Vertex adjvex;
	WeightType weight;
	PArc next;
}ANode;
typedef struct{
	VertexType v;
	PArc first;
}VerList[MAX];
typedef struct{
	VerList vertices;
	int vexnum,arcnum;
}LGraph,*PLGraph;



//ADT
typedef int ElementType;		 	
typedef int SetName;			  //顶点名
typedef ElementType SetType[MAX];


//ADT的方法
void InitializeVSet( SetType S, int N )
{ /* 初始化并查集 */
    ElementType X;
	
    for ( X=1; X<=N; X++ ) S[X] = -1;
}

void Union(SetType S,SetName Root1,SetName Root2){
	if (S[Root1] < S[Root2]) 
	{
		//Root1 比 Root2 子节点数更多，所以Root2并入Root1
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	} 
	else
	{
		//Root2 比 Root1 子节点数更多或相等，所以Root1并入Root2
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
}
//x是该顶点在数组中的下标
int Find(SetType S,ElementType x){
	//寻找x的根元素，即找到x所在的集合
	return S[x]<0 ? x : Find(S,S[x]);
}
bool CheckCycle( SetType VSet, Vertex V1, Vertex V2 )
{ /* 检查连接V1和V2的边是否在现有的最小生成树子集中构成回路 */
    Vertex Root1, Root2;
	
    Root1 = Find( VSet, V1 ); /* 得到V1所属的连通集名称 */
    Root2 = Find( VSet, V2 ); /* 得到V2所属的连通集名称 */
	
    if( Root1==Root2 ) /* 若V1和V2已经连通，则该边不能要 */
        return false;
    else { /* 否则该边可以被收集，同时将V1和V2并入同一连通集 */
        Union( VSet, Root1, Root2 );
        return true;
    }
}


//图的方法
PENode createENode(Vertex v1,Vertex v2,WeightType weight){
	PENode pE = (PENode)malloc(sizeof(ENode));
	pE->V1 = v1;
	pE->V2 = v2;
	pE->Weight = weight;
	return pE;
}
//邻接表的方法
PLGraph InitLGraph(int vexnum,int arcnum){
	int i;
	PLGraph pL = (PLGraph)malloc(sizeof(LGraph));
	pL->vexnum = vexnum;
	pL->arcnum = arcnum;
	for (i=0;i<pL->vexnum;i++)
	{
		pL->vertices[i].first = NULL;
	}
	return pL;
}
void InsertLGraph(PLGraph pL,ENode E){
	PArc pA;
	//有向图 v2是终点
	pA = (PArc)malloc(sizeof(ANode));
	pA->adjvex = E.V2;
	pA->weight = E.Weight;
	pA->next = pL->vertices[E.V1].first;
	pL->vertices[E.V1].first = pA;

	//无向图 
	pA = (PArc)malloc(sizeof(ANode));
	pA->adjvex = E.V1;
	pA->weight = E.Weight;
	pA->next = pL->vertices[E.V2].first;
	pL->vertices[E.V2].first = pA;
}


//最小堆的方法
bool isFull(PHeap H){
	return (H->count == H->len);
}
bool isEmpty(PHeap H){
	return (H->count == 0);
}
PHeap InitHeap(int len,ElementType guard){
	PHeap H = (PHeap)malloc(sizeof(HNode));
	H->data = (ElementType*)malloc((len+1)*sizeof(ElementType));
	H->len = len;
	H->count = 0;
	H->data[0] = guard;  /*定义"哨兵"为大于堆中所有可能元素的值*/
	return H;
}
//构建最小堆 n 有效个数
void PercUp(PENode ESet,int p,int n){
	int parent,child;
	ENode root = ESet[p];
	for (parent=p;parent*2 <= n;parent=child)
	{
		child = parent*2;
		if((child != n) && (ESet[child].Weight > ESet[child+1].Weight))
			child++;
		if(root.Weight <= ESet[child].Weight)break;
		else ESet[parent] = ESet[child];
	}
	ESet[parent] = root;
}

void Swap(int* a,int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int GetEdge(PENode ESet,int currentSize){
	
	Swap(&ESet[1],&ESet[currentSize]);
	PercUp(ESet,1,currentSize);
	return currentSize;
}

void InitializeESet(LGraph Graph,PENode ESet){
	Vertex V;
	PArc W;
	int ECount;
	
	ECount = 0;
    for ( V=0; V<Graph->vexnum; V++ )
        for ( W=Graph->vertices[V].first; W; W=W->next)
            if ( V < W->adjvex ) { /* 避免重复录入无向图的边，只收V1<V2的边 */
                ESet[ECount].V1 = V;
                ESet[ECount].V2 = W->adjvex;
                ESet[ECount++].Weight = W->weight;
            }
			/* 初始化为最小堆 */
	for ( ECount=Graph->arcnum/2; ECount>0; ECount-- )
		PercUp( ESet, ECount, Graph->arcnum );
}

