//front指向队头元素，rear指向队尾元素的下一位置
//初始化时，front与rear都指向队头
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct{
	ElementType *data;
	int front;
	int rear;
	int len;
}SqQueue,*PQueue;

bool QueueFull(SqQueue Q);
bool QueueEmpty(SqQueue Q);

void InitQueue(PQueue pQ,int len){
	pQ->data = (ElementType *)malloc(len*sizeof(SqQueue));
	if(pQ->data == NULL){
		printf("内存空间分配失败\n");
		exit(-1);
	}
	pQ->front = pQ->rear = 0;
	pQ->len = len;
}

bool EnQueue(PQueue pQ,ElementType x){
	bool flag = QueueFull(*pQ);
	if(!flag){
		pQ->data[pQ->rear] = x;
		pQ->rear = (pQ->rear+1)%pQ->len;
	}
	return flag ? false : true;
}

bool DeQueue(PQueue pQ,ElementType* x){
	bool flag = QueueEmpty(*pQ);
	if(!flag){
		*x = pQ->data[pQ->front];
		pQ->front = (pQ->front+1)%pQ->len;
	}
	return flag ? false : true;
}

bool QueueEmpty(SqQueue Q){
	return Q.front == Q.rear ? true : false;
}
bool QueueFull(SqQueue Q){
	return (Q.rear+1)%Q.len == Q.front ? true : false;
}
bool GetHead(SqQueue Q,ElementType* x){
	bool flag = QueueEmpty(Q);
	*x = Q.data[Q.front];
	return flag ? false : true;
}
void ClearQueue(PQueue pQ){
	free(pQ);
}
void Print(SqQueue Q){
	int i =0,x;
	for (i=0;i<Q.len-1;i++)
	{
		bool flag = EnQueue(&Q,i);
		printf("%d flag=%d\n",Q.data[i],flag);
	}
	GetHead(Q,&x);
	printf("x=%d\n",x);
	//ClearQueue(&Q);
	//printf("%d\n",Q.data[0]);
	for (i=0;i<Q.len;i++)
	{
		bool mark = DeQueue(&Q,&x);
		printf("x=%d mark=%d\n",x,mark);
	}
	printf("front=%d rear=%d\n",Q.front,Q.rear);
}
void main(){
	SqQueue Q;
	InitQueue(&Q,4);
	Print(Q);
}