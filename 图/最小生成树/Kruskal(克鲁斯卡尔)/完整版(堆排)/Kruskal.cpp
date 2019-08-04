#include <stdio.h>
#include <malloc.h>

#define MAX 20
#define MAXDATA 1000  /* ��ֵӦ���ݾ����������Ϊ���ڶ������п���Ԫ�ص�ֵ */
#define MINDATA -1	  /* ��ֵӦ���ݾ����������ΪС�ڶ������п���Ԫ�ص�ֵ */

typedef int VertexType;
typedef int Vertex;
typedef int WeightType;
typedef int ElementType;

//��
typedef struct{
	ElementType* data; //��1��ʼ�洢��0����ڱ�
	int count;
	int len;
}HNode,*PHeap;
typedef PHeap MaxHeap;
typedef PHeap MinHeap;


//ͼ
typedef struct{
	Vertex V1,V2;
	WeightType Weight;
}ENode,*PENode;
//�ڽӱ�
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
typedef int SetName;			  //������
typedef ElementType SetType[MAX];


//ADT�ķ���
void InitializeVSet( SetType S, int N )
{ /* ��ʼ�����鼯 */
    ElementType X;
	
    for ( X=1; X<=N; X++ ) S[X] = -1;
}

void Union(SetType S,SetName Root1,SetName Root2){
	if (S[Root1] < S[Root2]) 
	{
		//Root1 �� Root2 �ӽڵ������࣬����Root2����Root1
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	} 
	else
	{
		//Root2 �� Root1 �ӽڵ����������ȣ�����Root1����Root2
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
}
//x�Ǹö����������е��±�
int Find(SetType S,ElementType x){
	//Ѱ��x�ĸ�Ԫ�أ����ҵ�x���ڵļ���
	return S[x]<0 ? x : Find(S,S[x]);
}
bool CheckCycle( SetType VSet, Vertex V1, Vertex V2 )
{ /* �������V1��V2�ı��Ƿ������е���С�������Ӽ��й��ɻ�· */
    Vertex Root1, Root2;
	
    Root1 = Find( VSet, V1 ); /* �õ�V1��������ͨ������ */
    Root2 = Find( VSet, V2 ); /* �õ�V2��������ͨ������ */
	
    if( Root1==Root2 ) /* ��V1��V2�Ѿ���ͨ����ñ߲���Ҫ */
        return false;
    else { /* ����ñ߿��Ա��ռ���ͬʱ��V1��V2����ͬһ��ͨ�� */
        Union( VSet, Root1, Root2 );
        return true;
    }
}


//ͼ�ķ���
PENode createENode(Vertex v1,Vertex v2,WeightType weight){
	PENode pE = (PENode)malloc(sizeof(ENode));
	pE->V1 = v1;
	pE->V2 = v2;
	pE->Weight = weight;
	return pE;
}
//�ڽӱ�ķ���
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
	//����ͼ v2���յ�
	pA = (PArc)malloc(sizeof(ANode));
	pA->adjvex = E.V2;
	pA->weight = E.Weight;
	pA->next = pL->vertices[E.V1].first;
	pL->vertices[E.V1].first = pA;

	//����ͼ 
	pA = (PArc)malloc(sizeof(ANode));
	pA->adjvex = E.V1;
	pA->weight = E.Weight;
	pA->next = pL->vertices[E.V2].first;
	pL->vertices[E.V2].first = pA;
}


//��С�ѵķ���
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
	H->data[0] = guard;  /*����"�ڱ�"Ϊ���ڶ������п���Ԫ�ص�ֵ*/
	return H;
}
//������С�� n ��Ч����
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
            if ( V < W->adjvex ) { /* �����ظ�¼������ͼ�ıߣ�ֻ��V1<V2�ı� */
                ESet[ECount].V1 = V;
                ESet[ECount].V2 = W->adjvex;
                ESet[ECount++].Weight = W->weight;
            }
			/* ��ʼ��Ϊ��С�� */
	for ( ECount=Graph->arcnum/2; ECount>0; ECount-- )
		PercUp( ESet, ECount, Graph->arcnum );
}

