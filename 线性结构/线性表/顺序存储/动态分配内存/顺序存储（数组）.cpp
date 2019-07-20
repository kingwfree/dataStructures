#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct LNode{

	int *pBase;         //存储的是数组第一个元素的地址	
	int len;			//线性表长度
	int cnt;			//当前数组有效元素的个数

}L,*List;

void initArr(List Arr,int len);
bool isEmpty(List Arr);
void showArr(List Arr);
bool isFull(List Arr);
bool append(List Arr,int val);
bool insertArr(List Arr,int pos,int val);
bool deleteArr(List Arr,int pos);

//创建空表
void initArr(List Arr,int len){
	
	Arr->pBase = (int *)malloc(len*sizeof(L));
	if(Arr->pBase == NULL){
		printf("内存空间分配失败\n");
		exit(-1);
	}
	Arr->len = len;
	Arr->cnt = 0;
	return;
}

bool isEmpty(List Arr){
	if(Arr->cnt == 0)
		return true;
	else
		return false;

	//Arr->len == 0?return true:return false;
	
}

void showArr(List Arr){
	if(isEmpty(Arr)){
		printf("数组为空!\n");
	}else{
		for (int i=0;i<Arr->cnt;i++)
			printf("%d ",Arr->pBase[i]);
		printf("\n");
	}
}

bool isFull(List Arr){
	if(Arr->len == Arr->cnt){
		return true;
	}else{
		return false;
	}
}

bool append(List Arr,int val){
	if(isFull(Arr)){
		printf("数组已满!\n");
		return false;
	}else{
		Arr->pBase[Arr->cnt]=val;
		(Arr->cnt)++;
		return true;
	}
}

bool insertArr(List Arr,int pos,int val){
	int i=0;

	if (isFull(Arr))
	{
		printf("数组已满!\n");
		return false;
	}else{
		if (pos<1 || pos>Arr->len)
			return false;
		for (i=Arr->cnt-1;i>pos;i--)
		{
			Arr->pBase[i+1] = Arr->pBase[i];
		}
		Arr->pBase[pos-1] = val;
		(Arr->cnt)++;
		return true;
	}
}

bool deleteArr(List Arr,int pos){
	if(isEmpty(Arr)){
		printf("数组为空!\n");
		return false;
	}
	if(pos<1 || pos>Arr->cnt)
		return false;
	for (int i=pos;i<Arr->cnt;i++)
	{
		Arr->pBase[i-1] = Arr->pBase[i];
	}
	Arr->cnt--;
	return true;
}

int main(){
	L arr;
	initArr(&arr,5);
	showArr(&arr);
 	append(&arr,1);
 	insertArr(&arr,2,2);
 	append(&arr,3);
 	showArr(&arr);
 	deleteArr(&arr,3);
 	showArr(&arr);
	return 0;
}
