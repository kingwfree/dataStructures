//front指向头节点，rear指向尾节点，头节点的数据域为空
//初始化时，front与rear都指向头节点
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node{
	ElementType data;
	struct Node* next;
}LinkNode,*PNode;

typedef struct{
    PNode front,rear;
}LinkQueue,*PLink;

bool QueueEmpty(LinkQueue Q);
PNode createNode();

void InitQueue(PLink pQ){
	pQ->front = createNode();
	if (pQ->front == NULL)
	{
		printf("内存分配失败\n");
		exit(-1);
	}
	//将头节点的地址给rear
	pQ->rear = pQ->front;
	pQ->front->next = NULL;
}

void EnQueue(PLink pQ,ElementType x){
	PNode node = createNode();
	node->next=NULL;
	node->data=x;
	pQ->rear->next = node;
	pQ->rear = node;
}

bool DeQueue(PLink pQ,ElementType* x){
	int flag = QueueEmpty(*pQ);
	if(!flag){
		PNode tmp = pQ->front->next;
		*x = tmp->data;
		pQ->front->next = tmp->next;
		if(pQ->rear == tmp)
			pQ->rear = pQ->front;
		free(tmp);
	}
	return flag ? false : true;
}


bool GetHead(LinkQueue Q,ElementType *x){
	int flag = QueueEmpty(Q);
	*x = flag?NULL:Q.front->next->data;
	return flag ? false : true;
}

void ClearQueue(PLink pQ){
	free(pQ);
}

void Print(LinkQueue Q){
	PNode p = Q.front->next;
	while (p != NULL)
	{
		printf("%d ",p->data);
		p = p->next;
	}
}

bool QueueEmpty(LinkQueue Q){
	return Q.front == Q.rear ? true : false;
}

PNode createNode(){
	PNode node = (PNode)malloc(sizeof(LinkNode));
	return node;
}

void main(){
	LinkQueue Q;
	int i,x;
	InitQueue(&Q);
	for (i=0;i<5;i++)
	{
		EnQueue(&Q,i);
	}
	bool flag = GetHead(Q,&x);
	printf("x=%d flag=%d\n",x,flag);
	//ClearQueue(&Q);
	Print(Q);
	for (i=0;i<4;i++)
	{
		DeQueue(&Q,&x);
	}
	Print(Q);
}