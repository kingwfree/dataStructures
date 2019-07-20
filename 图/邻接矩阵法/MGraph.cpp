#include <stdio.h>
#include <malloc.h>

#define MaxVertexNum 100 
#define INFINITY 65535
typedef char VertexType;
typedef int Vertex;
typedef int EdgeType;
typedef int ElementType;

typedef struct{
	Vertex v1,v2;
	EdgeType weight;
}ENode,*PENode;
//�ڽӾ���ͼ
typedef struct{
	VertexType V[MaxVertexNum];
	EdgeType Edge[MaxVertexNum][MaxVertexNum];
	int vexnum,edgenum;
}MGraph,*PMGraph;

//����
typedef struct{
	ElementType data[MaxVertexNum];
	int count;
	int front,rear;
}Queue,*PQueue;

//ջ
typedef struct{
	ElementType data[MaxVertexNum];
	int top;
}Stack,*PStack;

//ջ�ķ���
PStack InitStack(){
	PStack pS = (PStack)malloc(sizeof(Stack));
	pS->top = -1;
	return pS;
}

bool StackEmpty(Stack S){
	return S.top == -1 ? true : false;
}
void EnStack(PStack pS,ElementType value){
	pS->data[++pS->top] = value;
}
bool DeStack(PStack pS,ElementType* value){
	bool flag = StackEmpty(*pS);
	if (!flag)
	{
		*value = pS->data[pS->top--];
	}
	return flag ? false : true;
}

//���еķ���
PQueue InitQueue(){
	PQueue pQ = (PQueue)malloc(sizeof(Queue));
	pQ->front = pQ->rear = pQ->count = 0;
	return pQ;
}
bool QueueEmpty(Queue Q){
	return Q.count == 0 ? true : false;
}
bool QueueFull(Queue Q){
	return Q.count == MaxVertexNum ? true : false;
}
bool EnQueue(PQueue pQ,ElementType value){
	bool flag = QueueFull(*pQ);
	if(!flag){
		pQ->data[pQ->rear]=value;
		pQ->rear = (pQ->rear+1)%MaxVertexNum;
		pQ->count++;
	}
	return flag ? false : true;
}
bool DeQueue(PQueue pQ,ElementType* v){
	int flag = QueueEmpty(*pQ);
	if (!flag)
	{
		*v = pQ->data[pQ->front];
		pQ->front = (pQ->front+1)%MaxVertexNum;
		pQ->count--;
	}
	return flag ? false : true;
}



//ͼ�ķ���
void InitMGraph(PMGraph pM,int vexnum,int edgenum){
	int i,j;
	pM->vexnum = vexnum;
	pM->edgenum = edgenum;
	for (i=0;i<MaxVertexNum;i++)
	{
		for (j=0;j<MaxVertexNum;j++)
		{
			pM->Edge[i][j] = INFINITY;
		}
	}
}

void InsertMGraph(PMGraph pM,ENode E){
	/* ����� <V1, V2> */
	pM->Edge[E.v1][E.v2] = E.weight;
	/* ��������ͼ����Ҫ�����<V2, V1> */
	pM->Edge[E.v2][E.v1] = E.weight;

}

PENode createEdge(Vertex v1,Vertex v2,EdgeType weight){
	PENode pE = (PENode)malloc(sizeof(ENode));
	pE->v1 = v1;
	pE->v2 = v2;
	pE->weight = weight;
	return pE;
}

void find(Vertex v){
	printf("������δ����ǵĽڵ�v=%d\n",v);
}

bool isEdge(MGraph M,Vertex v1,Vertex v2){
	return M.Edge[v1][v2] < INFINITY ? true : false;
}

bool visited[MaxVertexNum];
void InitVisited(MGraph M,bool visited[]){
	int i;
	for (i=0;i<M.vexnum;i++)
	{
		visited[i] = false;
	}
}
//�����������(Breadth First Search,BFS)
void BFS(MGraph M,Vertex v){
	InitVisited(M,visited);
	Vertex V,W;
	PQueue pQ = InitQueue();
	find(v);
	visited[v] = true;
	EnQueue(pQ,v);
	while (DeQueue(pQ,&V))
	{
		printf("����̽��v=%d\n",V);
		for(W=0;W<M.vexnum;W++){
			if(!visited[W] && isEdge(M,V,W)){
				find(W);
				visited[W] = true;
				EnQueue(pQ,W);
			}
		}
	}

}

//�����������(Depth First Search,DFS) �ݹ��
char s='-'; //���Դ�ӡ��
void DFStravel(MGraph M,Vertex v){
	Vertex W;
	find(v);
	visited[v] = true;
	//A-B B-C C-D C-E
	for (W=0;W<M.vexnum;W++)
	{
		//���ֻ�δ��̽�����ڽӵ�
		if (!visited[W] && isEdge(M,v,W)){
			printf("����̽��v=%d\n",v);
			printf("%d %c %d\n",v,s,W);
			DFStravel(M,W);
		}
	}
}
void DFS(MGraph M,Vertex v){
	InitVisited(M,visited);
	DFStravel(M,v);
}



//�����������(Depth First Search,DFS) ջ�ṹʵ��
void DFSstack(MGraph M,Vertex v){
	Vertex V,W;
	PStack pS = InitStack();
	find(v);
	InitVisited(M,visited);
	visited[v] = true;
	EnStack(pS,v);
	while (DeStack(pS,&V))
	{
		printf("����̽��v=%d\n",V);
		for (W=0;W<M.vexnum;W++)
		{
			if (!visited[W] && isEdge(M,V,W))
			{
				find(W);
				visited[W] = true;
				EnStack(pS,W);
			}
		}
	}
}


void Print(MGraph M){
	int i,j;
	for (i=0;i<M.vexnum;i++)
	{
		printf("%d ",M.V[i]);
	}
	for (i=0;i<M.vexnum;i++)
	{
		for (j=0;j<M.vexnum;j++)
		{
			printf("%d ",M.Edge[i][j]);
		}
	}
}

void main(){
	MGraph M;
	int i;
	char *arr[5] = {"A","B","C","D","E"};
	InitMGraph(&M,5,6);
	for (i=0; i<M.vexnum; i++){
		M.V[i] = *arr[i];
	}
	/*
		A B C D E
		0 1 2 3 4
	*/
	InsertMGraph(&M,*createEdge(1,0,1));
	InsertMGraph(&M,*createEdge(1,2,1));
	InsertMGraph(&M,*createEdge(2,3,1));
	InsertMGraph(&M,*createEdge(2,4,1));
	InsertMGraph(&M,*createEdge(0,2,1));
	InsertMGraph(&M,*createEdge(0,4,1));
	//Print(M);
	//BFS(M,0);
	
	
	//DFS(M,0);

	DFSstack(M,0);
}