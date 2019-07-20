#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Dstack{
	
	ElementType * Data;
	int top1;
	int top2;
	int len;

}Ds,*PDstack;

PDstack initDstack(PDstack pd,int len){
	pd->Data = (ElementType *)malloc(len*sizeof(Ds));
	if(pd->Data == NULL){
		printf("·ÖÅäÄÚ´æÊ§°Ü\n");
		exit(-1);
	}
	pd->len = len;
	pd->top1 = -1;
	pd->top2 = len;
	pd->Data[pd->top1]=NULL;
	pd->Data[pd->top2]=NULL;
	
	return pd;
}

bool isFull(PDstack pd){
	if(pd->top2 - pd->top1 == 1){
		printf("Õ»ÒÑÂú\n");
		return true;
	}
	return false;
}

bool isEmpty(PDstack pd){
	if(pd->top1==-1 && pd->top2 == pd->len){
		printf("¿ÕÕ»\n");
		return true;
	}
	return false;
}

void Push(PDstack pd,int val,int tag){
	if(!isFull(pd)){

		tag==1?pd->Data[++(pd->top1)]=val:pd->Data[--(pd->top2)]=val;
		
		
	}
	return;
}

void Pop(PDstack pd,int tag){
	if(!isEmpty(pd)){
		tag==1?pd->Data[(pd->top1)--]=NULL:pd->Data[(pd->top2)++]=NULL;
	}
	return;
}

void main(){
	Ds ds;
	PDstack pd = initDstack(&ds,4);
	Push(pd,1,1);
	Push(pd,1,0);
	printf("%d %d\n",pd->top1,pd->top2);
	printf("%d %d\n",pd->Data[pd->top1],pd->Data[pd->top2]);
	Pop(pd,1);
	Pop(pd,0);
	printf("%d %d\n",pd->top1,pd->top2);
	printf("%d %d\n",pd->Data[pd->top1],pd->Data[pd->top2]);
}