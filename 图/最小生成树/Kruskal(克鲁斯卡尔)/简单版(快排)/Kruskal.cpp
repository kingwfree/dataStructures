#include <stdio.h>
#include <malloc.h>

#define MAXE 100
#define MAXV 100
typedef int ElementType;

typedef struct{
    int vex1;                     //边的起始顶点
    int vex2;                      //边的终止顶点
    int weight;                    //边的权值
}Edge,*PEdge;

void kruskal(Edge E[],int n,int e)
{ 
    int i,j,m1,m2,sn1,sn2,k,sum=0;
	int* vset = (int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)        //初始化辅助数组
        vset[i]=i;
    k=1;//表示当前构造最小生成树的第k条边，初值为1
    j=0;//E中边的下标，初值为0
	while(k<e)//生成的边数小于e时继续循环
	{
		m1=E[j].vex1;
		m2=E[j].vex2;//取一条边的两个邻接点
		sn1=vset[m1];
		sn2=vset[m2];                           
		//分别得到两个顶点所属的集合编号
        if(sn1!=sn2)//两顶点分属于不同的集合，该边是最小生成树的一条边
        {//防止出现闭合回路 
            printf("V%d-V%d=%d\n",m1,m2,E[j].weight);
            sum+=E[j].weight;
            k++;                //生成边数增加 
            if(k>=n)
                break;
            for(i=0;i<n;i++)    //两个集合统一编号
                if (vset[i]==sn2)  //集合编号为sn2的改为sn1
                    vset[i]=sn1;
        }
		j++;                  //扫描下一条边
	}
    printf("最小权值之和=%d\n",sum);
}


//快排
void quicksort(Edge E[],int left,int right)
{
	if(left>=right)
		return;
	int i,j;
	Edge t;
	Edge temp=E[left]; //temp中存的就是基准数
	i=left;
	j=right;
	while(i!=j)
	{
		//顺序很重要，要先从右往左找
		while(E[j].weight >= temp.weight && i<j)
			j--;
		//再从左往右找
		while(E[i].weight <= temp.weight && i<j)
			i++;
		//交换两个数在数组中的位置
		if(i<j)//当哨兵i和哨兵j没有相遇时
		{
			t=E[i];
			E[i]=E[j];
			E[j]=t;
		}
	}
	//最终将基准数归位 
	
	E[left]=E[i];
	E[i]=temp;
	
	quicksort(E,left,i-1);//继续处理左边的，这里是一个递归的过程
	quicksort(E,i+1,right);//继续处理右边的，这里是一个递归的过程
}
Edge createENode(int v1,int v2,int w){
	
	PEdge pE = (PEdge)malloc(sizeof(Edge));
	pE->vex1 = v1;
	pE->vex2 = v2;
	pE->weight = w;
	return *pE;

}

void Print(Edge E[],int len){
	int i;
	for (i=0;i<len;i++)
	{
		printf("v%d-v%d=%d\n",E[i].vex1,E[i].vex2,E[i].weight);
	}
}
int main(){
	/*
	ElementType arr[6] = {5,6,8,4,9,3};
		quicksort(arr,0,5);
		Print(arr,6);*/
	
	Edge E[MAXE];
	int nume=9,numn=6;

	/*
        printf("输入顶数和边数:\n");
            scanf("%d%d",&numn,&nume);
            for(int i=0;i<nume;i++)
                scanf("%d%d%d",&E[i].vex1,&E[i].vex2,&E[i].weight);*/
        

	E[0] = createENode(0,3,5);
	E[1] = createENode(2,3,5);
	E[2] = createENode(0,2,1);
	E[3] = createENode(3,5,2);
	E[4] = createENode(1,4,3);
	E[5] = createENode(1,2,5);
	E[6] = createENode(2,4,6);
	E[7] = createENode(0,1,6);
	E[8] = createENode(2,5,4);
	quicksort(E,0,nume-1);
	//Print(E,9);
	kruskal(E,numn,nume);
	return 0;
}