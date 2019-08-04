#include <stdio.h>
#include <malloc.h>

#define MaxVertexNum 50
typedef char VertexType;
typedef int Vertex;
typedef int WeightType;
typedef int ElementType;

typedef struct{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
}ENode,*PENode;

//边表节点
typedef struct ArcNode{
	Vertex adjvex;
	WeightType weight;
	struct ArcNode* next;
}ANode,*PArc;

//顶点表
typedef struct{
	VertexType data;
	PArc first;
}AdjList[MaxVertexNum];

//邻接表
typedef struct{
	AdjList vertices;
	int vexnum,arcnum;
}LGraph,*PLGraph;

//队列
typedef struct{
	ElementType data[MaxVertexNum];
	int count,front,rear;
}Queue,*PQueue;

//队列的方法
PQueue InitQueue(){
	PQueue pQ = (PQueue)malloc(sizeof(Queue));
	pQ->count=pQ->front=pQ->rear=0;
	return pQ;
}
void EnQueue(PQueue pQ,ElementType value){
	pQ->data[pQ->rear] = value;
	pQ->rear = (pQ->rear+1)%MaxVertexNum;
	pQ->count++;
}
bool QueueEmpty(Queue Q){
	return Q.count == 0 ? true : false;
}
bool DeQueue(PQueue pQ,ElementType* value){
	bool flag = QueueEmpty(*pQ);
	*value = flag ? NULL : pQ->data[pQ->front];
	pQ->front = (pQ->front+1)%MaxVertexNum;
	pQ->count--;
	return flag ? false : true;
}

//图的方法
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

PENode createENode(Vertex v1,Vertex v2,WeightType weight){
	PENode pE = (PENode)malloc(sizeof(ENode));
	pE->V1 = v1;
	pE->V2 = v2;
	pE->Weight = weight;
	return pE;
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

bool visited[MaxVertexNum];
void Initvisited(bool visited[]){
	int i;
	for (i=0;i<MaxVertexNum;i++)
	{
		visited[i] = false;
	}
}
void find(Vertex v){
	printf("发现了未被标记的节点v=%d\n",v);
}
//广度优先探索
void BFS(LGraph L,Vertex v){
	Vertex v1,v2;
	Initvisited(visited);
	PQueue pQ = InitQueue();
	find(v);
	visited[v] = true;
	EnQueue(pQ,v);
	
	while (DeQueue(pQ,&v1))
	{
		printf("正在探索v=%d\n",v1);
		PArc pA = L.vertices[v1].first;
		while(pA != NULL){
			v2 = pA->adjvex;
			if (!visited[v2])
			{
				find(v2);
				visited[v2] = true;
				EnQueue(pQ,v2);
			}
			pA = pA->next;
		}
	}
}
//深度优先搜索(Depth First Search,DFS)
char s='-';
void DFStravel(LGraph L,Vertex v1){
	Vertex v2;
	find(v1);
	visited[v1] = true;
	PArc pA = L.vertices[v1].first;
	while (pA != NULL)
	{
		v2 = pA->adjvex;
		if (!visited[v2])
		{
			printf("正在探索v=%d\n",v1);
			printf("%d %c %d\n",v1,s,v2);
			DFStravel(L,v2);
		}
		pA = pA->next;
	}
}
void DSF(LGraph L,Vertex v1){
	Initvisited(visited);
	DFStravel(L,v1);
}

void Print(LGraph L){
	int i;
	for (i=0;i<L.vexnum;i++)
	{
		PArc pA = L.vertices[i].first;
		while (pA != NULL)
		{
			printf("i=%d adjvex=%d\n",i,pA->adjvex);
			pA = pA->next;
		}
	}
}
void main(){
	char arr[5] = {'A','B','C','D','E'};
	int i;
	PLGraph pL = InitLGraph(5,6);
	for (i=0;i<pL->vexnum;i++)
	{
		pL->vertices[i].data = arr[i];
	}

	InsertLGraph(pL,*createENode(0,2,1));
	InsertLGraph(pL,*createENode(0,4,1));
	InsertLGraph(pL,*createENode(1,0,1));
	InsertLGraph(pL,*createENode(1,2,1));
	InsertLGraph(pL,*createENode(2,3,1));
	InsertLGraph(pL,*createENode(2,4,1));
	//Print(*pL);
	//BFS(*pL,0);
	DSF(*pL,0);
}