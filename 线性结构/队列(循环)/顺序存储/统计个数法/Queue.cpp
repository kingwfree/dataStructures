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
	int count;
}SqQueue,*PQueue;
bool QueueFull(SqQueue Q);
bool QueueEmpty(SqQueue Q);

void InitQueue(PQueue pQ,int len){
	pQ->data=(ElementType*)malloc(len*sizeof(ElementType));
	if(pQ->data == NULL){
		printf("内存空间分配失败\n");
		exit(-1);
	}
	pQ->front=pQ->rear=pQ->count=0;
	pQ->len=len;
}

bool EnQueue(PQueue pQ,ElementType x){
	int flag = QueueFull(*pQ);
	if(!flag){
		pQ->data[pQ->rear] = x;
		pQ->rear = (pQ->rear+1)%pQ->len;
		pQ->count++;
	}
	return flag ? false : true;
}

bool DeQueue(PQueue pQ,ElementType* x){
	int flag = QueueEmpty(*pQ);
	if(!flag){
		*x = pQ->data[pQ->front];
		pQ->front = (pQ->front+1)%pQ->len;
		pQ->count--;
	}
	return flag ? false : true;
}

bool GetHead(SqQueue Q,ElementType* x){
	int flag = QueueEmpty(Q);
	*x = flag ? NULL : Q.data[Q.front];
	return flag ? false : true;
}
void ClearQueue(PQueue pQ){
	free(pQ);
}

bool QueueFull(SqQueue Q){
	return Q.count == Q.len ? true : false;
}
bool QueueEmpty(SqQueue Q){
	return Q.count == 0 ? true : false;
}

void Print(SqQueue Q){
	int i,x;
	for (i=0;i<Q.len;i++)
	{
		bool flag = EnQueue(&Q,i);
		printf("%d flag=%d\n",Q.data[i],flag);
	}
	int g = GetHead(Q,&x);
	printf("x=%d g=%d\n",x,g);

	//ClearQueue(&Q);

	for (i=0;i<Q.len;i++)
	{
		bool mark = DeQueue(&Q,&x);
		printf("x=%d mark=%d\n",x,mark);
	}
	bool mark = DeQueue(&Q,&x);
	printf("x=%d mark=%d\n",x,mark);
	printf("front=%d rear=%d\n",Q.front,Q.rear);
}

void main(){
	SqQueue Q;
	InitQueue(&Q,4);
	Print(Q);
}