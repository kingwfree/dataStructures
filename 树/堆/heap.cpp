#include <stdio.h>
#include <malloc.h>

#define MAXDATA 1000  /* 该值应根据具体情况定义为大于堆中所有可能元素的值 */
#define MINDATA -1	  /* 该值应根据具体情况定义为小于堆中所有可能元素的值 */
typedef int ElementType;

typedef struct{
	ElementType* data; //从1开始存储，0存放哨兵
	int count;
	int len;
}HNode,*PHeap;

typedef PHeap MaxHeap;
typedef PHeap MinHeap;

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

//最小堆的插入删除操作
void InsertMinHeap(MinHeap MinH,ElementType x){
	if(isFull(MinH))return;
	int i=++MinH->count;
	for (;MinH->data[i/2] > x;i /= 2)
		MinH->data[i] = MinH->data[i/2];
	MinH->data[i] = x;
}
void DeMinHeap(MinHeap MinH,ElementType* x){
	if(isEmpty(MinH))return;
	int parent,child;
	ElementType tmp = MinH->data[MinH->count--];
	*x = MinH->data[1];
	for (parent=1;parent*2 <= MinH->count;parent=child)
	{
		child = parent*2;
		if ((child != MinH->count) && (MinH->data[child] > MinH->data[child+1] ))
			child++;
		if(tmp <= MinH->data[child])break;
		else MinH->data[parent] = MinH->data[child];
	}
	MinH->data[parent] = tmp;
}

//构建最小堆
void PercUp(MinHeap MinH,int p){
	int parent,child;
	ElementType root = MinH->data[p];
	for (parent=p;parent*2 <= MinH->count;parent=child)
	{
		child = parent*2;
		if((child != MinH->count) && (MinH->data[child] > MinH->data[child+1]))
			child++;
		if(root <= MinH->data[child])break;
		else MinH->data[parent] = MinH->data[child];
	}
	MinH->data[parent] = root;
}
void BuildMinHeap(MinHeap MinH){
	int i;
	for (i=MinH->count/2;i>0;i--)
		PercUp(MinH,i);
}

//最大堆的插入删除操作
void InsertMaxHeap(MaxHeap MaxH,ElementType x){
	if (isFull(MaxH))return;
	int i;
	i = ++MaxH->count;
	//哨兵 data[0]里存放了一个最大值
	//如果不放哨兵，则条件要变为MaxH->data[i/2]<x && i>1
	for (;MaxH->data[i/2]<x;i/=2)
		MaxH->data[i] = MaxH->data[i/2];
	MaxH->data[i] = x;
}
void DeMaxHeap(MaxHeap MaxH,ElementType* x){
	if (isEmpty(MaxH))return;
	int parent,child;
	*x = MaxH->data[1];
	ElementType tmp = MaxH->data[MaxH->count--];
	//找到比最后一项小的长辈的数组下标
	//从上往下搜索，先从根开始
	for (parent=1;parent*2 <= MaxH->count;parent=child)
	{
		child = parent*2;
		//(child != MaxH->count) 确保有右节点，左节点都是数组偶数下标
		if((child != MaxH->count) && (MaxH->data[child]<MaxH->data[child+1]))
			child++;
		/*
		从上往下与最后一项进行比较
		因为根结点要被替换掉，所以可以视为根节点为空。
		若是最后一项（即tmp）比 该父亲的子节点大，则tmp成为这个子节点的父节点。
		若是最后一项（即tmp）比 该父亲的子节点小，则这个子节点填入父节点的位置。

		如果最后一项大于祖辈中的某一项就退出循环，
		此时的parent就是最后一项要插入的数组下标的位置
		*/
		if(tmp >= MaxH->data[child])break;
		else MaxH->data[parent] = MaxH->data[child];
	}
	MaxH->data[parent] = tmp;
}
//构建最大堆
void PercDown(MaxHeap MaxH,int p){
	//一个根加一个或两个子节点
	int parent,child;
	ElementType root = MaxH->data[p];
	for (parent=p;parent*2 <= MaxH->count;parent=child)
	{
		child=parent*2;
		if ((child != MaxH->count) && (MaxH->data[child] < MaxH->data[child+1]))
			child++;
		if(root >= MaxH->data[child])break;
		else MaxH->data[parent] = MaxH->data[child];
	}
	MaxH->data[parent] = root;
}
void BuildMaxHeap(MaxHeap MaxH){
	int i;
	/* 从最后一个结点的父节点开始，遍历到根结点1 */
	for (i=MaxH->count/2;i>0;i--)
		PercDown(MaxH,i);
}

int main(){

	int a[6] = {7, 3, 8, 5, 1, 2};
	int len = 12;    /* 数组长度 */
	int i,x,k;
	MaxHeap MaxH = InitHeap(len,MAXDATA);
	MinHeap MinH = InitHeap(len,MINDATA);
	for (i=1;i<=len;i++)
	{
		MaxH->data[i] = a[i-1];
		MinH->data[i] = a[i-1];
	}
	MaxH->count = 6;
	MinH->count = 6;
	BuildMaxHeap(MaxH);
	BuildMinHeap(MinH);

	InsertMaxHeap(MaxH,10);
	InsertMinHeap(MinH,10);
	printf("MaxH-in ");
	for (i=0;i<=MaxH->count;i++)
	{
		printf("%d ", MaxH->data[i]);
	}
	printf("\n");
	printf("MinH-in ");
	for (i=0;i<=MinH->count;i++)
	{
		printf("%d ", MinH->data[i]);
	}
	printf("\n");


	DeMaxHeap(MaxH,&x);
	DeMinHeap(MinH,&k);
	printf("MaxH-de ");
	printf("de-x=%d ",x);
	for (i=0;i<=MaxH->count;i++)
	{
		printf("%d ", MaxH->data[i]);
	}
	printf("\n");
	printf("MinH-de ");
	printf("de-k=%d ",k);
	for (i=0;i<=MinH->count;i++)
	{
		printf("%d ", MinH->data[i]);
	}
	printf("\n");

	return 0;
}