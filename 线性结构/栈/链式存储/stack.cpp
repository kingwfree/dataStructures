#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct StackList{
	
	ElementType data;
	struct StackList* next;

}SL,*PSlist;

PSlist initStackList(){

	PSlist pHead = (PSlist)malloc(sizeof(SL));
	if(pHead == NULL){
		printf("ÄÚ´æ·ÖÅäÊ§°Ü\n");
		exit(-1);
	}
	pHead->next=NULL;

	return pHead;

}

void Push(PSlist ps,int val){

	PSlist pNew = (PSlist)malloc(sizeof(SL));

	pNew->data = val;
	pNew->next = ps->next;
	ps->next = pNew;
	printf("push %d\n",ps->next->data);

}

bool isEmpty(PSlist ps){
	if(ps->next==NULL){
		printf("¿ÕÕ»\n");
		return true;
	}
	return false;
}

void Pop(PSlist ps){
	if(!isEmpty(ps)){
		PSlist Tmp = ps->next;
		ps->next = Tmp->next;
		printf("pop %d\n",Tmp->data);
		free(Tmp);
		Tmp = NULL;
		
	}
	return;
}

void main(){
	PSlist ps=initStackList();
	Push(ps,1);
	Push(ps,2);
	Push(ps,3);
	Pop(ps);
}

