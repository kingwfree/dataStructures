#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Stack{
	
	ElementType *pBase;
	int len;
	int top;

}S,*PStack;

void initStack(PStack ps,int len);
bool isEmpty(PStack ps);
bool isFull(PStack ps);
void Push(PStack ps,int val);
void Pop(PStack ps);

void initStack(PStack ps,int len){

	ps->pBase = (ElementType *)malloc(len*sizeof(S));
	if (ps == NULL)
	{
		printf("ÄÚ´æ·ÖÅäÊ§°Ü\n");
		exit(-1);
	}
	ps->top = -1;
	ps->len = len;
	return;
}

bool isEmpty(PStack ps){
	if (ps->top==0)
	{
		printf("¿ÕÕ»\n");
		return true;
	}
	return false;
}

bool isFull(PStack ps){
	if(ps->top == ps->len-1){
		printf("Õ»ÒÑÂú\n");
		return true;
	}
	return false;
}

void Push(PStack ps,int val){

	if (!isFull(ps))
	{
		ps->pBase[++(ps->top)] = val; 
		printf("%d %d\n",ps->top,ps->pBase[ps->top]);
	}
	 
	return;

}

void Pop(PStack ps){
	
	if(!isEmpty(ps)){
		
		ps->pBase[(ps->top)--]= NULL;
		printf("%d %d %d\n",ps->top,ps->pBase[ps->top+1],ps->pBase[ps->top]);

	}

	return ;

}

int main(){
	
	S ps;
	initStack(&ps,6);
	isEmpty(&ps);
	Push(&ps,1);
	Push(&ps,2);
	Push(&ps,3);
	Pop(&ps);
	return 0;

}