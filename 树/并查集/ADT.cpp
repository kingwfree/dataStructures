#include <stdio.h>

#define MAX 100

typedef int ElementType;		 	
typedef int SetName;			  //������
typedef ElementType SetType[MAX]; 
/*
	�������±굱�ɶ���������0��ʼ

	�����±� 0  1  2 3 4 5  6 7 8 9 
	��Ӧ���� 1  2  3 4 5 6  7 8 9 10 
	�����ֵ -1 0 -1 0 2 -1 0 2 5 5

	��������д�õ��Ӧ�ĸ��ڵ㣬
	�����ڵ���д������Ľ��������ʼΪ-1�����ʹ���������
*/
//Root1��Root2������Ӧ�����������е��±�
void Union(SetType S,SetName Root1,SetName Root2){
	if (S[Root1] < S[Root2]) 
	{
		//Root1 �� Root2 �ӽڵ������࣬����Root2����Root1
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	} 
	else
	{
		//Root2 �� Root1 �ӽڵ����������ȣ�����Root1����Root2
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
}
//x�Ǹö����������е��±�
int Find(SetType S,ElementType x){
	//Ѱ��x�ĸ�Ԫ�أ����ҵ�x���ڵļ���
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