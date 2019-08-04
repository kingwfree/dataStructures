#include <stdio.h>
#include <malloc.h>

#define MAXDATA 1000  /* ��ֵӦ���ݾ����������Ϊ���ڶ������п���Ԫ�ص�ֵ */
#define MINDATA -1	  /* ��ֵӦ���ݾ����������ΪС�ڶ������п���Ԫ�ص�ֵ */
typedef int ElementType;

typedef struct{
	ElementType* data; //��1��ʼ�洢��0����ڱ�
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
	H->data[0] = guard;  /*����"�ڱ�"Ϊ���ڶ������п���Ԫ�ص�ֵ*/
	return H;
}

//��С�ѵĲ���ɾ������
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

//������С��
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

//���ѵĲ���ɾ������
void InsertMaxHeap(MaxHeap MaxH,ElementType x){
	if (isFull(MaxH))return;
	int i;
	i = ++MaxH->count;
	//�ڱ� data[0]������һ�����ֵ
	//��������ڱ���������Ҫ��ΪMaxH->data[i/2]<x && i>1
	for (;MaxH->data[i/2]<x;i/=2)
		MaxH->data[i] = MaxH->data[i/2];
	MaxH->data[i] = x;
}
void DeMaxHeap(MaxHeap MaxH,ElementType* x){
	if (isEmpty(MaxH))return;
	int parent,child;
	*x = MaxH->data[1];
	ElementType tmp = MaxH->data[MaxH->count--];
	//�ҵ������һ��С�ĳ����������±�
	//���������������ȴӸ���ʼ
	for (parent=1;parent*2 <= MaxH->count;parent=child)
	{
		child = parent*2;
		//(child != MaxH->count) ȷ�����ҽڵ㣬��ڵ㶼������ż���±�
		if((child != MaxH->count) && (MaxH->data[child]<MaxH->data[child+1]))
			child++;
		/*
		�������������һ����бȽ�
		��Ϊ�����Ҫ���滻�������Կ�����Ϊ���ڵ�Ϊ�ա�
		�������һ���tmp���� �ø��׵��ӽڵ����tmp��Ϊ����ӽڵ�ĸ��ڵ㡣
		�������һ���tmp���� �ø��׵��ӽڵ�С��������ӽڵ����븸�ڵ��λ�á�

		������һ������汲�е�ĳһ����˳�ѭ����
		��ʱ��parent�������һ��Ҫ����������±��λ��
		*/
		if(tmp >= MaxH->data[child])break;
		else MaxH->data[parent] = MaxH->data[child];
	}
	MaxH->data[parent] = tmp;
}
//��������
void PercDown(MaxHeap MaxH,int p){
	//һ������һ���������ӽڵ�
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
	/* �����һ�����ĸ��ڵ㿪ʼ�������������1 */
	for (i=MaxH->count/2;i>0;i--)
		PercDown(MaxH,i);
}

int main(){

	int a[6] = {7, 3, 8, 5, 1, 2};
	int len = 12;    /* ���鳤�� */
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