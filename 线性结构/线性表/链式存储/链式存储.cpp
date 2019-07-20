#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct ListNode{

	ElementType data;
	ListNode* next;

} Node,*PNode;

void Memory(PNode p);							//判断空间分配是否成功
PNode CreateList(void);							//    创建链表函数定义
void Empty(PNode List);							//    判断是否为空链表
int TraverseList(PNode List);					//    遍历链表
PNode Positon(PNode p,int i,int pos);			//寻找所要操作节点的前一个结点
PNode FindNum(PNode List);						//    定义链表数值查询函数
PNode FindNode(PNode List,int pos);				//    定义链表节点查询函数
void Insert(PNode List,int pos,int val);		//定义链表插入函数
void Delete(PNode List,int pos);				//    定义删除链表元素函数
void DeleteTheList(PNode List);					//定义删除整个链表函数

//判断空间分配是否成功
void Memory(PNode p){
	if(p == NULL){
		printf("空间分配失败\n");
		exit(-1);
	}
}

//    创建链表函数定义
PNode CreateList(void){
	int len;
	int val;

	PNode pHead = (PNode)malloc(sizeof(Node));
	Memory(pHead);

	PNode pTail = pHead;
	pTail->next = NULL;
	
	printf("请输入节点个数：");
	scanf("%d",&len);
	for(int i=0;i<len;i++){
		PNode pNew = (PNode)malloc(sizeof(Node));
		Memory(pNew);
		printf("请输入第 %d 个节点的数据：",i+1);
		scanf("%d",&val);

		pNew->data = val;
		pTail->next = pNew;
		pNew->next = NULL;
		pTail = pNew;
	}

	return pHead;
}

//判断链表是否为空
void Empty(PNode List){
	PNode p = List;
	
	if(p == NULL){
		printf("链表为空\n");
		exit(-1);
	}
	
	//printf("链表不为空\n");
}

//    定义链表遍历函数
int TraverseList(PNode List){
	int j=0;
	PNode p = List->next;

	Empty(p);

	printf("遍历链表的值为\n");
	while(p != NULL){
		printf("%d\n",p->data);
		p = p->next;
		++j;
	}
	printf("链表长度为%d\n",j);
	return j;
}

//    定义链表数值查询函数
PNode FindNum(PNode List){
	PNode p = List->next;
	int num = 1;    //    用于记录链表节点位置
    int val = 0;    //    用于存放要查询的值

	Empty(p);

	printf("请输入要查询的数值：");
	scanf("%d",&val);
	while(p != NULL && p->data != val){
		p = p->next;
		++num;
	}
	if(p != NULL){
		printf("该值位于第%d个节点\n",num);
		return p;
	}else{
		printf("找不到该节点\n");
		return List;
	}	
}

//    定义链表节点查询函数
PNode FindNode(PNode List,int pos){
	PNode p= List->next;
	int num =1;

	Empty(p);

// 	while(p != NULL && num < pos){
// 		p = p->next;
// 		num++;
// 	}
	p = Positon(p,num,pos);
	if(p != NULL){
		printf("该节点值为%d\n",p->data);
		return p;
	}else{
		printf("找不到该节点\n");
		return List;
	}
}
//寻找所要操作节点的前一个结点
PNode Positon(PNode p,int i,int pos){
	while(p != NULL && i < pos){
		p = p->next;
		++i;
	}
	return p;
}

//定义链表插入函数
void Insert(PNode List,int pos,int val){
	PNode p = List;
	int i=0;
	while(p != NULL && i < pos - 1){
		p = p->next;
		++i;
	}
	p = Positon(p,i,pos-1);				//    寻找pos节点的前一个结点
	PNode Tmp = (PNode)malloc(sizeof(Node));
	Memory(Tmp);

	Tmp->data = val;
	Tmp->next = p->next;
	p->next = Tmp;
	
}

//    定义删除链表元素函数
void Delete(PNode List,int pos){
	PNode p = List;
	int i=0;

	Empty(p);

	p = Positon(p,i,pos-1);
	PNode Tmp = p->next;	//    定义临时指针Tmp指向要删除的节点
	p->next = Tmp->next;	//    使要删除节点的前驱结点指向其后驱节点
	free(Tmp);
	Tmp=NULL;	//    使Tmp指向空指针，防止产生野指针
}

//定义删除整个链表函数
void DeleteTheList(PNode List){
	PNode p,tmp;
	p = List->next;
	List->next = NULL;
	while(p != NULL){
		tmp = p->next;
		free(p);
		p = tmp;
	}
	printf("删除链表成功！\n");
}

int main(){
	PNode p = CreateList();
	TraverseList(p);
 	FindNode(p,3);
 	Insert(p,2,6);
 	TraverseList(p);
	Delete(p,3);
	TraverseList(p);
	DeleteTheList(p);
	TraverseList(p);
	return 0;
}