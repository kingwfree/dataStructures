#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct ListNode{

	ElementType data;
	ListNode* next;

} Node,*PNode;

void Memory(PNode p);							//�жϿռ�����Ƿ�ɹ�
PNode CreateList(void);							//    ��������������
void Empty(PNode List);							//    �ж��Ƿ�Ϊ������
int TraverseList(PNode List);					//    ��������
PNode Positon(PNode p,int i,int pos);			//Ѱ����Ҫ�����ڵ��ǰһ�����
PNode FindNum(PNode List);						//    ����������ֵ��ѯ����
PNode FindNode(PNode List,int pos);				//    ��������ڵ��ѯ����
void Insert(PNode List,int pos,int val);		//����������뺯��
void Delete(PNode List,int pos);				//    ����ɾ������Ԫ�غ���
void DeleteTheList(PNode List);					//����ɾ������������

//�жϿռ�����Ƿ�ɹ�
void Memory(PNode p){
	if(p == NULL){
		printf("�ռ����ʧ��\n");
		exit(-1);
	}
}

//    ��������������
PNode CreateList(void){
	int len;
	int val;

	PNode pHead = (PNode)malloc(sizeof(Node));
	Memory(pHead);

	PNode pTail = pHead;
	pTail->next = NULL;
	
	printf("������ڵ������");
	scanf("%d",&len);
	for(int i=0;i<len;i++){
		PNode pNew = (PNode)malloc(sizeof(Node));
		Memory(pNew);
		printf("������� %d ���ڵ�����ݣ�",i+1);
		scanf("%d",&val);

		pNew->data = val;
		pTail->next = pNew;
		pNew->next = NULL;
		pTail = pNew;
	}

	return pHead;
}

//�ж������Ƿ�Ϊ��
void Empty(PNode List){
	PNode p = List;
	
	if(p == NULL){
		printf("����Ϊ��\n");
		exit(-1);
	}
	
	//printf("����Ϊ��\n");
}

//    ���������������
int TraverseList(PNode List){
	int j=0;
	PNode p = List->next;

	Empty(p);

	printf("���������ֵΪ\n");
	while(p != NULL){
		printf("%d\n",p->data);
		p = p->next;
		++j;
	}
	printf("������Ϊ%d\n",j);
	return j;
}

//    ����������ֵ��ѯ����
PNode FindNum(PNode List){
	PNode p = List->next;
	int num = 1;    //    ���ڼ�¼����ڵ�λ��
    int val = 0;    //    ���ڴ��Ҫ��ѯ��ֵ

	Empty(p);

	printf("������Ҫ��ѯ����ֵ��");
	scanf("%d",&val);
	while(p != NULL && p->data != val){
		p = p->next;
		++num;
	}
	if(p != NULL){
		printf("��ֵλ�ڵ�%d���ڵ�\n",num);
		return p;
	}else{
		printf("�Ҳ����ýڵ�\n");
		return List;
	}	
}

//    ��������ڵ��ѯ����
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
		printf("�ýڵ�ֵΪ%d\n",p->data);
		return p;
	}else{
		printf("�Ҳ����ýڵ�\n");
		return List;
	}
}
//Ѱ����Ҫ�����ڵ��ǰһ�����
PNode Positon(PNode p,int i,int pos){
	while(p != NULL && i < pos){
		p = p->next;
		++i;
	}
	return p;
}

//����������뺯��
void Insert(PNode List,int pos,int val){
	PNode p = List;
	int i=0;
	while(p != NULL && i < pos - 1){
		p = p->next;
		++i;
	}
	p = Positon(p,i,pos-1);				//    Ѱ��pos�ڵ��ǰһ�����
	PNode Tmp = (PNode)malloc(sizeof(Node));
	Memory(Tmp);

	Tmp->data = val;
	Tmp->next = p->next;
	p->next = Tmp;
	
}

//    ����ɾ������Ԫ�غ���
void Delete(PNode List,int pos){
	PNode p = List;
	int i=0;

	Empty(p);

	p = Positon(p,i,pos-1);
	PNode Tmp = p->next;	//    ������ʱָ��Tmpָ��Ҫɾ���Ľڵ�
	p->next = Tmp->next;	//    ʹҪɾ���ڵ��ǰ�����ָ��������ڵ�
	free(Tmp);
	Tmp=NULL;	//    ʹTmpָ���ָ�룬��ֹ����Ұָ��
}

//����ɾ������������
void DeleteTheList(PNode List){
	PNode p,tmp;
	p = List->next;
	List->next = NULL;
	while(p != NULL){
		tmp = p->next;
		free(p);
		p = tmp;
	}
	printf("ɾ������ɹ���\n");
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