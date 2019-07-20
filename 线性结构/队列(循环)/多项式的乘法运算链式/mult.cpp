#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node{

	ElementType coef;
	ElementType expon;
	struct Node *next;

}Node,*PNode;
void isMemory(PNode p);
PNode ReadNode();						//初始化，读入公式
void isMemory(PNode p);
void Append(int c,int e,PNode *rear);	//入队
PNode Add(PNode p1,PNode p2);			//加法运算
void travel(PNode p);					//遍历
int compare(PNode p1,PNode p2);			//比较
PNode mult(PNode p1,PNode p2);			//乘法运算


void isMemory(PNode p){
	if(p==NULL){
		printf("内存分配失败\n");
		exit(-1);
	}
}

void Append(int c,int e,PNode rear){
	PNode p = (PNode)malloc(sizeof(Node));
	isMemory(p);
	p->coef=c;
	p->expon=e;
	p->next=rear->next;
	rear->next = p;
	rear = p;
}

PNode ReadNode(){
	int n,e,c;
	PNode tmp;
	printf("请输入要生成的节点数：");
	scanf("%d",&n);
	PNode front = (PNode)malloc(sizeof(Node));
	isMemory(front);
	PNode rear = front;
	rear->next=NULL;
	while (n--)
	{
		printf("%d ",n);
		scanf("%d %d",&c,&e);
		Append(c,e,rear);
	}
	tmp = front;
	front=front->next;
	free(tmp);
	tmp=NULL;
	return front;
}

void travel(PNode p){

	int len=1;
	while (p != NULL)
	{
		printf("%d %d %d\n",len,p->coef,p->expon);
		p = p->next;
		len++;
	}
	return;

}

int compare(PNode p1,PNode p2){
	if(p1->expon == p2->expon){
		return 1;
	}else if (p1->expon > p2->expon)
	{
			return 0;
	}else{
		return 2;
	}
}

PNode Add(PNode p1,PNode p2){
	int sum;
	PNode p=(PNode)malloc(sizeof(Node));
	isMemory(p);
	p->next=NULL;
	PNode rear = p;
	while(p1&&p2){
		switch (compare(p1,p2))
		{
		case 0:
			Append(p1->coef,p1->expon,rear);
			p1 = p1->next;
			break;
		case 1:
			sum = p1->coef+p2->coef;
			if(sum)Append(sum,p1->expon,rear);
			p1=p1->next;
			p2=p2->next;
			break;
		case 2:
			Append(p2->coef,p2->expon,rear);
			p2 = p2->next;
			break;
		}
	}
	for(;p1;p1=p1->next)Append(p1->coef,p1->expon,rear);
	for(;p2;p2=p2->next)Append(p2->coef,p2->expon,rear);
	PNode tmp = p;
	p=p->next;
	free(tmp);
	tmp=NULL;
	return p;

}
PNode mult(PNode p1,PNode p2){
	int c,e;
	PNode p=(PNode)malloc(sizeof(Node));
	isMemory(p);
	PNode rear=p;
	p->next=NULL;
	PNode t2=p2;
	while(p1){
		for (;p2;p2=p2->next)
		{
			c = p1->coef*p2->coef;
			e = p1->expon+p2->expon;
			Append(c,e,rear);
			printf("1\n");
		}
		printf("2\n");
		p2=t2;
		p1=p1->next;
	}
	free(t2);
	t2=NULL;
	PNode tmp = p;
	p = p->next;
	free(tmp);
	tmp=NULL;
	return p;
}


void main(){
	PNode p1 = ReadNode();
	PNode p2 = ReadNode();
	//travel(p1);
	//PNode p = Add(p1,p2);
	//travel(p);
	PNode pm= mult(p1,p2);
	travel(pm);
}

