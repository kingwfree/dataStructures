#include <stdio.h>

#define MaxSize 6

typedef int ElementType;
typedef struct{
	ElementType data[MaxSize];
	int top;
	int count;
}SqStack,*PStack;

void InitStack(PStack pS){
	pS->top = -1;
	pS->count=0;
}

bool StackEmpty(SqStack S){
	return S.top==-1 ? true:false;
}

bool Push(PStack pS,ElementType x){
	if (pS->top == MaxSize-1)return false;
	pS->data[++pS->top] = x;
	pS->count++;
	return true;
}
bool Pop(PStack pS,ElementType* x){
	if(StackEmpty(*pS))
		return false;
	*x = pS->data[pS->top--];
	pS->count--;
	return true;
}

bool GetTop(SqStack S,ElementType* x){
	if(StackEmpty(S))
		return false;
	*x = S.data[S.top];
	return true;
}

bool ClearStack(PStack pS){
	if(StackEmpty(*pS))
		return true;
	pS->top = -1;
	pS->count=0;
	return true;
}

void Print(SqStack S){
	int i;
	for (i=0;i<S.count;i++)
	{
		printf("%d ",S.data[i]);
	}
}

void main(){
	SqStack s;
	ElementType x;
	InitStack(&s);
	Push(&s,5);
	Push(&s,6);
	Push(&s,7);
	Pop(&s,&x);
	printf("%d ",x);
	Print(s);
}
