//�򵥰�
#include<stdio.h>  
  
#define MAX 100  
#define INFINITY 65535

int graph[MAX][MAX];  

int prim(int graph[][MAX], int vexnum)  
{  
	int lowcost[MAX],start[MAX];
	int i,j,min,minid,sum=0,count=0;
	//��ʼ��lowcost��start
	/*
		start �洢�����±�������ڵ����ʼ�ڵ�������±�
		�����±� 0 1 2 3 4 5
		�ڵ����� 1 2 3 4 5 6
	*/
	//lowcost��ʱ�洢����1�ڽӵĸ�����֮��ıߵ�Ȩ��
	//start��ʱ�洢����ʼ�㶼Ϊ0
    for (i=1;i<vexnum;i++)
	{
		lowcost[i] = graph[0][i];
		start[i]=0;
	}
	//0�Ǹ���û�и���
	start[0]=-1;
	count++;
	for (i=1;i<vexnum;i++)
	{
		min = INFINITY;
		minid = -1;
		for (j=1;j<vexnum;j++)
		{
			if(lowcost[j] < min && lowcost[j] != 0){
				min = lowcost[j];
				minid = j;
			}
		}
		printf("V%d-V%d=%d\n",start[minid],minid,min); 
		sum += min;
		lowcost[minid] = 0;
		count = minid != -1 ? count+1 : count;
		for (j=1;j<vexnum;j++)
		{
			/*
			�Ը��ҳ������·�����յ�Ϊ��ʼ�㣬
			�ҳ������ڽӵĵ������ɵıߵ�Ȩֵ��
			����ЩȨֵ��ԭ�еģ���lowcost��洢�ģ����·����ֵ��ҪС������graph[minid][j] < lowcost[j]��
			���滻ԭ�е����·�����ֵ������lowcost[j] = graph[minid][j];��
			�����¸��յ����ʼ�㡣����start[j] = minid;��
			*/
			if (graph[minid][j] < lowcost[j])
			{
				
				lowcost[j] = graph[minid][j];
				start[j] = minid;
			}
		}
	}
	/* MST���յĶ��㲻��|V|�� */
	sum = count < vexnum ? -1 : sum;
	printf("��СȨֵ֮��=%d\n",sum);
	return sum;
	

}  
void InsertGraph(int graph[][MAX],int v1,int v2,int weight){
	graph[v1][v2] = graph[v2][v1] = weight;
}
void InitGraph(int graph[][MAX],int vexnum){
	int i,j;
	for (i=0;i<vexnum;i++)
	{
		for (j=0;j<vexnum;j++)
		{
			graph[i][j] = INFINITY;
		}
	}
}

/*
int main()  
{  
	int i, j, k, m, n;  
	int cost;  
	scanf("%d%d",&m,&n);//m=����ĸ�����n=�ߵĸ���  

	for (i = 1; i <= m; i++)//��ʼ��ͼ 
	{  
		for (j = 1; j <= m; j++)  
		{  
			graph[i][j] = MAXCOST;  
		}  
	}   
	for (k = 1; k <= n; k++)  
	{  
		scanf("%d%d%d",&i,&j,&cost);
		graph[i][j] = cost;  
		graph[j][i] = cost;  
	}  
    prim(graph, m);  
    return 0;  
}
*/

int main()  
{   
	int i,j;
    InitGraph(graph,6);
	InsertGraph(graph,0,3,5);
	InsertGraph(graph,2,3,5);
	InsertGraph(graph,0,2,1);
	InsertGraph(graph,3,5,2);
	InsertGraph(graph,1,4,3);
	InsertGraph(graph,1,2,5);
	InsertGraph(graph,2,4,6);
	InsertGraph(graph,0,1,6);
	InsertGraph(graph,2,5,4);
	/*
	for (i=0;i<6;i++)
	{
		for (j=0;j<6;j++)
		{
			if (graph[i][j]<INFINITY)
			{
				printf("V%d-V%d %d\n",i,j,graph[i][j]);
			}
		}
	}
	*/
	
	
	prim(graph,6);
    return 0;  
}
