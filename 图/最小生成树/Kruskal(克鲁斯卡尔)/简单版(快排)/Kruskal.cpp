#include <stdio.h>
#include <malloc.h>

#define MAXE 100
#define MAXV 100
typedef int ElementType;

typedef struct{
    int vex1;                     //�ߵ���ʼ����
    int vex2;                      //�ߵ���ֹ����
    int weight;                    //�ߵ�Ȩֵ
}Edge,*PEdge;

void kruskal(Edge E[],int n,int e)
{ 
    int i,j,m1,m2,sn1,sn2,k,sum=0;
	int* vset = (int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)        //��ʼ����������
        vset[i]=i;
    k=1;//��ʾ��ǰ������С�������ĵ�k���ߣ���ֵΪ1
    j=0;//E�бߵ��±꣬��ֵΪ0
	while(k<e)//���ɵı���С��eʱ����ѭ��
	{
		m1=E[j].vex1;
		m2=E[j].vex2;//ȡһ���ߵ������ڽӵ�
		sn1=vset[m1];
		sn2=vset[m2];                           
		//�ֱ�õ��������������ļ��ϱ��
        if(sn1!=sn2)//����������ڲ�ͬ�ļ��ϣ��ñ�����С��������һ����
        {//��ֹ���ֱպϻ�· 
            printf("V%d-V%d=%d\n",m1,m2,E[j].weight);
            sum+=E[j].weight;
            k++;                //���ɱ������� 
            if(k>=n)
                break;
            for(i=0;i<n;i++)    //��������ͳһ���
                if (vset[i]==sn2)  //���ϱ��Ϊsn2�ĸ�Ϊsn1
                    vset[i]=sn1;
        }
		j++;                  //ɨ����һ����
	}
    printf("��СȨֵ֮��=%d\n",sum);
}


//����
void quicksort(Edge E[],int left,int right)
{
	if(left>=right)
		return;
	int i,j;
	Edge t;
	Edge temp=E[left]; //temp�д�ľ��ǻ�׼��
	i=left;
	j=right;
	while(i!=j)
	{
		//˳�����Ҫ��Ҫ�ȴ���������
		while(E[j].weight >= temp.weight && i<j)
			j--;
		//�ٴ���������
		while(E[i].weight <= temp.weight && i<j)
			i++;
		//�����������������е�λ��
		if(i<j)//���ڱ�i���ڱ�jû������ʱ
		{
			t=E[i];
			E[i]=E[j];
			E[j]=t;
		}
	}
	//���ս���׼����λ 
	
	E[left]=E[i];
	E[i]=temp;
	
	quicksort(E,left,i-1);//����������ߵģ�������һ���ݹ�Ĺ���
	quicksort(E,i+1,right);//���������ұߵģ�������һ���ݹ�Ĺ���
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
        printf("���붥���ͱ���:\n");
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