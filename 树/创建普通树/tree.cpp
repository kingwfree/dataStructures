#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node{
	ElementType data;
	struct Node *FirstChild;
	struct Node *NextBrother;
}Node,*PNode;

PNode createTree(int val,PNode FirstChild){
	PNode Proot = (PNode)malloc(sizeof(Node));
	if(Proot == NULL){
		printf("ÄÚ´æ·ÖÅäÊ§°Ü\n");
		exit(-1);
	}
	Proot->data=val;
	Proot->FirstChild=FirstChild;
	Proot->NextBrother=NULL;
	return Proot;
}

PNode append(int val,PNode Proot){
	
}


void main(){

}