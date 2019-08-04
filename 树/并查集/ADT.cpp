#include <stdio.h>

#define MAX 100

typedef int ElementType;		 	
typedef int SetName;			  //顶点名
typedef ElementType SetType[MAX]; 
/*
	把数组下标当成顶点名，从0开始

	数组下标 0  1  2 3 4 5  6 7 8 9 
	对应顶点 1  2  3 4 5 6  7 8 9 10 
	数组的值 -1 0 -1 0 2 -1 0 2 5 5

	数组中填写该点对应的父节点，
	而根节点填写这颗树的结点数，初始为-1，即就代表它自身；
*/
//Root1和Root2都是相应顶点在数组中的下标
void Union(SetType S,SetName Root1,SetName Root2){
	if (S[Root1] < S[Root2]) 
	{
		//Root1 比 Root2 子节点数更多，所以Root2并入Root1
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	} 
	else
	{
		//Root2 比 Root1 子节点数更多或相等，所以Root1并入Root2
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
}
//x是该顶点在数组中的下标
int Find(SetType S,ElementType x){
	//寻找x的根元素，即找到x所在的集合
	return S[x]<0 ? x : Find(S,S[x]);
}

int main(){
	int i;
	SetType S = {-1,0,-1,0,2,-1,0,2,5,5};
	/*
	for (i=0;i<10;i++)
	{
		printf("%d ",S[i]);
	}*/
	int root = Find(S,3);
	printf("root=%d ",root);
	Union(S,0,2);
	for (i=0;i<10;i++)
	{
		printf("v%d=%d ",i+1,S[i]+1);
	}
	return 0;
}