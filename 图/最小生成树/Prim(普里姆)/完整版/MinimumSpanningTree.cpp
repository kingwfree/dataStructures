//������
#include <stdio.h> 
#include <malloc.h> 
  
#define MAX 100  
#define INFINITY 65535

typedef char VertexType;
typedef int Vertex;
typedef int EdgeType;
typedef int ElementType;
typedef int WeightType;

//�߽ڵ�
typedef struct{
	Vertex v1,v2;
	WeightType weight;
}ENode,*PENode;  

//�ڽӾ���ͼ
typedef struct{
	VertexType V[MAX];
	WeightType Edge[MAX][MAX];
	int vexnum,edgenum;
}MGraph,*PMGraph;

//�߱�ڵ�
typedef struct ArcNode{
	Vertex adjvex;
	WeightType weight;
	struct ArcNode* next;
}ANode,*PArc;

//�����
typedef struct{
	VertexType V;
	PArc first;
}AdjList[MAX];

//�ڽӱ�
typedef struct{
	AdjList vertices;
	int vexnum,arcnum;
}LGraph,*PLGraph;

PENode createENode(Vertex v1,Vertex v2,WeightType weight){
	PENode pE = (PENode)malloc(sizeof(ENode));
	pE->v1 = v1;
	pE->v2 = v2;
	pE->weight = weight;
	return pE;
}

//�ڽӾ���ͼ�ķ���
PMGraph InitMGraph(int vexnum){
	int i,j;
	PMGraph pM = (PMGraph)malloc(sizeof(MGraph));
	pM->vexnum = vexnum;
	pM->edgenum = 0;
	for (i=0;i<=vexnum;i++)
	{
		for (j=0;j<=vexnum;j++)
		{
			pM->Edge[i][j] = INFINITY;
		}
	}
	return pM;
}

void InsertMGraph(PMGraph pM,PENode pE){
	pM->Edge[pE->v1][pE->v2] = pM->Edge[pE->v2][pE->v1] = pE->weight;
	pM->edgenum += 2;
	free(pE);
}

//�ڽӱ�ķ���
PLGraph InitLGraph(int vernum){
	int i;
	PLGraph pL = (PLGraph)malloc(sizeof(LGraph));
	pL->vexnum=vernum;
	pL->arcnum=0;
	for (i=0;i<=vernum;i++)
	{
		pL->vertices[i].first=NULL;
	}
	return pL;
}
void InsertLGraph(PLGraph pL,PENode pE){
	PArc pA = (PArc)malloc(sizeof(ANode));
	pA->adjvex = pE->v2;
	pA->weight = pE->weight;
	pA->next = pL->vertices[pE->v1].first;
	pL->vertices[pE->v1].first = pA;

	pA = (PArc)malloc(sizeof(ANode));
	pA->adjvex = pE->v1;
	pA->weight = pE->weight;
	pA->next = pL->vertices[pE->v2].first;
	pL->vertices[pE->v2].first = pA;

	pL->arcnum += 2;
}

//prim
int Findlowcost(MGraph M,int lowcost[]){
	int i,
		minid=-1,
		min = INFINITY;
	for (i=2;i<=M.vexnum;i++)
	{
		if(lowcost[i]<min && lowcost[i] != 0){
			min = lowcost[i];
			minid = i;
		}
	}
	return minid;
}
int prim(MGraph M,PLGraph pL)  
{  
	int lowcost[MAX],start[MAX];
	int i,minid,sum=0,vcount=0;
	PENode pE = (PENode)malloc(sizeof(ENode));
	//��ʼ��lowcost��start
	/*
		start �洢�����±�������ڵ����ʼ�ڵ�������±�
		�����±� 1 2 3 4 5 6
		�ڵ����� 1 2 3 4 5 6
	*/
	//lowcost��ʱ�洢����1�ڽӵĸ�����֮��ıߵ�Ȩ��
	//start��ʱ�洢����ʼ�㶼Ϊ0
    for (i=2;i<=M.vexnum;i++)
    {
		lowcost[i] = M.Edge[1][i];
		start[i] = 1;
		//��ʼ��������
		pL->vertices[i].V=i;
    }
	//0�Ǹ�
	lowcost[1] = 0;
	start[1] = 0;
	vcount++;
	//��ûѭ������1�Žڵ㲹��
	pL->vertices[1].V = 1;
	while (1)
	{
		minid = Findlowcost(M,lowcost);
		//printf("minid=%d",minid);
		//lowcost������ֵ����0��ض�����-1
		if (minid == -1)
			break;
		printf("v%d-v%d=%d\n",start[minid],minid,lowcost[minid]);
		pE->v1 = start[minid];
		pE->v2 = minid;
		pE->weight = lowcost[minid];
		InsertLGraph(pL,pE);
		sum += lowcost[minid];
		lowcost[minid] = 0;
		vcount++;
		for (i=2;i<=M.vexnum;i++)
		{
			if(M.Edge[minid][i] < lowcost[i]){
				lowcost[i] = M.Edge[minid][i];
				start[i] = minid;
			}
		}
	}
	free(pE);
	sum = vcount < M.vexnum-1 ? -1 : sum;
	printf("sum=%d\n",sum);
	return sum;

}
 

int main()  
{   
	int i,j;
	PArc pA;
	int vexnum=6;
	PMGraph pM = InitMGraph(vexnum);
	PLGraph pL = InitLGraph(vexnum);
	InsertMGraph(pM,createENode(1,4,5));
	InsertMGraph(pM,createENode(3,4,5));
	InsertMGraph(pM,createENode(1,3,1));
	InsertMGraph(pM,createENode(4,6,2));
	InsertMGraph(pM,createENode(2,5,3));
	InsertMGraph(pM,createENode(2,3,5));
	InsertMGraph(pM,createENode(3,5,6));
	InsertMGraph(pM,createENode(1,2,6));
	InsertMGraph(pM,createENode(3,6,4));
	/*
	//ԭʼ���ݴ����ڽӾ���ͼ
	for (i=0;i<vexnum;i++)
	{
		for (j=0;j<vexnum;j++)
		{
			if (pM->Edge[i][j]<INFINITY)
			{
				printf("V%d-V%d %d\n",i,j,pM->Edge[i][j]);
			}
		}
	}
	*/
	prim(*pM,pL);
	printf("\n");
	/*
	for (i=0;i<=vexnum;i++)
	{
		for (pA=pL->vertices[i].first;pA != NULL;pA=pA->next)
		{
			printf("pL V%d-V%d=%d\n",pL->vertices[i].V,pA->adjvex,pA->weight);
		}
	}
	*/
	printf("��С���������ڽӱ��洢\n");
	for (i=1;i<=vexnum;i++)
	{
		for (pA=pL->vertices[i].first;pA != NULL;pA=pA->next)
		{
			printf("pL V%d-V%d=%d\n",pL->vertices[i].V,pA->adjvex,pA->weight);
		}	
	}
	
    return 0;  
}
