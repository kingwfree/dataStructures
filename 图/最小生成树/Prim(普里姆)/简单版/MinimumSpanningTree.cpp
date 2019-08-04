//简单版
#include<stdio.h>  
  
#define MAX 100  
#define INFINITY 65535

int graph[MAX][MAX];  

int prim(int graph[][MAX], int vexnum)  
{  
	int lowcost[MAX],start[MAX];
	int i,j,min,minid,sum=0,count=0;
	//初始化lowcost和start
	/*
		start 存储数组下标所代表节点的起始节点的数组下标
		数组下标 0 1 2 3 4 5
		节点名称 1 2 3 4 5 6
	*/
	//lowcost此时存储了与1邻接的各个点之间的边的权重
	//start此时存储的起始点都为0
    for (i=1;i<vexnum;i++)
	{
		lowcost[i] = graph[0][i];
		start[i]=0;
	}
	//0是根，没有父亲
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
			以刚找出的最短路径的终点为起始点，
			找出与它邻接的点所构成的边的权值，
			若这些权值比原有的（即lowcost里存储的）最短路径的值还要小，（即graph[minid][j] < lowcost[j]）
			则替换原有的最短路径里的值，（即lowcost[j] = graph[minid][j];）
			并更新该终点的起始点。（即start[j] = minid;）
			*/
			if (graph[minid][j] < lowcost[j])
			{
				
				lowcost[j] = graph[minid][j];
				start[j] = minid;
			}
		}
	}
	/* MST中收的顶点不到|V|个 */
	sum = count < vexnum ? -1 : sum;
	printf("最小权值之和=%d\n",sum);
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
	scanf("%d%d",&m,&n);//m=顶点的个数，n=边的个数  

	for (i = 1; i <= m; i++)//初始化图 
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
